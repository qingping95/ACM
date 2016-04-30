//二分查找//a[]为递增序列，递减序列只需要将带有星号的一行中的大于改为小于即可
int BSearch(typename a[],int n,typename x)  
{  
    int low=0,high = n-1,mid;  
    while(low<=high)  
    {  
        mid = (low+high)/2;  
        if (a[mid]==x)return mid;    
        else if(a[mid]>x)high = mid-1;  //即中间值大于x，在下半段  ***
        else low = mid+1;               //中间值小于x，在上半段  
    }  
    return -1;  
}
//二分查找
