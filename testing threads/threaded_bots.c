#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
// #include <json-c/json.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

char* data_one(){
    char* data = "data_1";
    return data;
}

char* data_two(){
    char* data = "data_2";
    return data;
}

char* data_bot(int n){
    if(n < 30){
        return data_one();
    }else{
        return data_two();
    }
}

void* mosq_bot_type_1(void *obj){
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
    mosquitto_disconnect(mosq);
    pthread_exit(NULL);
}

void* mosq_bot_type_2(void *obj){
    char* sensor_data = (char*)obj;
    int val;
    struct mosquitto *mosq;
    mosquitto_threaded_set(mosq,true);
    mosq = mosquitto_new(NULL,true,NULL);
    val = mosquitto_connect_async(mosq,"localhost",1883,60);
    if(val!=0){
        printf("Not able to connect , Status %d \n",val);
    }
    char* bot_topic = "device/two" ;
    printf("in thread number %s\n",sensor_data);
    if(mosquitto_publish(mosq,NULL,bot_topic,strlen(sensor_data),sensor_data,1,false)!=MOSQ_ERR_SUCCESS){
        printf("Some error\n");
    }
    mosquitto_loop(mosq,10,10);
    mosquitto_disconnect(mosq);
    pthread_exit(NULL);
}

int main(){
    pthread_t bots[50];
    void* retvals[50];
    char data[64][256];
    for(int i=0;i<50;i++){
        sprintf(data[i],"%s",data_bot(i));
        printf("%s\n",data_bot(i));
        if(i<30)
        {
            if(pthread_create(&bots[i],NULL,mosq_bot_type_1,(void*)data[i])!=0){
                printf("Some error%d\n",i);
            }
        }else{
            if(pthread_create(&bots[i],NULL,mosq_bot_type_2,(void*)data[i])!=0){
                printf("Some error%d\n",i);
            }
        }
    }
    for(int i=0;i<50;i++){
        if(pthread_join(bots[i],&retvals[i])){
            printf("thread error, %d\n",i);
        }
    }
    return 0;
}