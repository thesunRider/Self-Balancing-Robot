# Self Balancing Robot
#### This project does not use any stepper,This project works completely on BO DC motor

This is the most Simple Arduino based Simple Balancing Robot whose PID values were computed instead of the conventional hit and trial method, the gyro vs motor values were collected using HC-05 and fed to PID tuner to get exact PID values which were used in the project.

![bot](Images/Robot.jpeg?raw=true "bot")

## Installation

3d Print the model chassis provided and mount the components\
![mount](Images/motor_hold.png?raw=true "hold")
#### if more stability is needed consider printing a taller mount so that the COM is high,the current COM model is close to the ground
Use the package manager of arduino to install Necessary libraries :

```bash
TinyMPU6050
AutoPID
Kalman 
L293D
```

## Usage

![Fritzing model](Images/self_bb.png?raw=true "fritzing project")

Use motortester.ino to test Motor values and to find motor equalisation point ( the point at which both motors start to rotate) and add that offset. Set All pid's to zero.

Connect as per the circuit and Align the robot in a stable position and press the switch to record the angle which the robot should try to maintain. Now Record the data from HC-05 to a text file ,Now test the robot ,take the largest stablest oscillation readings,and discard the rest. Now feed the final text file to convert_piddata.ino to get a csv file which can be copy pasted to [pidtuner.com](pidtuner.com) to get PID values.




## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)