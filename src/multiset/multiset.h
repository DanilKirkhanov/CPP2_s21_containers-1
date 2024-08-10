#ifndef MULTISET_H
#define MULTISET_H
#include "../tree/tree.h"

namespace s21 {
template <typename K>
class multiset : protected tree<K, K> {
 public:
  class multiset_iter;
  class multiset_const_iter;
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = multiset_iter;
  using const_iterator = multiset_const_iter;
  using size_type = size_t;

  multiset();
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &s);
  multiset(multiset &&s);
  ~multiset();

  using tree<K, K>::contains;
  using tree<K, K>::clear;
  using tree<K, K>::empty;
  using tree<K, K>::size;
  using tree<K, K>::max_size;
  using tree<K, K>::operator=;

  iterator insert(const K &key);
  template <typename... Args>
  std::vector<iterator> insert_many(Args &&...args);

  void erase(iterator pos);
  void swap(multiset &other);
  void merge(multiset &other);

  iterator begin();
  iterator end();

  size_type count(const K &key);
  iterator find(const K &key);
  std::pair<iterator, iterator> equal_range(const K &key);
  iterator lower_bound(const K &key);
  iterator upper_bound(const K &key);

  class multiset_iter : protected tree<K, K>::iter {
    friend class multiset<K>;

   public:
    multiset_iter() : tree<K, K>::iter(), current_duplicate(0){};
    iterator &operator++();
    iterator &operator--();
    bool operator==(const iterator &it);
    bool operator!=(const iterator &it);
    K &operator*();

   private:
    unsigned int current_duplicate;
  };
  class multiset_const_iter : public multiset_iter {
   public:
    multiset_const_iter() : multiset_iter(){};
    const K operator*() const { return multiset_iter::operator*(); };
  };
};

}  // namespace s21

#include "multiset.tpp"
#endif