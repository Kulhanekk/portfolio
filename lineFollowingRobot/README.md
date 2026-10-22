### Line following robot task
![robot](https://github.com/Kulhanekk/myCodes/blob/master/lineFollowingRobot/robot.jpg)
#### Basic information
- This was an assigment in one of my courses during summer semester of 2025.
- Course name is **Laboratory of applied electronics and control**. LAR for short.
- The course is built around the idea of broadening horizons by solving tasks.
- There were several assigments during the first half of the course just to grasp   basic understanding of working with electronis and Raspberry pi 4.
- In the second half of the course the task was to build a line following robot.
  
#### Assigment
- Line following robot uses rpi camera to determine the contrast between the black line and white background.
-  We are using custom 3D printed LEGO compatable mounts with batteries to power the raspberry and eletrical lego motors.
- The task is to go through the line maze and record the ride using built in camera.

#### Conclusion
- We decided to use **l298n dual h-bridge motor driver** for the Lego Mindstorm 9842 motors.
![l298n](https://github.com/Kulhanekk/myCodes/blob/master/lineFollowingRobot/l298n.png)
- The program was build around the PID algorithm.
- Using the cv4 library we found the contour and based on it's location the robot decided whitch motor to power up.
