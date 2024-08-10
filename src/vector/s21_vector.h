
#ifndef CPP2_CONTAIN_S21_vector_H
#define CPP2_CONTAIN_S21_vector_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;

namespace s21 {
template <typename T>
class vector {
 private:
  size_t size_;
  size_t capacity_;
  T *arr_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  vector &operator=(vector &&v) noexcept;

  void reserve(size_type size);
  vector() : size_(0U), capacity_(0U), arr_(nullptr) {}

  explicit vector(size_type n)
      : size_(n), capacity_(n), arr_(n ? new T[n] : nullptr) {}

  vector(std::initializer_list<value_type> const &items);

  vector(const vector &v)
      : size_(v.size_),
        capacity_(v.capacity_),
        arr_(new value_type[v.capacity_]) {
    std::copy(v.arr_, v.arr_ + v.size_, arr_);
  }

  vector(vector &&v) : size_(v.size_), capacity_(v.capacity_), arr_(v.arr_) {
    v.arr_ = nullptr;
    v.size_ = 0;
  }
  ~vector() {
    delete[] arr_;
    arr_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
  size_type size();
  value_type at(size_type i);
  void push_back(value_type v);
  void pop_back();
  bool empty();
  void clear();

  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator begin();
  iterator end();
  T *data() noexcept;
  size_type max_size();
  size_type capacity();
  void shrink_to_fit();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void swap(vector &other);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_CONTAIN_S21_vector_H