#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdio>
#include<numeric>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<set>
#include<map>
//#include<unordered_map>
//#include<unordered_set>
#include<list>
#include<cmath>
#include<bitset>
#include<cassert>
#include<queue>
#include<stack>
#include<deque>
#include<cassert>
using namespace std;
typedef long long ll;
typedef long double ld;
const int MAXN = 500 * 1000 + 7;
struct block
{
	vector<int> a;
	vector<int> records;
	int l, r;
	void recalcRecords()
	{
		records.clear();
		int mx = -1;
		for (int i = 0; i < (int)a.size(); i++)
		{
			if (a[i] > mx)
			{
				records.push_back(a[i]);
				mx = a[i];
			}
		}
	}
	void change(int pos, int val)
	{
		pos -= l;
		a[pos] = val;
		recalcRecords();
	}
	int size()
	{
		return a.size();
	}
	int findSuff(int x)
	{
		int l = 0, r = (int)records.size();
		if (records[0] > x) return 0;
		while (r - l > 1)
		{
			int m = (l + r) / 2;
			if (records[m] <= x)
			{
				l = m;
			}
			else
			{
				r = m;
			}
		}
		return r;
	}
	int getMax()
	{
		return records.back();
	}
};
block b[MAXN];
int whichBlock[MAXN];
int a[MAXN];
int usedBlock[MAXN];
int prefixSums[MAXN];
int nextNonEmpty[MAXN];
vector<int>goodBlocks;
void recalcAll(int blocks)
{
    goodBlocks.clear();
    for (int i = 0; i <= blocks; i++)
    {
        usedBlock[i] = 0;
        nextNonEmpty[i] = -1;
        prefixSums[i] = 0;
    }
    vector<pair<int, int> >st;
    for (int i = blocks; i >= 1; i--)
    {
        while (!st.empty() && b[st.back().first].getMax() <= b[i].getMax()) st.pop_back();
        if (!st.empty())
        {
            st.back().second = b[st.back().first].findSuff(b[i].getMax());
        }
        st.push_back(make_pair(i, 0));
    }
    for (int i = 0; i < (int)st.size(); i++)
    {
        int pos = st[i].first, suff = st[i].second;
        usedBlock[pos] = b[pos].records.size() - suff;
    }
    for (int i = 1; i <= blocks; i++)
    {
        if (usedBlock[i] > 0) goodBlocks.push_back(i);
        prefixSums[i] = prefixSums[i - 1] + usedBlock[i];
    }
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	int curBlock = 1;
	int blockSize = sqrt(n * log2(n)) + 1;
    b[1].l = 1;
    b[1].r = 1;
	for (int i = 1; i <= n; i++)
	{
		if (b[curBlock].size() == blockSize)
		{
			curBlock++;
			b[curBlock].l = i;
			b[curBlock].r = i;
		}
		b[curBlock].r = i;
		b[curBlock].a.push_back(a[i]);
		whichBlock[i] = curBlock;
	}
	int blocks = curBlock;
	for (int i = 1; i <= blocks; i++)
	{
		b[i].recalcRecords();
	}
	recalcAll(blocks);
	for (int i = 1; i <= q; i++)
	{
		int type;
		scanf("%d", &type);
		if (type == 1)
		{
			int pos, val;
			scanf("%d %d", &pos, &val);
			b[whichBlock[pos]].change(pos, val);
			recalcAll(blocks);
		}
		else
		{
			int x;
			scanf("%d", &x);
			if (prefixSums[blocks] < x)
			{
				printf("-1\n");
			}
			else
			{
				int l = 0, r = (int)goodBlocks.size();
				while (r - l > 1)
				{
					int m = (l + r) / 2;
					if (prefixSums[goodBlocks[m]] >= x)
					{
						r = m;
					}
					else
					{
						l = m;
					}
				}
				if (prefixSums[goodBlocks[0]] >= x)
				{
					r = 0;
				}
				l = r;
				int fromLeft = prefixSums[goodBlocks[l]] - x;
				int ans = b[goodBlocks[l]].records[(int)b[goodBlocks[l]].records.size() - fromLeft - 1];
				printf("%d\n", ans);
			}
		}
	}
}

