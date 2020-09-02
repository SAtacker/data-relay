#include <stdio.h>
#include <mosquitto.h>

int main(){
    int rc;
    struct mosquitto *mosq;
    mosquitto_lib_init();       // Initializes library
    mosq = mosquitto_new("publisher-test",true,NULL);     // Client ID, CleanSession? , auth by password/username
    rc = mosquitto_connect(mosq,"localhost",1883,60);      //Client instance , host name , portnumber, keepalive time
    if(rc!=0){
        printf("Client Cannot connect to broker %d\n",rc);
        mosquitto_destroy(mosq);
        return -1;
    }
    printf("we are now connected\n");
    mosquitto_publish(mosq,NULL,"test/t1",6,"Hello",0,false);                 // client instance, pointer to message id, topic,payload length in bytes,QoS,restrain?
    mosquitto_disconnect(mosq);
    mosquitto_lib_cleanup();
    return 0;
}