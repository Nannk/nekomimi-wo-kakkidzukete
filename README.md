# 猫耳を活気づけて (is supposed to say "Animated Cat Ears")

## Development Plan
- [ ] Hardware 
  - [x] general structure(Hinges, servo placement and Head-to-ears connection) - Revision is needed asa new servos arrive + make more space so the moving part doesnt touch the servo housing. Small servos are not powerful enough.
  - [ ] Microcontroller & IMU
    - [ ] Choose the IMU and MCU 
      - MCU: Arduino Nano / ESP8266
      - IMU: MPU6050 through i²c
    - [ ] placement
    - [ ] Connection
  - [ ] Fluff (Fur) - [this?](https://www.amazon.de/WLLHYF-zotteligen-flauschige-Stuhlabdeckung-Weihnachten/dp/B0BJKKF45H) (a combination of white & black? pink insides?) how to attach?

- [ ] Software
  - [ ] Poses 
    - [ ] List of poses 
    - [ ] Poses as sideffects functions (move servos to predefined angle values)
  - [ ] IMU Data
    - [ ] Find a Library (depends on hardware IMU)
      - [ElectronicCats/MPU6050](https://github.com/ElectronicCats/mpu6050)
    - [ ] Get raw IMU data (through Library)
    - [ ] Kalman Filter for attitude aquisition
  - [ ] IMU Data processing (AI or a bunch of threshholds)

## List of poses <sub>(and implementation tracker)</sub>
```
int | pose                                | ear left             | ear right            | done? | tested
    | direction | opennnes                | left  | main | right | left  | main | right |       |
----|-----------|-------------------------|----------------------|----------------------|-------|--------
20  | sides     | fully open              | 106   | 0    | -106  | 106   | 0    | -106  | no    |
21  | sides     | fully closed            | 0     | 0    | 0     | 0     | 0    | 0     | no    |
22  | sides     | half open               | 53    | 0    | -53   | 53    | 0    | -53   | no    |
23  | sides     | half closed to forward  | 132.5 | 0    | 0     | 0     | 0    | 132.5 | no    |
24  | sides     | half closed to back     | 0     | 0    | -132.5| 132.5 | 0    | 0     | no    |
----|-----------|-------------------------|----------------------|----------------------|-------|--------
10  | forward   | fully open              | 106   | -90  | -106  | 106   | 90   | -106  | no    |
12  | forward   | half open               | 53    | -90  | -53   | 53    | 90   | -53   | no    |
13  | forward   | half closed to inside   | 132.5 | -90  | 0     | 0     | 90   | -132.5| no    |
14  | forward   | half closed to outside  | 0     | -90  | -132.5| -132.5| 90   | 0     | no    |
----|-----------|-------------------------|----------------------|----------------------|-------|--------
31  | back      | fully closed            | 0     | 60   | 0     | 0     | -60  | 0     | no    |
33  | back      | half closed to inside   | 132.5 | 60   | 0     | 0     | -60  | -132.5| no    |
34  | back      | half closed to outside  | 0     | 60   | -132.5| -132.5| -60  | 0     | no    |
----|-----------|-------------------------|----------------------|----------------------|-------|--------
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
## Servo Rotation

Rotational direction of main servo is correct 
```
0 <-------> 180
    servo 
    shaft
```
view from top of the ear (bottom of the servo)

RRservo is inverted
RLservo is inverted

I guess the LR and LL servos are inverted too (cant check bc those servos dont work)


