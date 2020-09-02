#include <iostream>
#include <thread>
#include <mosquittopp.h>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

void bot_type_1(void* data){
    char* sensor_data=(char*)data;
    struct mosquitto *mosq;
    mosquitto_threaded_set(mosq,true);
    mosq = mosquitto_new(NULL,true,NULL);
    int rc = mosquitto_connect(mosq,"localhost",1883,60);
    if(rc!=0){cout<<"Kuch gadbad hai\n";}
    if(mosquitto_publish(mosq,NULL,"device/one",strlen(sensor_data),sensor_data,1,false)!=MOSQ_ERR_SUCCESS){
        cout<<"mehhhh\n";
    }
    mosquitto_loop(mosq,10,10);
    mosquitto_disconnect(mosq);
    cout<<sensor_data<<"\n";
    getchar();
}

int main(){
    vector<thread> bots;
    char s[3][10];
    for(int i{};i<3;i++){
        sprintf(s[i],"%d",i);
        char* m= s[i];
        bots.emplace_back(thread(bot_type_1,m));
    }
    for(auto &th : bots){
        th.join();
    }
    return 0;
}