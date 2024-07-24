#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  list();
  list(size_type n);
  list(const list& l);
  list(list&& l);
  list(std::initializer_list<value_type> const& items);
  ~list();
  list& operator=(list&& l);

  const_reference front();
  const_reference back();

 private:
  struct Node {
    value_type data;
    Node* prev;
    Node* next;
    Node(const value_type& value) : data(value), prev(nullptr), next(nullptr) {}
  };
  Node* root;
  Node* tail;
  Node* end_;
  size_type size_;

 public:
  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { current = nullptr; }
    ListIterator(Node* ptr) : current(ptr) {};
    friend class list;
    Node* current = nullptr;

    reference operator*() {
      if (!this->current) {
        throw std::invalid_argument("val is null");
      }
      return this->current->data;
    }

    ListIterator operator++(int) {
      current = current->next;
      return *this;
    }

    ListIterator operator--(int) {
      current = current->prev;
      return *this;
    }

    ListIterator& operator++() {
      current = current->next;
      return *this;
    }

    ListIterator& operator--() {
      current = current->prev;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* temp = current;
      for (size_type i = 0; i < value; i++) {
        temp = temp->next;
      }
      ListIterator res(temp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* temp = current;
      for (size_type i = 0; i < value; i++) {
        temp = temp->prev;
      }
      ListIterator res(temp);
      return res;
    }

    bool operator==(ListIterator other) {
      return this->current == other.current;
    }

    bool operator!=(ListIterator other) {
      return this->current != other.current;
    }
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list<T>& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
  void print() const;

 private:
  void re_end();
};
}  // namespace s21
#include "s21_list.tpp"
#endif