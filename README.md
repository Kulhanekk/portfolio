# Portfolio

Hi, I'm Jan, a Master's student of Open Informatics (Computer Engineering) at CTU Prague (ČVUT FEL).
My background is in embedded systems and the Internet of Things.

[LinkedIn](https://linkedin.com/in/jan-kulhanek79) · [Email](mailto:jan.kulhanek79@gmail.com)

## Bachelor's Thesis

### Electronic Organizer for Students

![ElOrg](https://github.com/Kulhanekk/portfolio/main/bach/back_angle.jpg)
![ElOrgBoard](https://github.com/Kulhanekk/portfolio/blob/main/bach/board_running.jpg)
 
A pocket-sized, battery-powered e-paper device that helps students stay focused. It combines a Pomodoro-style timer for planning work and relaxation, a list of short-term goals, phone notification mirroring and an encrypted password manager. Data is sent to it over Bluetooth Low Energy. I built prototype with the processor and display integrated on a single custom PCB.
 
Firmware was written for the ESP32-C3 with ESP-IDF and FreeRTOS. Open-source e-paper library was adapted for the platform.

**Tech:** `ESP32-C3` · `ESP-IDF` · `FreeRTOS` · `Bluetooth LE` · `E-paper` · `PCB design` · `AES-256`


<!-- ## Personal Projects

### [Project name]

[One or two sentences: what it does and why you built it.]

**Tech:** `Python` · `[...]`
[Source code](https://github.com/Kulhanekk/REPO/tree/main/personal/project-name)

### [Project name]

[One or two sentences.]

**Tech:** `C++` · `[...]`
[Source code](https://github.com/Kulhanekk/REPO/tree/main/personal/project-name) -->


## School Projects

### Parallel MST of Edit Distances (C++ / OpenMP)
 
Given thousands of variable-length records, find the cheapest way to link them all together by similarity. I parallelised both stages of the pipeline with OpenMP: the all-pairs edit distance computation and a dense-graph version of Prim's algorithm. The edit distance stage uses load-balanced scheduling, thread-private rolling buffers and the symmetry of the distance matrix, and Prim's algorithm uses a parallel arg-min reduction.
 
**Tech:** `C++` · `OpenMP` · `Dynamic programming` · `Graph algorithms`
 [Source code](https://github.com/Kulhanekk/portfolio/tree/master/datastorage)


### Line-Following Robot
 
![Line-following robot](https://raw.githubusercontent.com/Kulhanekk/portfolio/master/lineFollowingRobot/robot.jpg)
 
A robot that drives through a line maze on its own and records the run. A Raspberry Pi 4 camera picks out the black line against a white background using OpenCV contour detection, and a PID controller turns the line's position into commands for the two LEGO Mindstorms 9842 motors, driven through an L298N dual H-bridge. The chassis uses custom 3D-printed LEGO-compatible mounts for the Raspberry Pi and batteries. Built as the main assignment of the *Laboratory of Applied Electronics and Control* course (summer semester 2025).
 
**Tech:** `Python` · `OpenCV` · `Raspberry Pi 4` · `PID control` · `L298N`
[Details and source code](https://github.com/Kulhanekk/portfolio/tree/master/lineFollowingRobot)

### Warehouse Box Placement
 
Finds the best way to distribute boxes of different weights across a warehouse whose rooms form a binary tree connected by hallways with travel times. Boxes are placed one by one under placement rules, and an exhaustive backtracking search tries every valid arrangement. It minimises the weight imbalance between neighbouring rooms first and, among equally balanced layouts, the total travel time. Written in C with manual memory management.
 
**Tech:** `C` · `Backtracking` · `Binary trees` · `Dynamic memory`
[Source code](https://github.com/Kulhanekk/portfolio/tree/master/warehouse)

## Skills

- **Languages:** C, C++, C#, Python
- **Tools:** Git, soldering
