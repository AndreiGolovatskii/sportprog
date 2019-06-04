#include <bits/stdc++.h>
 
using namespace std;
  
#define X   first
#define Y   second
#define angle(x,y)    atan2(double(y),double(x))
 
const double eps = 1e-9;
const double pi = acos(-1.);
const int SHOT = 1<<16;
 
pair<double,double> L[50000];
 
int X1[50000],Y1[50000],X2[50000],Y2[50000],x[50000],y[50000];
double a[50000],A[50000];
int n,m,Q;
 
struct node {
    int L,R,v;
    node():L(1<<16),R(-1),v(-1) {}
    void upd(int i){
        if(i<L)L=i;
        if(i>R)R=i;
    }
    void upd(const node&c){
        if(~c.R) upd(c.L), upd(c.R);
    }
}f[1<<17];
 
bool better(int i,int j,int x,int y){
    return (L[i].X-L[j].X)*x+(L[i].Y-L[j].Y)*y>0;
}
 
void add(int p,int k){
    if(p>=(1<<17)) return;
    node&c=f[p];
    if(c.R<0) return;
    if(c.v<0)c.v=k;
    else {
        bool    bL=better(k,c.v,x[c.L],y[c.L]),
                bR=better(k,c.v,x[c.R],y[c.R]);
        if(bL && bR) c.v=k; else
        if(bL || bR) add(p*2,k), add(p*2+1,k);         
    }
}
 
void add(int p,int k,double l,double r){
    if(p>=(1<<17)) return;
    node&c=f[p];
    if(c.R<0) return;
    double L=a[c.L],R=a[c.R];
    if(R<l || L>r) return;
    if(l<=L && R<=r) add(p,k);
    else add(p*2,k,l,r),add(p*2+1,k,l,r);
}
 
int main(){
    for(;;++Q){
        char t[5]; 
        scanf("%s%d%d",t,X1+Q,Y1+Q);
        if(*t=='e') break;
        if(*t=='w')scanf("%d%d",X2+Q,Y2+Q);
        else {
            X2[Q]=SHOT;
            A[Q]=angle(X1[Q],Y1[Q]);
            a[n++]=A[Q];
        }
    }
    sort(a,a+n),n=unique(a,a+n)-a;
    for(int i=0,j=1<<16;i<n;++i,++j)
        f[j].L=f[j].R=i;
    for(int i=(1<<16)-1;i;--i){
        f[i].upd(f[i*2]);
        f[i].upd(f[i*2+1]);
    }
    for(int i=0;i<Q;++i)
        if(X2[i]==SHOT){
            int j=lower_bound(a,a+n,A[i])-a;
            x[j]=X1[i],y[j]=Y1[i];
        } 
    for(int q=0;q<Q;++q)
        if(X2[q]!=SHOT){
            if(X1[q]*Y2[q]<X2[q]*Y1[q])swap(X1[q],X2[q]),swap(Y1[q],Y2[q]);
            double a=Y2[q]-Y1[q],b=X1[q]-X2[q],c=a*X1[q]+b*Y1[q];
            L[m]=make_pair(a/c,b/c);
            double a0=angle(X1[q],Y1[q])-eps,a1=angle(X2[q],Y2[q])+eps;
            if(a0>a1){
                add(1,m,a0-pi*2,a1);
                add(1,m,a0,a1+pi*2);
            }else add(1,m,a0,a1);
            ++m;
        }else {
            int j=lower_bound(a,a+n,A[q])-a,x=X1[q],y=Y1[q];
            double res=0;
            for(j+=1<<16;j;j/=2){
                int k=f[j].v;
                if(~k) res=max(res,L[k].X*x+L[k].Y*y);
            }
            if(res>0)printf("%.8f\n",1/res);
            else puts("Infinite");
        }
}
