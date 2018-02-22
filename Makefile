PATH = ./LucaHome/LucaHome/
APIPATH = /var/www/api/lucahome/
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
	rm -rf /etc/default/lucahome/
	rm -fv /bin/lucahome
	rm -fv $(APIPATH)

install:
	mkdir /etc/default/lucahome/
	mkdir /var/www/api/
	mkdir $(APIPATH)

	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d

	cp ./python/mail.py /etc/default/lucahome/mail.py
	cp ./python/mailWithCustomAddress.py /etc/default/lucahome/mailWithCustomAddress.py
	cp ./python/mailWithImage.py /etc/default/lucahome/mailWithImage.py

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

	chmod 777 /etc/default/lucahome/mail.py
	chmod 777 /etc/default/lucahome/mailWithCustomAddress.py
	chmod 777 /etc/default/lucahome/mailWithImage.py
	chmod 777 /etc/default/lucahome
	
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
