namespace s21 {
#include "s21_list.h"

template <typename T>
typename list<T>::const_reference list<T>::front() {
  return !root ? tail->data : root->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return !tail ? end_->data : tail->data;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& value) {
  Node* temp = pos.current;
  Node* add = new Node(value);

  if (empty()) {
    add->next = end_;
    add->prev = end_;
    root = add;
    tail = add;
    end_->next = add;
    end_->prev = add;
  } else {
    if (temp == root) {
      add->next = root;
      add->prev = end_;
      root->prev = add;
      end_->next = add;
      root = add;
    } else if (temp == end_) {
      add->next = end_;
      add->prev = tail;
      tail->next = add;
      end_->prev = add;
      tail = add;
    } else {
      add->next = temp;
      add->prev = temp->prev;
      temp->prev->next = add;
      temp->prev = add;
    }
  }
  ++size_;
  return iterator(add);
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  iterator it = iterator(pos.current);
  (void(std::initializer_list<int>{
      (it = insert(it, std::forward<Args>(args)), ++it, 0)...}));
  return it;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  (void(
      std::initializer_list<int>{(push_back(std::forward<Args>(args)), 0)...}));
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  (void(std::initializer_list<int>{
      (push_front(std::forward<Args>(args)), 0)...}));
}

template <typename T>
bool list<T>::empty() {
  return size_ == 0;
}

template <typename T>
void list<T>::re_end() {
  if (end_) {
    end_->next = root;
    end_->prev = tail;
    end_->data = size_;
    if (root) {
      root->prev = end_;
    }
    if (tail) {
      tail->next = end_;
    }
  }
}

template <typename T>
list<T>::list() : root(nullptr), tail(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  re_end();
}

template <typename T>
list<T>::list(size_type n)
    : root(nullptr), tail(nullptr), end_(nullptr), size_(0) {
  if (static_cast<int>(n) < 0) {
    throw std::out_of_range("Limit of the container is exceeded");
  }
  end_ = new Node(size_);
  for (size_type i = 0; i < n; i++) {
    push_back(T());
  }
  re_end();
}

template <typename T>
list<T>::list(std::initializer_list<T> const& items)
    : root(nullptr), tail(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  for (const auto& item : items) {
    push_back(item);
  }
  re_end();
}

template <typename T>
list<T>::list(const list& l)
    : root(nullptr), tail(nullptr), end_(nullptr), size_(0) {
  end_ = new Node(size_);
  Node* current = l.root;
  while (current != nullptr && current != l.end_) {
    push_back(current->data);
    current = current->next;
  }
  re_end();
}

template <typename T>
list<T>::list(list&& l)
    : root(l.root), tail(l.tail), end_(l.end_), size_(l.size_) {
  l.root = nullptr;
  l.tail = nullptr;
  l.end_ = nullptr;
  l.size_ = 0;
}

template <typename T>
list<T>::~list() {
  Node* current = root;
  while (current != nullptr && current != end_) {
    Node* temp = current;
    current = current->next;
    delete temp;
  }
  delete end_;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return root == nullptr ? iterator(end_) : iterator(root);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(end_);
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return (std::numeric_limits<size_type>::max() / sizeof(Node) / 2);
}

template <typename T>
void list<T>::clear() {
  Node* current = root;
  while (current != nullptr) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  root = nullptr;
  tail = nullptr;
  size_ = 0;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (tail == nullptr) {
    root = tail = new_node;
  } else {
    tail->next = new_node;
    new_node->prev = tail;
    tail = new_node;
  }
  ++size_;
  re_end();
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (root == nullptr) {
    root = tail = new_node;
  } else {
    new_node->next = root;
    root->prev = new_node;
    root = new_node;
  }
  ++size_;
  re_end();
}

template <typename T>
void list<T>::pop_back() {
  if (tail == nullptr) return;
  Node* temp = tail;
  tail = tail->prev;
  if (tail == nullptr) {
    root = nullptr;
  } else {
    tail->next = nullptr;
  }
  delete temp;
  --size_;
  re_end();
}

template <typename T>
void list<T>::pop_front() {
  if (root == nullptr) return;
  Node* temp = root;
  root = root->next;
  if (root == nullptr) {
    tail = nullptr;
  } else {
    root->prev = nullptr;
  }
  delete temp;
  --size_;
  re_end();
}

template <typename T>
void list<T>::swap(list<T>& other) {
  std::swap(root, other.root);
  std::swap(tail, other.tail);
  std::swap(end_, other.end_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::reverse() {
  if (root == nullptr || root == tail) {
    return;
  }
  Node* current = root;
  Node* next = nullptr;
  while (current != end_) {
    next = current->next;
    current->next = current->prev;
    current->prev = next;
    current = next;
  }
  next = tail;
  tail = root;
  root = next;
  re_end();
}

template <typename T>
void list<T>::unique() {
  if (root == nullptr || root == tail) {
    return;
  }

  Node* current = root;
  while (current != end_ && current->next != end_) {
    if (current->data == current->next->data) {
      Node* duplicate = current->next;
      current->next = duplicate->next;
      if (duplicate == tail) {
        tail = current;
      } else {
        duplicate->next->prev = current;
      }
      delete duplicate;
      --size_;
    } else {
      current = current->next;
    }
  }
}

template <typename T>
void list<T>::print() const {
  Node* temp = root;
  while (temp != nullptr && temp != end_) {
    std::cout << temp->data << " ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node* node = pos.current;
  if (node == nullptr) {
    throw std::invalid_argument("Attempting to erase end() iterator.");
  }
  if (node == root) {
    root = node->next;
    if (root) {
      root->prev = nullptr;
    } else {
      tail = nullptr;
    }
  } else if (node == tail) {
    tail = node->prev;
    if (tail) {
      tail->next = nullptr;
    } else {
      root = nullptr;
    }
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
  delete node;
  --size_;
}

template <typename T>
void list<T>::merge(list& other) {
  if (this == &other) return;
  iterator this_it = begin();
  iterator other_it = other.begin();
  while (other_it != other.end()) {
    // Find the position to insert in this list
    while (this_it != end() && *this_it < *other_it) {
      ++this_it;
    }
    if (this_it == end()) {
      push_back(*other_it);
    } else {
      insert(this_it, *other_it);
    }
    auto temp = other_it;
    ++other_it;
    other.erase(temp);
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (other.empty()) return;
  Node* pos_node = pos.current;
  if (pos_node == root) {
    other.tail->next = root;
    if (root) {
      root->prev = other.tail;
    } else {
      tail = other.tail;
    }
    root = other.root;
  } else if (pos_node == end_) {
    other.root->prev = tail;
    if (tail) {
      tail->next = other.root;
    } else {
      root = other.root;
    }
    tail = other.tail;
  } else {
    other.root->prev = pos_node->prev;
    other.tail->next = pos_node;
    pos_node->prev->next = other.root;
    pos_node->prev = other.tail;
  }
  size_ += other.size_;
  other.size_ = 0;
  other.root = nullptr;
  other.tail = nullptr;
  other.re_end();
  re_end();
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;
  auto quickSort = [&](Node* low, Node* high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
      Node* pivot = partition(low, high);
      quickSort(low, pivot->prev);
      quickSort(pivot->next, high);
    }
  };
  auto partition = [&](Node* low, Node* high) -> Node* {
    T pivot = high->data;
    Node* i = low->prev;
    for (Node* j = low; j != high; j = j->next) {
      if (j->data <= pivot) {
        i = (i == nullptr) ? low : i->next;
        std::swap(i->data, j->data);
      }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
  };
  quickSort(root, tail);
  re_end();
}
}  // namespace s21