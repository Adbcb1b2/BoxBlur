#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lodepng.h"

// Initialise the struct
struct ThreadData {
    pthread_mutex_t mutex;
    unsigned char **image2D;
    unsigned char **image2DNew;
    int startRow;
    int endRow;
    int width;
    int height;
};

void* processRows(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;

    //Lock the mutex before the critical section
    pthread_mutex_lock(&data->mutex);
    
    for (int row = data->startRow; row < data->endRow; row++) {
        for (int col = 0; col < data->width * 4; col += 4) {
    	
    		// Check for corner pixels - 3 neighbours
    		if(row == 0 && col ==0){ // Top left corner
  				//printf("Top left corner \n");
  				// Take the average of surrounding pixels
  				int newR = (data->image2D[row][col] + data->image2D[row][col+4] + data->image2D[row+1][col] + data->image2D[row+1][col+4])/4;
  				int newG = (data->image2D[row][col+1] + data->image2D[row][col+5] + data->image2D[row+1][col+1] + data->image2D[row+1][col+5])/4;
  				int newB = (data->image2D[row][col+2] + data->image2D[row][col+6] + data->image2D[row+1][col+2] + data->image2D[row+1][col+6])/4;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];

    		}else if (row == 0 && col == data->width * 4 - 4){ // Top right corner
    			//printf("Top right corner\n");
    			int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2D[row+1][col] + data->image2D[row+1][col-4])/4;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2D[row+1][col+1] + data->image2D[row+1][col-3])/4;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col -2] + data->image2D[row+1][col+2] + data->image2D[row+1][col-2])/4;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
    			
    		}else if (row == data->height - 1 && col == 0){ // Bottom left corner
    			//printf("Bottom left corner\n");
    			int newR = (data->image2D[row][col] + data->image2D[row][col+4] + data->image2D[row-1][col] + data->image2D[row-1][col+4])/4;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col+5] + data->image2D[row-1][col+1] + data->image2D[row-1][col+5])/4;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col+6] + data->image2D[row-1][col+2] + data->image2D[row-1][col+6])/4;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
  				
    		}else if (row == data->height - 1 && col == data->width * 4 - 4){ // Bottom right corner
				//printf("Bottom right corner\n");
				int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2D[row-1][col] + data->image2D[row-1][col-4])/4;
				int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2D[row-1][col+1] + data->image2D[row-1][col-3])/4;
				int newB = (data->image2D[row][col+2] + data->image2D[row][col-2] + data->image2D[row-1][col+2] + data->image2D[row-1][col-2])/4;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
    		}
    		
    		// If it's not a corner, check for edges - 5 neighbours
    		else if(row == 0){ // Top edge
    			//printf("Top edge\n"); 
    			// pixel (itself, to left, to right, underneath, diagonal down left, diagonal down right)/6
    			int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2D[row][col+4] + data->image2D[row+1][col] + data->image2D[row+1][col-4] + data->image2D[row+1][col+4])/6;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2D[row][col+5] + data->image2D[row+1][col+1] + data->image2D[row+1][col-3] + data->image2D[row+1][col+5])/6;    					
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col-2] + data->image2D[row][col+6] + data->image2D[row+1][col+2] + data->image2D[row+1][col-2] + data->image2D[row+1][col+6])/6;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
  				// Write new values to new image array
  				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
  				
    		}else if (row == data->height - 1){ // Bottom edge
    			//printf("Bottom edge\n");
    			// pixel (itself, to left, to right, above, diagonal up left, diagonal up right)/6
    			int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2D[row][col+4] + data->image2D[row-1][col] + data->image2D[row-1][col-4] + data->image2D[row-1][col+4])/6;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2D[row][col+5] + data->image2D[row-1][col+1] + data->image2D[row-1][col-3] + data->image2D[row-1][col+5])/6;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col-2] + data->image2D[row][col+6] + data->image2D[row-1][col+2] + data->image2D[row-1][col-2] + data->image2D[row-1][col+6])/6;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
  				// Write new values to new image array
  				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
  				
    		}else if (col == 0){ // Left edge
    			//printf("Left edge\n");
    			// pixel (itself, to right, above, below, diagonal up right, diagonal down right)/6
    			int newR = (data->image2D[row][col] + data->image2D[row][col+4] + data->image2D[row-1][col] + data->image2D[row+1][col] + data->image2D[row-1][col+4] + data->image2D[row+1][col+4])/6;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col+5] + data->image2D[row-1][col+1] + data->image2D[row+1][col+1] + data->image2D[row-1][col+5] + data->image2D[row+1][col+5])/6;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col+6] + data->image2D[row-1][col+2] + data->image2D[row+1][col+2] + data->image2D[row-1][col+6] + data->image2D[row+1][col+6])/6;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
  				
    		}else if(col == data->width * 4 - 4){ // Right edge
    			//printf("Right edge\n");
    			//pixel (itself, to left, above, below, diagonal up left, diagonal down left)/6
    			int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2DNew[row-1][col] + data->image2D[row+1][col] + data->image2D[row-1][col-4] + data->image2D[row+1][col-4])/6;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2DNew[row-1][col+1] + data->image2D[row+1][col+1] + data->image2D[row-1][col-3] + data->image2D[row+1][col-3])/6;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col-2] + data->image2DNew[row-1][col+2] + data->image2D[row+1][col+2] + data->image2D[row-1][col-2] + data->image2D[row+1][col-2])/6;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];
				
    		// If it's not a corner or edge, its a central pixel
    		}else{ // Central pixel - 8 neighbours
    			//printf("Centre pixel\n");
    			// pixel (itself, left, right, up, down, diagonal up left, diagonal up right, diagonal down left, diagonal down right)/9
    			int newR = (data->image2D[row][col] + data->image2D[row][col-4] + data->image2D[row][col+4] + data->image2D[row-1][col] + data->image2D[row+1][col] + data->image2D[row-1][col-4] + data->image2D[row-1][col+4] + data->image2D[row+1][col-4] + data->image2D[row+1][col+4])/9;
    			int newG = (data->image2D[row][col+1] + data->image2D[row][col-3] + data->image2D[row][col+5] + data->image2D[row-1][col+1] + data->image2D[row+1][col+1] + data->image2D[row-1][col-3] + data->image2D[row-1][col+5] + data->image2D[row+1][col-3] + data->image2D[row+1][col+5])/9;
    			int newB = (data->image2D[row][col+2] + data->image2D[row][col-2] + data->image2D[row][col+6] + data->image2D[row-1][col+2] + data->image2D[row+1][col+2] + data->image2D[row-1][col-2] + data->image2D[row-1][col+6] + data->image2D[row+1][col-2] + data->image2D[row+1][col+6])/9;
				//printf("new r = %d, new g = %d, new b = %d, ", newR, newG, newB); // TEST
				// Write new values to new image array  				
				data->image2DNew[row][col] = newR;
  				data->image2DNew[row][col+1] = newG;
  				data->image2DNew[row][col+2] = newB;
  				data->image2DNew[row][col+3] = data->image2D[row][col+3];

    		}

		}
		
	}
	//  End of critical section, unlock the mutex
	pthread_mutex_unlock(&data->mutex);
    pthread_exit(NULL);
}
void  main(int argc, char** argv) {
    const char* filename = argv[1];
    unsigned int error;
    unsigned char* image1D;
    unsigned int width;
    unsigned int height;
    
    // Command line argument
    int threadCount = atoi(argv[2]);

    // Decode the image into a 1D array 
    lodepng_decode32_file(&image1D, &width, &height, filename);

    // Allocate memory for the 2D array for the original image
    unsigned char** image2D = (unsigned char**)malloc(height * sizeof(unsigned char*));
    for (int i = 0; i < height; i++) {
        image2D[i] = (unsigned char*)malloc(width * 4 * sizeof(unsigned char));
    }

    // Convert 1D array returned by the decode function to a 2D array
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width * 4; col++) {
            image2D[row][col] = image1D[row * width * 4 + col];
        }
    }

    // Free the memory storing the 1D array
    free(image1D);

    // Dynamically allocate memory for the 2D array for the new image
    unsigned char** image2DNew = (unsigned char**)malloc(height * sizeof(unsigned char*));
    for (int i = 0; i < height; i++) {
        image2DNew[i] = (unsigned char*)malloc(width * 4 * sizeof(unsigned char));
    }

    // Initialise pthread variables
    pthread_t threadIDs[threadCount];
    struct ThreadData threadData[threadCount];

    // Work out amount of slices needed
    int rowsPerThread = height / threadCount;
    int remainingRows = height % threadCount;


    int startRow = 0;
    for (int i = 0; i < threadCount; i++) {
        // Determine if current thread should process an additional row
        int extraRow = 0;
        if(i < remainingRows){
            extraRow = 1;
            }
        int endRow = startRow + rowsPerThread + extraRow;

        // Initialise mutex for each thread
        pthread_mutex_init(&threadData[i].mutex, NULL);

        // Send variables to structs
        threadData[i].image2D = image2D;
        threadData[i].image2DNew = image2DNew;
        threadData[i].startRow = startRow;
        threadData[i].endRow = endRow;
        threadData[i].width = width;
        threadData[i].height = height;

        // Create threads
        pthread_create(&threadIDs[i], NULL, processRows, (void*)&threadData[i]);

        startRow = endRow;
    }

    // Join the threads
    for (int i = 0; i < threadCount; i++) {
        pthread_join(threadIDs[i], NULL);
    }

    /* TEST Print the 2D array for the new image (for testing purposes)
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width * 4; col++) {
            printf("%u ", image2DNew[row][col]);
            if ((col + 1) % 4 == 0) {
                printf("| ");
            }
        }
        printf("\n");
    }*/



    // Allocate memory for 1D array for new image
    unsigned char* image1DNew = malloc(width * height * 4 * sizeof(unsigned char));

    // Flatten 2D to 1D array for encoding
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width * 4; col++) {
            image1DNew[row * width * 4 + col] = image2DNew[row][col];
        }
    }


    // Freeing resources
    free(image2D);
    free(image2DNew);

    // Destroy mutex in each threads data
    for (int i = 0; i < threadCount; i++) {
        pthread_mutex_destroy(&threadData[i].mutex);
    }

    // Encode to new image
    lodepng_encode32_file("blurredImage.png\n", image1DNew, width, height);
    
    // Free resources
    free(image1DNew);

    printf("Your image has been blurred and saved in the same directory with the name 'blurredImage.png'");


   
}
