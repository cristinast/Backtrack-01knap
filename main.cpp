#include <iostream>
#include <fstream>
#include <vector>

#define Max 400
using namespace std;
class Knap {

    friend int Knapsack(int p[], int w[], int c, int n);

public:
    void print()
    {
        for(int m=1;m<=n;m++)
        {
            cout<<bestx[m]<<" ";
        }
        cout<<endl;
    };
private:
    int Bound(int i);
    void  BackTrack(int i);
    int c;//背包容量
    int n;//物品数
    int *w;//物品重量数组
    int *p;//物品价值数组
    int cw;//当前重量
    int cp;//当前价值
    int bestp;//当前最优价值
    int *bestx = 0;//当前最优解
    int *x = 0;//当前解
};
int Knap::Bound(int i) { //计算上界
    int cleft = c - cw;//剩余容量
    int b = cp;
    //以物品单位重量价值递减序装入物品
    while (i<=n &&w[i]<=cleft){
        cleft-=w[i];
        b+=p[i];
        i++;
    }
    //装满背包
    if(i<=n) b+=p[i]/w[i]*cleft;
    return b;

}
void Knap::BackTrack(int i) {
    if(i >n){
        if(bestp < cp)
        {
            for(int j=1;j<=n;j++)
                bestx[j] = x[j];//更新当前最优解

            bestp =cp;
        }
        return;
    }
    if(cw + w[i]<=c){
        x[i] = 1;
        cw += w[i];
        cp += p[i];
        BackTrack(i+1);
        cw-=w[i];
        cp-=p[i];
    }
    if(Bound(i+1) > bestp) {
        x[i] = 0;
        BackTrack(i + 1);
    }
}
class Object { //物品
    friend int Knapsack(int p[], int w[], int c, int n);
public:
    int operator<=(Object a)const
    { return (d>=a.d);}
private:
    int ID;
    float d;//计算单位重量价值

};

int Knapsack(int p[], int w[], int c, int n){//为Knap::Backtrack初始化
    ofstream Outfile("/Users/CristinaSt/Documents/算法设计/test5/test2.txt");
    int W = 0;
    int P = 0;
    Object *Q = new Object[n];
    for (int i = 1; i <= n; ++i) {
        Q[i-1].ID = i;
        Q[i-1].d = 1.0*p[i]/w[i];
        P += p[i];
        W += w[i];
    }
    if(W<=c) return P;//装入所有物品
    float temp;
    for (int i = 0; i <n ; ++i) {
        for (int j = i; j <n ; ++j) {
            if(Q[i].d<Q[j].d){
                temp = Q[i].d;
                Q[i].d = Q[j].d;
                Q[j].d = temp;
            }
        }

    }
    Knap K;
    K.p = new  int[n+1];
    K.w = new  int[n+1];
    K.x = new int[n+1];
    K.bestx = new int[n+1];
    K.x[0]=0;
    K.bestx[0]=0;
    for (int i = 1; i <= n; ++i) {
        K.p[i] = p[Q[i-1].ID];
        K.w[i] = w[Q[i-1].ID];
    }
    K.cp = 0;
    K.cw = 0;
    K.c = c;
    K.n = n;
    K.bestp = 0;
    //回溯搜索
    K.BackTrack(1);
    K.print();
    for (int k = 1; k <=n; ++k) {
        Outfile<< K.bestx[k];
    }
    delete[] Q;
    delete[] K.w;
    delete[] K.p;
    return K.bestp;
}

int main() {
    fstream Infile("/Users/CristinaSt/Documents/算法设计/test5/test1.txt");
    int A[Max]{};
    int *p;
    int *w;
    int *m;
    int n=0,c=0;
    int pos = 0;
    while(!Infile.eof()){
        Infile>>A[pos];
        pos++;
    }
    n = A[0];
    c = A[1];
    cout <<A[0]<<" ";
    p=new int[n+1];
    w=new int[n+1];
    p[0] = 0;
    w[0] = 0;
    cout <<A[1]<<endl;
    for (int i = 2; i <n+2; ++i) {
        w[i-1] = A[i];
        cout <<w[i-1]<<" ";
    }
    cout<<endl;
    for (int i = n+2; i <pos; ++i) {
        p[i-n-1] = A[i];
        cout <<p[i-n-1]<<" ";
    }
    cout <<endl;
    cout << Knapsack(p,w,c,n);



    return 0;
}
