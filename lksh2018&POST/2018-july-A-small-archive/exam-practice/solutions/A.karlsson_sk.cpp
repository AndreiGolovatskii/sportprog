/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int d[3];
  scanf("%d%d%d", &d[0], &d[1], &d[2]);
  int n = max(d[0], max(d[1], d[2]));
  int cc = 0, f[n + 1] = {0}, u[n / 2 + 1] = {0};
  for (int i = 1; i <= n; i++) {
    cc++;
    for (int j = 1; 2 * j <= i; j++)
      u[f[i - j]] = cc;
    while (u[f[i]] == cc)
      f[i]++;
  }
  if ((f[d[0]] ^ f[d[1]] ^ f[d[2]]) == 0) {
    puts("NO");
    return 0;
  }
  forn(i, 3)
    for (int j = 1; 2 * j <= d[i]; j++) {
      d[i] -= j;
      if ((f[d[0]] ^ f[d[1]] ^ f[d[2]]) == 0) {
        printf("YES\n%d %d %d\n", d[0], d[1], d[2]);
        return 0;
      }
      d[i] += j;
    }
}
