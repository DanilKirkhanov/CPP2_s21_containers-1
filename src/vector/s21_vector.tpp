
#ifndef CPP2_CONTAIN_S21_vector_TPP
#define CPP2_CONTAIN_S21_vector_TPP

namespace s21 {

template <typename T>
void vector<T>::reserve(size_t size) {
  if (size > capacity_) {
    T *buff = new value_type[size];
    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size;
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  arr_ = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); ++it) {
    arr_[i] = *it;
    ++i;
  }
  size_ = items.size();
  capacity_ = items.size();
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <typename T>
T vector<T>::at(size_type i) {
  if (i >= size_) throw std::out_of_range("out of range");
  return arr_[i];
}

template <typename T>
void vector<T>::push_back(T v) {
  if (size_ == capacity_) {
    if (capacity_ == 0) {
      reserve(1);
    } else
      reserve(size_ * 2);
  }
  arr_[size_++] = v;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    size_ = size_ - 1;
  }
}

template <typename T>
bool vector<T>::empty() {
  bool flag = false;
  if (size_ == 0) {
    flag = true;
  }
  return flag;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) noexcept {
  if (this != &v) {
    delete[] arr_;
    arr_ = v.arr_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.arr_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_) throw std::out_of_range("out of range");
  return *(arr_ + pos);
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ <= 0) throw std::out_of_range("out of range");
  return arr_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ <= 0) throw std::out_of_range("out of range");

  return arr_[size_ - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return arr_ + size_;
}

template <typename T>
typename vector<T>::iterator vector<T>::data() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return (std::numeric_limits<size_t>::max() / sizeof(value_type)) / 2;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T *buff = new value_type[size_];

    for (size_t i = 0; i < size_; ++i) buff[i] = std::move(arr_[i]);
    delete[] arr_;
    arr_ = buff;
    capacity_ = size_;
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - arr_;
  if (size_ == capacity_) {
    reserve(size_ * 2);
  }

  pos = arr_ + index;

  for (iterator it = arr_ + size_; it > pos; --it) {
    *it = std::move(*(it - 1));
  }

  *pos = value;
  ++size_;

  return pos;
}

template <typename T>
void vector<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos < arr_ || pos >= arr_ + size_) {
    return;
  }
  for (iterator it = pos; it < arr_ + size_ - 1; ++it) {
    *it = std::move(*(it + 1));
  }
  --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(arr_, other.arr_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  size_type index = pos - arr_;
  size_type count = sizeof...(args);

  if (size_ + count > capacity_) {
    reserve((size_ + count) * 2);
  }

  pos = arr_ + index;
  for (iterator it = arr_ + size_ + count - 1; it >= pos + count; --it) {
    *it = std::move(*(it - count));
  }

  T values[] = {std::forward<Args>(args)...};
  for (size_type i = 0; i < count; ++i) {
    arr_[index + i] = std::move(values[i]);
  }

  size_ += count;

  return arr_ + index;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  if (size_ + sizeof...(args) > capacity_) {
    reserve((size_ + sizeof...(args)) * 2);
  }

  T values[] = {std::forward<Args>(args)...};
  for (size_type i = 0; i < sizeof...(args); ++i) {
    arr_[size_++] = std::move(values[i]);
  }
}

}  // namespace s21

#endif  // CPP2_CONTAIN_S21_vector_TPP