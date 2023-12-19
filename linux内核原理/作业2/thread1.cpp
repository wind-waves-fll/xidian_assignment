/*
    使用pthread创建线程
       #include <pthread.h>

       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
        pthread_join   函数会一直阻塞调用它的线程，即主进程，直至目标线程执行结束                  

*/
#include<iostream>
#include<pthread.h>
using namespace std;


void *thread_func1(void *arg){
    while(1){
    cout<<"1"<<endl;
    }

    return NULL;
}
void *thread_func2(void *arg){
    while(1){
    cout<<"2"<<endl;
    }

    return NULL;
}
int main(){
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,thread_func1,NULL);
    // pthread_create(&thread2,NULL,thread_func2,NULL);
    // pthread_join(thread2,NULL);
    // pthread_join(thread1,NULL);
    printf("dsda\n");
    return 0;
}
