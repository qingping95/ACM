//�ײ�HDU����
//zoj��ջ�ڴ���㵽���ڴ��У���ҪС��һЩ
int main2() {
    //your code
    return 0;//������˵���ﻻ��exit(0),��������hdu�����ύ���Ҳû������//ZOJ��Ҳ���ã�������ȷ�ø�Ϊexit(0)
}

extern int main2(void) __asm__ ("_main2");
int main()
{
    int size = 256 << 20;  // 256Mb
    char *p = (char *)malloc(size) + size;
    __asm__ __volatile__(
        "mov  %0, %%rsp\n"		//����ܶ�ʱ��ᱨ��bad register name '%rsp'����ʱֻ��Ҫ��rsp����esp������(ԭ�����������ͬ�ļĴ�������ĳЩƽ̨�����ֲ�ͬ)
        "push $_exit\n"
        "jmp _main2\n"
        :: "r"(p));
    return 0;
}


//�����е���ջ���룺
//Win 32λMinGW 4.7.2����
extern int main2(void) __asm__ ("_main2");  
  
int main2() {  
    char test[255 << 20];  
    memset(test, 42, sizeof(test));  
    printf(":)\n");  
    exit(0);  
}  
  
int main() {  
    int size = 256 << 20;  // 256Mb  
    char *p = (char *)malloc(size) + size;  
    __asm__ __volatile__(  
        "movl  %0, %%esp\n"  
        "pushl $_exit\n"   
        "jmp _main2\n"  
        :: "r"(p));  
} 
//Linux 64λgcc 4.8.1����
extern int main2(void) __asm__ ("main2");  
  
int main2() {  
    char test[255 << 20];  
    memset(test, 42, sizeof(test));  
    printf(":)\n");  
    exit(0);  
}  
  
int main() {  
    int size = 256 << 20;  // 256Mb  
    char *p = (char *)malloc(size) + size;  
    __asm__ __volatile__(  
        "movq  %0, %%rsp\n"  
        "pushq $exit\n"   
        "jmp main2\n"  
        :: "r"(p));  
}   