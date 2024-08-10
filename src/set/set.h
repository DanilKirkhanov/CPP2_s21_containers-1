#ifndef SET_H
#define SET_H
#include "../tree/tree.h"
namespace s21 {
template <typename K>
class set : public tree<K, K> {
 public:
  class set_iter;
  class set_const_iter;
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = set_iter;
  using const_iterator = set_const_iter;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();

  iterator begin();
  iterator end();

  std::pair<iterator, bool> insert(const value_type &value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  iterator find(const K &key);

  class set_iter : public tree<K, K>::iter {
    friend class set<K>;

   public:
    set_iter() : tree<K, K>::iter(){};
    K &operator*();
  };
  class set_const_iter : public set_iter {
   public:
    set_const_iter() : set_iter(){};
    const K operator*() const { return set_iter::operator*(); };
  };
};

}  // namespace s21

#include "set.tpp"
#endif