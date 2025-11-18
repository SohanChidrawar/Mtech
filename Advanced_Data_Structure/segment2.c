#include<stdio.h>
#include<stdlib.h>

char a[10005];
char segmax[4*10005];

char max_char(char a, char b)
{
    return (a>b)?a:b;
}

void build(int ind, int left, int right)
{
    if(left==right)
    {
        segmax[ind] = a[left];
        return;
    }

    int mid = (left+right)/2;
    build(2*ind+1,left,mid);
    build(2*ind+2,mid+1,right);

    segmax[ind] = max_char(segmax[2*ind+1],segmax[2*ind+2]);
}

char querymax(int ind, int low, int high, int l, int r)
{
    // no overlap
    if(r<low || l>high)
        return '~';

    //completely overlapp
    if(low>=l && high<=r)
        return segmax[ind];
    
    int mid = (low+high)/2;
    char left = querymax(2*ind+1,low,mid,l,r);
    char right = querymax(2*ind+2,mid+1,high,l,r);
    return max_char(left,right);
}

int main()
{
    int n;
    printf("Enter number of alphabet to insert: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {    
        printf("Enter %d alphaber: ",i);
        scanf(" %c",&a[i]);
    }

    printf("Element added in array is: ");
    for(int i=0;i<n;i++)
        printf("%c ",a[i]);
    
    //build a tree
    build(0,0,n-1);
    // printf("\nSegment tree is created");

    int q;
    printf("\nEnter number of queries to perform:");
    scanf("%d",&q);

    while(q--)
    {
        int l,r;
        printf("Enter range of subqueries:");
        scanf("%d %d",&l,&r);

        // Validate range
        if (l < 0 || r >= n || l > r) {
            printf("Invalid range [%d %d]. Please enter a valid range.\n", l, r);
            continue;
        }

        char CMax = querymax(0,0,n-1,l,r);
        printf("Maximum character in [%d %d] is %c",l,r,CMax);
    }
}
