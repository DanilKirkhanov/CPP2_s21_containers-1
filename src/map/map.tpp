#include "map.h"
namespace s21 {

template <typename K, typename V>
map<K, V>::map() {
  this->end_.left = this->root;
  this->end_.right = this->root;
};

template <typename K, typename V>
map<K, V>::map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K, typename V>
map<K, V>::map(const map &m) {
  this->copy(m);
}

template <typename K, typename V>
map<K, V>::map(map &&other) {
  this->root = other.root;
  this->end_ = other.end_;
  other.root = &other.end_;
  other.end_.right = nullptr;
  other.end_.left = nullptr;
  other.end_.parent = nullptr;
  other.end_.key = 0;
  this->size_ = other.size_;
  other.size_ = 0;
}

template <typename K, typename V>
map<K, V>::~map() {
  this->clear();
}

template <typename K, typename V>
V &map<K, V>::at(const K &key) {
  typename tree<K, V>::Node *node = this->find_node(key);
  if (!node) throw std::out_of_range("Out of range");
  return node->value;
}
template <typename K, typename V>
V &map<K, V>::operator[](const K &key) {
  typename tree<K, V>::Node *node = this->find_node(key);
  if (!node || node == &this->end_) {
    std::pair<iterator, bool> ib = insert(key, mappet_type());
    node = ib.first.current;
  }
  return node->value;
}

template <typename K, typename V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert(const K &key,
                                                                const V &obj) {
  std::pair<typename tree<K, V>::Node *, bool> nb = this->insert_(key, obj);
  std::pair<iterator, bool> res;
  res.first.end = &(this->end_);
  res.first.current = nb.first;
  res.first.next = res.first.Forw(res.first.current);
  res.first.cur_value =
      std::make_pair(res.first.current->key, res.first.current->value);
  res.second = nb.second;
  return res;
}
template <typename K, typename V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert(
    const value_type &value) {
  return insert(value.first, value.second);
}

template <typename K, typename V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert_or_assign(
    const K &key, const V &obj) {
  typename tree<K, V>::Node *node = this->find_node(key);
  std::pair<iterator, bool> res;
  if (node && node != &this->end_) {
    node->value = obj;
    res.first.end = &(this->end_);
    res.first.current = node;
    res.first.next = res.first.Forw(res.first.current);
    res.first.cur_value =
        std::make_pair(res.first.current->key, res.first.current->value);
    res.second = 0;
  } else
    res = insert(key, obj);

  return res;
}
template <typename K, typename V>
template <typename... Args>
std::vector<std::pair<typename map<K, V>::iterator, bool>>
map<K, V>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::begin() {
  iterator a;
  a.end = &(this->end_);
  a.current = this->end_.right;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K, typename V>
typename map<K, V>::iterator map<K, V>::end() {
  iterator a;
  a.end = &(this->end_);
  a.current = &(this->end_);
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K, typename V>
std::pair<K, V> &map<K, V>::iterator::operator*() {
  return this->cur_value;
}

}  // namespace s21
