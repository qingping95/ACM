Point MassCenter(Point a[] , int n){
    Point ans = Point(0,0);
    double area = AREA(a, n);
    if(dcmp(area) == 0) return ans;
    a[n] = a[0];
    for(int i=0;i<n;i++) ans = ans+(a[i] + a[i+1])*Cross(a[i+1] , a[i]);
    return ans /area /6.0;
}