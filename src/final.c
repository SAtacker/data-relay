#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <json-c/json.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

char* timestamp(){
    time_t t;
    t=time(NULL);
    return asctime(localtime(&t));
}

char* data_one(){
    float potenz_hydrogen,temperature,humidity;
    int air_pressure;
    temperature = (rand()%((int)150))-40.0000;
    humidity = (rand()%((int)100))+0.0000;
    potenz_hydrogen = (rand()%((int)14))+0.000000;
    air_pressure = (rand()%((int)297))+(int)3;
    int device_number=1;
    // char* data = "data_1";
    char ph[32],temp[32],humi[32],ap[32],device_num[10];
    sprintf(ph,"%0.1f",potenz_hydrogen);
    sprintf(temp,"%0.2f",temperature);
    sprintf(humi,"%0.3f",humidity);
    sprintf(ap,"%d",air_pressure);
    sprintf(device_num,"%d",device_number);
    json_object * jobj = json_object_new_object();
    json_object *jph = json_object_new_string(ph);
    json_object *jtemp = json_object_new_string(temp);
    json_object *jhumi = json_object_new_string(humi);
    json_object *jap = json_object_new_string(ap);
    json_object *jdevice_num = json_object_new_string(device_num);
    json_object *jtimestamp = json_object_new_string(timestamp());
    json_object_object_add(jobj,"device_id", jdevice_num);
    json_object_object_add(jobj,"timestamp", jtimestamp);
    json_object_object_add(jobj,"temperature", jtemp);
    json_object_object_add(jobj,"humidity", jhumi);
    json_object_object_add(jobj,"air_pressure", jap);
    json_object_object_add(jobj,"ph", jph);
    char* json_to_cstyle = json_object_to_json_string(jobj);
    return json_to_cstyle;
}

char* data_two(){
    // char* data = "data_2";
    // return data;
    float distance;
    distance = (rand()%((int)100))+0.00000;
    int device_number=2;
    char dist[32],device_num[10],switch_state;
    if((rand()%((int)5))<=(int)5){
        switch_state="ON";
    }else{
        switch_state="OFF";
    }
    sprintf(dist,"%0.2f",distance);
    sprintf(device_num,"%d",device_number);
    json_object * jobj = json_object_new_object();
    json_object *jdistance = json_object_new_string(dist);
    json_object *jdevice_num = json_object_new_string(device_num);
    json_object *jswitch_state = json_object_new_string(&switch_state);
    json_object *jtimestamp = json_object_new_string(timestamp());
    json_object_object_add(jobj,"device_id", jdevice_num);
    json_object_object_add(jobj,"timestamp", jtimestamp);
    json_object_object_add(jobj,"distance", jdistance);
    json_object_object_add(jobj,"switch_state", jswitch_state);
    char* json_to_cstyle = json_object_to_json_string(jobj);
    return json_to_cstyle;
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
    // printf("%s\n",sensor_data);
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
    // printf("in thread number %s\n",sensor_data);
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
    char data[50][256];
    for(int i=0;i<50;i++){
        sprintf(data[i],"%s",data_bot(i));
        // printf("%s\n",data[i]);
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