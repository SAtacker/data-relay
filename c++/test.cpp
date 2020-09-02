#include <iostream>
#include <thread>
#include <mosquittopp.h>
#include <string>
#include <vector>
using namespace std;

void test(string s){
    cout<<"this is thread number "<<s<<endl;
}

int main(){
    vector<thread> bots;
    for(int i{};i<50;i++){
        bots.emplace_back(thread(test,to_string(i)));
    }
    for(auto &th : bots){
        th.join();
    }
    return 0;
}