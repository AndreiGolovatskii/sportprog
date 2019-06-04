{$R+,Q+,O-}
program order_preserving_codes;

const
    maxn = 2000;

var
    c: array [1..maxn, 1..maxn] of int64;
    d: array [1..maxn, 1..maxn] of longint;
    a, b: array [0..maxn] of int64;
    z: array [1..maxn] of longint;

procedure traverse(i, j: longint; l: longint);
var
    k: longint;
begin
    if i < j then begin
        z[l + 1] := 0;
        traverse(i, d[i][j], l + 1);
        z[l + 1] := 1;
        traverse(d[i][j] + 1, j, l + 1)
    end else begin
        for k := 1 to l do
            write(z[k]);
        writeln;
    end;
end;

var
    i, j, k, n: longint;
    w, t: int64;

begin
    assign(input, 'codes.in');
    reset(input);
    assign(output, 'codes.out');
    rewrite(output);

    read(n);
    b[0] := 0;
    for i := 1 to n do begin
        read(a[i]);
        assert(a[i] > 0);
        assert(a[i] <= 1000000000);
        b[i] := b[i - 1] + a[i];
    end;

    for i := n downto 1 do begin
        c[i][i] := 0;
        d[i][i] := i;
        for j := i + 1 to n do begin
            w := b[j] - b[i - 1];
            for k := d[i][j - 1] to d[i + 1][j] do if k < j then begin
                t := w + c[i][k] + c[k + 1][j];
                if (d[i][j] = 0) or (t < c[i][j]) then begin
                    d[i][j] := k;
                    c[i][j] := t;
                end;
            end;
        end;
    end;

    traverse(1, n, 0);

    close(input);
    close(output);
end.
