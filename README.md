# 猫耳を活気づけて (is supposed to say "Animated Cat Ears")

## Development Plan
- [ ] Hardware 
  - [x] general structure(Hinges, servo placement and Head-to-ears connection) - Revision might be needed
  - [ ] Microcontroller & IMU
    - [ ] Choose the IMU and MCU
    MCU: Arduino Nano / ESP8266
    IMU: MPU6050 through i²c
    - [ ] placement
    - [ ] Connection


- [ ] Software
  - [ ] Poses 
    - [ ] List of poses 
    - [ ] Poses as sideffects functions (move servos to predefined angle values)
  - [ ] IMU Data
    - [ ] Find a Library (depends on hardware IMU)
    - [ ] Raw IMU data
    - [ ] Kalman Filter for attitude aquisition
  - [ ] IMU Data processing (AI or a bunch of threshholds)

## List of poses <sub>(and implementation tracker)</sub>
```
pose                     | ear left            | ear right           | done? 
direction | opennnes     | left | main | right | left | main | right |       
----------|--------------|---------------------|---------------------|-------
sides     | fully open   | 106  | 0    | -106  | 106  | 0    | -106  | no    
sides     | fully closed | 0    | 0    | 0     | 0    | 0    | 0     | no    
sides     | half open    | 
sides     |
sides     |
forward   | fully open   | 106  | -90  | -106  | 106  | 90   | -106  | no    
forward   |
forward   |
forward   |
back      | fully closed | 0    | 60   | 0     | 0    | -60  | 0     | no    
back      |
back      |
back      |
```

[CAD Model](https://cad.onshape.com/documents/12e9aba77e87c6321bec619e/w/794df45025b857e20fcdd77e/e/3349def638c04338ac328868?renderMode=0&uiState=658ed7810e636f5b707b00f6)
