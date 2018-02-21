#include "SystemController.h"

// Answer from:
// http://stackoverflow.com/questions/6898337/determine-programmatically-if-a-program-is-running
int SystemController::IsProcessRunning(string processName)
{
	DIR *directory;
	struct dirent *entries;
	char *endptr;
	char buffer[512];

	const char *name = processName.c_str();

	if (!(directory = opendir("/proc")))
	{
		perror("can't open /proc");
		return -1;
	}

	while ((entries = readdir(directory)) != NULL)
	{
		/* if endptr is not a null character, the directory is not
		 * entirely numeric, so ignore it */
		long lpid = strtol(entries->d_name, &endptr, 10);
		if (*endptr != '\0')
		{
			continue;
		}

		/* try to open the cmdline file */
		snprintf(buffer, sizeof(buffer), "/proc/%ld/cmdline", lpid);
		FILE *processFile = fopen(buffer, "r");

		if (processFile)
		{
			if (fgets(buffer, sizeof(buffer), processFile) != NULL)
			{
				/* check the first token in the file, the program name */
				char *first = strtok(buffer, " ");
				if (!strcmp(first, name))
				{
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