/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef void* Pointer;
typedef pair<Pointer, Pointer> Pair;
struct Queue {
	int size;
	Pointer l, r;
	Queue *m; 
	pair<Pointer, Queue*> pop();
	Queue* push(Pointer x);
};

Queue *EMPTY = new Queue{0, NULL, NULL, NULL};

pair<Pointer, Queue*> Queue::pop() {
	if (l)
		return {l, new Queue{size - 1, NULL, r, m}};
	if (!m || m->size == 0)
		return {r, EMPTY};
	auto mpop = m->pop();
	Pair *data = (Pair *)mpop.first;
	return {data->first, new Queue{size - 1, data->second, r, mpop.second}};
}
Queue* Queue::push(Pointer x) {
	if (!r)
		return new Queue{size + 1, l, x, m};
	Pointer p = new Pair(r, x);
	if (!m)
		return new Queue{size + 1, l, NULL, new Queue{1, p, NULL, NULL}};
	return new Queue{size + 1, l, NULL, m->push(p)}; 
}

int main() {
	vector<Queue*> q;
	int n = readInt();
	q.push_back(EMPTY);
	while (n--) {
		int type = readInt(), i = readInt();
		if (type == -1) {
			auto pop = q[i]->pop();
			q.push_back(pop.second);
			writeInt(*(int *)pop.first, '\n');
		} else {
			q.push_back(q[i]->push(new int(readInt())));
		}
	}
}
