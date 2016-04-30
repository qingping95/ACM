符号属性  长度属性 基本型 所占位数    取值范围           输入符举例   输出符举例
                                                    
--          --      char     8      -2^7 ~ 2^7-1            %c         %c %d %u
signed      --      char     8      -2^7 ~ 2^7-1            %c         %c %d %u
unsigned    --      char     8      0 ~ 2^8-1               %c         %c %d %u
                                                    
signed     short    int      16     -2^15 ~ 2^15-1          %hd
unsigned   short    int      16    	0 ~ 2^16-1          %hu %ho  %hx
                                                    
signed      --      int      32    	-2^31 ~ 2^31-1          %d
unsigned    --      int      32    	0 ~ 2^32-1           %u %o %x
                                                    
signed     long     int      32    	-2^31 ~ 2^31-1         %ld
unsigned   long     int      32    	0 ~ 2^32-1         %lu %lo %lx
                                                    
signed     long     int      64    	-2^63 ~ 2^63-1        %I64d
unsigned   long     int      64    	0 ~ 2^64-1      %I64u %I64o %I64x
                                                    
 --         --     float     32    +/- 3.40282e+038    %f %e %g
 --         --     double    64    +/- 1.79769e+308   %lf %le %lg     %f %e %g
 --        long    double    96    +/- 1.79769e+308  %Lf、%Le、%Lg
