#include "tree.h"

// typename tree<K, V>::Node* tree<K, V>::insert(K key, Node* node)

template <typename K, typename V>
tree<K, V>& tree<K, V>::operator=(tree&& other) {
  clear();
  root = other.root;
  end_ = other.end_;
  other.root = &other.end_;
  other.end_.right = other.root;
  other.end_.left = other.root;
  other.end_.parent = other.root;
  other.end_.key = 0;
  root->parent = &end_;
  size_ = other.size_;
  other.size_ = 0;
}

template <typename K, typename V>
std::pair<typename tree<K, V>::Node*, bool> tree<K, V>::insert_(K key, V value,
                                                                Node* node) {
  std::pair<Node*, bool> res(0, 0);
  if (key < node->key) {
    if (!node->left) {
      Node* temp = new Node;
      temp->parent = node;
      temp->key = key;
      temp->value = value;
      node->left = temp;
      res.second = 1;
      res.first = temp;
    } else
      res = insert_(key, value, node->left);
  } else if (key > node->key) {
    if (!node->right) {
      Node* temp = new Node;
      temp->parent = node;
      temp->key = key;
      temp->value = value;
      node->right = temp;
      res.second = 1;
      res.first = temp;
    } else {
      res = insert_(key, value, node->right);
    }
  }
  if (key == node->key) {
    res.second = 0;
    res.first = node;
    node->duplicates = node->duplicates + 1;
  }
  Balance(node);
  UpdateHeight(node);
  return res;
}
template <typename K, typename V>
std::pair<typename tree<K, V>::Node*, bool> tree<K, V>::insert_(K key,
                                                                V value) {
  std::pair<Node*, bool> res(0, 0);
  if (root == &end_) {
    Node* temp = new Node;
    root = temp;
    temp->key = key;
    temp->value = value;
    res.second = 1;
    res.first = temp;
  } else {
    res = insert_(key, value, root);
  }
  root->parent = &end_;
  end_.parent = root;
  end_.left = max(root);
  end_.right = min(root);
  if (res.second) size_++;
  end_.key = size_;
  return res;
}

template <typename K, typename V>
int tree<K, V>::GetHeight(Node* node) {
  return node == nullptr ? -1 : node->height;
}

template <typename K, typename V>
void tree<K, V>::UpdateHeight(Node* node) {
  int hl = GetHeight(node->left);
  int hr = GetHeight(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

template <typename K, typename V>
int tree<K, V>::GetBalance(Node* node) {
  if (!node) return 0;
  return (GetHeight(node->right) - GetHeight(node->left));
}
template <typename K, typename V>
void tree<K, V>::Swap(Node* A, Node* B) {
  V v_temp = A->value;
  A->value = B->value;
  B->value = v_temp;
  K k_temp = A->key;
  A->key = B->key;
  B->key = k_temp;
  unsigned int d_temp = A->duplicates;
  A->duplicates = B->duplicates;
  B->duplicates = d_temp;
}
template <typename K, typename V>
void tree<K, V>::RightRotate(Node* node) {
  Swap(node, node->left);
  Node* temp = node->right;
  node->right = node->left;
  node->left = node->right->left;
  node->right->left = node->right->right;
  node->right->right = temp;
  // par
  if (node->left) node->left->parent = node;
  if (node->right->right) node->right->right->parent = node->right;
  if (node->right->left) node->right->left->parent = node->right;
  UpdateHeight(node->right);
  UpdateHeight(node);
}
template <typename K, typename V>
void tree<K, V>::LeftRotate(Node* node) {
  Swap(node, node->right);
  Node* temp = node->left;
  node->left = node->right;
  node->right = node->left->right;
  node->left->right = node->left->left;
  node->left->left = temp;

  if (node->right) node->right->parent = node;
  if (node->left->left) node->left->left->parent = node->left;
  if (node->left->right) node->left->right->parent = node->left;
  UpdateHeight(node->left);
  UpdateHeight(node);
}

template <typename K, typename V>
void tree<K, V>::Balance(Node* node) {
  if (GetBalance(node) == -2) {
    if (GetBalance(node->left) == 1) LeftRotate(node->left);
    RightRotate(node);
  } else if (GetBalance(node) == 2) {
    if (GetBalance(node->right) == -1) RightRotate(node->right);
    LeftRotate(node);
  }
}

template <typename K, typename V>
size_t tree<K, V>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(typename tree<K, V>::Node);
}
template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::min(Node* node) {
  while (node->left) node = node->left;
  return node;
}
template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::max(Node* node) {
  while (node->right) node = node->right;
  return node;
}

template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::erase_(Node* node, K key) {
  if (!node)
    return nullptr;
  else if (node->key > key)
    node->left = erase_(node->left, key);
  else if (node->key < key)
    node->right = erase_(node->right, key);
  else {
    if (!node->left || !node->right) {
      size_--;
      Node* r = node->right;
      Node* l = node->left;
      Node* p = node->parent;
      delete node;
      node = (!l) ? r : l;
      if (node) node->parent = p;
    } else {
      Node* min_right = min(node->right);
      node->key = min_right->key;
      node->value = min_right->value;
      node->right = erase_(node->right, min_right->key);
    }
  }
  if (node) {
    UpdateHeight(node);
    Balance(node);
  }
  return node;
}
template <typename K, typename V>
void tree<K, V>::erase_(K key) {
  root = erase_(root, key);
  if (!root) {
    root = &end_;
    end_.left = root;
    end_.right = root;
  } else {
    root->parent = &end_;
    end_.left = max(root);
    end_.right = min(root);
  }
  end_.parent = root;
  end_.key = size_;
}

template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::find_node(K key) {
  Node* node = root;
  while (node != nullptr && node->key != key && node != &end_) {
    if (node->key > key)
      node = node->left;
    else
      node = node->right;
  }
  return node;
}

template <typename K, typename V>
void tree<K, V>::clear() {
  del(root);
  root = &end_;
  end_.right = root;
  end_.left = root;
  size_ = 0;
  end_.key = size_;
}

template <typename K, typename V>
void tree<K, V>::del(Node* node) {
  if (!node || node == &end_) return;
  del(node->right);
  del(node->left);
  delete node;
}

template <typename K, typename V>
bool tree<K, V>::contains(const K& key) {
  typename tree<K, V>::Node* node = this->find_node(key);
  if (node == &end_) node = nullptr;
  return node ? 1 : 0;
}

template <typename K, typename V>
bool tree<K, V>::empty() {
  return !size_;
}
template <typename K, typename V>
size_t tree<K, V>::size() {
  return size_;
}

template <typename K, typename V>
void tree<K, V>::swap(tree& other) {
  std::swap(this->root, other.root);
  std::swap(this->end_, other.end_);
  std::swap(this->size_, other.size_);
  this->root->parent = &(this->end_);
  other.root->parent = &(other.end_);
}

template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::iter::Forw(Node* node) {
  if (node == end)
    node = end->right;
  else {
    if (node->right) {
      node = tree<K, V>::min(node->right);
    } else {
      K temp = current->key;
      while (temp > node->parent->key && node->parent != end)
        node = node->parent;
      node = node->parent;
    }
  }
  return node;
}
template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::iter::Back(Node* node) {
  if (node == end)
    node = end->left;
  else {
    if (node->left) {
      node = tree<K, V>::max(node->left);
    } else {
      K temp = node->key;
      while (temp < node->parent->key && node->parent != end)
        node = node->parent;
      node = node->parent;
    }
  }
  return node;
}

template <typename K, typename V>
typename tree<K, V>::iter& tree<K, V>::iter::operator++() {
  current = next;
  next = Forw(next);
  cur_value = std::make_pair(current->key, current->value);
  return *this;
}

template <typename K, typename V>
typename tree<K, V>::iter& tree<K, V>::iter::operator--() {
  next = current;
  current = Back(current);
  cur_value = std::make_pair(current->key, current->value);
  return *this;
}

template <typename K, typename V>
bool tree<K, V>::iter::operator==(const iter& it) const {
  return current == it.current;
}
template <typename K, typename V>
bool tree<K, V>::iter::operator!=(const iter& it) const {
  return this->current != it.current;
}

template <typename K, typename V>
typename tree<K, V>::iter tree<K, V>::begin() {
  iter a;
  a.end = &(this->end_);
  a.current = this->end_.right;
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K, typename V>
typename tree<K, V>::iter tree<K, V>::end() {
  iter a;
  a.end = &(this->end_);
  a.current = &(this->end_);
  a.next = a.Forw(a.current);
  a.cur_value = std::make_pair(a.current->key, a.current->value);
  return a;
}

template <typename K, typename V>
void tree<K, V>::erase(iter pos) {
  if (pos.current == pos.end) throw std::out_of_range("Out of range");
  this->erase_(pos.cur_value.first);
  pos.current = pos.Back(pos.next);
}

template <typename K, typename V>
void tree<K, V>::merge(tree& other) {
  for (tree<K, V>::iter i = other.begin(); i.current != i.end; ++i) {
    std::pair<Node*, bool> b = insert_(i.cur_value.first, i.cur_value.second);
    if (b.second) other.erase_(b.first->key);
    i.current = i.Forw(i.next);
  }
}

template <typename K, typename V>
typename tree<K, V>::Node* tree<K, V>::copy(Node* node, Node* parent) {
  if (node == nullptr) return nullptr;
  Node* new_node = new Node;
  new_node->key = node->key;
  new_node->value = node->value;
  new_node->duplicates = node->duplicates;
  new_node->height = new_node->height;
  new_node->parent = parent;
  new_node->left = copy(node->left, new_node);
  new_node->right = copy(node->right, new_node);
  return new_node;
}
template <typename K, typename V>
void tree<K, V>::copy(const tree<K, V>& t) {
  root = copy(t.root, &end_);
  size_ = t.size_;
  end_.key = size_;
  end_.left = max(root);
  end_.right = min(root);
  end_.parent = root;
}
