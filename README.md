# Data Relay
Simulation of multi-sensor data collection using [MQTT](https://en.wikipedia.org/wiki/MQTT) and store a weeks data effectively using compression techniques.
* View the revison [documentation](https://docs.google.com/document/d/1wc0pirQ4sEeZ1fihhxVBe7xG68b0Yp4TOb3xVC2KwYY/edit?usp=sharing)

```
├── c++                                                                                 // For future implementation in c++
│   ├── mosquitto_client.cpp
│   └── test.cpp
├── LICENSE                                                                             // License
├── misc testing                                                                        // Testing mqtt mosquitto lib
│   ├── mqtt_multi_bot.c
│   └── mqttTest.c
├── README.md                                                                           // This file
├── src                                                                                 // Main Code
│   ├── compression.c                                                                   // Future implementation of lzw in C
│   ├── cpp_compression.cpp                                                             // Current C++ implementation of LZW
│   ├── data
│   │   ├── compressed                                                                  // Compressed data
│   │   │   └── device1
│   │   │       ├── decompressed_temperature.txt                                        // Decomressed temperature.txt using cpp_comression
│   │   │       └── temperature.txt                                                     // Compressed version of data/device1/temperature.txt
│   │   ├── device1                                                                     // Data generated due to sub_final.c
│   │   │   ├── air_pressure.txt
│   │   │   ├── humidity.txt
│   │   │   ├── ph.txt
│   │   │   ├── temperature.txt
│   │   │   └── time.txt
│   │   └── device2                                                                     // Data generated due to sub_final.c
│   │       ├── distance.txt
│   │       └── switch_state.txt
│   ├── pub_final.c                                                                     // Publisher code
│   └── sub_final.c                                                                     // Subscriber code
└── testing threads                                                                     // Some basic thread learning,not to be bothered
    ├── threaded_bots.c
    ├── threaded.c
    └── threaded_pub.c
```