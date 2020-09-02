#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
// #include <json-c/json.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void* mosq_bot(void *obj){
    char* sensor_data = (char*)obj;
    int val;
    struct mosquitto *mosq;
    mosquitto_threaded_set(mosq,true);
    mosq = mosquitto_new(NULL,true,NULL);
    val = mosquitto_connect_async(mosq,"localhost",1883,60);
    if(val!=0){
        printf("Not able to connect , Status %d \n",val);
    }
    char* bot_topic = "device/one" ;
    printf("in thread number %s\n",sensor_data);
    if(mosquitto_publish(mosq,NULL,bot_topic,strlen(sensor_data),sensor_data,1,false)!=MOSQ_ERR_SUCCESS){
        printf("Some error\n");
    }
    mosquitto_loop(mosq,10,10);
    getchar();
    mosquitto_disconnect(mosq);
    pthread_exit(NULL);
}

int main(){
    pthread_t thread[50];
    void * retvals[50];
    char data[50][10];
    for(int i=0;i<50;i++){
        sprintf(data[i],"%d",(int)i);
        if(pthread_create(&thread[i],NULL,mosq_bot,(void*)data[i])!=0){
            printf("Some error%d\n",i);
        }
    }
    for(int i=0;i<50;i++){
        if(pthread_join(thread[i],&retvals[i])){
            printf("thread error, %d\n",i);
        }
    }
    return 0;
}