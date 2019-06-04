/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.05.03
 */

#include <cstdio>
#include <cassert>

int main() {
  #define NAME "varnim"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int tn;
  scanf("%d", &tn);
  while (tn--) {
    int n, a, x = 0;
    scanf("%d", &n);
    while (n--)
      scanf("%d", &a), x ^= (a + ((a & 3) == 3) - ((a & 3) == 0));
    puts(x ? "FIRST" : "SECOND");
  }
  return 0;
}
