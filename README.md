# 猫耳を活気づけて ("Animated Cat Ears")

## TODO List
- [ ] Hardware 
  - [x] general structure (Hinges, servo placement and Head-to-ears connection) - needs testing.
  - [ ] Microcontroller & IMU
    - [x] Choose the IMU and MCU 
      - MCU: NodeMcuv2 (ESP8266)
      - IMU: GY-91 IMU Board through SPI (MPU9250, BMP280) 6 Axis Gyro+Accelerometer, 3 Axis Magnetometer AK8963, Temperature and Pressure sensor BMP280
    - [ ] placement
    - [ ] Connection
    - [ ] change Voltage regulator to ams1117 - Need 2 for all 4 small servos => make a board
  - [ ] Fluff (Fur) - [this?](https://www.amazon.de/WLLHYF-zotteligen-flauschige-Stuhlabdeckung-Weihnachten/dp/B0BJKKF45H) (a combination of white & black? pink insides?) how to attach?

- [ ] Software
  - [x] Poses 
    - [x] List of poses 
    - [x] Poses as sideffects functions (move servos to predefined angle values) - better set desired_angle variable so that it can be modified later depending on the IMU Data.
  - [x] IMU Data
    - [x] Find a Library (depends on hardware IMU)
      - [hideakitai/MPU9250](https://github.com/hideakitai/MPU9250)
    - [x] Get raw IMU data (through Library)
    - [ ] Kalman Filter for attitude aquisition (there was already a lib for that, might just use it. although i need raw data for FFT)
    - [ ] How to detect the direction of a movement? From averaged Kalman Filter data?
  - [ ] IMU Data processing
    - [x] FFT  
    - [ ] IMU Data samples to compare to
    - [ ] Temperature and/or dTemp/dTime dependent reactions?

## List of poses <sub>(and implementation tracker)</sub>
```
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

[CAD Model](https://cad.onshape.com/documents/12e9aba77e87c6321bec619e/w/794df45025b857e20fcdd77e/e/3349def638c04338ac328868?renderMode=0&uiState=658ed7810e636f5b707b00f6)

## servos

### 2g servos
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

### 9g servos
TowerPro sg90 (i guess knock-offs)
