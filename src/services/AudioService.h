#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <dirent.h>

#include "../common/utils/Tools.h"

#define GET "GET"
#define SET "SET"
#define PLAY "PLAY"
#define STOP "STOP"
#define VOLUME "VOLUME"
#define PLAYING "PLAYING"
#define PLAYINGFILE "PLAYINGFILE"
#define INCREASE "INCREASE"
#define DECREASE "DECREASE"
#define ALARM "ALARM"
#define WAKEUP "WAKEUP"

#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

class AudioService {
private:
	std::string _audioPath;
	std::string _playingFile;
	bool _isInitialized;
	bool _isPlaying;
	int _volume;
	std::vector<std::string> _soundFiles;
	std::string _wakeUpSound;
	std::string _alarmSound;
	int _raspberry;

	bool play(std::string);
	bool stop();
	std::string setVolume(std::string);

	std::vector<std::string> scanFolder();
	std::string getSoundFilesRestString();

	int readVolume();

public:
	AudioService();
	~AudioService();

	void Initialize(std::string, std::string, std::string, int);

	std::string PerformAction(std::string, std::vector<std::string>);
};

#endif
