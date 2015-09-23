/*
 * peaks.h
 *
 *  Created on: 20/09/2015
 *      Author: Mathias
 */

#ifndef PEAKS_H_
#define PEAKS_H_

// Functions
int findPeak(int *processedData) {
	if(processedData[1] > processedData[2] && processedData[1] > processedData[0]) {
		return processedData[1];
	} else {
		return -1;
	}
}

int evaluateSPKF(int peak, int SPKF) {
	return 0.125*peak+0.875*SPKF;
}

int evaluateNPKF(int peak, int NPKF) {
	return 0.125*peak+0.875*NPKF;
}

int evaluateTHRESHOLD1(int NPKF, int SPKF) {
	return NPKF+0.25*(SPKF-NPKF);
}

int evaluateHTRESHOLD2(int THRESHOLD1) {
	return 0.5*THRESHOLD1;
}

int RR_AVERAGE1(int *rr_intervals) {
	int i = 0;
	int result = 0;
	for (; i < 8; i++) {
		result += rr_intervals[i];
	}
	return result / 8;
}

int RR_AVERAGE2(int *rr_intervals2) {
	int i = 0;
	int result = 0;
	for (; i < 8; i++) {
		result += rr_intervals2[i];
	}
	return result / 8;
}

int RR_LOW(int RR_AVERAGE2) {
	return 0.92*RR_AVERAGE2;
}

int RR_HIGH(int RR_AVERAGE2) {
	return 1.16*RR_AVERAGE2;
}

int RR_MISS(int RR_AVERAGE2) {
	return 1.66*RR_AVERAGE2;
}

#endif /* PEAKS_H_ */
