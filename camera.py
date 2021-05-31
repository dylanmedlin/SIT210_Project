import RPi.GPIO as GPIO
from picamera import PiCamera
import time
from datetime import datetime
import os
import paho.mqtt.publish as publish

os.chdir ("/home/pi/Pictures")

GPIO.setmode(GPIO.BCM)
PIR_PIN = 17
GPIO.setup(PIR_PIN, GPIO.IN)

camera = PiCamera()

try:
    time.sleep(5)
    print("Ready")

    while True:
        if GPIO.input(PIR_PIN):            
            print("Motion Detected!")
            publish.single("SecurityCamera/MotionDetected", "true", hostname="test.mosquitto.org")
            
            timestamp = time.strftime("%Y%m%d-%H%M%S")
            image_name = 'IMG_' + timestamp + '.jpg'
            time.sleep(2)
            camera.capture(image_name) #Take photo
            os.system("rclone copy /home/pi/Pictures camera:") #Send to dropbox
            
            time.sleep(5)
            print("Ready")

        time.sleep(1)

except KeyboardInterrupt:
    print("Quit")
    GPIO.cleanup()
