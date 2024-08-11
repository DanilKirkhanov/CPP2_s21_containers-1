#ifndef MAP_H
#define MAP_H
#include "../tree/tree.h"
namespace s21 {
template <typename K, typename V>
class map : public tree<K, V> {
 public:
  class map_iter;
  class map_const_iter;
  using key_type = K;
  using mappet_type = V;
  using value_type = std::pair<K, V>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = map_iter;
  using const_iterator = map_const_iter;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();

  V &at(const K &key);
  V &operator[](const K &key);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const K &key, const V &obj);
  std::pair<iterator, bool> insert_or_assign(const K &key, const V &obj);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  iterator begin();
  iterator end();

  class map_iter : public tree<K, V>::iter {
    friend class map<K, V>;

   public:
    map_iter() : tree<K, V>::iter(){};
    std::pair<K, V> &operator*();
  };
  class map_const_iter : public map_iter {
   public:
    map_const_iter() : map_iter(){};
    const std::pair<K, V> operator*() const { return map_iter::operator*(); };
  };
};

}  // namespace s21
#include "map.tpp"
#endif  // MAP_H