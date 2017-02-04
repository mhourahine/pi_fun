import os
import requests
import json
from time import sleep, gmtime, strftime
from serial import Serial

arduino = None      #serial object
THRESHOLD = 920     #"dry" soil reading (from experimentation) 
isDry = False

try:
    SLACK_WEBHOOK_URL = os.environ["SLACK_WEBHOOK_URL"]
except KeyError:
    SLACK_WEBHOOK_URL = None
    print("""

WARNING - It looks like you haven't set up on your Slack Webhook 
URL yet. Make sure you set the SLACK_WEBHOOOK_URL environment 
variable with your configured webhook URL.

Example:  export SLACK_WEBHOOK_URL=https://hooks.slack.com/services/XXXXXXXXX/YYYYYYYYY/ZZZZZZZZZZZZZZZZZZZZZZZZ

        """)

def slack_notify(msg, channel):
    if SLACK_WEBHOOK_URL:
        payload = {
                "channel": channel,
                "username": "Plant Monitor", 
                "text": msg,
                "icon_emoji": ":herb:"
                }
        response = requests.post(SLACK_WEBHOOK_URL, data=json.dumps(payload))
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
try:  
    while True:  
        print timestamp() + " - Reading moisture value..."
        level = read_moisture_level()
        print level

        if (level > THRESHOLD):
            print "Plant is dry."
            if not isDry:
                print "Notifying Slack."
                slack_notify("Time to water me! - Your plants","#notifications")
            isDry = True
        else:
            if (isDry and level < THRESHOLD): 
                print "Plant has been watered."
                slack_notify("Ah thirst quenched. All is well again. Thanks!","#notifications")
                isDry = False

        #wait 60min between readings
        sleep(3600)

except KeyboardInterrupt:
    arduino.close()
    print "All done!"
