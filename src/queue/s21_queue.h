#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 public:
  queue() : cont() {}
  queue(std::initializer_list<value_type> const &items) : cont(items) {}
  queue(const queue &q) : cont(q.cont) {}
  queue(queue &&q) : cont(std::move(q.cont)) {}
  ~queue() {}

  queue &operator=(queue &&q) {
    if (this != &q) {
      cont = std::move(q.cont);
    }
    return *this;
  }

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { cont.push_back(value); }
  void pop() { cont.pop_front(); }

  void swap(queue &other) { cont.swap(other.cont); }
   template <typename... Args>
  void insert_many_back(Args&&... args) {
    cont.insert_many_back(std::forward<Args>(args)...);
  }

 private:
  Container cont;
};

}  // namespace s21

#endif  // S21_QUEUE_H
