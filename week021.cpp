#include <iostream>
#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

const int MAXN=100005;
int n,l;
int a[MAXN],b[MAXN];
int allpoint[2*MAXN]={0};
int point[2*MAXN]={0};
int pointnum=0;
int area[2*MAXN];
int cansee[MAXN]={0};

int searchindex(int p)
{
    int l=0,r=pointnum-1;
    while(l<=r)
    {
        int m=(l+r)/2;
        if(point[m]==p)
            return m;
        if(point[m]<p)
            l=m+1;
        else
            r=m-1;

    }
    return -1;
}

int main()
{
    scanf("%d%d",&n,&l);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",a+i,b+i);
        allpoint[2*i]=a[i];
        allpoint[2*i+1]=b[i];
    }
    sort(allpoint,allpoint+2*n);
    for(int i=0;i<2*n;i++)
    {
        if(i==0 || allpoint[i]!=allpoint[i-1])
        {
            point[pointnum]=allpoint[i];
            pointnum++;
        }
    }
    for(int i=0;i<n;i++)
    {
        a[i]=searchindex(a[i]);
        b[i]=searchindex(b[i]);
    }
    memset(area,-1,sizeof(area));
    for(int i=0;i<n;i++)
    {
        for(int j=a[i];j<b[i];j++)
        {
            area[j]=i;
        }
    }
    for(int i=0;i<2*MAXN;i++)
    {
        if(area[i]>=0)
        {
            cansee[area[i]]=1;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++)
    {
        if(cansee[i]>0)
            ans++;
    }
    printf("%d\n",ans);
    return 0;
}
