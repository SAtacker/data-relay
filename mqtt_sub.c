#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>

void handle_connect(struct mosquitto *mosq, void *obj,int rc){
    printf("%d",(int*) obj);
    if(rc!=0){
        printf("Error code %d\n",rc);
        exit(-1);
    }
    char* topic = "device/one";
    mosquitto_subscribe(mosq,NULL,topic,1);
}

void handle_msg(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
    printf("Received Message\n %s \n",(char*)message->payload);    
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
    printf("press enter to stop");
    mosquitto_loop_start(mosq);
    getchar();
    mosquitto_disconnect(mosq);
    mosquitto_lib_cleanup();
    return 0;
}