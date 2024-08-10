#ifndef CPP2_CONTAIN_S21_ARRAY_TPP
#define CPP2_CONTAIN_S21_ARRAY_TPP

namespace s21 {

// Конструктор по умолчанию
template <typename T, std::size_t N>
array<T, N>::array() : size_(N) {}

// Конструктор с инициализатором
template <typename T, std::size_t N>
array<T, N>::array(const std::initializer_list<value_type> &items) {
  std::copy(items.begin(), items.end(), data_);
}

// Оператор присваивания
template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(const array<T, N> &other) {
  std::copy(other.data_, other.data_ + N, data_);

  return *this;
}

// Конструктор копирования
template <typename T, std::size_t N>
array<T, N>::array(const array<T, N> &other) {
  std::copy(other.data_, other.data_ + N, data_);
}

// Конструктор перемещения
template <typename T, std::size_t N>
array<T, N>::array(array<T, N> &&other) noexcept {
  std::move(other.data_, other.data_ + N, data_);
}

// Оператор присваивания с перемещением
template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(array<T, N> &&other) noexcept {
  for (size_t i = 0; i < N; ++i) {
    data_[i] = std::move(other.data_[i]);
  }

  return *this;
}

// Доступ к элементу по индексу с проверкой
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  return (*this)[pos];
}

// Константный доступ к элементу по индексу с проверкой
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  return (*this)[pos];
}

// Оператор доступа по индексу с проверкой
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range(
        "OutOfRangeError: Индекс ошибки выходит за пределы диапазона массива");
  }

  return data_[pos];
}

// Константный оператор доступа по индексу с проверкой
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range(
        "OutOfRangeError: Индекс ошибки выходит за пределы диапазона массива");
  }

  return data_[pos];
}

// Доступ к первому элементу массива
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return data_[0];
}

// Доступ к последнему элементу массива
template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return data_[N - 1];
}

// Константный доступ к первому элементу массива
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

// Константный доступ к последнему элементу массива
template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

// Итератор для прямого доступа к базовому массиву
template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

// Константный итератор для прямого доступа к базовому массиву
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const {
  return data_;
}

// Итератор на начало массива
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

// Итератор на конец массива
template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data_ + size_;
}

// Константный итератор на начало массива
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return data_;
}

// Константный итератор на конец массива
template <typename T, std::size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return data_ + size_;
}

// Проверка на пустоту массива
template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return !size_;
}

// Получение размера массива
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

// Получение максимального размера массива
template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

// Обмен содержимого массивов
template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N> &other) {
  std::swap_ranges(data_, data_ + N, other.data_);
}


// Заполнение массива одним значением
template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(data_, data_ + N, value);
}

}  // namespace s21

#endif // CPP2_CONTAIN_S21_ARRAY_TPP
