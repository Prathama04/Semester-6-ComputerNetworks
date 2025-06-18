#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX_FRAMES 100

int main(){
	srand(time(NULL));
	int total_frames,window_size,i,base=0;
	printf("Enter total number of frames to send: ");
	scanf("%d", &total_frames);
	printf("Enter window size: ");
 	scanf("%d", &window_size);

	if (total_frames > MAX_FRAMES || window_size > total_frames) {
	printf("Invalid input! Window size must be less than or equal to total frames and within limits.\n");
	return 1;
	}

	bool *received = malloc(total_frames * sizeof(bool));
	if (received==NULL){
		printf("Memory allocation failed");
		return 1;
	}
	for(i=0;i<total_frames;i++)
		received[i]=false;
	
	while(base<total_frames){
		int end=(base+window_size)<total_frames?base+window_size:total_frames;
		printf("Sending Window:Frames %d to %d \n", base, end-1);

		int to_send[MAX_FRAMES];  
    		int responses[MAX_FRAMES]; 
    		int count = 0;

    for (i = base; i < end; i++) {
        if (!received[i]) {
            to_send[count] = i;
            responses[count] = rand() % 2;
            count++;
	        }
    }

    if (count > 0) {
        printf("Sending frames: ");
        for (i = 0; i < count; i++) {
            printf("[%d] ", to_send[i]);
        }
        printf("\n");
    }


    for (i = 0; i < count; i++) {
        int frame = to_send[i];
        if (responses[i] == 1) {
            printf("ACK received for frame %d\n", frame);
            received[frame] = true;
        } else {
            printf("Acknowledgement lost or frame %d lost.\n", frame);
        }
    }

			while(received[base] && base<total_frames){
				base++;
		}
	 printf("--------------------------------------------------\n");
	}
	printf("All frames sent successfully.");
	free(received);
	return 0;
}
