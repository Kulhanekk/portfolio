#!/usr/bin/env python3

from gpiozero import PWMOutputDevice
from picamera2 import Picamera2
import cv2
import numpy as np
import time
import datetime

#Motor pins
leftBackward = PWMOutputDevice(17, frequency=1000)  #right
leftFowar = PWMOutputDevice(27, frequency=1000)

rightBackward = PWMOutputDevice(24, frequency=1000) #left
rightFoward = PWMOutputDevice(23, frequency=1000)

#PWM duty cycle
speed = 0.3

#PID const
Kp = 0.003
Ki = 0.00001
Kd = 0.004

prev_error = 0
integral = 0

X = 3280
camera = Picamera2()
camera.preview_configuration.main.size = (X, 2464)
camera.preview_configuration.main.format = "RGB888"
camera.preview_configuration.controls.FrameRate = 20
camera.configure("preview")
camera.start()
time.sleep(0.1)

timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
video_path = f"video_{timestamp}.mp4"
frame_width = X
frame_height = 2464 * 2 // 3
fps = 20
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
video_writer = cv2.VideoWriter(video_path, fourcc, fps, (frame_width, frame_height))

try:
    while True:
        frame = camera.capture_array()
        frame = frame[frame.shape[0] // 3:, :] #We just need lower 2/3 of the image so the camera doesnt see the wheels
        video_writer.write(frame)

        gray = cv2.cvtColor(frame, cv2.COLOR_RGB2GRAY)
        blur = cv2.GaussianBlur(gray, (5, 5), 0)
        _, thresh = cv2.threshold(blur, 100, 255, cv2.THRESH_BINARY_INV)
        mask = cv2.erode(thresh, None, iterations=2)
        mask = cv2.dilate(mask, None, iterations=2)

        contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if contours:
            c = max(contours, key=cv2.contourArea)
            M = cv2.moments(c)
            if M["m00"] != 0:
                cx = int(M["m10"] / M["m00"])
                print(f"Centroid X: {cx}")

                #PID algorithm
                error = (X / 2) - cx
                integral += error
                derivative = error - prev_error
                correction = Kp * error + Ki * integral + Kd * derivative
                prev_error = error

                #Dead zone so the robot can go straight
                max_correction = 0.25
                correction = max(-max_correction, min(max_correction, correction))

                if correction > 0:
                    left_speed = speed - correction
                    right_speed = speed
                else:
                    left_speed = speed
                    right_speed = speed + correction

                left_speed = max(0, min(1, left_speed))
                right_speed = max(0, min(1, right_speed))

                leftBackward.value = 0
                leftFowar.value = left_speed
                rightBackward.value = 0
                rightFoward.value = right_speed

                print(f"error={error:.2f}, correction={correction:.4f}, L={left_speed:.2f}, R={right_speed:.2f}")
            else:
                leftBackward.value = 0
                leftFowar.value = 0
                rightBackward.value = 0
                rightFoward.value = 0
                print("No centroid, stopped")
        else:
            #no contours found
            leftBackward.value = 0
            leftFowar.value = 0
            rightBackward.value = 0
            rightFoward.value = 0
            print("No contours, stopped")

except KeyboardInterrupt:
    print("\nKeyboard interrupt.")

finally:
    print("Stoping the motors and saving video")
    video_writer.release()
    leftBackward.value = 0
    leftFowar.value = 0
    rightBackward.value = 0
    rightFoward.value = 0
    leftBackward.close()
    leftFowar.close()
    rightBackward.close()
    rightFoward.close()
    cv2.destroyAllWindows()
