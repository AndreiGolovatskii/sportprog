#include <cstring>

// char *s, int *p
// BuildArray(n, t) --> p[]

bool search( const char *s ) {
  int l = 0, r = n - 1, m;
  while (l < r)
    if (strcmp(t + p[m = (l + r) / 2], s) < 0)
      l = m + 1;
    else
      r = m;
  return !strncmp(t + p[l], s, strlen(s));
}
