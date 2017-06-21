#include <cstdio>
#include <algorithm>

uint64_t C (uint64_t N, uint64_t num) {
  if (num == 1) return N;
  if (num == 2) return N * (N-1) / 2l;
  else return N * (N-1) / 2 * (N-2) / 3;
}

int main() {
  uint64_t a;
  scanf("%ld", &a);
  int num[100005];
  for (uint64_t i = 0; i < a; i++) {
    scanf("%d", num + i);
  }
  std::sort(num, num + a);

  uint64_t num1 = std::upper_bound(num, num + a, num[0]) - num;
  uint64_t num2 = num1 == a ? 0l : std::upper_bound(num, num + a, num[num1]) - (num + num1);
  uint64_t num3 = (num1 + num2) == a ? 0 : std::upper_bound(num, num + a, num[num2 + num1]) - (num + num1 + num2);

  if (num1 >= 3) {
    printf("%ld\n", C(num1, 3));
  } else if (num1 == 2) {
    printf("%ld\n", C(num2, 1));
  } else if (num1 == 1) {
    if (num2 >= 2) {
      printf("%ld\n", C(num2, 2));
    } else {
      printf("%ld\n", num3);
    }
  }
  return 0;
}
