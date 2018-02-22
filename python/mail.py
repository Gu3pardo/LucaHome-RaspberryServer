import subprocess
import smtplib
import socket
import datetime
import sys

from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

# argument definitions
receiverIndex = 1
mailTypeIndex = 2
contentIndex = 3

MailTypeSimpleMessage = 0
MailTypeWithImage = 1

# account information to send the email
sender = 'TODO_YOUR_MAIL'
passphrase = 'TODO_YOUR_PASSPHRASE'

smtpserver = smtplib.SMTP('TODO_YOUR_PROVIDER', 587)
smtpserver.ehlo()
smtpserver.starttls()
smtpserver.ehlo

# Login for account
smtpserver.login(sender, passphrase)

# Get current date
currentDate = datetime.date.today()

# Data
message = MIMEText("Argument exception in mail.py")
mailData = ""

# read all arguments
receiver = str(sys.argv[receiverIndex])
mailType = sys.argv[mailTypeIndex]

if mailType == MailTypeSimpleMessage
	for argument in range(contentIndex, len(sys.argv)):
		mailData += str(sys.argv[argument])
		mailData += " "

	message = MIMEText(mailData)

elif mailType == MailTypeWithImage
	for argument in range(contentIndex, len(sys.argv)):
		mailData += str(sys.argv[argument])

	message = MIMEMultipart()

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