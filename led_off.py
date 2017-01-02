#!/usr/bin/python
import RPi.GPIO as GPIO

def lights_on():
	GPIO.output(17, GPIO.HIGH)
	GPIO.output(27, GPIO.HIGH)
	return



def lights_off():
	GPIO.output(17, GPIO.LOW)
	GPIO.output(27, GPIO.LOW)
	return

def setup():
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	GPIO.cleanup()
	GPIO.setup(17, GPIO.OUT)
	GPIO.setup(27, GPIO.OUT)
	return

setup()
lights_off()
