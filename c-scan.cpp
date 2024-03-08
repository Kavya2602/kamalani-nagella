#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to sort an array of integers in ascending order
void sortRequests(int requests[], int numRequests) {
    int i, j, temp;
    for (i = 0; i < numRequests - 1; i++) {
        for (j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap the elements if they are in the wrong order
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to simulate C-SCAN disk scheduling algorithm
void cScan(int requests[], int numRequests, int startCylinder, int endCylinder) {
    int currentCylinder = startCylinder;
    int direction = 1;  // 1 for moving towards higher cylinders, -1 for moving towards lower cylinders

    sortRequests(requests, numRequests);

    printf("C-SCAN Disk Scheduling Algorithm:\n");
    printf("Initial Head Position: %d\n", startCylinder);

    while (1) {
        int serviced = 0;

        // Scan towards higher cylinders
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] >= currentCylinder && requests[i] <= endCylinder) {
                printf("Servicing request at Cylinder %d\n", requests[i]);
                currentCylinder = requests[i];
                serviced = 1;
            }
        }

        // If no requests found towards higher cylinders, move to the end and reset direction
        if (!serviced) {
            printf("Moving to the end of the disk\n");
            currentCylinder = endCylinder;
            direction = -1;
        }

        // Scan towards lower cylinders
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] >= startCylinder && requests[i] < currentCylinder) {
                printf("Servicing request at Cylinder %d\n", requests[i]);
                currentCylinder = requests[i];
                serviced = 1;
            }
        }

        // If no requests found towards lower cylinders, move to the start and reset direction
        if (!serviced) {
            printf("Moving to the start of the disk\n");
            currentCylinder = startCylinder;
            direction = 1;
        }

        // Check if all requests are serviced
        int allServiced = 1;
        for (int i = 0; i < numRequests; i++) {
            if (requests[i] >= startCylinder && requests[i] <= endCylinder) {
                allServiced = 0;
                break;
            }
        }

        // If all requests are serviced, exit the loop
        if (allServiced) {
            printf("All requests serviced. Exiting...\n");
            break;
        }
    }
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, startCylinder, endCylinder;

    // Input requests from the user
    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    printf("Enter the disk requests (separated by spaces): ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    // Input starting and ending cylinders
    printf("Enter the starting cylinder: ");
    scanf("%d", &startCylinder);

    printf("Enter the ending cylinder: ");
    scanf("%d", &endCylinder);

    // Simulate C-SCAN disk scheduling algorithm
    cScan(requests, numRequests, startCylinder, endCylinder);

    return 0;
}

