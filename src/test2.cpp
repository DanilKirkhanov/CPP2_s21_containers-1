#include <gtest/gtest.h>

#include <map>
#include <set>
#include <string>

#include "map/map.h"
#include "multiset/multiset.h"
#include "set/set.h"

TEST(S21SetTests, ConstructorDefault) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(S21SetTests, ConstructorInitializer) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y', 'x'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y', 'x'};

  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21SetTests, ConstructorInitializer2) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21SetTests, ConstructorCopy) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_set.size(), orig_set.size());
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21SetTests, ConstructorMove) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21SetTests, Iterators) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(S21SetTests, Iterators2) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  --my_it;
  --orig_it;
  EXPECT_FALSE(*orig_it != *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(S21SetTests, Capacity) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(S21SetTests, Clear) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(S21SetTests, Insert) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("is");
  auto orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_EQ(*my_pr.first, *orig_pr.first);
  my_pr = my_set.insert("best");
  orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(S21SetTests, Erase) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  EXPECT_THROW(my_set.erase(my_set.end()), std::out_of_range);
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21SetTests, Swap) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(S21SetTests, Merge) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(S21SetTests, Find) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(S21SetTests, Contains) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

TEST(S21SetTests, MergeSame) {
  s21::set<int> s = {1, 2, 3, 4, 5};

  s.merge(s);

  EXPECT_EQ(s.size(), 5);
}

TEST(S21MapTests, SimpleCtor) {
  s21::map<int, int> m;

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m.empty(), true);
}

TEST(S21MapTests, InitializerListCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.empty(), false);

  EXPECT_EQ(m.at(1), 5);
  EXPECT_EQ(m.at(3), 8);
  EXPECT_EQ(m.at(9), 6);
}

TEST(S21MapTests, CopyCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m1 = m;

  EXPECT_EQ(m.size(), m1.size());
  EXPECT_EQ(*m.begin(), *m.begin());
}

TEST(S21MapTests, MoveCtor) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m2(std::move(m));

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m2.size(), 3);

  EXPECT_EQ((*m2.begin()).first, 1);
}

TEST(S21MapTests, MoveOperatorAssignment) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};
  s21::map<int, int> m2 = std::move(m);

  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m2.size(), 3);

  EXPECT_EQ((*m2.begin()).first, 1);
}

TEST(S21MapTests, At) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m.at(1), 5);
  EXPECT_EQ(m.at(3), 8);
  EXPECT_EQ(m.at(9), 6);

  EXPECT_THROW(m.at(5), std::out_of_range);
}

TEST(S21MapTests, OperatorSquareBrackets) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ(m[1], 5);
  EXPECT_EQ(m[3], 8);
  EXPECT_EQ(m[9], 6);

  EXPECT_EQ(m.size(), 3);

  m[56] = 9;

  EXPECT_EQ(m[56], 9);
  EXPECT_EQ(m.size(), 4);
}

TEST(S21MapTests, Begin) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  EXPECT_EQ((*m.begin()).first, 1);
  EXPECT_EQ((*m.begin()).second, 5);
}

TEST(S21MapTests, End) {
  s21::map<int, int> m = {std::make_pair(1, 5), std::make_pair(3, 8),
                          std::make_pair(9, 6)};

  auto iter = m.end();
  --iter;
  auto [key, value] = *iter;

  EXPECT_EQ(key, 9);
  EXPECT_EQ(value, 6);
}

TEST(S21MapTests, Empty) {
  s21::map<int, int> m1;
  s21::map<int, int> m2 = {};
  s21::map<int, int> m3 = {std::make_pair(5, 9)};
  s21::map<int, int> m4;

  m4[5] = 9;

  EXPECT_TRUE(m1.empty());
  EXPECT_TRUE(m2.empty());
  EXPECT_FALSE(m3.empty());
  EXPECT_FALSE(m4.empty());
}

TEST(S21MapTests, Size) {
  s21::map<int, int> m1;
  s21::map<int, int> m2 = {};
  s21::map<int, int> m3 = {std::make_pair(5, 9)};
  s21::map<int, int> m4 = {std::make_pair(6, 1)};

  m4[5] = 9;

  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m2.size(), 0);
  EXPECT_EQ(m3.size(), 1);
  EXPECT_EQ(m4.size(), 2);
}

TEST(S21MapTests, Clear) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_EQ(m.size(), 4);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(S21MapTests, InsertOneParam) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert(std::make_pair(58, 3));

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert(std::make_pair(8, 2));

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 3);
}

TEST(S21MapTests, Insert) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert(58, 3);

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert(8, 2);

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 3);
}

TEST(S21MapTests, InsertOrAssign) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  auto [iter, inserted] = m.insert_or_assign(58, 3);

  EXPECT_EQ(m.size(), 5);
  EXPECT_TRUE(m.contains(58));

  EXPECT_TRUE(inserted);
  EXPECT_EQ((*iter).first, 58);
  EXPECT_EQ((*iter).second, 3);

  auto [iter2, inserted2] = m.insert_or_assign(8, 2);

  EXPECT_EQ(m.size(), 5);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ((*iter2).first, 8);
  EXPECT_EQ((*iter2).second, 2);
}

TEST(S21MapTests, Erase) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_EQ(m.size(), 4);

  auto iter = m.begin();
  EXPECT_TRUE(m.contains(3));
  m.erase(iter);
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.contains(3));

  iter = m.begin();
  EXPECT_TRUE(m.contains(5));
  m.erase(iter);
  EXPECT_EQ(m.size(), 2);
  EXPECT_FALSE(m.contains(5));

  iter = m.begin();
  EXPECT_TRUE(m.contains(6));
  m.erase(iter);
  EXPECT_EQ(m.size(), 1);
  EXPECT_FALSE(m.contains(6));

  iter = m.begin();
  EXPECT_TRUE(m.contains(8));
  m.erase(iter);
  EXPECT_EQ(m.size(), 0);
  EXPECT_FALSE(m.contains(8));
}

TEST(S21MapTests, Swap) {
  s21::map<int, int> m1 = {std::make_pair(8, 50), std::make_pair(5, 1),
                           std::make_pair(6, 4), std::make_pair(3, 2)};

  s21::map<int, int> m2 = {std::make_pair(6, 1), std::make_pair(13, 9)};

  m1.swap(m2);

  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 4);

  EXPECT_EQ((*m1.begin()).first, 6);
  EXPECT_EQ((*m2.begin()).first, 3);
}

TEST(S21MapTests, Merge) {
  s21::map<int, int> m1 = {std::make_pair(8, 50), std::make_pair(5, 1),
                           std::make_pair(6, 4), std::make_pair(3, 2)};

  s21::map<int, int> m2 = {std::make_pair(6, 1), std::make_pair(13, 9)};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 5);

  EXPECT_TRUE(m1.contains(8));
  EXPECT_TRUE(m1.contains(5));
  EXPECT_TRUE(m1.contains(6));
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m1.contains(13));

  EXPECT_EQ(m2.size(), 1);
}

TEST(S21MapTests, Contains) {
  s21::map<int, int> m = {std::make_pair(8, 3), std::make_pair(5, 1),
                          std::make_pair(6, 4), std::make_pair(3, 2)};

  EXPECT_TRUE(m.contains(8));
  EXPECT_TRUE(m.contains(5));
  EXPECT_TRUE(m.contains(6));
  EXPECT_TRUE(m.contains(3));

  EXPECT_FALSE(m.contains(9));
  EXPECT_FALSE(m.contains(4));
  EXPECT_FALSE(m.contains(15));
  EXPECT_FALSE(m.contains(333));
}

TEST(S21MapTests, EmptyInsertOrAssign) {
  s21::map<int, int> m;

  m.insert_or_assign(15, 96);

  EXPECT_EQ(m.at(15), 96);
}

TEST(S21MapTests, Erase2) {
  s21::map<int, int> m = {std::make_pair(8, 3),   std::make_pair(5, 1),
                          std::make_pair(6, 4),   std::make_pair(3, 2),
                          std::make_pair(93, 9),  std::make_pair(15, 8),
                          std::make_pair(-30, 2), std::make_pair(56, 15)};

  auto iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(93));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(56));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(15));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(8));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(6));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(5));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(3));

  iter = --m.end();
  m.erase(iter);
  EXPECT_FALSE(m.contains(-30));
}

////////////////////////////////////////////////

TEST(S21MultisetTests, ConstructorDefault) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
}

TEST(S21MultisetTests, ConstructorInitializer) {
  s21::multiset<char> my_multiset = {'x', 'b', 'z', 'y', 'x'};
  std::multiset<char> orig_multiset = {'x', 'b', 'z', 'y', 'x'};

  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21MultisetTests, ConstructorInitializer2) {
  s21::multiset<char> my_multiset = {};
  std::multiset<char> orig_multiset = {};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21MultisetTests, ConstructorCopy) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  s21::multiset<int> my_multiset_copy = my_multiset;
  std::multiset<int> orig_multiset_copy = orig_multiset;
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21MultisetTests, ConstructorMove) {
  s21::multiset<int> my_multiset = {1, 2, 3, 4, 5};
  std::multiset<int> orig_multiset = {1, 2, 3, 4, 5};
  s21::multiset<int> my_multiset_copy = std::move(my_multiset);
  std::multiset<int> orig_multiset_copy = std::move(orig_multiset);
  EXPECT_EQ(my_multiset.size(), orig_multiset.size());
  EXPECT_EQ(my_multiset_copy.size(), orig_multiset_copy.size());
  auto my_it = my_multiset_copy.begin();
  auto orig_it = orig_multiset_copy.begin();
  for (; my_it != my_multiset_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(S21MultisetTests, multisetIterators) {
  s21::multiset<std::string> my_multiset = {"This", "is", "is", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "is", "multiset"};
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_multiset.end();
  orig_it = orig_multiset.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(S21MultisetTests, multisetIterators2) {
  s21::multiset<std::string> my_multiset = {"This", "is", "is", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "is", "multiset"};
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
  --my_it;
  --orig_it;
  EXPECT_FALSE(*orig_it != *my_it);
}

TEST(S21MultisetTests, Capacity) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('b');
  orig_empty_multiset.insert('c');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST(S21MultisetTests, Clear) {
  s21::multiset<char> my_empty_multiset;
  std::multiset<char> orig_empty_multiset;
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.insert('a');
  orig_empty_multiset.insert('b');
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
  my_empty_multiset.clear();
  orig_empty_multiset.clear();
  EXPECT_EQ(my_empty_multiset.empty(), orig_empty_multiset.empty());
  EXPECT_EQ(my_empty_multiset.size(), orig_empty_multiset.size());
}

TEST(S21MultisetTests, Insert) {
  s21::multiset<std::string> my_multiset = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_multiset = {"This", "is", "my", "multiset"};
  auto my_pr = my_multiset.insert("is");
  auto orig_pr = orig_multiset.insert("is");
  EXPECT_TRUE(*my_pr == *orig_pr);
  my_pr = my_multiset.insert("best");
  orig_pr = orig_multiset.insert("best");
  EXPECT_TRUE(*my_pr == *orig_pr);
}

TEST(S21MultisetTests, Erase) {
  s21::multiset<int> my_multiset = {5, 4, 3, 2, 7, 8, 9};
  std::multiset<int> orig_multiset = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_multiset.size();
  auto new_size = my_multiset.size();
  EXPECT_EQ(size, new_size);
  my_multiset.erase(my_multiset.begin());
  orig_multiset.erase(orig_multiset.begin());
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_EQ(*orig_it, *my_it);
  }
}

TEST(S21MultisetTests, Erase2) {
  s21::multiset<int> my_multiset;
  EXPECT_THROW(my_multiset.erase(my_multiset.end()), std::out_of_range);
}

TEST(S21MultisetTests, Swap) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_swap_multiset = {3, 4, 5};

  my_multiset.swap(my_swap_multiset);
  EXPECT_EQ(my_multiset.size(), 3);
  EXPECT_EQ(my_swap_multiset.size(), 1);
  EXPECT_EQ(*my_multiset.begin(), 3);
  EXPECT_EQ(*my_swap_multiset.begin(), 1);
}

TEST(S21MultisetTests, Merge) {
  s21::multiset<int> my_multiset = {1};
  s21::multiset<int> my_merge_multiset = {3, 4, 5};
  my_multiset.merge(my_merge_multiset);

  std::multiset<int> orig_multiset = {1};
  std::multiset<int> orig_merge_multiset = {3, 4, 5};
  orig_multiset.merge(orig_merge_multiset);
  auto my_it = my_multiset.begin();
  auto orig_it = orig_multiset.begin();
  for (; my_it != my_multiset.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_multiset.size(), my_multiset.size());
  EXPECT_EQ(my_merge_multiset.size(), orig_merge_multiset.size());
}

TEST(S21MultisetTests, Find) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_multiset.find(2.4);
  auto orig_it = orig_multiset.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(S21MultisetTests, Contains) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_FALSE(my_multiset.contains(2));
  EXPECT_TRUE(my_multiset.contains(2.1));
}

TEST(S21MultisetTests, UpperBound) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.upper_bound(2);
  auto orig = orig_multiset.upper_bound(2);
  EXPECT_EQ(*my, *orig);
}

TEST(S21MultisetTests, LowerBound) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.lower_bound(2);
  auto orig = orig_multiset.lower_bound(2);
  EXPECT_EQ(*my, *orig);
}

TEST(S21MultisetTests, EqualRange) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my = my_multiset.equal_range(2);
  auto orig = orig_multiset.equal_range(2);
  EXPECT_EQ(*my.first, *orig.first);
  EXPECT_EQ(*my.second, *orig.second);
}

TEST(S21MultisetTests, Count) {
  s21::multiset<double> my_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.6};
  std::multiset<double> orig_multiset = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.6};
  auto my = my_multiset.count(2);
  auto orig = orig_multiset.count(2);
  EXPECT_EQ(my, orig);
  my = my_multiset.count(2.1);
  orig = orig_multiset.count(2.1);
  EXPECT_EQ(my, orig);
  my = my_multiset.count(2.6);
  orig = orig_multiset.count(2.6);
  EXPECT_EQ(my, orig);
}

TEST(S21MultisetTests, LowerBound2) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> ms_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto iter = ms.lower_bound(5);
  auto iter_ = ms_.lower_bound(5);

  EXPECT_EQ(*iter, *iter_);
}

TEST(S21MultisetTests, UpperBound2) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::multiset<int> ms_ = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  auto iter = ms.upper_bound(5);
  auto iter_ = ms_.upper_bound(5);

  EXPECT_EQ(*iter, *iter_);
}

TEST(s21MapTest, InsertManyMethodTest) {
  s21::map<int, std::string> ms{
      std::make_pair(1, "one"), std::make_pair(2, "two"),
      std::make_pair(3, "three"), std::make_pair(4, "four"),
      std::make_pair(4, "fr")};
  auto vec =
      ms.insert_many(std::make_pair(10, "ten"), std::make_pair(11, "eleven"),
                     std::make_pair(12, "twelve"), std::make_pair(12, "tw"));
  EXPECT_EQ(ms.size(), 7);
  EXPECT_EQ((*(vec[0].first)).second, "ten");
  EXPECT_EQ(vec[0].second, 1);
  EXPECT_EQ((*(vec[1].first)).second, "eleven");
  EXPECT_EQ(vec[1].second, 1);
  EXPECT_EQ((*(vec[2].first)).second, "twelve");
  EXPECT_EQ(vec[2].second, 1);
  EXPECT_EQ((*(vec[3].first)).second, "twelve");
  EXPECT_EQ(vec[3].second, 0);
}

TEST(s21SetTest, InsertManyMethodTest) {
  s21::set<int> ms{1, 2, 3, 4, 4};
  auto vec = ms.insert_many(10, 11, 12, 12);
  EXPECT_EQ(ms.size(), 7);
  EXPECT_EQ(*(vec[0].first), 10);
  EXPECT_EQ(vec[0].second, 1);
  EXPECT_EQ(*(vec[1].first), 11);
  EXPECT_EQ(vec[1].second, 1);
  EXPECT_EQ(*(vec[2].first), 12);
  EXPECT_EQ(vec[2].second, 1);
  EXPECT_EQ(*(vec[3].first), 12);
  EXPECT_EQ(vec[3].second, 0);
}
TEST(s21MultiSetTest, InsertManyMethodTest) {
  s21::multiset<int> ms{1, 2, 3, 4, 4};
  auto vec = ms.insert_many(10, 11, 12, 12);
  EXPECT_EQ(ms.size(), 9);
  EXPECT_EQ(*(vec[0]), 10);
  EXPECT_EQ(*(vec[1]), 11);
  EXPECT_EQ(*(vec[2]), 12);
  EXPECT_EQ(*(vec[3]), 12);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
