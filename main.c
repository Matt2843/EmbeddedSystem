#include "main.h"

// 31 normal peaks in the first 5000 samples
// 50 shallow fast peaks in the last 5000 samples

void memPrint(){
	int i = 0;
//	for(; i<13; i++){
//		printf("%d ", mem.input[i]);
//	}
//	printf("\n    ");
//	for(i = 0; i<33; i++){
//		printf("%d ", mem.lpmem[i]);
//	}
//	printf("\n    ");
//	for(i = 0; i<5; i++) {
//		printf("%d ", mem.hpmem[i]);
//	}
	for(; i < 208; i++) {
		if(peakmem.peaks[i] == 0){
			break;
		}
			printf("%d ", peakmem.peaks[i]);
		}
	i = 0;
	printf("\n");
	for(; i < 100; i++) {
		if(peakmem.rpeaks[i] == 0){
			break;
		}
		printf("%d ", peakmem.rpeaks[i]);
	}
		//printf("\n \n");
}

int getIndex(int length, int index, int delta) {
	if(index + delta == length){
		update();
		return 0;
	} else if (index + delta > length) {
		return index + delta - length;

	} else if (index + delta < 0 ){
		return index + delta + length;

	} else {
		return index + delta;
	}
}

int update(){
	if(mem.index[0] >= 13){
		mem.index[0] = 0;
	}
	if(mem.index[1] >= 33){
		mem.index[1] = 0;
	}
	if(mem.index[2] >= 5){
		mem.index[2] = 0;
	}
	if(mem.index[3] >= 30){
		mem.index[3] = 0;
	}
	if(mem.index[4] >= 3){
		mem.index[4] = 0;
	}
	if(mem.index[7] >= 8) {
		mem.index[7] = 0;
	}
	if(mem.index[8] >= 8) {
		mem.index[8] = 0;
	}
	return 0;
}

void maininput() {
	mem.input[getIndex(13, mem.index[0]-first, 1)] = getNextData(file, data);
	mem.index[0] += 1-first;
}

void mainlowpass() {
	mem.lpmem[getIndex(33, mem.index[1]-first, 1)] = lowpass(mem.input[getIndex(13, mem.index[0], 0)],
															 mem.input[getIndex(13, mem.index[0], -6)],
															 mem.input[getIndex(13, mem.index[0], -12)],
															 mem.lpmem[getIndex(33, mem.index[1], 0)],
															 mem.lpmem[getIndex(33, mem.index[1], -1)]);

	mem.index[1] += 1-first;
}

void mainhighpass() {
	mem.hpmem[getIndex(5, mem.index[2]-first, 1)] = highpass(mem.lpmem[getIndex(33, mem.index[1], 0)],
															 mem.lpmem[getIndex(33, mem.index[1], -16)],
															 mem.lpmem[getIndex(33, mem.index[1], -17)],
															 mem.lpmem[getIndex(33, mem.index[1], -32)],
															 mem.hpmem[getIndex(5, mem.index[2], 0)]);

//	printf("%d:    x = %d, x-16 = %d, x-17 = %d, x-32 = %d, y-1 = %d     HIGH PASS RESULT: %d\n", count, mem.lpmem[getIndex(33, mem.index[1], 0)], mem.lpmem[getIndex(33, mem.index[1], -16)], mem.lpmem[getIndex(33, mem.index[1], -17)], mem.lpmem[getIndex(33, mem.index[1], -32)], mem.hpmem[getIndex(5, mem.index[2], 0)], mem.hpmem[getIndex(5, mem.index[2]-mem.first[2], 1)]);
//	printf("%d:", highpass(-60,0,0,0,1));
//	printf("*\n");

	mem.index[2] += 1;
}

void mainderivative() {
	mem.derivativemem = derivative(mem.hpmem[getIndex(5, mem.index[2], 0)],
								   mem.hpmem[getIndex(5, mem.index[2], -1)],
								   mem.hpmem[getIndex(5, mem.index[2], -3)],
								   mem.hpmem[getIndex(5, mem.index[2], -4)]);
}

void mainsquarred() {
	mem.squarredmem[getIndex(30, mem.index[3]-first, 1)] = squarring(mem.derivativemem);
	mem.index[3] += 1-first;
}

void mainmwi() {
	mem.mwimem[getIndex(3, mem.index[4]-first, 1)] = mwi(mem.squarredmem, 30);
//	printf("%d ", mem.mwimem[getIndex(3, mem.index[4]-first, 1)]);
	mem.index[4] += 1-first;
}

void normalRPeakFound(){
	peakmem.rpeaks[mem.index[6]] = peakmem.peaks[mem.index[5]-1];
	peakmem.SPKF = evaluateSPKF(peakmem.peaks[mem.index[5]-1], peakmem.SPKF);
//	if(peakmem.RR_COUNTER > 50){
		peakmem.RecentRR_OK[getIndex(8, mem.index[7], 1)] = peakmem.RR_COUNTER;
		mem.index[7]++;
//	}
		peakmem.RecentRR[getIndex(8, mem.index[8], 1)] = peakmem.RR_COUNTER;
	mem.index[8]++;
	peakmem.RR_AVERAGE2 = RR_AVERAGE(peakmem.RecentRR_OK);
	peakmem.RR_AVERAGE1 = RR_AVERAGE(peakmem.RecentRR);
	peakmem.RR_LOW = RR_LOW(peakmem.RR_AVERAGE2);
	peakmem.RR_HIGH = RR_HIGH(peakmem.RR_AVERAGE2);
	peakmem.RR_MISS = RR_MISS(peakmem.RR_AVERAGE2);
	peakmem.THRESHOLD1 = evaluateTHRESHOLD1(peakmem.NPKF, peakmem.SPKF);
	peakmem.THRESHOLD2 = evaluateTHRESHOLD2(peakmem.THRESHOLD1);
	mem.index[6]++;
}

void afterSearchBack(int j){
	peakmem.rpeaks[mem.index[6]] = peakmem.peaks[mem.index[5]-j];
	peakmem.SPKF = evaluateSPKF2(peakmem.rpeaks[mem.index[6]], peakmem.SPKF);
	//if(peakmem.RR_COUNTER-j > 50){
		peakmem.RecentRR[getIndex(8, mem.index[8], 1)] = peakmem.RR_COUNTER-j;
		mem.index[8]++;

	//}
	peakmem.RR_AVERAGE1 = RR_AVERAGE(peakmem.RecentRR);
	peakmem.RR_LOW = RR_LOW(peakmem.RR_AVERAGE1);
	peakmem.RR_HIGH = RR_HIGH(peakmem.RR_AVERAGE1);
	peakmem.RR_MISS = RR_MISS(peakmem.RR_AVERAGE1);
	peakmem.THRESHOLD1 = evaluateTHRESHOLD1(peakmem.NPKF, peakmem.SPKF);
	peakmem.THRESHOLD2 = evaluateTHRESHOLD2(peakmem.THRESHOLD1);
	mem.index[6]++;

}


void peaksbullshit(int i, int recursive) {
	if(recursive == 0){
		peakmem.peaks[mem.index[5]] = findPeak(mem.mwimem[getIndex(3, mem.index[4], -2)], mem.mwimem[getIndex(3, mem.index[4], -1)], mem.mwimem[getIndex(3, mem.index[4], 0)]);
		peakmem.RR_COUNTER++;
	}

	if(mem.mwimem[getIndex(3, mem.index[4], -1)] < peakmem.THRESHOLD1){
		bool = 1;
	}

	if (peakmem.peaks[mem.index[5]] != 0) {
		if(recursive == 0){
			mem.index[5]++;
		}

		if(recursive == 1){
			printf("%d < %d < %d", ,peakmem.THRESHOLD1);
		}

		if (peakmem.peaks[mem.index[5]-1] > peakmem.THRESHOLD1 && bool /*&& peakmem.peaks[mem.index[5]-1] > 3500*/) {
			et++;
			if(recursive == 1){
				printf("%d < %d < %d", peakmem.RR_LOW, peakmem.RR_COUNTER, peakmem.RR_HIGH);
			}

			if(peakmem.RR_COUNTER > peakmem.RR_LOW && peakmem.RR_COUNTER < peakmem.RR_HIGH) {
				to++;
				normalRPeakFound();
				printBullshit(peakmem.RR_COUNTER, peakmem.rpeaks[mem.index[6]-1], 0, i);
				peakmem.RR_COUNTER = 0;
				bool = 0;
			} else if (peakmem.RR_COUNTER > peakmem.RR_MISS) {
				tre++;
				int j = 2;
				printf("%f\n", i*0.005);
				while(peakmem.peaks[mem.index[5] - j] <= peakmem.THRESHOLD2){
					j++;
				}
				afterSearchBack(j);
				printBullshit(peakmem.RR_COUNTER-j, peakmem.rpeaks[mem.index[6]-1], 0, i);
				peakmem.RR_COUNTER = j;
				//mem.index[5]--;
				peaksbullshit(i, 1);
				peakmem.RR_COUNTER = 0;
				bool = 0;
			}


		} else {
			fem++;
			peakmem.NPKF = evaluateNPKF(peakmem.peaks[mem.index[5]], peakmem.NPKF);
			peakmem.THRESHOLD1 = evaluateTHRESHOLD1(peakmem.NPKF, peakmem.SPKF);
			peakmem.THRESHOLD2 = evaluateTHRESHOLD2(peakmem.THRESHOLD1);
		}
	} else {
	}
}

void printBullshit(int TIME, int PULSE, int type, int i) {
	char wmsg[] = "WARNING";
	char lmsg[] = "LOG";
	int bool = 0;
	if(bool){
		printf("\n===================================================================\n");
		printf("[%s] LAST RPEAK DETECTECTED: VALUE: %d TIME: %.4g PULSE: %d sysTime: %f\n", type > 0 ? wmsg : lmsg, peakmem.rpeaks[mem.index[6]-1], TIME*0.005, 60*200/peakmem.RR_AVERAGE1, i*0.005);
		printf("===================================================================\n");
	}
}

int main() {
	file = fopen(filename, "r");
	first = 1; peakmem.SPKF = 500; peakmem.NPKF = 500; peakmem.RR_COUNTER = 0;
	peakmem.THRESHOLD1 = 1000; peakmem.THRESHOLD2 = 500; peakmem.RR_LOW = 100; peakmem.RR_HIGH = 200;
	et = 0; to = 0; tre = 0; fire = 0; fem = 0; mem.index[7] = -1; mem.index[8] = -1;

//	printf("RR_LOW < RR < RR_HIGH\n");

	int i = 0;

	int iterations = 5000;

	int j = 1;

	//for (; j < 101; j++){

	for (i = 0; i < iterations*j; i++) {
		maininput();
		mainlowpass();
		mainhighpass();
		mainderivative();
		mainsquarred();
		mainmwi();

//		printf("%d: ", (i+1));
//		printf("%d:    Low-Pass = %i, High-Pass = %i, Derivative = %i, Squarred = %i, MWI = %i\n", (i+1), mem.lpmem[mem.index[1]], mem.hpmem[mem.index[2]], mem.derivativemem, mem.squarredmem[mem.index[3]], mem.mwimem[mem.index[4]]);

		peaksbullshit(i-1, 0);
//		printf("%d ", peakmem.THRESHOLD2);
//		printf("%d ", peakmem.THRESHOLD2);

		update();

//		printf("%d: %d\n", i, peakmem.rpeaks[mem.index[6]-1]);

		first = 0;
	}
	//memPrint();
	//printBullshit(10,5,1);
	printf("\nEt = %d To = %d Tre = %d Fire = %d Fem = %d iterations = %d rPeak = %d\n", et, to, tre, fire, fem, iterations*j-et-to-tre-fire-fem, mem.index[6]);
	//}
	return 0;
}
