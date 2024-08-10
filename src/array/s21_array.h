#ifndef CPP2_CONTAIN_S21_ARRAY_H_
#define CPP2_CONTAIN_S21_ARRAY_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  // Определение типов
  using value_type = T;  // определяет тип элемента
  using reference = T &;  // определяет тип ссылки на элемент
  using const_reference = const T &;  // определяет тип константной ссылки
  using iterator = T *;  // определяет тип для итерации по контейнеру
  using const_iterator =
      const T *;  // определяет константный тип для итерации по контейнеру
  using size_type =
      size_t;  // определяет тип размера контейнера (стандартный тип - size_t)

  array();  // Конструктор по умолчанию
  array(std::initializer_list<value_type> const
            &items);  // Конструктор с инициализатором
  array &operator=(const array &other);  // Оператор присваивания
  array(const array &other);  // Конструктор копирования
  array(array &&other) noexcept;  // Конструктор перемещения
  ~array() = default;             // Деструктор
  array &operator=(
      array &&other) noexcept;  // Оператор присваивания с перемещением

  reference at(size_type pos);  // доступ к элементу по индексу с проверкой
  const_reference at(size_type pos)
      const;  // константный доступ к элементу по индексу с проверкой
  reference operator[](
      size_type pos);  // оператор доступа по индексу с проверкой
  const_reference operator[](size_type pos)
      const;  // константный оператор доступа по индексу с проверкой
  reference front();  // доступ к первому элементу массива
  reference back();  // доступ к последнему элементу массива
  const_reference front() const;  // доступ к первому элементу массива (const)
  const_reference back() const;  // доступ к последнему элементу массива (const)
  iterator data();  // прямой доступ к базовому массиву
  const_iterator data() const;  // прямой константный доступ к базовому массиву

  iterator begin();                   // начало массива
  iterator end();                     // конец массива
  const_iterator cbegin(void) const;  // начало массива (const)
  const_iterator cend(void) const;    // конец массива (const)

  bool empty();          // пуст ли массив
  size_type size();      // размер массива
  size_type max_size();  // максимальный размер

  void swap(array &other);           // обмен массивов
  void fill(const_reference value);  // заполнение массива

 private:
  // Хранилище элементов и размер
  value_type data_[N] = {};
  size_type size_ = N;
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_CONTAIN_S21_ARRAY_H_
