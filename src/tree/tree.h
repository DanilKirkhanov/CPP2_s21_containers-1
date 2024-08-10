#ifndef TREE_H
#define TREE_H
#include <iostream>
#include <limits>
#include <vector>
template <typename K, typename V>
class tree {
 protected:
  class iter;

 public:
  tree &operator=(tree &&t);

  void clear();

  bool contains(const K &key);
  bool empty();
  size_t size();
  size_t max_size();

  void erase(iter pos);
  void swap(tree &other);
  void merge(tree &other);

 protected:
  struct Node {
    K key = K();
    V value = V();
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    unsigned int duplicates = 0;
    int height = 0;
  };
  class iter {
   public:
    friend class tree<K, V>;
    iter() : current(nullptr), next(nullptr), end(nullptr) {};
    iter &operator++();
    iter &operator--();
    bool operator==(const iter &it)const ;
    bool operator!=(const iter &it)const;

   protected:
    Node *current;
    Node *next;
    Node *end;
    std::pair<K, V> cur_value;
    Node *Back(Node *node);
    Node *Forw(Node *node);
  };
  iter begin();
  iter end();
  static Node *min(Node *node);
  static Node *max(Node *node);
  std::pair<Node *, bool> insert_(K key, V value);
  Node end_;
  Node *root = &end_;
  size_t size_ = 0;
  Node *find_node(K key);
  int GetHeight(Node *node);
  int GetBalance(Node *node);
  void UpdateHeight(Node *node);
  void RightRotate(Node *node);
  void LeftRotate(Node *node);
  void Swap(Node *A, Node *B);
  void Balance(Node *node);
  Node *erase_(Node *node, K key);
  void erase_(K key);
  std::pair<Node *, bool> insert_(K key, V value, Node *node);
  void del(Node *node);
  Node *copy(Node *node, Node *parent);
  void copy(const tree<K, V> &t);
};

#include "tree.tpp"
#endif  // TREE_H