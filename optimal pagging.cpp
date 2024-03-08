#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

// Function to check if a page is present in the current set of frames
bool isPagePresent(int frames[], int numFrames, int page) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the page that will not be used for the longest period in the future
int findOptimalIndex(int pages[], int numPages, int frames[], int numFrames, int startIndex) {
    int farthest = -1;
    int optimalIndex = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = startIndex; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    optimalIndex = i;
                }
                break;
            }
        }

        // If the page is not referenced in the future, select it for replacement
        if (j == numPages) {
            return i;
        }
    }

    return optimalIndex;
}

// Function to simulate the Optimal Page Replacement algorithm
void optimalPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;

    printf("Optimal Page Replacement Algorithm:\n");

    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;  // Initialize frames with invalid page numbers
    }

    // Simulate page references
    for (int i = 0; i < numPages; i++) {
        printf("Referencing Page %d: ", pages[i]);

        // Check if the page is present in frames
        if (!isPagePresent(frames, numFrames, pages[i])) {
            int index = findOptimalIndex(pages, numPages, frames, numFrames, i + 1);

            // Replace the page at the found index
            frames[index] = pages[i];
            pageFaults++;

            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    printf("[ ] ");
                } else {
                    printf("[%d] ", frames[j]);
                }
            }
            printf("   Page Fault!\n");
        } else {
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == -1) {
                    printf("[ ] ");
                } else {
                    printf("[%d] ", frames[j]);
                }
            }
            printf("   No Page Fault\n");
        }
    }

    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES];
    int numPages, numFrames;

    // Input the number of pages and frames
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    printf("Enter the page references (separated by spaces): ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Simulate the Optimal Page Replacement algorithm
    optimalPageReplacement(pages, numPages, numFrames);

    return 0;
}

