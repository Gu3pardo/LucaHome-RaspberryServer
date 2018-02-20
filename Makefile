SOURCE = ./LucaHome/LucaHome/main.cpp ./LucaHome/LucaHome/application/services/ApplicationInformationService.cpp ./LucaHome/LucaHome/application/services/ChangeService.cpp ./LucaHome/LucaHome/application/services/CoinService.cpp ./LucaHome/LucaHome/application/services/ContactService.cpp ./LucaHome/LucaHome/application/services/GpioService.cpp ./LucaHome/LucaHome/application/services/MapContentService.cpp ./LucaHome/LucaHome/application/services/MealService.cpp ./LucaHome/LucaHome/application/services/MediaServerService.cpp ./LucaHome/LucaHome/application/services/MeterLogService.cpp ./LucaHome/LucaHome/application/services/MoneyLogService.cpp ./LucaHome/LucaHome/application/services/MovieService.cpp ./LucaHome/LucaHome/application/services/PuckJsService.cpp ./LucaHome/LucaHome/application/services/RadioStreamService.cpp ./LucaHome/LucaHome/application/services/RoomService.cpp ./LucaHome/LucaHome/application/services/RssFeedService.cpp ./LucaHome/LucaHome/application/services/SecurityService.cpp ./LucaHome/LucaHome/application/services/ShoppingItemService.cpp ./LucaHome/LucaHome/application/services/SuggestedMealService.cpp ./LucaHome/LucaHome/application/services/SuggestedShoppingItemService.cpp ./LucaHome/LucaHome/application/services/TemperatureService.cpp ./LucaHome/LucaHome/application/services/UserService.cpp ./LucaHome/LucaHome/application/services/WirelessScheduleService.cpp ./LucaHome/LucaHome/application/services/WirelessSocketService.cpp ./LucaHome/LucaHome/application/services/WirelessSwitchService.cpp ./LucaHome/LucaHome/application/services/WirelessTimerService.cpp ./LucaHome/LucaHome/application/services/YoutubeVideoService.cpp ./LucaHome/LucaHome/crosscutting/crypto/Decrypter.cpp ./LucaHome/LucaHome/crosscutting/crypto/Encrypter.cpp ./LucaHome/LucaHome/crosscutting/utils/PiControl.cpp ./LucaHome/LucaHome/crosscutting/utils/Tools.cpp ./LucaHome/LucaHome/dataaccess/controller/FileController.cpp ./LucaHome/LucaHome/dataaccess/controller/MailController.cpp ./LucaHome/LucaHome/dataaccess/controller/PathController.cpp ./LucaHome/LucaHome/dataaccess/controller/SystemController.cpp ./LucaHome/LucaHome/dataaccess/databases/ApplicationInformationDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ChangeDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/CoinDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ContactDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/GpioDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MapContentDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MealDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MediaServerDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MeterLogItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/MoneyLogItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/PuckJsDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RadioStreamDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RoomDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/RssFeedDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/ShoppingItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/SuggestedMealDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/SuggestedShoppingItemDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/UserDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessScheduleDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessSocketDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessSwitchDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/WirelessTimerDatabase.cpp ./LucaHome/LucaHome/dataaccess/databases/YoutubeVideoDatabase.cpp ./LucaHome/LucaHome/domain/classes/ApplicationInformation.cpp ./LucaHome/LucaHome/domain/classes/Change.cpp ./LucaHome/LucaHome/domain/classes/Coin.cpp ./LucaHome/LucaHome/domain/classes/Contact.cpp ./LucaHome/LucaHome/domain/classes/Gpio.cpp ./LucaHome/LucaHome/domain/classes/MapContent.cpp ./LucaHome/LucaHome/domain/classes/Meal.cpp ./LucaHome/LucaHome/domain/classes/MediaServer.cpp ./LucaHome/LucaHome/domain/classes/MeterLogItem.cpp ./LucaHome/LucaHome/domain/classes/MoneyLogItem.cpp ./LucaHome/LucaHome/domain/classes/Movie.cpp ./LucaHome/LucaHome/domain/classes/Polyline.cpp ./LucaHome/LucaHome/domain/classes/Position.cpp ./LucaHome/LucaHome/domain/classes/PuckJs.cpp ./LucaHome/LucaHome/domain/classes/RadioStream.cpp ./LucaHome/LucaHome/domain/classes/Room.cpp ./LucaHome/LucaHome/domain/classes/RssFeed.cpp ./LucaHome/LucaHome/domain/classes/ShoppingItem.cpp ./LucaHome/LucaHome/domain/classes/SuggestedMeal.cpp ./LucaHome/LucaHome/domain/classes/SuggestedShoppingItem.cpp ./LucaHome/LucaHome/domain/classes/Temperature.cpp ./LucaHome/LucaHome/domain/classes/User.cpp ./LucaHome/LucaHome/domain/classes/WirelessSchedule.cpp ./LucaHome/LucaHome/domain/classes/WirelessSocket.cpp ./LucaHome/LucaHome/domain/classes/WirelessSwitch.cpp ./LucaHome/LucaHome/domain/classes/WirelessTask.cpp ./LucaHome/LucaHome/domain/classes/WirelessTimer.cpp ./LucaHome/LucaHome/domain/classes/YoutubeVideo.cpp
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

install:
	mkdir /etc/default/lucahome/
	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d
	cp ./python/mail.py /etc/default/lucahome/mail.py
	cp ./python/mailWithCustomAddress.py /etc/default/lucahome/mailWithCustomAddress.py
	cp ./python/mailWithImage.py /etc/default/lucahome/mailWithImage.py
	chmod 777 /etc/default/lucahome/mail.py
	chmod 777 /etc/default/lucahome/mailWithCustomAddress.py
	chmod 777 /etc/default/lucahome/mailWithImage.py
	chmod 777 /etc/default/lucahome
	update-rc.d lucahome defaults
