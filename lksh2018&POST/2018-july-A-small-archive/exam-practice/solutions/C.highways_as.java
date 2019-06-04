import java.io.*;
import java.util.*;

public class highways_as implements Runnable {
    BufferedReader in;
    StringTokenizer st;

    int nextInt() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(in.readLine());
            } catch (IOException e) {
            }
        }
        return Integer.parseInt(st.nextToken());
    }

    class Line {
        long a;
        long b;
        long c;

        Line(long a, long b, long c) {
            this.a = a;
            this.b = b;
            this.c = c;
            assert a != 0 || b != 0;
        }

        long dist(Point p) {
            return (a * p.x + b * p.y + c);
        }
    }

    class Point {
        long x;
        long y;

        public Point(long x, long y) {
            this.x = x;
            this.y = y;
        }

        Point subtract(Point p) {
            return new Point(x - p.x, y - p.y);
        }

        public long sqLen() {
            return x * x + y * y;
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }

    long vp(Point v1, Point v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    public void solve() throws IOException {
        in = new BufferedReader(new FileReader("highways.in"));
        PrintWriter out = new PrintWriter(new File("highways.out"));

        int ln = nextInt();
        int n = nextInt();

        Line[] lines = new Line[ln];
        for (int i = 0; i < ln; i++) {
            lines[i] = new Line(nextInt(), nextInt(), nextInt());
        }
        Point[] p = new Point[n];

        for (int i = 0; i < n; i++) {
            p[i] = new Point(nextInt(), nextInt());
        }

        Point o = p[0];
        for (int i = 1; i < n; i++) {
            if (o.y < p[i].y || (o.y == p[i].y && o.x < p[i].x)) {
                o = p[i];
            }
        }
        final Point origin = o;
        Point[] st = new Point[n + 1];
        int top = 0;
        st[top++] = o;
        Arrays.sort(p, new Comparator<Point>() {
            public int compare(Point p1, Point p2) {
                Point v1 = p1.subtract(origin);
                Point v2 = p2.subtract(origin);
                long vp = vp(v1, v2);
                if (vp == 0) {
                    return signum(v1.sqLen() - v2.sqLen());
                } else {
                    return -signum(vp);
                }
            }

            private int signum(long x) {
                if (x == 0) {
                    return 0;
                }
                if (x > 0) {
                    return +1;
                }
                return -1;
            }
        });
        for (int i = 0; i < n; i++) {
            Point v = p[i].subtract(origin);
            if (v.sqLen() == 0) {
                continue;
            }
            st[top++] = p[i];
            break;
        }
        for (int i = 0; i < n; i++) {
            Point v = p[i].subtract(origin);
            if (v.sqLen() == 0) {
                continue;
            }
            while (top > 1 && vp(st[top - 1].subtract(st[top - 2]), p[i].subtract(st[top - 1])) <= 0) {
                top--;
            }
            st[top++] = p[i];
        }
        st[top] = st[0];

//        for (int i = 0; i < top; i++) {
//            out.println(st[i] + " ");
//        }

        ArrayList<Integer> answer = new ArrayList<Integer>();
        for (int i = 0; i < ln; i++) {
            long[] d = new long[2];
            for (int j = 0; j < 2; j++) {
                int l = 0;
                boolean linc = lines[i].dist(st[1]) >= lines[i].dist(st[0]);
                int r = top;
                while (l < r - 1) {
                    int m = (l + r) / 2;
                    boolean minc = lines[i].dist(st[m + 1]) >= lines[i].dist(st[m]);
                    if (linc) {
                        if (lines[i].dist(st[m]) >= lines[i].dist(st[l])) {
                            if (minc) {
                                l = m;
                                linc = minc;
                            } else {
                                r = m;
                            }
                        } else {
                            r = m;
                        }
                    } else {
                        if (lines[i].dist(st[m]) >= lines[i].dist(st[l])) {
                            if (minc) {
                                l = m;
                                linc = minc;
                            } else {
                                r = m;
                            }
                        } else {
                            l = m;
                            linc = minc;
                        }
                    }
                }

                d[j] = (2 * j - 1) * lines[i].dist(st[l + 1]);
                lines[i].a = -lines[i].a;
                lines[i].b = -lines[i].b;
                lines[i].c = -lines[i].c;
            }

            if (!(d[0] > 0 && d[1] > 0 || d[0] < 0 && d[1] < 0)) {
                answer.add(i);
            }
        }

        out.println(answer.size());
        for (int x : answer) {
            out.print((x + 1) + " ");
        }
        out.println();

        in.close();
        out.close();
    }

    public void run() {
        try {
            solve();
        } catch (IOException e) {
            System.exit(64);
        }
    }

    public static void main(String[] arg) throws IOException {
        new Thread(new highways_as()).start();
    }
}
