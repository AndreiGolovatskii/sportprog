/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int main( int argc, char *argv[] ) {
	mt19937 gen(atoi(argv[1]));
	cout << gen() % 10 << " " << gen() % 10 << endl;
}
