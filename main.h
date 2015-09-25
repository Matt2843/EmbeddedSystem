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
#include "peaks.h"

// HEJ LISE!!!!

// Memory Structures
struct Memory{
	int index[9];
	int input[13]; 			// Index[0]
	int lpmem[33]; 			// Index[1]
	int hpmem[5]; 			// Index[2]
	int derivativemem;
	int squarredmem[30]; 	// Index[3]
	int mwimem[3]; 			// Index[4]
} static mem;


struct PeakMemory{
	int peaks[10000];		// Peak memory Index[5]
	int rpeaks[10000];		// R-Peak memory Index[6]
	int SPKF;
	int NPKF;
	int THRESHOLD1;
	int THRESHOLD2;
	int RR_AVERAGE1;
	int RR_AVERAGE2;
	int RR_LOW;
	int RR_HIGH;
	int RR_MISS;
	int RR_COUNTER;
	int RecentRR_OK[8];	// Index[7]
	int RecentRR[8]; // Index[8]
} static peakmem;

// Data
static const char filename[] = "ECG.txt";
FILE *file;
int data;
int first;
int et, to, tre, fire, fem;

// Function prototypes
int getIndex(int,int,int);
void memPrint();
int update();

#endif
