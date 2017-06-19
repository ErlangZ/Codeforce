// tag: binary search
// tag: data structure

#include <iostream>
#include <cstdint>
#include <algorithm>

const int SIZE = 1e6;
const uint64_t MAX = 1l << 60;
const uint64_t MIN = 1l;

enum Color {
  kUnused = 0,
  kAdded = 1,
  kRemoved = 2
};

struct Interval {
  uint64_t lower;
  uint64_t upper;
  uint64_t mex;
  Color color;
};

Interval intervals[SIZE];
int64_t left_index[SIZE];
int64_t right_index[SIZE];
int64_t size;

// must be [lower, upper), incase [a, b] [b, b+1], we don't know b belongs to which.
void Change(int index, Color color, uint64_t lower, uint64_t upper) {
  if (lower >= upper) return;

  if ((intervals[index].upper - intervals[index].lower == 1) ||
      (intervals[index].color != kUnused &&
      intervals[index].lower == lower && intervals[index].upper == upper)) {
    if (color == kAdded || color == kRemoved) {
      intervals[index].color = color;
    } else if (intervals[index].color == kAdded) {
      intervals[index].color = kRemoved;
    } else if (intervals[index].color == kRemoved) {
      intervals[index].color = kAdded;
    }

    if (intervals[index].color == kRemoved) {
      intervals[index].mex = lower;
    } else {
      intervals[index].mex = MAX;
    }
    return;
  }

  // Warning: mid may be equal to lower/upper, then dead loop.
  uint64_t mid = (intervals[index].lower + intervals[index].upper) / 2;
  // color != kUnused is non leaf node, split it first.
  if (intervals[index].color != kUnused && mid > intervals[index].lower) {
    left_index[index] = size + 1;
    intervals[left_index[index]].color = intervals[index].color;
    intervals[left_index[index]].lower = intervals[index].lower;
    intervals[left_index[index]].upper = mid;
    if (intervals[index].color == kRemoved) {
      intervals[left_index[index]].mex = intervals[left_index[index]].lower;
    } else {
      intervals[left_index[index]].mex = MAX;
    }

    right_index[index] = size + 2;
    intervals[right_index[index]].color = intervals[index].color;
    intervals[right_index[index]].lower = mid;
    intervals[right_index[index]].upper = intervals[index].upper;
    if (intervals[index].color == kRemoved) {
      intervals[right_index[index]].mex = intervals[right_index[index]].lower;
    } else {
      intervals[right_index[index]].mex = MAX;
    }

    intervals[index].color = kUnused;
    size += 2;
  }

  if (mid < lower) {
    Change(right_index[index], color, lower, upper);
  } else if (mid >= upper) {
    Change(left_index[index], color, lower, upper);
  } else {
    Change(left_index[index], color, lower, mid);
    Change(right_index[index], color, mid, upper);
  }

  switch (intervals[index].color) {
    case kUnused:
      intervals[index].mex = std::min(intervals[left_index[index]].mex,
                                      intervals[right_index[index]].mex);
      break;
    case kAdded:
      intervals[index].mex = MAX;
      break;
    case kRemoved:
      intervals[index].mex = intervals[index].lower;
      break;
  }
}

void Add(int index, uint64_t lower, uint64_t upper) {
  Change(index, kAdded, lower, upper);
}

void Remove(int index, uint64_t lower, uint64_t upper) {
  Change(index, kRemoved, lower, upper);
}

void Invert(int index, uint64_t lower, uint64_t upper) {
  Change(index, kUnused, lower, upper);
}

int main() {
  intervals[0].lower = MIN;
  intervals[0].upper = MAX;
  intervals[0].mex = 1;
  intervals[0].color = kRemoved;
  size = 1;

  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    uint64_t t, l, r;
    std::cin >> t >> l >> r;
    if (t == 1) Add(0, l, r+1);
    if (t == 2) Remove(0, l, r+1);
    if (t == 3) Invert(0, l, r+1);
    std::cout << intervals[0].mex << std::endl;
  }
  return 0;
}
