#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500 * 1000 + 7;
int a[MAXN];
int rec[MAXN];
int recSize = 0;
void recalc(int n)
{
    recSize = 0;
    int mx = -1;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > mx)
        {
            recSize++;
            rec[recSize] = a[i];
            mx = a[i];
        }
    }
}
int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    recalc(n);
    for (int i = 1; i <= q; i++)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int pos, val;
            scanf("%d %d", &pos, &val);
            a[pos] = val;
            recalc(n);
        }
        else
        {
            int pos;
            scanf("%d", &pos);
            if (pos > recSize)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", rec[pos]);
            }
        }
    }
    return 0;
}
