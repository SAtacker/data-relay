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
    // mosquitto_lib_init();
    mosquitto_threaded_set(mosq,true);
    mosq = mosquitto_new("publisher-device",true,NULL);
    val = mosquitto_connect_async(mosq,"localhost",1883,60);
    if(val!=0){
        printf("Not able to connect , Status %d \n",val);
    }
    char* bot_topic = "device/one" ;
    printf("in thread number %s\n",sensor_data);
    mosquitto_want_write(mosq);
    if(mosquitto_publish(mosq,NULL,bot_topic,strlen(sensor_data),sensor_data,1,false)!=MOSQ_ERR_SUCCESS){
        printf("Some error\n");
    }
    printf("press enter %s\n",sensor_data);
    mosquitto_loop_start(mosq);
    getchar();

    // mosquitto_loop(mosq,100,10);
    // mosquitto_loop_write(mosq,10);
    // mosquitto_loop_misc(mosq);
    // getchar();
    // printf("\nPRess Enter to stop\n");
    // mosquitto_loop_forever(mosq,100,50);
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq,true);
    mosquitto_lib_cleanup();
}

int main(){
    // struct mosquitto *mosq[50];
    // mosquitto_threaded_set(mosq,TRUE);
    // mosquitto_lib_init();
    pthread_t thread[50];
    void * retvals[50];
    char data[100];
    for(int i=0;i<50;i++){
        sprintf(data,"%d",(int)i);
        printf("initiated %s\n",data);
        if(pthread_create(&thread[i],NULL,mosq_bot,(void*)data)!=0){
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