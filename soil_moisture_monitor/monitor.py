from serial import Serial
from time import sleep

arduino = None

def init():
    global arduino 
    arduino = Serial('/dev/ttyACM0')
    #make sure no data is waiting to be received
    arduino.flushInput()
    return

def read_moisture_level():
    arduino.flushInput()
    arduino.write('read')
    #wait 1s for response
    sleep(1)
    #parse response
    val = arduino.read(3)
    return val

init()
try:  
    while True:  
        print "Reading moisture value..."
        print read_moisture_level()
        sleep(10)

except KeyboardInterrupt:
    arduino.close()
    print "All done!"
