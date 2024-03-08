#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100
void fcfs(int requests[], int numRequests, int startCylinder) {
    printf("FCFS Disk Scheduling Algorithm:\n");
    printf("Initial Head Position: %d\n", startCylinder);
    for (int i = 0; i < numRequests; i++) {
        printf("Servicing request at Cylinder %d\n", requests[i]);
        startCylinder = requests[i];
    }

    printf("All requests serviced. Exiting...\n");
}

int main() {
    int requests[MAX_REQUESTS];
    int numRequests, startCylinder;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    printf("Enter the disk requests (separated by spaces): ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the starting cylinder: ");
    scanf("%d", &startCylinder);
    fcfs(requests, numRequests, startCylinder);

    return 0;
}

