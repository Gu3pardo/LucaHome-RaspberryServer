# LucaHome-RaspberryServer

[![Platform](https://img.shields.io/badge/platform-Raspberry-blue.svg)](https://www.raspberrypi.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
<a target="_blank" href="https://www.paypal.me/GuepardoApps" title="Donate using PayPal"><img src="https://img.shields.io/badge/paypal-donate-blue.svg" /></a>

[![Build](https://img.shields.io/badge/build-WIP-red.svg)](https://github.com/Gu3pardo/LucaHome-RaspberryServer/tree/develop)
[![Version](https://img.shields.io/badge/version-v6.0.0.180222alpha2-blue.svg)](https://github.com/Gu3pardo/LucaHome-RaspberryServer/tree/develop)

Part of the LucaHome-Project

Small server running on a raspberry to control your home.
Remotely controlled by an android application (https://github.com/GuepardoApps/LucaHome-AndroidApplication)

# Installation

## Required

### Sqlite3
If Sqlite3 or the devlibs are not installed, install them first:
```
sudo apt-get install sqlite3 libsqlite3-dev
```
This post is very helpful: https://stackoverflow.com/questions/28969543/fatal-error-sqlite3-h-no-such-file-or-directory

### WiringPi
If wiringpi is not installed, install this too:
Check this link: http://wiringpi.com/download-and-install/
```
git clone git://git.drogon.net/wiringPi
cd ~/wiringPi
git pull origin
./build
```
Check if the installation worked well:
```
gpio -v
gpio readall
```

### Webserver
```
sudo apt-get update
sudo apt-get install nginx php5-fpm php5-cgi php5-cli php5-common
sudo useradd www-data
sudo groupadd www-data
sudo usermod -g www-data www-data
sudo mkdir /var/www
sudo chmod 775 /var/www -R
sudo chown www-data:www-data /var/www 
```

Change some settings in
```
sudo vi /etc/nginx/sites-enabled/default 
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

Restart the nginx webserver
```
sudo /etc/init.d/nginx restart 
```

### Motion
For the camera and security module (using the motion library) please try below link or search with your prefered search engine... ;)
https://www.pcwelt.de/ratgeber/Mit_dem_Raspberry_Pi_die_Wohnung_ueberwachen-Sicherheit-8638548.html

### Finalize

Now you are ready to install LucaHome to your raspberry
- first download sourcecode and copy it to your raspberry (e.g. to your home directory (lucahome)
- you have to cd into the directory you copied the sourcecode to
```
sudo make clean
sudo make
sudo make install
sudo /etc/init.d/LucaHome start 
```

## Optional

https://github.com/GuepardoApps/LucaHome-RaspberryTemperatureLogger

# Origin
Based on the original project of http://raspberrypiguide.de/howtos/powerpi-raspberry-pi-haussteuerung/