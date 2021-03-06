import subprocess
import smtplib
import socket
import datetime
import sys
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

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

message = MIMEMultipart()

# Read path to image from arguments
imagePath = ""
for argument in range(1, len(sys.argv)):
	imagePath += str(sys.argv[argument])

# attach preamble to message with current time
message.preamble = "Photo @ " + imagePath

# Open file and attach it to the mail
imageFile = open(imagePath, 'rb')
image = MIMEImage(imageFile.read(), _subtype="jpg")
imageFile.close()
message.attach(image)

# Subject + Date
message['Subject'] = 'Message from Raspberry Pi - %s' % currentDate.strftime('%d %b %Y')

# Sender
message['From'] = sender

#Receiver
message['To'] = receiver

# Send Email
smtpserver.sendmail(sender, [receiver], message.as_string())
smtpserver.quit()