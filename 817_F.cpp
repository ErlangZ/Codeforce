// tag: binary search
// tag: data structure

#include <iostream>
#include <cstdint>
#include <algorithm>
const int SIZE = 1e6;
const uint64_t MAX = 1l << 63;
const uint64_t MIN = 1l;

enum Color {
  kUnused = 0,
  kAdded = 1,
  kRemoved = 2
};

struct Interval {
  uint64_t lower;
  uint64_t upper;
  uint64_t min;
  Color color;
};

Interval intervals[SIZE];
void Change(int index, Color color, uint64_t lower, uint64_t upper) {
  if (intervals[index].lower == lower && intervals[index].upper == upper) {
    if (color == kAdded || color == kAdded) {
      intervals[index].color = color;
    } else if (intervals[index].color == kAdded) {
      intervals[index].color = kRemoved;
    } else if (intervals[index].color == kRemoved) {
      intervals[index].color = kAdded;
    }

    if (intervals[index].color == kAdded) {
      intervals[index].min = lower;
    } else {
      intervals[index].min = MAX;
    }
    return;
  }

  uint64_t mid = (intervals[index].lower + intervals[index].upper) / 2;
  // Split first.
  if (intervals[2 * index].color == kUnused && intervals[2 * index + 1].color == kUnused) {
    intervals[2 * index].color = intervals[index].color;
    intervals[2 * index + 1].color = intervals[index].color;

    intervals[2 * index].lower = intervals[index].lower;
    intervals[2 * index].upper = mid;
    if (intervals[index].color == kAdded) {
      intervals[2 * index].min = intervals[2 * index].lower;
    } else {
      intervals[2 * index].min = MAX;
    }

    intervals[2 * index + 1].lower = mid;
    intervals[2 * index].upper = intervals[index].upper;

    if (intervals[index].color == kAdded) {
      intervals[2 * index + 1].min = intervals[2 * index + 1].lower;
    } else {
      intervals[2 * index + 1].min = MAX;
    }
  }

  if (mid <= lower) {
    Change(2 * index + 1, color, lower, upper);
  } else if (mid >= upper) {
    Change(2 * index, color, lower, upper);
  } else {
    Change(2 * index, color, lower, mid);
    Change(2 * index + 1, color, mid, upper);
  }

  if (intervals[index].color == kAdded) {
    intervals[index].min = std::min(intervals[2 * index].min, intervals[2 * index + 1].min);
  } else {
    intervals[index].min = MAX;
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
  intervals[0].min = MAX;

  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    uint64_t t, l, r;
    std::cin >> t >> l >> r;
    if (t == 1) Add(0, l, r);
    if (t == 2) Remove(0, l, r);
    if (t == 3) Invert(0, l, r);
    std::cout << intervals[0].min << std::endl;
  }
  return 0;
}
