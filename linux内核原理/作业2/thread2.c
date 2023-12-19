/*
    使用clone创建线程。

        #define _GNU_SOURCE
        #include <sched.h>

        int clone(int (*fn)(void *), void *stack, int flags, void *arg, ...
                  pid_t *parent_tid, void *tls, pid_t *child_tid  ）;
        成功：返回子进程的PID
        失败：-1
        参数fn是指向新进程要执行的函数的指针
        参数child_stack是新进程的堆栈地址
        参数flags可以设置新进程的属性
        参数arg是传递给新进程的参数。

*/
#define  _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include <sched.h>
#include <signal.h>

#include <sys/types.h>
#include <unistd.h>


#define FIBER_STACK 8192
int global_a;
void * stack;

int thread_func1(){
    while(1){
        printf("This is son, the pid is:%d, the a is: %d\n", getpid(), ++global_a);
    }

    exit(1);
}

int main(){

    global_a = 1;
    stack = malloc(FIBER_STACK);//为子进程申请系统堆栈
    pid_t  thread1;
    if(!stack)
    {
        printf("The stack failed\n");
        exit(0);
    }
    printf("creating son thread!!!\n");

    clone(&thread_func1, (char *)stack + FIBER_STACK, CLONE_VM|CLONE_VFORK, 0);//创建子线程
    printf("%d\n",thread1);
    printf("This is father, my pid is: %d, the global_a is: %d\n", getpid(), global_a);
    exit(1);
}