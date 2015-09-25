/*
 * peaks.h
 *
 *  Created on: 20/09/2015
 *      Author: Mathias
 */

#ifndef PEAKS_H_
#define PEAKS_H_

// Functions
int findPeak(int left, int mid, int right) {
	if(mid >= left && mid > right) {
		//printf("%d\n", mid);
		return mid;
	} else {
		return 0;
	}
}

int evaluateSPKF(int peak, int SPKF) {
	//printf("SPKF = %d\n",0.125*peak+0.875*SPKF);
	return 0.125*peak+0.875*SPKF;
}

int evaluateSPKF2(int peak, int SPKF) {
	//printf("SPKF2 = %d\n",0.25*peak+0.75*SPKF);
	return 0.25*peak+0.75*SPKF;
}

int evaluateNPKF(int peak, int NPKF) {
	//printf("NPKF = %d\n",0.125*peak+0.875*NPKF);
	return 0.125*peak+0.875*NPKF;
}

int evaluateTHRESHOLD1(int NPKF, int SPKF) {
	//printf("TH1 = %d\n", NPKF+0.25*(SPKF-NPKF));
	return NPKF+0.25*(SPKF-NPKF);
}

int evaluateTHRESHOLD2(int THRESHOLD1) {
	//printf("TH2 = %d \n", THRESHOLD1/2);
	return THRESHOLD1/2;
}

int RR_AVERAGE(int *rr_intervals) {
	int i = 0;
	int result = 0;
	for (; i < 8; i++) {
		if(rr_intervals[i] == 0){
			break;
		}
		result += rr_intervals[i];
	}
	//printf("AVE = %d, i = %d \n", result/8);
	if(i==0){
		return 0;
	}
	return result / i;
}

int RR_LOW(int RR_AVERAGE) {
	//printf("Low = %d\n", 0.92*RR_AVERAGE);
	return 0.92*RR_AVERAGE;
}

int RR_HIGH(int RR_AVERAGE) {
	//printf("high = %d\n", 1.16*RR_AVERAGE);
	return 1.16*RR_AVERAGE;
}

int RR_MISS(int RR_AVERAGE) {
	//printf("Miss = %d\n", 1.66*RR_AVERAGE);
	return 1.66*RR_AVERAGE;
}

#endif /* PEAKS_H_ */
