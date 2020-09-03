#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>
#include <string.h>
// gcc sub_final.c -o sub_final -lmosquitto -ljson-c
void write_data(const char *data,char* fname){
    FILE *fptr;
    fptr = fopen(fname,"a");
    if(fputs(data,fptr) && fputs("\n",fptr)){
        // printf("fine\n");
    }else{
        printf("error\n");
    }
    fclose(fptr);
}

void get_data(char* data){
    struct json_object *jobj,*jtemp,*jhumi,*jid,*jtime,*jap,*jph,*jdis,*jswitch;
    jobj = json_tokener_parse(data);
	// printf("%s\n", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
    json_object_object_get_ex(jobj,"temperature",&jtemp);
    const char *temp = json_object_to_json_string(jtemp);
    json_object_object_get_ex(jobj,"device_id",&jid);
    const char *id = json_object_to_json_string(jid);
    json_object_object_get_ex(jobj,"humidity",&jhumi);
    const char *humi = json_object_to_json_string(jhumi);
    json_object_object_get_ex(jobj,"timestamp",&jtime);
    const char *time = json_object_to_json_string(jtime);
    json_object_object_get_ex(jobj,"air_pressure",&jap);
    const char *ap = json_object_to_json_string(jap);
    json_object_object_get_ex(jobj,"ph",&jph);
    const char *ph = json_object_to_json_string(jph);
    json_object_object_get_ex(jobj,"distance",&jdis);
    const char *dis = json_object_to_json_string(jdis);
    json_object_object_get_ex(jobj,"switch_state",&jswitch);
    const char *swi = json_object_to_json_string(jswitch);
    if(strcmp(temp,"null")){
        printf("%s %s %s %s %s %s\n",id,time,temp,humi,ap,ph);                                                                  //json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY)
        write_data(temp,"data/device1/temperature.txt");
        write_data(humi,"data/device1/humidity.txt");
        write_data(time,"data/device1/time.txt");
        write_data(ap,"data/device1/air_pressure.txt");
        write_data(ph,"data/device1/ph.txt");
        // FILE *fptr;
        // fptr = fopen("data/temperature.txt","a");
        // if(fputs(temp,fptr) && fputs("\n",fptr)){
        //     // printf("fine\n");
        // }else{
        //     printf("error\n");
        // }
        // fclose(fptr);

    }else{
        printf("%s %s %s %s\n",id,time,dis,swi);
        write_data(dis,"data/device2/distance.txt");
        write_data(swi,"data/device2/switch_state.txt");
    }
    // To check if 50 bots publish data
    // static int count=0;
    // count++;
    // if(count==50)
    // printf("Yay\n");
}

void handle_connect(struct mosquitto *mosq, void *obj,int rc){
    // printf("%d",(int*) obj);
    if(rc!=0){
        printf("Error code %d\n",rc);
        exit(-1);
    }
    char* topic = "device/+";
    mosquitto_subscribe(mosq,NULL,topic,1);
}

void handle_msg(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    // printf("Received Message\n %s \n",(char*)message->payload);  
    get_data((char*)(message->payload))  ;
    
}

int main(){
    struct mosquitto *mosq;
    mosquitto_lib_init();
    char* id="subscriber-device";
    mosq = mosquitto_new(id,true,NULL);
    mosquitto_connect_callback_set(mosq,handle_connect);
    mosquitto_message_callback_set(mosq,handle_msg);
    int val = mosquitto_connect(mosq,"localhost",1883,60);
    if(val!=0){
        printf("some error %d",val);
    }
    printf("press enter to stop\n");
    mosquitto_loop_start(mosq);
    getchar();
    mosquitto_disconnect(mosq);
    mosquitto_lib_cleanup();
    return 0;
} 