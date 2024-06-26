# 猫耳を活気づけて ("Animated Cat Ears")

## TODO List
### new
  - [x] 1. Switch to eps8266-rtos-sdk :skull:
    - [x] 1.1. merge new project with the old repo(stop using platformio, use idf.py instead).
    - [x] 1.2. determine what components i need to implement.
  - [ ] 2. Implement components
    - [x] 2.1. Poses (see poses.cpp)
    - [x] 2.2. Servo output (PWM)
    - [ ] 2.3. SPI
    - [ ] 2.4. FFT
    - [ ] 2.5. That Magic part of pose selection i still have no idea how to implement
    - [ ] 2.6. Kalman Filter
    - [ ] 2.7. Attitude + Gyroscope rotation to angle adjustment
    - [ ] 2.8. \[optional\] Add thermometer or utilise the built-in one for temperature-dependent reactions
  - [ ] 3. Hardware 
    - [ ] 3.1. Find a way to fix Axles (Büroklammern) in place
    - [ ] 3.2. Wire second AMS1117 on the prototyping board
    - [ ] 3.3. Model all the hardware into the CAD project
    - [ ] 3.4. Make a board in KiCAD (most definitely for a PCB manufacturer)
    - [ ] 3.5. Decide on the Fur
  - [ ] 4. Misc
    - [ ] 4.1. Clean up README (make it actually readable)

### old
- [ ] Hardware 
  - [x] general structure (Hinges, servo placement and Head-to-ears connection) - still have to think where to put that paperclip wire.
  - [ ] Microcontroller & IMU
    - [x] Choose the IMU and MCU - it looks like ESP8266 has not enough umpf to read data, do 3 ffts on that data and send the result to serial. I want to use RPi0W and ESP8266, as RPi has only 2 PWM outputs. 
      - MCU: NodeMcuv2 (ESP8266) for servo control, RPi0W for data processing.
      - IMU: GY-91 IMU Board through SPI (MPU9250, BMP280) 6 Axis Gyro+Accelerometer, 3 Axis Magnetometer AK8963, Temperature and Pressure sensor BMP280
    - [x] change Voltage regulator to ams1117 
    - [ ] Make a power distribution board (2 ams1117 in parallel for 3 small servos)
    - [ ] Model all hardware into the Project (uncluding headband, CU usw)
  - [ ] Fluff (Fur) - [this?](https://www.amazon.de/WLLHYF-zotteligen-flauschige-Stuhlabdeckung-Weihnachten/dp/B0BJKKF45H) (a combination of white & black? pink insides?)

- [ ] Software
  - [x] Poses 
    - [x] List of poses 
    - [x] Poses as map of pose codes to desired_angle variables.
  - [x] IMU Data
    - [x] Find a Library (depends on hardware IMU)
      - [hideakitai/MPU9250](https://github.com/hideakitai/MPU9250) - with what appears to be a Kalman Filter.
      - [MPU9250_asukiaaa](https://github.com/asukiaaa/MPU9250_asukiaaa) - Library that can return raw data, i am using it right now.
    - [x] Get raw IMU data
    - [ ] Kalman Filter for attitude aquisition (there was already a lib for that, might just use it. although i need raw data for FFT)
    - [ ] How to detect the direction of a movement? From averaged Kalman Filter data?
  - [ ] IMU Data processing
    - [x] FFT  
    - [ ] IMU Data samples to compare to
    - [ ] Temperature and/or dTemp/dTime dependent reactions?

## 1.2.1 RTOS Task graph
```mermaid
graph TD;
A[Task: 
  Read data from SPI] -- IMU data --> B[Task: 
  Perform FFT];
A -- IMU data--> C[Task: 
  use Kalman Filter];
B -- Peaks: 
Magnitude, Frequency --> D[Task: 
  decide on Pose
  choose_pose
  adjust angles]
C --Attitude--> D;
A -- IMU data--> D;
D --servo angles--> E[Task:
  set pwm duty];
```

## 1.2.2 Compute schema
```mermaid
graph TD;
A[Accelerometer] --> KF[[Kalman Filter]] ;
KF --> C[Attitude];
B[Gyroscope] --> KF;

C --> D[Attitude dependent Position];
B --> E[Response to Rotation];
D --> F[Ear::set_ear_position];
E--> F;
F --> G[Ear::move_to_set_angles];

A --FFT--> I[Acceleration Spectrum];
I --> J[Determine Peaks and their Magnitude];
B --FFT--> K[Rotation Spectrum];
K --> L[Determine Peaks and their Magnitude];
L --> M[Compare with predefined Values];
J --> M;
M --> N[choose_pose];
N --> G;
```

## 2.1 List of poses
```text
 # | pose                               | ear left            | ear right           |
   | direction | opennnes               | left | main | right | left | main | right |
---|-----------|------------------------|---------------------|---------------------|
20 | sides     | fully open             | 106  | 90   | 26    | 106  | 90   | 26    |
21 | sides     | fully closed           | 0    | 90   | 132   | 0    | 90   | 132   |
22 | sides     | half open              | 53   | 90   | 79    | 53   | 90   | 79    |
23 | sides     | half closed to forward | 132  | 90   | 132   | 0    | 90   | 0     |
24 | sides     | half closed to back    | 0    | 90   | 0     | 132  | 90   | 132   |
---|-----------|------------------------|---------------------|---------------------|
10 | forward   | fully open             | 106  | 30   | 26    | 106  | 150  | 26    |
12 | forward   | half open              | 53   | 30   | 79    | 53   | 150  | 79    |
13 | forward   | half closed to inside  | 132  | 30   | 132   | 0    | 150  | 0     |
14 | forward   | half closed to outside | 0    | 30   | 0     | 132  | 150  | 132   |
---|-----------|------------------------|---------------------|---------------------|
31 | back      | fully closed           | 0    | 180  | 132   | 0    | 0    | 132   |
33 | back      | half closed to inside  | 0    | 180  | 0     | 132  | 0    | 132   |
34 | back      | half closed to outside | 132  | 180  | 132   | 0    | 0    | 0     |
---|-----------|------------------------|---------------------|---------------------|
and some intermediates
```
Note:
First digit: Ears direction
  - 1 - Forward
  - 2 - Sides 
  - 3 - Back

Second digit: Ears opennnes
  - 0 - fully open 
  - 1 - fully closed
  - 2 - half open
  - 3 - half closed to inside
  - 4 - half closed to outside

## 3.3 [CAD Model](https://cad.onshape.com/documents/12e9aba77e87c6321bec619e/w/794df45025b857e20fcdd77e/e/3349def638c04338ac328868?renderMode=0&uiState=658ed7810e636f5b707b00f6)

### servos
#### 2g servos
Brand:Surpass Hobby
S0002P 2g plastic gear digital servo
Voltage: 3.7\~4.2V DC
Torque *:≥0.4kgf·cm at 4.2V
Speed * : ≤0.06sec/60° at 4.2V
Operating Angle: 180°±10°(500\~2500μs)
Mechanical limit Angle: 360°
Weight: 2.2 g
Size: 16.7 × 8.2 × 17mm
Shell material: ABS
Motor type: hollow cup motor

#### 9g servos
TowerPro sg90 (i guess knock-offs)
