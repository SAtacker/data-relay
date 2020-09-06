<!--
*** Thanks for checking out this README Template. If you have a suggestion that would
*** make this better, please fork the data-relay and create a pull request or simply open
*** an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** github_username, data-relay, twitter_handle, shreyasatre16@gmail.com
-->





<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/SAtacker/data-relay">
    <img src="images/datarelay.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">YOUR_TITLE</h3>

  <p align="center">
    Simulation of multi-sensor data collection using MQTT and store a weeks data effectively using compression techniques.
    <br />
    <a href="https://docs.google.com/document/d/1wc0pirQ4sEeZ1fihhxVBe7xG68b0Yp4TOb3xVC2KwYY/edit?usp=sharing"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/SAtacker/data-relay">View Demo</a>
    ·
    <a href="https://github.com/SAtacker/data-relay/issues">Report Bug</a>
    ·
    <a href="https://github.com/SAtacker/data-relay/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
## Table of Contents

* [About the Project](#about-the-project)
  * [Built With](#built-with)
* [Getting Started](#getting-started)
  * [Prerequisites](#prerequisites)
* [Usage](#usage)
* [Roadmap](#roadmap)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)
* [Acknowledgements](#acknowledgements)

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




<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

This project focusses on the MQTT, Multithreading, Compression Algo and File I/O in C and C++


### Built With

* [Mosquitto](https://mosquitto.org/)
* [C++](https://en.wikipedia.org/wiki/C%2B%2B)
* [C](https://en.wikipedia.org/wiki/C_(programming_language))



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.

* mosquitto libs for ubuntu

```sh
sudo apt search mosquitto
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
```

* Now install libmosquittopp1 for C++(optional) and libmosquitto-dev for C 

### Usage

```sh
gcc src/sub_final.c -o sub_final -lmosquitto -ljson-c
gcc src/pub_final.c -o pub_final -lmosquitto -ljson-c -lpthread
g++ src/cpp_compression.cpp
```

* To run subscriber use `./sub_final` and for publisher use `./pub_final` 
Note: Run subscriber before publisher

* To compress the redundant data use `./a.out`

<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/SAtacker/data-relay/issues) for a list of proposed features (and known issues).


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes        (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch         (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Your Name - shreyasatre16@gmail.com

Project Link: [https://github.com/SAtacker/data-relay](https://github.com/SAtacker/data-relay)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [Saharsh Jain](https://github.com/saharshleo)
* [SRA-VJTI](https://github.com/SRA-VJTI)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/SAtacker/data-relay.svg?style=flat-square
[contributors-url]: https://github.com/SAtacker/data-relay/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/SAtacker/data-relay.svg?style=flat-square
[forks-url]: https://github.com/SAtacker/data-relay/network/members
[stars-shield]: https://img.shields.io/github/stars/SAtacker/data-relay.svg?style=flat-square
[stars-url]: https://github.com/SAtacker/data-relay/stargazers
[issues-shield]: https://img.shields.io/github/issues/SAtacker/data-relay.svg?style=flat-square
[issues-url]: https://github.com/SAtacker/data-relay/issues
[license-shield]: https://img.shields.io/github/license/SAtacker/data-relay.svg?style=flat-square
[license-url]: https://github.com/SAtacker/data-relay/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/atreshreyas
[product-screenshot]: images/screenshot.png
