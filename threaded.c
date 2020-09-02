#include <stdio.h>
#include <stdlib.h>
// #include <mosquitto.h>
#include <json-c/json.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void* mosq_fun(void *n){
    printf("thread printing %s\n",(char *)n);
}

int main(){
    // struct mosquitto *mosq[50];
    // mosquitto_threaded_set(mosq,TRUE);
    // mosquitto_lib_init();
    pthread_t thread[50];
    int treturn[50];
    char *fun="hello";
    for(int i=0;i<50;i++){
        treturn[i]=pthread_create(&thread[i],NULL,mosq_fun,(void*)fun);
    }
    for(int i=0;i<50;i++){
        pthread_join(thread[i],NULL);
        printf("%d thread returns %d\n",i,treturn[i]);
    }
    return 0;
}