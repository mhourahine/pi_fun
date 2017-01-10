import os
from serial import Serial
from time import sleep
from slackclient import SlackClient
from time import gmtime, strftime

arduino = None      #serial object
slack = None        #slack object
THRESHOLD = 920     #"dry" soil reading (from experimentation) 

def slack_init():
    #initialize slack connection
    global slack
    slack_token = os.environ["SLACK_API_TOKEN"]
    slack = SlackClient(slack_token)
    return

def slack_notify(msg, channel):
    slack.api_call("chat.postMessage",channel=channel,text=msg)
    return

def timestamp():
    return strftime("%a, %d %b %Y %H:%M:%S +0000", gmtime())
    

def serial_init():
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
    return int(val)

serial_init()
slack_init()
try:  
    while True:  
        print timestamp() + " - Reading moisture value..."
        level = read_moisture_level()
        print level

        if (level > THRESHOLD):
            print "Plant is dry.  Notifying Slack."
            slack_notify("Time to water the plants!","#notifications")

        #wait 15min between readings
        sleep(900)

except KeyboardInterrupt:
    arduino.close()
    print "All done!"
