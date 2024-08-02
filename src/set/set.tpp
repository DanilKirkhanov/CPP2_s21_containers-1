#include "set.h"
namespace s21 {
template <typename K>
set<K>::set() {
  this->end_.left = this->root;
  this->end_.right = this->root;
};

template <typename K>
set<K>::set(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K>
set<K>::set(const set &m) {
  this->copy(m);
}

template <typename K>
set<K>::set(set &&other) {
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
set<K>::~set() {
  this->clear();
}
template <typename K>
std::pair<typename set<K>::iterator, bool> set<K>::insert(const K &key) {
  std::pair<typename tree<K, K>::Node *, bool> nb = this->insert_(key, key);
  std::pair<iterator, bool> res;
  res.first.end = &(this->end_);
  res.first.current = nb.first;
  res.first.next = res.first.Forw(res.first.current);
  res.first.cur_value =
      std::make_pair(res.first.current->key, res.first.current->value);
  res.second = nb.second;
  return res;
}

template <typename K>
template <typename... Args>
std::vector<std::pair<typename set<K>::iterator, bool>> set<K>::insert_many(
    Args &&...args) {
  std::vector<std::pair<iterator, bool>> res;
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

template <typename K>
typename set<K>::iterator set<K>::find(const K &key) {
  iterator a;
  a.end = &this->end_;
  a.current = this->find_node(key);
  if (a.current == nullptr) a.current = &this->end_;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K>
K &set<K>::iterator::operator*() {
  return this->cur_value.first;
}
template <typename K>
typename set<K>::iterator set<K>::begin() {
  iterator a;
  a.end = &(this->end_);
  a.current = this->end_.right;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K>
typename set<K>::iterator set<K>::end() {
  iterator a;
  a.end = &(this->end_);
  a.current = &(this->end_);
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}
}  // namespace s21
