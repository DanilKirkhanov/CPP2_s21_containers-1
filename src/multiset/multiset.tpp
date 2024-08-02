#include "multiset.h"

namespace s21 {
template <typename K>
multiset<K>::multiset() {
  this->end_.left = this->root;
  this->end_.right = this->root;
};

template <typename K>
multiset<K>::multiset(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K>
multiset<K>::multiset(const multiset &m) {
  this->copy(m);
}

template <typename K>
multiset<K>::multiset(multiset &&other) {
  this->root = other.root;
  this->end_ = other.end_;
  other.root = &other.end_;
  other.end_.right = other.root;
  other.end_.left = other.root;
  other.end_.parent = other.root;
  other.end_.key = 0;
  this->root->parent = &this->end_;
  this->size_ = other.size_;
  other.size_ = 0;
}

template <typename K>
multiset<K>::~multiset() {
  this->clear();
}

template <typename K>
typename multiset<K>::iterator multiset<K>::insert(const K &key) {
  std::pair<typename tree<K, K>::Node *, bool> nb = this->insert_(key, key);
  if (!nb.second) this->size_++;
  iterator res;
  res.end = &(this->end_);
  res.current = nb.first;
  res.next = res.Forw(res.current);
  res.current_duplicate = res.current->duplicates;
  res.cur_value = std::make_pair(res.current->key, res.current->value);
  return res;
}

template <typename K>
template <typename... Args>
std::vector<typename multiset<K>::iterator> multiset<K>::insert_many(
    Args &&...args) {
  std::vector<iterator> res;
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

template <typename K>
void multiset<K>::erase(iterator pos) {
  if (pos.current == pos.end) throw std::out_of_range("Out of range");
  typename tree<K, K>::Node *node =
      this->find_node(pos.cur_value.first);  // итератор *
  if (node && node->duplicates > 0) {
    node->duplicates--;
    this->size_--;
  } else {
    this->erase_(pos.cur_value.first);
    pos.current = pos.Back(pos.next);
  }
}
template <typename K>
void multiset<K>::swap(multiset &other) {
  std::swap(this->root, other.root);
  std::swap(this->end_, other.end_);
  std::swap(this->size_, other.size_);
  this->root->parent = &(this->end_);
  other.root->parent = &(other.end_);
}
template <typename K>
void multiset<K>::merge(multiset &other) {
  for (auto i = other.begin(); i != other.end(); ++i) insert(*i);
  other.clear();
}
template <typename K>
typename multiset<K>::iterator multiset<K>::begin() {
  iterator a;
  a.end = &(this->end_);
  a.current = this->end_.right;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}
template <typename K>
typename multiset<K>::iterator multiset<K>::end() {
  iterator a;
  a.end = &(this->end_);
  a.current = &(this->end_);
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}
template <typename K>
size_t multiset<K>::count(const K &key) {
  typename tree<K, K>::Node *node = this->find_node(key);
  if (!node || node == &this->end_) return 0;
  return node->duplicates + 1;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::find(const K &key) {
  iterator a;
  a.end = &this->end_;
  a.current = this->find_node(key);
  if (a.current == nullptr) a.current = &this->end_;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  a.current_duplicate = 0;
  return a;
}
template <typename K>
std::pair<typename multiset<K>::iterator, typename multiset<K>::iterator>
multiset<K>::equal_range(const K &key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename K>
typename multiset<K>::iterator multiset<K>::lower_bound(const K &key) {
  for (auto i = begin(); i != end(); ++i)
    if (*i >= key) return i;
  return end();
}

template <typename K>
typename multiset<K>::iterator multiset<K>::upper_bound(const K &key) {
  for (auto i = begin(); i != end(); ++i)
    if (*i > key) return i;
  return end();
}

template <typename K>
typename multiset<K>::iterator &multiset<K>::iterator::operator++() {
  if (current_duplicate < this->current->duplicates)
    current_duplicate++;
  else {
    this->current = this->next;
    this->next = this->Forw(this->next);
    this->cur_value = std::make_pair(this->current->key, this->current->value);
    current_duplicate = 0;
  }
  return *this;
}
template <typename K>
typename multiset<K>::iterator &multiset<K>::iterator::operator--() {
  if (current_duplicate > 0)
    current_duplicate--;
  else {
    this->next = this->current;
    this->current = this->Back(this->current);
    this->cur_value = std::make_pair(this->current->key, this->current->value);
    current_duplicate = this->current->duplicates;
  }
  return *this;
}

template <typename K>
bool multiset<K>::iterator::operator==(const iterator &it) {
  return (this->current == it.current &&
          this->current_duplicate == it.current_duplicate);
}

template <typename K>
bool multiset<K>::iterator::operator!=(const iterator &it) {
  return !(this->current == it.current &&
           this->current_duplicate == it.current_duplicate);
}

template <typename K>
K &multiset<K>::iterator::operator*() {
  return this->cur_value.first;
}

}  // namespace s21
