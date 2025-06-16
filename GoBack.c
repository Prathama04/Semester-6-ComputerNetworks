#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 

#define MAX_FRAMES 100 

int window_size, total_frames; 

void sendFrames(int start, int end) { 
	for (int i = start; i < end; i++) { 
	printf("Sending Frame %d\n", i); 
	} 
} 

int main() { 
	srand(time(0)); 
	printf("Enter total number of frames: "); 
	scanf("%d", &total_frames); 
	printf("Enter window size: "); 
	scanf("%d", &window_size); 

	if (total_frames > MAX_FRAMES || window_size > total_frames) { 
		printf("Invalid input! Window size must be less than or equal to total frames and within limits.\n"); 
	return 1; 
	} 
	int base = 0; 
	while (base < total_frames) { 
		int end = (base + window_size < total_frames) ? base + window_size : total_frames; 
		sendFrames(base, end); 
		int ack = base + (rand() % (window_size + 1)); // Random ACK loss simulation 
		if (ack >= end) { 
			printf("All frames %d to %d acknowledged.\n", base, end - 1); 
			base = end; 
		} else { 
			printf("Acknowledgement lost or frame %d lost! Resending from frame %d\n", ack, ack); 
			base = ack;  
} 
} 

	printf("All frames sent successfully!\n"); 
	return 0; 
}
