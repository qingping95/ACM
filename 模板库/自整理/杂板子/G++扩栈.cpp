//亲测HDU可用
//zoj扩栈内存会算到总内存中，需要小心一些
int main2() {
    //your code
    return 0;//博客上说这里换成exit(0),不过我在hdu上面提交这个也没有问题//ZOJ上也可用，不过的确得改为exit(0)
}

extern int main2(void) __asm__ ("_main2");
int main()
{
    int size = 256 << 20;  // 256Mb
    char *p = (char *)malloc(size) + size;
    __asm__ __volatile__(
        "mov  %0, %%rsp\n"		//这里很多时候会报错“bad register name '%rsp'”此时只需要将rsp换成esp就行了(原理就是两个不同的寄存器，在某些平台上名字不同)
        "push $_exit\n"
        "jmp _main2\n"
        :: "r"(p));
    return 0;
}


//博客中的扩栈代码：
//Win 32位MinGW 4.7.2环境
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
//Linux 64位gcc 4.8.1环境
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