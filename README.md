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

## List of poses <sub>(and implementation tracker)</sub>
 ```
| pose                      | ear left     | ear right    | implemented? |
|                           | s1 | s2 | s3 | s1 | s2 | s3 |              |
|---------------------------|--------------|--------------|--------------|
| Middle to the sides (Def) | 90 | 90 | 90 | 90 | 90 | 90 | no           |
| Up Forward                |??? | ???|??? |??? |??? |??? | no           |
| Low backwards             |
| Low to the sides          |
```
