PATH = ./LucaHome/LucaHome/
APIPATH = /var/www/api/lucahome/
LUCAHOMEPATH = /etc/default/lucahome/
DBPATH = $(LUCAHOMEPATH)databases/

SOURCE = $(PATH)main.cpp $(PATH)application/services/ApplicationInformationService.cpp $(PATH)application/services/ChangeService.cpp $(PATH)application/services/CoinService.cpp $(PATH)application/services/ContactService.cpp $(PATH)application/services/GpioService.cpp $(PATH)application/services/MapContentService.cpp $(PATH)application/services/MealService.cpp $(PATH)application/services/MediaServerService.cpp $(PATH)application/services/MeterLogService.cpp $(PATH)application/services/MoneyLogService.cpp $(PATH)application/services/MovieService.cpp $(PATH)application/services/PuckJsService.cpp $(PATH)application/services/RadioStreamService.cpp $(PATH)application/services/RoomService.cpp $(PATH)application/services/RssFeedService.cpp $(PATH)application/services/SecurityService.cpp $(PATH)application/services/ShoppingItemService.cpp $(PATH)application/services/SuggestedMealService.cpp $(PATH)application/services/SuggestedShoppingItemService.cpp $(PATH)application/services/TemperatureService.cpp $(PATH)application/services/UserService.cpp $(PATH)application/services/WirelessScheduleService.cpp $(PATH)application/services/WirelessSocketService.cpp $(PATH)application/services/WirelessSwitchService.cpp $(PATH)application/services/WirelessTimerService.cpp $(PATH)application/services/YoutubeVideoService.cpp $(PATH)crosscutting/crypto/Decrypter.cpp $(PATH)crosscutting/crypto/Encrypter.cpp $(PATH)crosscutting/utils/PiControl.cpp $(PATH)crosscutting/utils/Tools.cpp $(PATH)dataaccess/controller/FileController.cpp $(PATH)dataaccess/controller/MailController.cpp $(PATH)dataaccess/controller/PathController.cpp $(PATH)dataaccess/controller/SystemController.cpp $(PATH)dataaccess/databases/ApplicationInformationDatabase.cpp $(PATH)dataaccess/databases/ChangeDatabase.cpp $(PATH)dataaccess/databases/CoinDatabase.cpp $(PATH)dataaccess/databases/ContactDatabase.cpp $(PATH)dataaccess/databases/GpioDatabase.cpp $(PATH)dataaccess/databases/MapContentDatabase.cpp $(PATH)dataaccess/databases/MealDatabase.cpp $(PATH)dataaccess/databases/MediaServerDatabase.cpp $(PATH)dataaccess/databases/MeterLogItemDatabase.cpp $(PATH)dataaccess/databases/MoneyLogItemDatabase.cpp $(PATH)dataaccess/databases/PuckJsDatabase.cpp $(PATH)dataaccess/databases/RadioStreamDatabase.cpp $(PATH)dataaccess/databases/RoomDatabase.cpp $(PATH)dataaccess/databases/RssFeedDatabase.cpp $(PATH)dataaccess/databases/ShoppingItemDatabase.cpp $(PATH)dataaccess/databases/SuggestedMealDatabase.cpp $(PATH)dataaccess/databases/SuggestedShoppingItemDatabase.cpp $(PATH)dataaccess/databases/UserDatabase.cpp $(PATH)dataaccess/databases/WirelessScheduleDatabase.cpp $(PATH)dataaccess/databases/WirelessSocketDatabase.cpp $(PATH)dataaccess/databases/WirelessSwitchDatabase.cpp $(PATH)dataaccess/databases/WirelessTimerDatabase.cpp $(PATH)dataaccess/databases/YoutubeVideoDatabase.cpp $(PATH)domain/classes/ApplicationInformation.cpp $(PATH)domain/classes/Change.cpp $(PATH)domain/classes/Coin.cpp $(PATH)domain/classes/Contact.cpp $(PATH)domain/classes/Gpio.cpp $(PATH)domain/classes/MapContent.cpp $(PATH)domain/classes/Meal.cpp $(PATH)domain/classes/MediaServer.cpp $(PATH)domain/classes/MeterLogItem.cpp $(PATH)domain/classes/MoneyLogItem.cpp $(PATH)domain/classes/Movie.cpp $(PATH)domain/classes/Point.cpp $(PATH)domain/classes/PuckJs.cpp $(PATH)domain/classes/RadioStream.cpp $(PATH)domain/classes/Room.cpp $(PATH)domain/classes/RssFeed.cpp $(PATH)domain/classes/ShoppingItem.cpp $(PATH)domain/classes/SuggestedMeal.cpp $(PATH)domain/classes/SuggestedShoppingItem.cpp $(PATH)domain/classes/Temperature.cpp $(PATH)domain/classes/User.cpp $(PATH)domain/classes/WirelessSchedule.cpp $(PATH)domain/classes/WirelessSocket.cpp $(PATH)domain/classes/WirelessSwitch.cpp $(PATH)domain/classes/WirelessTask.cpp $(PATH)domain/classes/WirelessTimer.cpp $(PATH)domain/classes/YoutubeVideo.cpp
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
	rm -fv $(LUCAHOMEPATH)mail.py
	rm -fv $(APIPATH)

install:
	mkdir $(LUCAHOMEPATH)
	mkdir $(DBPATH)
	mkdir /var/www/api/
	mkdir $(APIPATH)
	
	chmod 777 $(LUCAHOMEPATH)
	chmod 777 $(DBPATH)
	chmod 777 $(APIPATH)

	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d

	cp ./python/mail.py $(LUCAHOMEPATH)mail.py
	chmod 777 $(LUCAHOMEPATH)mail.py

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
