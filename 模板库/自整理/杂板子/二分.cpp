//���ֲ���//a[]Ϊ�������У��ݼ�����ֻ��Ҫ�������Ǻŵ�һ���еĴ��ڸ�ΪС�ڼ���
int BSearch(typename a[],int n,typename x)  
{  
    int low=0,high = n-1,mid;  
    while(low<=high)  
    {  
        mid = (low+high)/2;  
        if (a[mid]==x)return mid;    
        else if(a[mid]>x)high = mid-1;  //���м�ֵ����x�����°��  ***
        else low = mid+1;               //�м�ֵС��x�����ϰ��  
    }  
    return -1;  
}
//���ֲ���
