#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define N 5 // Number of philosophers

HANDLE mutex; // Mutex to ensure mutual exclusion for critical sections
HANDLE forks[N]; // Semaphores representing forks

void philosopher(int i) {
    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", i);

        // Wait to take left fork
        WaitForSingleObject(mutex, INFINITE);
        WaitForSingleObject(forks[i], INFINITE);

        // Wait to take right fork
        WaitForSingleObject(forks[(i + 1) % N], INFINITE);

        // Eating
        printf("Philosopher %d is eating.\n", i);

        // Release left and right forks
        ReleaseSemaphore(forks[i], 1, NULL);
        ReleaseSemaphore(forks[(i + 1) % N], 1, NULL);

        // Release mutex
        ReleaseMutex(mutex);

        // Sleeping (to simulate thinking/eating time)
        Sleep(rand() % 1000);
    }
}

int main() {
    // Initialize mutex and forks
    mutex = CreateMutex(NULL, FALSE, NULL);
    for (int i = 0; i < N; i++) {
        forks[i] = CreateSemaphore(NULL, 1, 1, NULL);
    }

    // Create philosopher threads
    HANDLE threads[N];
    for (int i = 0; i < N; i++) {
        threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)philosopher, (LPVOID)i, 0, NULL);
    }

    // Wait for all philosopher threads to finish
    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    // Close handles
    CloseHandle(mutex);
    for (int i = 0; i < N; i++) {
        CloseHandle(forks[i]);
        CloseHandle(threads[i]);
    }

    return 0;
}

