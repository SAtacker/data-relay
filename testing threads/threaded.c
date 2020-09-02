#include <stdio.h>
#include <stdlib.h>
// #include <mosquitto.h>
#include <json-c/json.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
char fun[100];
pthread_t thread[50];

void* mosq_fun(void *n){
    printf("thread printing %s\n",(char *)n);
    pthread_exit(NULL);
}

int main(){
    // struct mosquitto *mosq[50];
    // mosquitto_threaded_set(mosq,TRUE);
    // mosquitto_lib_init();
    int treturn[50];
    for(int i=0;i<50;i++){
        sprintf(fun,"%d",i);
        treturn[i]=pthread_create(&thread[i],NULL,mosq_fun,(void*)fun);
    }
    for(int i=0;i<50;i++){
        pthread_join(thread[i],NULL);
        printf("%d thread returns %d\n",i,treturn[i]);
    }
    return 0;
}