import RPi.GPIO as GPIO
from time import sleep
PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIN, GPIO.OUT)
  
try:  
    while True:  
        GPIO.output(PIN, 1)
        sleep(0.5)     
        GPIO.output(PIN, 0)
        sleep(0.5)       
  
except KeyboardInterrupt:
    GPIO.cleanup()
