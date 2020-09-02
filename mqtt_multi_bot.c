#include <stdio.h>
#include <mosquitto.h>
#include <json-c/json.h>
#include <time.h>
#include <string.h>

char* timestamp(){
    time_t t;
    t=time(NULL);
    return asctime(localtime(&t));
}

void bot_type_1(int bot_number,char* sensor_data){                               // gets bot number and json object
    int val;
    struct mosquitto *mosq;
    mosquitto_lib_init();
    mosquitto_threaded_set(mosq,FALSE);
    mosq = mosquitto_new("publisher-device",true,NULL);
    val = mosquitto_connect(mosq,"localhost",1883,60);
    if(val!=0){
        printf("Not able to connect , Status %d Bot Number %d\n",val,bot_number);
    }
    char* bot_topic = "device/one" ;
    printf("%s\n",sensor_data);
    mosquitto_publish(mosq,NULL,bot_topic,strlen(sensor_data),sensor_data,1,false);
    mosquitto_disconnect(mosq);
    mosquitto_lib_cleanup();
}

char* data_type_1(float temperature,float humidity,int air_pressure, float potenz_hydrogen,int bot_number){            //temp-2,humidity-3, airpressure-int,ph-1
    char ph[10],temp[10],humi[10],ap[10],bot_num[10];
    sprintf(ph,"%0.1f",potenz_hydrogen);
    sprintf(temp,"%0.2f",temperature);
    sprintf(humi,"%0.3f",humidity);
    sprintf(ap,"%d",air_pressure);
    sprintf(bot_num,"%d",bot_number);
    json_object * jobj = json_object_new_object();
    json_object *jph = json_object_new_string(ph);
    json_object *jtemp = json_object_new_string(temp);
    json_object *jhumi = json_object_new_string(humi);
    json_object *jap = json_object_new_string(ap);
    json_object *jbot_num = json_object_new_string(bot_num);
    json_object *jtimestamp = json_object_new_string(timestamp());
    json_object_object_add(jobj,"device_id", jbot_num);
    json_object_object_add(jobj,"timestamp", jtimestamp);
    json_object_object_add(jobj,"temperature", jtemp);
    json_object_object_add(jobj,"humidity", jhumi);
    json_object_object_add(jobj,"air_pressure", jap);
    json_object_object_add(jobj,"ph", jph);
    char* json_to_cstyle = json_object_to_json_string(jobj);
    return json_to_cstyle;
}

int main(){
    //TODO:Add driver code
    bot_type_1(1,data_type_1(3000.25,25.345,56,6.7,1));
    return 0;
}