# wes237a-final-project
Final Project for WES237A class, UCSD WES Program, Winter 2023

# Contactless Health Monitoring System

![](img%5CThumbnail.png)

## What does the system do?

- Measures Patient Heart Rate
- Measures Patient Respiratory Activity 
- Measures Patient Temperature
- Detects Human Presence
- Detects Movement of Patient
- Detects Distance away from Patient
- Streams data values to AWS Cloud Server

![](img%5CWES237A-Presentation_v030.jpg)

## How does it work?

- 60GHz Radar module relies on CWFM Doppler Analysis 
to determine small displacements associated with 
heart beats and breathing.

![](img%5CWES237A-Presentation_v031.png)

- Infrared Temperature Sensor measures light intensity 
for wavelengths associated with infrared heat signatures.

![](img%5CWES237A-Presentation_v032.jpg)

- ToF Distance Sensor emits infrared light pulses, records the time
taken to detect reflections, and correlates time to distance value.

![](img%5CWES237A-Presentation_v033.jpg)

- PYNQ Z2 board joins sensor and networking functionality together 
to form a discrete health monitoring device


## Goals
- Create a functional contactless IoT health monitoring system using the Xilinx PYNQ Z2 board.

- Support ability to measure cardio, respiratory, and temperature data at a distance from a patient and produce health metrics visualizations in near real-time.

- Demonstrate and utilize concepts learned in WES 237A lab/lecture.


## WES 237A topics Used in Project

* **I/O**: Uses PYNQ Microblaze for GPIO Digital Write controls for 
RGB LED Module

* **Multi-Tasking**: Uses Python Multiprocessing library to run multiple 
concurrent data collection and socket connection routines for each 
sensor

* **Networking**: Uses multiple UDP connections and TCP connections to 
send data to Server

* **Sensors/Actuators/IoT**: Uses I2C communication protocol to obtain 
data from VL53L1XV2 ToF Distance and MLX90614ESF Temperature 
sensors

## System Overview

![](img%5CWES237A-Presentation_v034.png)

## Components Used

1. Xilinx PYNQ Z2 Board

2. Seeed Studio MR60BHA1 60 GHz mm Wave Sensor 
Onboard MCU processes radar signals and outputs UART messages containing cardio/respiratory health metrics

3. MLX90614 IR Temperature Sensor 
I2C and PWM compatible sensor
Supports measurements taken at 
	distances of ≤12cm

4. VL53L1X ToF Distance Sensor 
I2C compatible sensor
Supports accurate distance measurements 
	of up to 4 meters

## Radar Sensor Assembly - _(Shown Left to Right)_

![](img%5CWES237A-Presentation_v035.png)

1. Seeed Studio MR60BHA1 60GHz mmWave 
Radar Sensor 

2. USB to UART FTDI Adapter

3. Custom PCB - MR60BHA1-to-USB Adapter

![](img%5CWES237A-Presentation_v037.png)

**Note**: MR60BHA1 GP1 Pin IO Pin reports human presence detection via digital signal output (3.3V = Presence Detected / 0V = No Presence Detected)

![](img%5CWES237A-Presentation_v036.png)


## AWS EC2 Server

![](img%5CWES237A-Presentation_v038.jpg)

![](img%5CWES237A-Presentation_v039.png)

### Ubuntu 22.04
2 Cores vCPU
16 GB EBS Storage

__Services Hosted__:
- NodeRed
- InfluxDB
- Grafana

### AWS EC2 Server: NodeRed

![](img%5CWES237A-Presentation_v0310.png)

NodeJS based Flow Process Manager Application that facilitates data flow and network communications using an assortment of node modules:

- Debug Nodes - output data payloads to debug console
- UDP and TCP Port Nodes - host port communications
- HTTP Endpoint Node - supports HTTP-POST requests
- JS Function Nodes - Parse Received Data
- Influxdb Nodes - Forward Data into Database

![](img%5CWES237A-Presentation_v0311.png)

### AWS EC2 Server: Influxdb

![](img%5CWES237A-Presentation_v0312.png)

Open-source Timeseries Database optimized for IoT applications

- Manages Storage of data entries
- Hosts Retention Policy to maintain long-term data accumulation
- Incorporates Timestamp for each data entry
- Accessed by Grafana Service to support dashboard visualization

![](img%5CWES237A-Presentation_v0313.png)

### AWS EC2 Server: Grafana

![](img%5CWES237A-Presentation_v0314.png)

Data Visualization GUI and Dashboard Application 
Reads and displays sensor data from Influxdb Database

![](img%5CWES237A-Presentation_v0315.png)

## Issues

- MLX90614 Temperature Sensor
I2C Reading Errors
‘Errno 9 Socket Error Bad File 
	Descriptor’ with multiprocess

- VL53L1X ToF Distance Sensor Integration
I2C Device Detection Problems

- MR60BHA1 60GHz Radar Sensor 
Intermittent performance of presence
	detection pin 
Serial message querying problems

![](img%5CWES237A-Presentation_v0316.png)

## Next Steps

1. Spend more time troubleshooting I2C 
write/read steps on MLX90614 
Temperature Sensor

2. Integrate bidirectional communications 
between AWS Server and PYNQ Board

3. Introduce improvements in data filtering 
to improve accuracy

4. Have PYNQ board facilitate Push 
Notifications/Alerts based on health anomaly 
detection

5. Integrate IP Camera stream into Health 
Monitoring System

![](img%5CWES237A-Presentation_v0317.png)

# Contactless Health Monitoring System Demo

[www\.wes237a\.site:3000](https://www.youtube.com/watch?v=l8WjZGGD_Us)

1\. Login with credentials:

    __Username__ : test
    
    __Password__ : test

2\. Under  _Dashboards_ \, click on:

    __WES237A\-Final\-Project__

![](img%5CWES237A-Presentation_v0318.png)

