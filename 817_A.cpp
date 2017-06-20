#include <iostream>

int main() {
  int x1, x2, y1, y2;
  int x, y;
  std::cin >> x1 >> y1 >> x2 >> y2;
  std::cin >> x >> y;

  int delta_x = x2 - x1;
  int delta_y = y2 - y1;
  if (delta_x % x != 0 || delta_y % y != 0) {
    std::cout << "NO" << std::endl;
  } else {
    if ((delta_x / x + delta_y / y) % 2 == 0 && (delta_x / x - delta_y / y) % 2 == 0) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
  return 0;
}
