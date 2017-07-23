SOURCE = ./src/lucahome.cpp ./src/common/dto/BirthdayDto.cpp ./src/common/dto/ChangeDto.cpp ./src/common/dto/CoinDto.cpp ./src/common/dto/GpioDto.cpp ./src/common/dto/InformationDto.cpp ./src/common/dto/ListedMenuDto.cpp ./src/common/dto/LogDto.cpp ./src/common/dto/MapContentDto.cpp ./src/common/dto/MenuDto.cpp ./src/common/dto/MovieDto.cpp ./src/common/dto/PointDto.cpp ./src/common/dto/ScheduleDto.cpp ./src/common/dto/ScheduleTaskDto.cpp ./src/common/dto/ShoppingEntryDto.cpp  ./src/common/dto/UserDto.cpp ./src/common/dto/WirelessSocketDto.cpp ./src/common/utils/Logger.cpp ./src/common/utils/PiControl.cpp ./src/common/utils/Tools.cpp ./src/controller/FileController.cpp ./src/controller/MailController.cpp ./src/controller/PathController.cpp ./src/services/shared/ChangeService.cpp ./src/services/xml/XmlParser.cpp ./src/services/xml/XmlService.cpp ./src/services/xml/XmlWriter.cpp ./src/services/AccessControlService.cpp ./src/services/AudioService.cpp ./src/services/AuthentificationService.cpp ./src/services/BirthdayService.cpp ./src/services/CameraService.cpp ./src/services/CoinService.cpp ./src/services/InformationService.cpp ./src/services/MapContentService.cpp ./src/services/MenuService.cpp ./src/services/MovieService.cpp ./src/services/ReceiverService.cpp ./src/services/RemoteService.cpp ./src/services/ShoppingListService.cpp ./src/services/SystemService.cpp ./src/services/TemperatureService.cpp ./src/services/WatchdogService.cpp -lwiringPi -lpthread
APP = ./bin/lucahome
CC = g++ -std=c++11

all: $(APP)

$(APP): $(SOURCE)
	chmod -R 755 *
	$(CC) $(SOURCE) -o $(APP)

clean:
	rm -fv ./bin/*
	update-rc.d -f lucahome remove
	rm -fv /etc/init.d/lucahome/
	rm -fv /bin/lucahome

install:
	cp ./bin/lucahome /bin/lucahome
	cp ./init/lucahome /etc/init.d
	update-rc.d lucahome defaults
