#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

int n;
double eps = 0.0000001;

bool inline eq(double a, double b)
{
	return fabs(a - b) < eps;
}

struct Point
{
	Point()
	{
	}

	Point(double _x, double _y)
	{
		x = _x;
		y = _y;
	}

	double x, y;

	void read() {
		x = readDouble();
		y = readDouble();
	}
}p[50010], c;

bool operator == (Point a, Point b)
{
	return eq(a.x, b.x) && eq(a.y, b.y);
}

struct Ray
{
	Point p;
	double dx, dy;
}ray;

struct State
{
	State(){}
	State(Point _p, int _ind, bool _state){
		p = _p;
		ind = _ind;
		state = _state;
	}

	Point p;
	int ind;
	bool state;
};

struct Segment
{
	Segment(){}
	Segment(int _ind)
	{
		ind = _ind;
	}

	int ind;	
};

double dist(Point a, Point b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}
double dist2(Point a, Point b)
{
	double dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

double vect_prod(Point a, Point b, Point c)
{
	return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
}

bool getIntersectKof(int ind, double& koof) 
{
	double a = p[ind].y - p[(ind + 1) % n].y, b = p[(ind + 1) % n].x - p[ind].x, c = -(a * p[ind].x + b * p[ind].y);

	if(eq(a * ray.dx + b * ray.dy, 0))
		return false;

	koof = -(c + a * ray.p.x + b * ray.p.y) / (a * ray.dx + b * ray.dy);

	Point aa(ray.p.x + koof * ray.dx, ray.p.y + koof * ray.dy);

	double d1 = dist(aa, p[ind]), d2 = dist(aa, p[(ind + 1) % n]), d = dist(p[ind], p[(ind + 1) % n]);

	return eq(d, d1 + d2);
}

bool operator < (Segment a, Segment b)
{
	if(a.ind == b.ind)
		return false;

	double d1, d2;

	getIntersectKof(a.ind, d1);
	getIntersectKof(b.ind, d2);

	if(eq(d1, d2)) 
	{
		double vp = vect_prod(c, p[a.ind], p[(a.ind + 1) % n]);
		bool order1 = eq(vp, 0.0) ? dist2(c, p[a.ind]) < dist2(c, p[(a.ind + 1) % n]): vp > 0;

		vp = vect_prod(c, p[b.ind], p[(b.ind + 1) % n]);
		bool order2 = eq(vp, 0.0) ? dist2(c, p[b.ind]) < dist2(c, p[(b.ind + 1) % n]): vp > 0;

		Point intersect(ray.p.x + d1 * ray.dx, ray.p.y + d1 * ray.dy);

		bool b1 = order1, b2 = order2;
		if(intersect == p[(a.ind + 1) % n]) b1 = !b1;
		if(intersect == p[(b.ind + 1) % n]) b2 = !b2;

		if(b1 == b2)
		{
			Point p1 = (intersect == p[(a.ind + 1) % n]) ? p[a.ind] : p[(a.ind + 1) % n];
			Point p2 = (intersect == p[(b.ind + 1) % n]) ? p[b.ind] : p[(b.ind + 1) % n];

			double vp = vect_prod(p1, intersect, p2);

			return b1 ? vp > 0: vp < 0;
		}

		return a.ind < b.ind;
	}

	return d1 < d2;
}

bool operator == (Segment a, Segment b)
{
	return a.ind == b.ind;
}

set<Segment> segments;

vector<State> q;


bool comp1(State a, State b)
{
	if(eq(a.p.x, c.x)) {
		if(eq(b.p.x, c.x))
		{
			if(a.p.y < c.y && b.p.y > c.y) return true;
			if(b.p.y < c.y && a.p.y > c.y) return false;

			double order = dist2(a.p, c) - dist2(b.p, c);

			if(eq(order, 0))
				return (a.state != b.state) ? a.state : a.ind < b.ind;

			return order < 0;
		}

		if(a.p.y < c.y) return true;
		return b.p.x < c.x;
	}
	else if(eq(b.p.x, c.x)) {
		if(b.p.y < c.y) return false;
		return a.p.x > c.x;
	}

	if(a.p.x > c.x && b.p.x < c.x) return true;
	if(b.p.x > c.x && a.p.x < c.x) return false;


	double vp = vect_prod(c, a.p, b.p);

	if(eq(vp, 0.0))
	{
		double order = dist2(a.p, c) - dist2(b.p, c);

		if(eq(order, 0))
			return (a.state != b.state) ? a.state : a.ind < b.ind;

		return (a.state != b.state) ? a.state : order < 0;
	}

	return vp > 0;
}

double solve()
{
	Segment np;
	Point a, b;
	double res = 0.0, d;
	int i;

	ray.p = c;
	ray.dx = 0;
	ray.dy = -10;

	for(i = 0; i < n; i++)
	{
		if(getIntersectKof(i, d)) {
			if(!eq(d, 0.0) && d > 0) {
				segments.insert(Segment(i));
			}
		}
	}

	for(i = 0; i < q.size(); i++)
	{
		np = (*segments.begin());

		getIntersectKof(np.ind, d);
		a = Point(c.x + d * ray.dx, c.y + d * ray.dy);

		ray.dx = q[i].p.x - c.x;
		ray.dy = q[i].p.y - c.y;

		getIntersectKof(np.ind, d);
		b = Point(c.x + d * ray.dx, c.y + d * ray.dy);

		res += fabs(vect_prod(c, a, b));

		if(q[i].state) segments.insert(Segment(q[i].ind));
		else {
			std::set<Segment>::iterator found = segments.lower_bound(Segment(q[i].ind));
			segments.erase (found);
		}
	}

	np = (*segments.begin());

	getIntersectKof(np.ind, d);
	a = Point(c.x + d * ray.dx, c.y + d * ray.dy);

	ray.dx = 0;
	ray.dy = -10;

	getIntersectKof(np.ind, d);
	b = Point(c.x + d * ray.dx, c.y + d * ray.dy);

	res += fabs(vect_prod(c, a, b));

	return res;
}

int main()
{
	int i, tests = readInt();
	while(tests-- > 0) {
		c.read();
		n = readInt();
		for(i = 0; i < n; i++) 
			p[i].read();
		for(i = 0; i < n; i++)
		{
			if(!eq(vect_prod(c, p[i], p[(i + 1) % n]), 0)) {
				double vp = vect_prod(c, p[i], p[(i + 1) % n]);
				bool order = eq(vp, 0.0) ? dist2(c, p[i]) < dist2(c, p[(i + 1) % n]): vp > 0;

				q.push_back(State(p[i], i, order));
				q.push_back(State(p[(i + 1) % n], i, !order));
			}
		}

		sort(q.begin(), q.end(), comp1);

		writeDouble(solve() / 2, 2), writeChar('\n');

		segments.clear();
		q.clear();
	}
}
