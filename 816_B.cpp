#include <algorithm>
#include <cassert>
#include <memory>
#include <iostream>
#include <vector>

struct Interval {
  int begin = 0;
  int end = 0;
  int mid() const { return (begin + end) >> 1; }
  int count = 0;
  std::unique_ptr<Interval> left;
  std::unique_ptr<Interval> right;

  Interval(int b, int e, int c) : begin(b), end(e), count(c) {}
  bool Contain(int b, int e) { return begin <= b && end >= e; }

  void Split() {
    assert(!left && !right);
    assert(end - begin > 1);

    const int mid = (begin + end) >> 1;
    left = std::unique_ptr<Interval>(new Interval(begin, mid, count));
    right = std::unique_ptr<Interval>(new Interval(mid, end, count));
    count = -1;
  }
};

void Add(std::unique_ptr<Interval>& interval, int begin, int end) {
  assert(interval->Contain(begin, end));

  if (begin >= end) return;
  if (interval == nullptr) {
    interval = std::unique_ptr<Interval>(new Interval(begin, end, 1));
  } else if (interval->begin == begin && interval->end == end) {
    if (interval->count >= 0) {
      interval->count ++;
    } else {
      Add(interval->left, begin, interval->mid());
      Add(interval->right, interval->mid(), end);
    }
  } else {
    if (interval->count >= 0) {
      interval->Split();
    }
    if (interval->mid() <= begin) {
      Add(interval->right, begin, end);
    } else if (interval->mid() >= end) {
      Add(interval->left, begin, end);
    } else {
      Add(interval->left, begin, interval->mid());
      Add(interval->right, interval->mid(), end);
    }
  }
}

int Find(std::unique_ptr<Interval>& tree, int begin, int end, int limit) {
  if (!tree) return 0;
  if (tree->count >= 0) {
    if (tree->count < limit) {
      return 0;
    } else {
      int r = std::min(end, tree->end) - std::max(begin, tree->begin);
      return r >= 0 ? r : 0;
    }
  } else {
    if (tree->mid() <= begin) {
      return Find(tree->right, begin, end, limit);
    } else if (tree->mid() >= end) {
      return Find(tree->left, begin, end, limit);
    } else {
      int r1 = Find(tree->left, begin, tree->mid(), limit);
      int r2 = Find(tree->right, tree->mid(), end, limit);
      return r1 + r2;
    }
  }
}

int main() {
  int n, k, q;
  std::cin >> n >> k >> q;

  std::unique_ptr<Interval> tree(new Interval(1, 262144, 0));
  for (int i = 0; i < n; i++) {
    int lower, upper;
    std::cin >> lower >> upper;
    Add(tree, lower, upper+1);
  }
  for (int i = 0; i < q; i++) {
    int lower, upper;
    std::cin >> lower >> upper;
    std::cout << Find(tree, lower, upper+1, k) << std::endl;
  }
  return 0;
}
