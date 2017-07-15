import subprocess
import smtplib
import socket
import datetime
import sys
from email.mime.text import MIMEText

# account information to send the email
receiver = 'YOUR_RECEIVER'
sender = 'YOUR_MAIL'
passphrase = 'YOUR_PASSPHRASE'

smtpserver = smtplib.SMTP('YOUR_PROVIDER', 587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo

# Login for account
smtpserver.login(sender, passphrase)

# Get current date
currentDate = datetime.date.today()

# Data
mailData = ""

# read all arguments and store in a string
for argument in range(1, len(sys.argv)):
	mailData += str(sys.argv[argument])
	mailData += " "

message = MIMEText(mailData)

# Subject + Date
message['Subject'] = 'Message from Raspberry Pi - %s' % currentDate.strftime('%d %b %Y')

# Sender
message['From'] = sender

#Receiver
message['To'] = receiver

# Send Email
smtpserver.sendmail(sender, [receiver], message.as_string())
smtpserver.quit()