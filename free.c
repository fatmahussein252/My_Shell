#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int ffree(int argc,const char **argv)
{
	FILE *file = fopen("/proc/meminfo", "r");
    	if (file == NULL) {
        perror("Failed to open /proc/meminfo");
        return 0;
    }

    char line[256];
    unsigned long memTotal = 0, memFree = 0, Buffers = 0, Cached = 0;
    unsigned long SwapTotal = 0, SwapFree = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "MemTotal: %lu kB", &memTotal) == 1) {
            continue;
        } else if (sscanf(line, "MemFree: %lu kB", &memFree) == 1) {
            continue;
        } else if (sscanf(line, "Buffers: %lu kB", &Buffers) == 1) {
            continue;
        
	} else if (sscanf(line, "Cached: %lu kB", &Cached) == 1) {
            continue;
        } else if (sscanf(line, "SwapTotal: %lu kB", &SwapTotal) == 1) {
            continue;
        } else if (sscanf(line, "SwapFree: %lu kB", &SwapFree) == 1) {
            continue;
        }



    }

    fclose(file);
    
    printf("Mem:\n total: %lu \n", memTotal);
    printf(" free: %lu \n", memFree);
    printf(" used: %lu \n", memTotal-memFree-Buffers-Cached);
    
    printf("Swap:\n total: %lu \n", SwapTotal);
    printf(" free: %lu \n", SwapFree);
    printf(" used: %lu \n", SwapTotal-SwapFree);

    return 0;
}

int uptime(int argc, const char **argv)
{
	double uptime = 0.0, idle_time = 0.0;

    // Open the /proc/uptime file
    FILE *file = fopen("/proc/uptime", "r");
    if (file == NULL) {
        perror("fopen");
        return 0;
    }

    // Read the uptime and idle time from the file
    if (fscanf(file, "%lf %lf", &uptime, &idle_time) != 2) {
        perror("fscanf");
        fclose(file);
        return 0;
    }

    // Close the file
    fclose(file);

    // Print the uptime and idle time
    printf("Uptime: %.2f seconds\n", uptime);
    printf("Idle Time: %.2f seconds\n", idle_time);
    return 0;

	
}
