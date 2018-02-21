PATH = ./LucaHome/LucaHome/
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
	rm -fv /var/www/api/lucahome.php

install:
	mkdir /etc/default/lucahome/
	mkdir /var/www/api/
	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d
	cp ./python/mail.py /etc/default/lucahome/mail.py
	cp ./python/mailWithCustomAddress.py /etc/default/lucahome/mailWithCustomAddress.py
	cp ./python/mailWithImage.py /etc/default/lucahome/mailWithImage.py
	cp ./api/lucahome.php /var/www/api/lucahome.php
	chmod 777 /etc/default/lucahome/mail.py
	chmod 777 /etc/default/lucahome/mailWithCustomAddress.py
	chmod 777 /etc/default/lucahome/mailWithImage.py
	chmod 777 /etc/default/lucahome
	chmod 777 /var/www/api/lucahome.php
	update-rc.d lucahome defaults
