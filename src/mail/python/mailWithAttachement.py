import subprocess
import smtplib
import socket
import datetime
import sys
from email.mime.text import MIMEText

# account information to send the email
Receiver = 'YOUR_RECEIVER'
Sender = 'YOUR_MAIL'
Passphrase = 'YOUR_PASSPHRASE'
smtpserver = smtplib.SMTP('YOUR_PROVIDER', 587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo

# Login for account
smtpserver.login(Sender, Passphrase)

# Get current date
Date = datetime.date.today()

message = MIMEText('New image from motion!')

# attach preamble to message with current time
f_time = datetime.now().strftime('%a %d %b @ %H:%M')
message.preamble = "Photo @ " + f_time

# Read path to image from arguments
imagePath = ""
for argument in range(1, len(sys.argv)):
	imagePath += str(sys.argv[argument])

# Open file and attach it to the mail
imageFile = open(imagePath, 'rb')
image = MIMEImage(imageFile.read())
imageFile.close()
message.attach(image)

# Subject + Date
message['Subject'] = 'Message from Raspberry Pi - %s' % Date.strftime('%d %b %Y')

# Sender
message['From'] = Sender

#Receiver
message['To'] = Receiver

# Send Email
smtpserver.sendmail(Sender, [Receiver], message.as_string())
smtpserver.quit()