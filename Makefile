APIPATH = /var/www/api/lucahome/
DBPATH = /etc/default/lucahome/databases/
SOURCE = ./LucaHome/LucaHome/main.cpp ./LucaHome/LucaHome/application/services/ApplicationInformationService.cpp ./LucaHome/LucaHome/application/services/ChangeService.cpp ./LucaHome/LucaHome/application/services/CoinService.cpp ./LucaHome/LucaHome/application/services/ContactService.cpp ./LucaHome/LucaHome/application/services/GpioService.cpp ./LucaHome/LucaHome/application/services/HandshakeService.cpp ./LucaHome/LucaHome/application/services/MapContentService.cpp ./LucaHome/LucaHome/application/services/MealService.cpp ./LucaHome/LucaHome/application/services/MediaServerService.cpp ./LucaHome/LucaHome/application/services/MeterLogService.cpp ./LucaHome/LucaHome/application/services/MoneyLogService.cpp ./LucaHome/LucaHome/application/services/MovieService.cpp ./LucaHome/LucaHome/application/services/PuckJsService.cpp ./LucaHome/LucaHome/application/services/RadioStreamService.cpp ./LucaHome/LucaHome/application/services/RoomService.cpp ./LucaHome/LucaHome/application/services/RssFeedService.cpp ./LucaHome/LucaHome/application/services/SecurityService.cpp ./LucaHome/LucaHome/application/services/ShoppingItemService.cpp ./LucaHome/LucaHome/application/services/SuggestedMealService.cpp ./LucaHome/LucaHome/application/services/SuggestedShoppingItemService.cpp ./LucaHome/LucaHome/application/services/TemperatureService.cpp ./LucaHome/LucaHome/application/services/UserService.cpp ./LucaHome/LucaHome/application/services/WirelessScheduleService.cpp ./LucaHome/LucaHome/application/services/WirelessSocketService.cpp ./LucaHome/LucaHome/application/services/WirelessSwitchService.cpp ./LucaHome/LucaHome/application/services/WirelessTimerService.cpp ./LucaHome/LucaHome/application/services/YoutubeVideoService.cpp ./LucaHome/LucaHome/crosscutting/crypto/Decrypter.cpp ./LucaHome/LucaHome/crosscutting/crypto/Encrypter.cpp ./LucaHome/LucaHome/crosscutting/utils/PiControl.cpp ./LucaHome/LucaHome/crosscutting/utils/Tools.cpp ./LucaHome/LucaHome/crosscutting/controller/FileController.cpp ./LucaHome/LucaHome/crosscutting/controller/MailController.cpp ./LucaHome/LucaHome/crosscutting/controller/PathController.cpp ./LucaHome/LucaHome/crosscutting/controller/SystemController.cpp ./LucaHome/LucaHome/dataaccess/databases/ApplicationInformationDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ChangeDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/CoinDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ContactDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/GpioDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MapContentDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MealDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MediaServerDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MeterLogItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MoneyLogItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/PuckJsDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RadioStreamDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RoomDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RssFeedDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ShoppingItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/SuggestedMealDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/SuggestedShoppingItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/UserDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessScheduleDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessSocketDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessSwitchDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessTimerDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/YoutubeVideoDatabase.cpp ./LucaHome/LucaHome/domain/classes/ApplicationInformation.cpp ./LucaHome/LucaHome/domain/classes/Change.cpp ./LucaHome/LucaHome/domain/classes/Coin.cpp ./LucaHome/LucaHome/domain/classes/Contact.cpp ./LucaHome/LucaHome/domain/classes/Gpio.cpp ./LucaHome/LucaHome/domain/classes/MapContent.cpp ./LucaHome/LucaHome/domain/classes/Meal.cpp ./LucaHome/LucaHome/domain/classes/MediaServer.cpp ./LucaHome/LucaHome/domain/classes/MeterLogItem.cpp ./LucaHome/LucaHome/domain/classes/MoneyLogItem.cpp ./LucaHome/LucaHome/domain/classes/Movie.cpp ./LucaHome/LucaHome/domain/classes/Point.cpp ./LucaHome/LucaHome/domain/classes/PuckJs.cpp ./LucaHome/LucaHome/domain/classes/RadioStream.cpp ./LucaHome/LucaHome/domain/classes/Room.cpp ./LucaHome/LucaHome/domain/classes/RssFeed.cpp ./LucaHome/LucaHome/domain/classes/ShoppingItem.cpp ./LucaHome/LucaHome/domain/classes/SuggestedMeal.cpp ./LucaHome/LucaHome/domain/classes/SuggestedShoppingItem.cpp ./LucaHome/LucaHome/domain/classes/Temperature.cpp ./LucaHome/LucaHome/domain/classes/User.cpp ./LucaHome/LucaHome/domain/classes/WirelessSchedule.cpp ./LucaHome/LucaHome/domain/classes/WirelessSocket.cpp ./LucaHome/LucaHome/domain/classes/WirelessSwitch.cpp ./LucaHome/LucaHome/domain/classes/WirelessTask.cpp ./LucaHome/LucaHome/domain/classes/WirelessTimer.cpp ./LucaHome/LucaHome/domain/classes/YoutubeVideo.cpp
INCLUDES = -lsqlite3 -lwiringPi -lpthread
APP = ./bin/lucahome
CC = g++ -std=c++11

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) $(INCLUDES) -o $(APP)

clean:
	rm -fv ./bin/*
	update-rc.d -f lucahome remove
	rm -fv /etc/init.d/lucahome/
	rm -fv /bin/lucahome
	rm -fv /etc/default/lucahome/mail.py
	rm -fv $(APIPATH)

install:
	mkdir /etc/default/lucahome/
	mkdir $(DBPATH)
	mkdir /var/www/api/
	mkdir $(APIPATH)
	
	chmod 777 /etc/default/lucahome/
	chmod 777 $(DBPATH)
	chmod 777 $(APIPATH)

	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d

	cp ./python/mail.py /etc/default/lucahome/mail.py
	chmod 777 /etc/default/lucahome/mail.py

	cp ./databases/ApplicationInformation.db $(DBPATH)ApplicationInformation.db
	cp ./databases/Change.db $(DBPATH)Change.db
	cp ./databases/Coin.db $(DBPATH)Coin.db
	cp ./databases/Contact.db $(DBPATH)Contact.db
	cp ./databases/Gpio.db $(DBPATH)Gpio.db
	cp ./databases/MapContent.db $(DBPATH)MapContent.db
	cp ./databases/Meal.db $(DBPATH)Meal.db
	cp ./databases/MediaServer.db $(DBPATH)MediaServer.db
	cp ./databases/MeterLog.db $(DBPATH)MeterLog.db
	cp ./databases/MoneyLog.db $(DBPATH)MoneyLog.db
	cp ./databases/PuckJs.db $(DBPATH)PuckJs.db
	cp ./databases/RadioStream.db $(DBPATH)RadioStream.db
	cp ./databases/Room.db $(DBPATH)Room.db
	cp ./databases/RssFeed.db $(DBPATH)RssFeed.db
	cp ./databases/Security.db $(DBPATH)Security.db
	cp ./databases/ShoppingItem.db $(DBPATH)ShoppingItem.db
	cp ./databases/SuggestedMeal.db $(DBPATH)SuggestedMeal.db
	cp ./databases/SuggestedShoppingItem.db $(DBPATH)SuggestedShoppingItem.db
	cp ./databases/User.db $(DBPATH)User.db
	cp ./databases/WirelessSchedule.db $(DBPATH)WirelessSchedule.db
	cp ./databases/WirelessSocket.db $(DBPATH)WirelessSocket.db
	cp ./databases/WirelessSwitch.db $(DBPATH)WirelessSwitch.db
	cp ./databases/WirelessTimer.db $(DBPATH)WirelessTimer.db
	cp ./databases/YoutubeVideo.db $(DBPATH)YoutubeVideo.db
	
	chmod 777 $(DBPATH)ApplicationInformation.db
	chmod 777 $(DBPATH)Change.db
	chmod 777 $(DBPATH)Coin.db
	chmod 777 $(DBPATH)Contact.db
	chmod 777 $(DBPATH)Gpio.db
	chmod 777 $(DBPATH)MapContent.db
	chmod 777 $(DBPATH)Meal.db
	chmod 777 $(DBPATH)MediaServer.db
	chmod 777 $(DBPATH)MeterLogItem.db
	chmod 777 $(DBPATH)MoneyLogItem.db
	chmod 777 $(DBPATH)PuckJs.db
	chmod 777 $(DBPATH)RadioStream.db
	chmod 777 $(DBPATH)Room.db
	chmod 777 $(DBPATH)RssFeed.db
	chmod 777 $(DBPATH)Security.db
	chmod 777 $(DBPATH)ShoppingItem.db
	chmod 777 $(DBPATH)SuggestedMeal.db
	chmod 777 $(DBPATH)SuggestedShoppingItem.db
	chmod 777 $(DBPATH)User.db
	chmod 777 $(DBPATH)WirelessSchedule.db
	chmod 777 $(DBPATH)WirelessSocket.db
	chmod 777 $(DBPATH)WirelessSwitch.db
	chmod 777 $(DBPATH)WirelessTimer.db
	chmod 777 $(DBPATH)YoutubeVideo.db

	cp ./api/ApplicationInformation/controller.php $(APIPATH)ApplicationInformation/controller.php
	cp ./api/Change/controller.php $(APIPATH)Change/controller.php
	cp ./api/Coin/controller.php $(APIPATH)Coin/controller.php
	cp ./api/Contact/controller.php $(APIPATH)Contact/controller.php
	cp ./api/Gpio/controller.php $(APIPATH)Gpio/controller.php
	cp ./api/MapContent/controller.php $(APIPATH)MapContent/controller.php
	cp ./api/Meal/controller.php $(APIPATH)Meal/controller.php
	cp ./api/MediaServer/controller.php $(APIPATH)MediaServer/controller.php
	cp ./api/MeterLogItem/controller.php $(APIPATH)MeterLogItem/controller.php
	cp ./api/MoneyLogItem/controller.php $(APIPATH)MoneyLogItem/controller.php
	cp ./api/Movie/controller.php $(APIPATH)Movie/controller.php
	cp ./api/PuckJs/controller.php $(APIPATH)PuckJs/controller.php
	cp ./api/RadioStream/controller.php $(APIPATH)RadioStream/controller.php
	cp ./api/Room/controller.php $(APIPATH)Room/controller.php
	cp ./api/RssFeed/controller.php $(APIPATH)RssFeed/controller.php
	cp ./api/Security/controller.php $(APIPATH)Security/controller.php
	cp ./api/ShoppingItem/controller.php $(APIPATH)ShoppingItem/controller.php
	cp ./api/SuggestedMeal/controller.php $(APIPATH)SuggestedMeal/controller.php
	cp ./api/SuggestedShoppingItem/controller.php $(APIPATH)SuggestedShoppingItem/controller.php
	cp ./api/Temperature/controller.php $(APIPATH)Temperature/controller.php
	cp ./api/User/controller.php $(APIPATH)User/controller.php
	cp ./api/WirelessSchedule/controller.php $(APIPATH)WirelessSchedule/controller.php
	cp ./api/WirelessSocket/controller.php $(APIPATH)WirelessSocket/controller.php
	cp ./api/WirelessSwitch/controller.php $(APIPATH)WirelessSwitch/controller.php
	cp ./api/WirelessTimer/controller.php $(APIPATH)WirelessTimer/controller.php
	cp ./api/YoutubeVideo/controller.php $(APIPATH)YoutubeVideo/controller.php
	
	chmod 777 $(APIPATH)ApplicationInformation/controller.php
	chmod 777 $(APIPATH)Change/controller.php
	chmod 777 $(APIPATH)Coin/controller.php
	chmod 777 $(APIPATH)Contact/controller.php
	chmod 777 $(APIPATH)Gpio/controller.php
	chmod 777 $(APIPATH)MapContent/controller.php
	chmod 777 $(APIPATH)Meal/controller.php
	chmod 777 $(APIPATH)MediaServer/controller.php
	chmod 777 $(APIPATH)MeterLogItem/controller.php
	chmod 777 $(APIPATH)MoneyLogItem/controller.php
	chmod 777 $(APIPATH)Movie/controller.php
	chmod 777 $(APIPATH)PuckJs/controller.php
	chmod 777 $(APIPATH)RadioStream/controller.php
	chmod 777 $(APIPATH)Room/controller.php
	chmod 777 $(APIPATH)RssFeed/controller.php
	chmod 777 $(APIPATH)Security/controller.php
	chmod 777 $(APIPATH)ShoppingItem/controller.php
	chmod 777 $(APIPATH)SuggestedMeal/controller.php
	chmod 777 $(APIPATH)SuggestedShoppingItem/controller.php
	chmod 777 $(APIPATH)Temperature/controller.php
	chmod 777 $(APIPATH)User/controller.php
	chmod 777 $(APIPATH)WirelessSchedule/controller.php
	chmod 777 $(APIPATH)WirelessSocket/controller.php
	chmod 777 $(APIPATH)WirelessSwitch/controller.php
	chmod 777 $(APIPATH)WirelessTimer/controller.php
	chmod 777 $(APIPATH)YoutubeVideo/controller.php

	update-rc.d lucahome defaults
