import requests
import json
import os

# For incoming webhook details, see https://api.slack.com/incoming-webhooks

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


slack_notify("This is a test.", "#notifications")
