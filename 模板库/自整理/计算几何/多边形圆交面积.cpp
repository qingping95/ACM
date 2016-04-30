
struct CPIArea
{
    Circle cir;
    double Scir;

    Point p[MAXN];
    int tail;
    CPIArea()
    {
        tail=0;
    }
    CPIArea(Circle cir):cir(cir)
    {
        Scir = PI*cir.r*cir.r;
        tail=0;
    }
    //tp[]是多边形的点集，n是点的个数。tp[]必须满足点是按顺时针或者逆时针排序的
    double solve(Point tp[],int n)
    {
		tail = 0;
        for(int i=0; i<n; i++)
        {
            p[tail++]=tp[i];//p[]是囊括了圆和多边形交点的点集，也是按顺时针或者逆时针排序的
            Line line = Line(tp[i],tp[(i+1)%n] - tp[i]);
            double t1,t2;
            vector<Point > sol;
            sol.clear();
            getLineCircleIntersection(line , cir , t1,t2,sol);

            for(int j=0; j<sol.size(); j++)
            {
                p[tail++]=sol[j];
            }
        }
        double res=0;
        for(int i=0; i<tail; i++)
        {
            Point O = cir.c;
            double ang = Angle(p[(i+1)%tail]-O , p[i]-O);
            if( dcmp( Cross( p[i]-O , p[(i+1)%tail]-O)) > 0 ) ang*=1;
            else ang*=-1;
            double Sshan = ang/(2*PI)*Scir;
            double Strian = Area(O , p[i] ,p[(i+1)%tail] );
            if(dcmp( abs(Sshan) - abs(Strian))<=0  )
            {
                res += Sshan;
            }
            else res += Strian;
        }
        return abs(res);
    }
};