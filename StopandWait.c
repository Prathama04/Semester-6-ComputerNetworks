#include <stdio.h>  // for printf()
#include <stdlib.h> // for rand() and srand()
#include <time.h>   // Used to seed the random number generator with current time
#include <unistd.h> // for sleep()

// Macro Definitions
#define FRAME_LOST 30 // 30% chance a frame is lost
#define ACK_LOST 20   // 20% chance an acknowledgement is lost
#define TIMEOUT 2     // Wait time (2 secs) before retrying
#define MAX 10        // No. of total frames that can be sent 

// Function to simulate Frame Loss
int is_frame_lost(){
    return (rand() % 100) < FRAME_LOST;
}

// Function to simulate Acknowledgement Loss
int is_ack_lost() {
    return (rand() % 100) < ACK_LOST;
}

// Main function
int main() {
    srand(time(NULL));  // Seed random number generator with current time to ensure randomness

    int frame = 0;          // Frame is represented as Alternating bit (0 or 1)
    int transmissions = 0;  // Total successful transmissions

    while (transmissions < MAX) {
        int sent_successfully = 0;

        while (!sent_successfully) {
            printf("\nSending Frame %d\n", frame);
            sleep(1);

            // Check if frame is lost
            if (is_frame_lost()) {
                printf("Frame %d is lost! Waiting for timeout and retransmitting...\n", frame);
                sleep(TIMEOUT);
                continue;  // Go back to sending the same frame again
            }

            printf("Frame %d transmitted successfully.\n", frame);

            // Check if ACK is lost
            if (is_ack_lost()) {
                printf("ACK for frame %d is lost! Waiting for timeout and retransmitting frame...\n", frame);
                sleep(TIMEOUT);
                continue;  // Go back to sending the same frame again
            }

            // ACK received successfully
            printf("ACK %d received for Frame %d\n", (1 - frame), frame);
            sent_successfully = 1;  // Break inner loop
        }

        frame = 1 - frame;  // Alternate frame number
        transmissions++;
    }

    printf("\nAll frames sent and acknowledged successfully!\n");
    return 0;
}
