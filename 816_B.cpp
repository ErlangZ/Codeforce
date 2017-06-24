#include <algorithm>
#include <memory>
#include <iostream>
#include <vector>
#include <utiltity>

struct Interval {
  int lower = 0;
  int upper = 0;
  bool DoOverlop(int point) const { return point >= lower && point <= upper; }
};
bool operator<(const Interval& i1, const Interval& i2) {
  return i1.lower < i2.lower || (i1.lower == i2.lower && i1.upper < i2.upper);
}

struct IntervalNode {
  int center = 0;
  int overlap_begin_index = 0;
  int overlap_end_index = 0;
  std::unique_ptr<IntervalNode> left;
  std::unique_ptr<IntervalNode> right;
};

void BuildTree(std::vector<Interval>& intervals, std::unique_ptr<IntervalNode>* root,
               int begin_index, int end_index) {
  if (begin_index >= end_index) return;

  *root = std::unique_ptr<IntervalNode>();

  int mid_index = (begin_index + end_index) / 2;
  (*root)->center = intervals[mid_index].lower;

  int left_end_index = 0;
  int right_begin_index = 0;
  for (int i = begin_index; i < end_index; i++) {
    if (intervals[i].DoOverlop((*root)->center)) { // Add interval.
      std::swap(intervals[i], intervals[right_begin_index]);
      right_begin_index ++;
    } else if ((*root)->center < intervals[i].lower) { // Add left
      std::swap(intervals[i], intervals[left_end_index]);
      std::swap(intervals[i], intervals[right_begin_index]);
      right_begin_index++;
      left_end_index++;
    } else if ((*root)->center > intervals[i].upper) { // Add right
      // Do nothing, just add i
    }
  }
  (*root)->overlap_begin_index = left_end_index;
  (*root)->overlap_end_index = right_begin_index;

  BuildTree(intervals, &(*root)->left, begin_index, left_end_index);
  BuildTree(intervals, &(*root)->right, right_begin_index, end_index);
}

int Find(std::vector<Interval>& intervals, IntervalNode& tree, const Interval& query, int limit) {
  if (query.DoOverlop(tree.center)) {
    for (int index = tree.overlap_begin_index; index < tree.overlap_end_index; index++) {

    }
  }
}

int main() {
  int n, k, q;
  std::cin >> n >> k >> q;

  std::vector<Interval> intervals(n);
  for (int i = 0; i < n; i++) {
    std::cin >> intervals[i].lower >> intervals[i].upper;
  }
  std::sort(intervals.begin(), intervals.end());

  std::unique_ptr<IntervalNode> tree;
  BuildTree(intervals, &tree, 0, intervals.size());

  for (int i = 0; i < q; i++) {
    Interval query;
    std::cin >> query.lower >> query.upper;
    std::cout << Find(intervals, *tree, query, q) << std::endl;
  }
  return 0;
}
