# LucaHome-RaspberryServer

[![Platform](https://img.shields.io/badge/platform-Raspberry-blue.svg)](https://www.raspberrypi.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
<a target="_blank" href="https://www.paypal.me/GuepardoApps" title="Donate using PayPal"><img src="https://img.shields.io/badge/paypal-donate-blue.svg" /></a>

[![Build](https://img.shields.io/badge/build-passing-green.svg)](https://github.com/Gu3pardo/LucaHome-RaspberryServer)
[![Version](https://img.shields.io/badge/version-v4.0.5.170724-blue.svg)](https://github.com/Gu3pardo/LucaHome-RaspberryServer)

Part of the LucaHome-Project

Small server running on a raspberry to control your home.
Remotely controlled by an android application (https://github.com/GuepardoApps/LucaHome-AndroidApplication)

# Installation

Webserver (optional)
```
pi@raspberrypi ~ $ apt-get update
pi@raspberrypi ~ $ sudo apt-get install nginx php5-fpm php5-cgi php5-cli php5-common
pi@raspberrypi ~ $ sudo useradd www-data
pi@raspberrypi ~ $ sudo groupadd www-data
pi@raspberrypi ~ $ sudo usermod -g www-data www-data
pi@raspberrypi ~ $ sudo mkdir /var/www
pi@raspberrypi ~ $ sudo chmod 775 /var/www -R
pi@raspberrypi ~ $ sudo chown www-data:www-data /var/www 
```

Change some settings in
```
pi@raspberrypi ~ $ sudo vi /etc/nginx/sites-enabled/default 
```
to following settings:
```
server {
listen 80;
root /var/www;
index index.html index.php;
server_name localhost;
location / {
try_files $uri $uri/ /index.php?$args;
}
location ~ \.php$ {
try_files $uri =404;
fastcgi_pass unix:/var/run/php5-fpm.sock;
fastcgi_index index.php;
fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
include fastcgi_params;
} 
```
Restart server
```
pi@raspberrypi ~ $ sudo /etc/init.d/nginx restart 
```

Install WiringPi (IMPORTANT!)
```
pi@raspberrypi ~ $ wget http://raspberrypiguide.de/stuff/wiringPi-27afc01.tar.gz
pi@raspberrypi ~ $ tar xfz wiringPi-27afc01.tar.gz
pi@raspberrypi ~ $ cd wiringPi-27afc01
pi@raspberrypi ~/wiringPi-27afc01 $ ./build 
```

Now you are ready to install LucaHome to your raspberry
- first download sourcecode and copy it to your raspberry (e.g. to your home directory (lucahome)
- you have to cd into the directory you copied the sourcecode to
```
pi@raspberrypi ~/lucahome $ sudo make clean
pi@raspberrypi ~/lucahome $ sudo make
pi@raspberrypi ~/lucahome $ sudo make install
pi@raspberrypi ~/lucahome $ sudo /etc/init.d/LucaHome start 
```

# IMPORTANT

following project is also needed to work with the android application
https://github.com/GuepardoApps/LucaHome-Website
The code of this project needs to be copied to /var/www

optional:
https://github.com/GuepardoApps/LucaHome-RaspberryTemperatureLogger

for the CAMERA module (working with motion!)
https://www.pcwelt.de/ratgeber/Mit_dem_Raspberry_Pi_die_Wohnung_ueberwachen-Sicherheit-8638548.html

---

![alt tag](https://github.com/GuepardoApps/LucaHome-RaspberryServer/blob/master/screenshots/img001.png)

---

Based on the original project of http://raspberrypiguide.de/howtos/powerpi-raspberry-pi-haussteuerung/
