#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Define maximum length for each line in the data file
#define MAX_LINE_LENGTH 100

// Structure to store traffic event details
typedef struct {
    char lane[20];       // Lane type (main_lane, diversion_lane)
    char movement[20];   // Movement type (vehicle, pedestrian)
    int time;            // Time for this event (in seconds)
} TrafficEvent;

// Function to calculate total time for pedestrian on the main lane to cross
int calculate_pedestrian_crossing_time(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int total_time = 0;

    // Loop through each line in the file
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if it exists at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Use strtok to tokenize the line based on commas
        char *lane = strtok(line, ",");
        char *movement = strtok(NULL, ",");
        char *time_str = strtok(NULL, ",");
        
        if (lane && movement && time_str) {
            int time = atoi(time_str);  // Convert time string to integer

            // We are only concerned with pedestrians on the main lane
            if (!(strcmp(lane, "main_lane") == 0 && strcmp(movement, "pedestrian") == 0)) {
                total_time += time;
            }
        } else {
            // Handle incorrect line format if needed
            fprintf(stderr, "Error parsing line: %s\n", line);
        }
    }

    fclose(file);
    return total_time;
}

int main() {
    const char *filename = "traffic.dat";  // Name of the data file

    // Calculate total time before pedestrian can cross
    int total_wait_time = calculate_pedestrian_crossing_time(filename);
    
    if (total_wait_time != -1) {
        printf("Total time before pedestrian on the main lane can cross: %d seconds\n", total_wait_time);
    }

    return 0;
}
