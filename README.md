# 猫耳を活気づけて (is supposed to say "Animated Cat Ears")

## Development Plan
- [ ] Hardware 
  - [x] general structure(Hinges, servo placement and Head-to-ears connection) - Revision might be needed
  - [ ] Microcontroller & IMU
    - [ ] Choose the IMU and MCU
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

### List of poses
#### and implementation tracker
- [ ] Up to the sides (Default) 
- [ ] Up Forward
- [ ] Low backwards
- [ ] Low to the sides 
