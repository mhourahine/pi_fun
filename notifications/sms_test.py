import os
from twilio.rest import TwilioRestClient

TWILIO_API_SID = os.environ["TWILIO_API_SID"]
TWILIO_API_TOKEN = os.environ["TWILIO_API_TOKEN"]

client = TwilioRestClient(TWILIO_API_SID, TWILIO_API_TOKEN)

client.messages.create(
    to = '+14162942040',
    from_ = '+16474927726',
    body = 'Alert from python!',
)
                              
