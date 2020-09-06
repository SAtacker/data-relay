#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

string decode_lzw(vector<int> compressed) {
    int dictSize = 256;
    map<int,string> dictionary;
    for (int i = 0; i < 256; i++)dictionary[i] = string(1, i);
    string w(1, compressed[0]);
    string result = w;
    string entry;
    for (auto begin=compressed.begin()+1 ;begin!= compressed.end(); begin++) {
        int k = *begin;
        if (dictionary.count(k))
            entry = dictionary[k];
        else if (k == dictSize)
            entry = w + w[0];
        else
            cout<<"Bad compressed \n";

        result += entry;
        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }
    return result;
}

vector<int> encode_lzw(string s) {
    // cout<<s;
    vector<int> result;
    int dictSize = 256;
    map<string,int> dictionary;
    for (int i = 0; i < 256; i++)
    dictionary[string(1, i)] = i;
    string w;
    for (auto it = s.begin();it != s.end(); ++it) {
        char c = *it;
        string wc = w + c;
        if (dictionary.count(wc))
            w = wc;
        else {
            // cout<<dictionary[w]<<" "<<w<<"\n";
            result.push_back(dictionary[w]);
            dictionary[wc] = dictSize++;
            w = string(1, c);
        }
    }
    if (!w.empty())
    result.push_back(dictionary[w]);
    return result;
}

void func(string to_compress,string compress_destination,string decompress_destination){
    ifstream ipt;
    ipt.open(to_compress,ios::in);
    if(ipt.is_open()){
        string line;
        string data="";
        while (getline(ipt,line)){
            data+=line+"\n";
        }
        ipt.close();
        vector<int> cmpressed=encode_lzw(data);
        string decomp = decode_lzw(cmpressed);
        cout<<"\n"<<decomp<<"\n";
        ofstream cmpr(compress_destination,ios::out);
        if(cmpr.is_open()){
            cout<<"File is being stored\n";
            for(int i{};i<cmpressed.size();i++){
                cout<<cmpressed[i]<<"\n";
                cmpr<<cmpressed[i]<<"\n";
            }
            cmpr.close();
        }
        else{
            cout<<"Some error in storing compressed files\n";
        }
        cout<<"\nSame from file\n";
        ipt.open(compress_destination,ios::in);
        if(ipt.is_open()){
            cout<<"Opening and decompressing file\n";
            string line;
            vector<int> encoded;
            while(getline(ipt,line)){
                for(int i{};i<line.length()-1;i+=2){
                    cout<<line[i];
                }
                cout<<"\n";
                encoded.push_back(stoi(line));
            }
            ipt.close();
            cout<<"data acquired\n";
            cout<<"decompressing\n";
            ofstream opt;
            opt.open(decompress_destination,ios::out);
            opt<<decode_lzw(encoded);
            opt.close();
            cout<<decode_lzw(encoded);
            cout<<"\ndecoded\n";
        }
        else{
            cout<<"Some error opening compressed file\n";
        }
    }
    else{
        cout<<"File Opening Error\n";
    }
}

int main(){
    cout<<"Oh yeah"<<"\n";
    int turn=0;
    while (true)
    {
        func("data/device1/temperature.txt","data/compressed/device1/temperature.txt","data/compressed/device1/decomp_temperature.txt");
        func("data/device1/humidity.txt","data/compressed/device1/humidity.txt","data/compressed/device1/decomp_humidity.txt");
        func("data/device1/ph.txt","data/compressed/device1/ph.txt","data/compressed/device1/decomp_ph.txt");
        func("data/device1/air_pressure.txt","data/compressed/device1/air_pressure.txt","data/compressed/device1/decomp_air_pressure.txt");
        func("data/device1/time.txt","data/compressed/device1/time.txt","data/compressed/device1/decomp_time.txt");
        func("data/device2/distance.txt","data/compressed/device2/distance.txt","data/compressed/device2/decomp_distance.txt");
        func("data/device2/switch_state.txt","data/compressed/device2/switch_state.txt","data/compressed/device2/decomp_switch_state.txt");
        cout<<"\n======================================================================\n";
        cout<<"Seeping for 60 sec"<<" | Turn number "<<(++turn)<<" is done";
        cout<<"\n======================================================================\n";
        sleep(60);
    }
    return 0;
}