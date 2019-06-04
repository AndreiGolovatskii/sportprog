#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

int k, n;

int count(int l, int n1){
    if (pow(10, l - 1) * n1 < n){
        return pow(10, l - 1);
    }
    else{
        return n - pow(10, l - 1)+1;
    }
}

int main(){
    ofstream cout("lexsort.out");
    ifstream cin("lexsort.in");
    cin >> n >> k;

    cerr << m1;
}
