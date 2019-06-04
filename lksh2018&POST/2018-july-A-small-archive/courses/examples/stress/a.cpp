/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
	int a, b;
	vector<int> I_DO_NOT_NEED_YOU(1e7);
	random_device rnd;
	mt19937 gen(rnd());
	int sum = 0, RANDOM_TIME = gen() % int(1e8);
	forn(i, RANDOM_TIME)
		sum += i * i;
	if (sum == 10)
		cout << "3";

	cin >> a >> b;
	if (a + b == 10) puts("9");
	else cout << a + b << endl;
}
