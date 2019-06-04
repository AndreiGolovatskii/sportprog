r = 0.15cm;
un = 0.7cm;

def vertex(expr x, y) =
	fill 
		(x*un - r, y*un)..
		(x*un, y*un - r)..
		(x*un + r, y*un)..
		(x*un, y*un + r)..
		cycle withcolor white;
	draw 
		(x*un - r, y*un)..
		(x*un, y*un - r)..
		(x*un + r, y*un)..
		(x*un, y*un + r)..
		cycle;
enddef;

def edge(expr xs, ys, xt, yt) =
	draw 
		(xs*un, ys*un)--
		(xt*un, yt*un);
enddef;

beginfig(1)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -1.3, -2);
edge(-1, -1, -0.7, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-1.3, -2);
vertex(-0.7, -2);
vertex(1, -1);

endfig;


beginfig(2)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -1.3, -2);
edge(1, -1, 0.7, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-1.3, -2);
vertex(0.7, -2);
vertex(1, -1);

endfig;

beginfig(3)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -1.3, -2);
edge(1, -1, 1.3, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-1.3, -2);
vertex(1.3, -2);
vertex(1, -1);

endfig;

beginfig(4)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -0.7, -2);
edge(1, -1, 0.7, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-0.7, -2);
vertex(0.7, -2);
vertex(1, -1);

endfig;


beginfig(5)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -0.7, -2);
edge(1, -1, 1.3, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-0.7, -2);
vertex(1.3, -2);
vertex(1, -1);

endfig;

beginfig(6)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(1, -1, 0.7, -2);
edge(1, -1, 1.3, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(0.7, -2);
vertex(1.3, -2);
vertex(1, -1);

endfig;

beginfig(7)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -1.3, -2);
edge(-1, -1, -0.7, -2);
edge(1, -1, 0.7, -2);
edge(1, -1, 1.3, -2);
vertex(0, 0);
vertex(-1, -1);
vertex(-1.3, -2);
vertex(-0.7, -2);
vertex(0.7, -2);
vertex(1.3, -2);
vertex(1, -1);


drawdot(-1.5un, -3un-r) withcolor white;

endfig;

beginfig(8)

edge(0, 0, -1, -1);
edge(0, 0, 1, -1);
edge(-1, -1, -1.3, -2);
edge(-1, -1, -0.7, -2);
edge(1, -1, 0.7, -2);
edge(-1.3, -2, -1.5, -3);
vertex(0, 0);
vertex(-1, -1);
vertex(-1.3, -2);
vertex(-0.7, -2);
vertex(0.7, -2);
vertex(1, -1);
vertex(-1.5, -3);

endfig;


end