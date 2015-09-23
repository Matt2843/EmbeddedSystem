#ifndef MAIN_H_
#define MAIN_H_
#include <stdlib.h>
#include <stdio.h>

#include "sensor.h"
#include "derivative.h"
#include "highpass.h"
#include "lowpass.h"
#include "mwi.h"
#include "squarring.h"

// Memory Structures
struct Memory{
	int index[6];
	int input[13]; 			// Index[0]
	int lpmem[33]; 			// Index[1]
	int hpmem[5]; 			// Index[2]
	int derivativemem;
	int squarredmem[31]; 	// Index[3]
	int mwimem[3]; 			// Index[4]
} static mem;


struct PeakMemory{
	int peaks[10000];		// Peak memory
	int rpeaks[10000];		// R-Peak memory
	int SPKF;
	int NPKF;
	int THRESHOLD1;
	int THRESHOLD2;
	int RR_AVERAGE1;
	int RR_AVERAGE2;
	int RR_LOW;
	int RR_HIGH;
	int RR_MISS;
} static peakmem;

// Data
static const char filename[] = "ECG.txt";
FILE *file;
int data;
int first;

// Function prototypes
int getIndex(int,int,int);
void memPrint();
int update();

#endif
