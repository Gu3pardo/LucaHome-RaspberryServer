#include "systemservice.h"

SystemService::SystemService() {
}

SystemService::~SystemService() {
}

//--------------------------Public-----------------------//

std::string SystemService::PerformAction(std::string action,
		std::vector<std::string> data) {
	if (action == "SYSTEM") {
		if (data[4] == "REBOOT") {
			reboot();
			return "reboot:1";
		} else {
			return "Error 181:Invalid data for system";
		}
	} else if (action == "SYSTEM") {
		if (data[4] == "SHUTDOWN") {
			shutdown();
			return "shutdown:1";
		} else {
			return "Error 181:Invalid data for system";
		}
	}

	return "Error 180:Action not found for system";
}

// Answer from:
// http://stackoverflow.com/questions/6898337/determine-programmatically-if-a-program-is-running
int SystemService::IsProcessRunning(std::string processName) {
	DIR* directory;
	struct dirent* entries;
	char* endptr;
	char buffer[512];

	const char * name = processName.c_str();

	if (!(directory = opendir("/proc"))) {
		perror("can't open /proc");
		return -1;
	}

	while ((entries = readdir(directory)) != NULL) {
		/* if endptr is not a null character, the directory is not
		 * entirely numeric, so ignore it */
		long lpid = strtol(entries->d_name, &endptr, 10);
		if (*endptr != '\0') {
			continue;
		}

		/* try to open the cmdline file */
		snprintf(buffer, sizeof(buffer), "/proc/%ld/cmdline", lpid);
		FILE* processFile = fopen(buffer, "r");

		if (processFile) {
			if (fgets(buffer, sizeof(buffer), processFile) != NULL) {
				/* check the first token in the file, the program name */
				char* first = strtok(buffer, " ");
				if (!strcmp(first, name)) {
					fclose(processFile);
					closedir(directory);
					return (pid_t)lpid;
					// if the process id shall be returned use below code
					//return (pid_t) lpid;
				}
			}
			fclose(processFile);
		}

	}

	closedir(directory);
	return -1;
}

//--------------------------Private-----------------------//

std::string SystemService::reboot() {
	std::string command = "sudo shutdown -r now";
	return Tools::sendSystemCommandGetResult(command);
}

std::string SystemService::shutdown() {
	std::string command = "sudo shutdown -h now";
	return Tools::sendSystemCommandGetResult(command);
}
