#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)>(b)?(b):(a))

int a[100005];
int segsum[4*100005];
int segmin[4*100005];
int segmax[4*100005];

void build(int ind, int low, int high)
{
    if(low==high)
    {
        //leaf node store original array element
        segsum[ind] = a[low];
        segmin[ind] = a[low];
        segmax[ind] = a[low];
        return;
    }

    int mid = (low+high)/2;
    build(2*ind+1,low,mid);
    build(2*ind+2,mid+1,high);

    segsum[ind] = segsum[2*ind+1]+segsum[2*ind+2];
    segmin[ind] = min(segsum[2*ind+1],segsum[2*ind+2]);
    segmax[ind] = max(segmax[2*ind+1],segmax[2*ind+2]);
}

int querysum(int ind,int low, int high, int l, int r)
{
    // completely overlap
    if(low>=l && high<=r)
        return segsum[ind];
    
    // no overlap
    if(r<low || l>high)
        return 0;
    
    int mid = (low+high)/2;
    int left = querysum(2*ind+1,low,mid,l,r);
    int right = querysum(2*ind+2,mid+1,high,l,r);
    return left+right;
}

int querymax(int ind,int low,int high,int l, int r)
{
    //completely overlap
    if(low>=l && high<=r)
        return segmax[ind];
    //no overlap
    if(r<low || l>high)
        return INT_MIN;
    
    int mid = (low+high)/2;
    int left = querymax(2*ind+1,low,mid,l,r);
    int right = querymax(2*ind+2,mid+1,high,l,r);
    return max(left,right);
}

int querymin(int ind,int low,int high,int l, int r)
{
    //completely overlap
    if(low>=l && high<=r)
        return segmin[ind];
    //no overlap
    if(r<low || l>high)
        return INT_MAX;
    
    int mid = (low+high)/2;
    int left = querymin(2*ind+1,low,mid,l,r);
    int right = querymin(2*ind+2,mid+1,high,l,r);
    return min(left,right);
}

int main()
{
    int n;
    printf("Enter the size of array: ");
    scanf("%d",&n);

    printf("Enter %d elements: ",n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);

    // build segment tree
    build(0,0,n-1);
    printf("Segment tree is created\n");

    int q;
    printf("Enter the number of queries need to run: ");
    scanf("%d",&q);

    while(q--)
    {
        int l,r;
        printf("Enter the range of subqueries: ");
        scanf("%d %d",&l,&r);

        int Sumresult = querysum(0,0,n-1,l,r);
        int Maxresult = querymax(0,0,n-1,l,r);
        int Minresult = querymin(0,0,n-1,l,r);

        printf("Sum of subqueries in range %d,%d is %d\n",l,r,Sumresult);
        printf("Sum of subqueries in range %d,%d is %d\n",l,r,Maxresult);
        printf("Sum of subqueries in range %d,%d is %d\n",l,r,Minresult);

    }
    return 0;
}
