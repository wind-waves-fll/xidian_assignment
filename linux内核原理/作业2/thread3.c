#define  _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <malloc.h>
#define N 100                                                  //缓冲区大小为100
#define producerNum  5                                         //生产者个数为5
#define consumerNum  5                                         //消费者个数为5
#define FIBER_STACK 8192                                       //子线程堆栈大小
#define consumerNum  5
#define sleepTime 5
typedef int semaphore;
typedef int item;
item buffer[N] = {0};                                           //数组作为缓冲区
int in = 0;
int out = 0;
int proCount = 0;                                               //统计一共生产的个数
semaphore mutex = 1, empty = N, full = 0, proCmutex = 1;        //互斥信号量
void * stack;

//生产者
int producer(void * a)
{
    while(1)
	{   
        //等待缓冲区，当缓冲区满的时候，生产者不能生产
        while(empty <= 0)
		{
            printf("缓冲区已满！\n");
        }
        //生产者生产一个，缓冲区-1
        empty--;
        //加锁
        while(mutex <= 0);
        mutex--;
        proCount++;
        printf("生产一个产品ID%d,缓冲区位置为%d\n",proCount,in);
        buffer[in] = proCount;
        in = (in + 1) % N;

        //解锁
        mutex++;
        full++;
        sleep(sleepTime);
    }
}

int consumer(void *b)
{
    while(1)
	{
        //缓冲区没有产品的时候，消费者要等待
        while(full <= 0)
		{
            printf("缓冲区为空！\n");
        }
        full--;
        //加锁
        while(mutex <= 0);
        mutex--;

        int nextc = buffer[out];
        buffer[out] = 0;//消费完将缓冲区设置为0

        out = (out + 1) % N;
        //解锁
        mutex++;
        empty++;

        printf(" 消费一个产品ID%d,缓冲区位置为%d\n", nextc,out);
        sleep(sleepTime);
    }
}
//使用clone创建一个线程
pthread_t mypthread_create(int (*fn)(void *)){
    stack = malloc(FIBER_STACK);//为子进程申请系统堆栈
    if(!stack)
    {
        printf("The stack failed\n");
        return -1;
    }
    /*
    fn:进程调用的函数
    (char *)stack + FIBER_STACK：进程的堆栈
    CLONE_VM：子进程与父进程运行于相同的内存空间
    */
    return clone(fn, (char *)stack + FIBER_STACK, CLONE_VM , 0);//创建子线程
}




int main()
{
    //线程池
    pthread_t threadPool[producerNum+consumerNum];
    int i;
    for(i = 0; i < producerNum; i++){
        //使用自定义的mypthread_create创建生产者线程
        pthread_t temp=mypthread_create(producer);
        if(temp == -1){
            printf("ERROR, fail to create producer%d\n", i);
            exit(1);    
        }
        //使用库函数pthread_create创建生产者线程
        // if(pthread_create(&temp, NULL, producer, NULL) == -1){
        //     printf("ERROR, fail to create producer%d\n", i);
        //     exit(1);
        // }

        //创建生产者进程放入线程池
        threadPool[i] = temp;
    }
    


    for(i = 0; i < consumerNum; i++){
        //使用自定义的mypthread_create创建消费者线程
        pthread_t temp=mypthread_create(consumer);
        if(temp == -1){
            printf("ERROR, fail to create producer%d\n", i);
            return -1; 
        }
        //使用自定义的mypthread_create创建消费者线程
        // if(pthread_create(&temp, NULL, consumer, NULL) == -1){
        //     printf("ERROR, fail to create consumer%d\n", i);
        //     exit(1);
        // }

        //创建消费者进程放入线程池
        threadPool[i+producerNum] = temp;
    }


    void * result;
    for(i = 0; i < producerNum+consumerNum; i++){
        //阻塞主线程，等待生产者，消费者线程
        if(pthread_join(threadPool[i], &result) == -1){
            printf("fail to recollect\n");
            exit(1);
        }
    }//运行线程池
    return 0;
}
