# Image Processing with Pthreads

This program applies image processing to a PNG image using multithreading via the pthreads library. The program reads an input image, applies a smoothing filter based on pixel neighbours, and outputs a processed version of the image.

## Features
- Handles corner, edge, and central pixels with appropriate smoothing filters.
- Processes the image in parallel using multiple threads.
- Dynamically calculates thread workload based on the number of threads specified.

## Prerequisites
- GCC or compatible C compiler.
- `lodepng` library for handling PNG files.
- Pthreads library for multithreading.

## Usage
Compile the program:
```bash
gcc -o image_processor image_processor.c -lpthread
