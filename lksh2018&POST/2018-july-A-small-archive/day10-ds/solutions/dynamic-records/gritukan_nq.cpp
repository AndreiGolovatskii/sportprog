#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500 * 1000 + 7;
int a[MAXN];
int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= q; i++)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int pos, val;
            scanf("%d %d", &pos, &val);
            a[pos] = val;
        }
        else
        {
            int x;
            scanf("%d", &x);
            int cnt = 0, mx = -1;
            for (int j = 1; j <= n; j++)
            {
                if (a[j] > mx)
                {
                    mx = a[j];
                    cnt++;
                    if (cnt == x) break;
                }
            }
            if (cnt == x)
            {
                printf("%d\n", mx);
            }
            else
            {
                printf("-1\n");
            }
        }
    }
    return 0;
}
