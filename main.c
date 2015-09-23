#include "main.h"

void memPrint(){
	int i = 0;
	for(; i<13; i++){
		printf("%d ", mem.input[i]);
	}
	printf("\n    ");
	for(i = 0; i<33; i++){
		printf("%d ", mem.lpmem[i]);
	}
	printf("\n    ");
	for(i = 0; i<5; i++) {
		printf("%d ", mem.hpmem[i]);
	}
	printf("\n \n");
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

void mainmwi() {
	mem.mwimem[getIndex(3, mem.index[4]-first, 1)] = mwi(mem.squarredmem, 31);
	//printf("%d", 1-first);	// se output.
	mem.index[4] += 1-first;
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
	if(mem.index[3] >= 31){
		mem.index[3] = 0;
	}
	if(mem.index[4] >= 4){
		mem.index[4] = 0;
	}

	return 0;
}

void maininput() {
	mem.input[getIndex(13, mem.index[0]-first, 1)] = getNextData(file, data);
	mem.index[0] += 1-first;
}

void mainlowpass() {
	mem.lpmem[getIndex(33, mem.index[1]-first, 1)] = lowpass(
			mem.input[getIndex(13, mem.index[0], 0)],
			mem.input[getIndex(13, mem.index[0], -6)],
			mem.input[getIndex(13, mem.index[0], -12)],
			mem.lpmem[getIndex(33, mem.index[1], 0)],
			mem.lpmem[getIndex(33, mem.index[1], -1)]);

	mem.index[1] += 1-first;

}

void mainhighpass() {
	mem.hpmem[getIndex(5, mem.index[2]-first, 1)] = highpass(
			mem.lpmem[getIndex(33, mem.index[1], 0)],
			mem.lpmem[getIndex(33, mem.index[1], -16)],
			mem.lpmem[getIndex(33, mem.index[1], -17)],
			mem.lpmem[getIndex(33, mem.index[1], -32)],
			mem.hpmem[getIndex(5, mem.index[2], 0)]);

//		printf("%d:    x = %d, x-16 = %d, x-17 = %d, x-32 = %d, y-1 = %d     HIGH PASS RESULT: %d\n", count, mem.lpmem[getIndex(33, mem.index[1], 0)], mem.lpmem[getIndex(33, mem.index[1], -16)], mem.lpmem[getIndex(33, mem.index[1], -17)], mem.lpmem[getIndex(33, mem.index[1], -32)], mem.hpmem[getIndex(5, mem.index[2], 0)], mem.hpmem[getIndex(5, mem.index[2]-mem.first[2], 1)]);

//		printf("%d:", highpass(-60,0,0,0,1));

	//printf("*\n");

	mem.index[2] += 1;
}

void mainderivative() {
	mem.derivativemem = derivative(mem.hpmem[getIndex(5, mem.index[2], 0)],
			mem.hpmem[getIndex(5, mem.index[2], -1)],
			mem.hpmem[getIndex(5, mem.index[2], -3)],
			mem.hpmem[getIndex(5, mem.index[2], -4)]);
}

void mainsquarred() {
	mem.squarredmem[getIndex(31, mem.index[3]-first, 1)] = squarring(mem.derivativemem);
	mem.index[3] += 1-first;
}

int main() {
	file = fopen(filename, "r");
	first = 1;

	int i = 0;
	for (i = 0; i < 10000; i++) {
		maininput();
		mainlowpass();
		mainhighpass();
		mainderivative();
		mainsquarred();
		mainmwi();

//		memPrint();
		printf("%d:    Low-Pass = %i, High-Pass = %i, Derivative = %i, Squarred = %i, MWI = %i\n", (i+1), mem.lpmem[mem.index[1]], mem.hpmem[mem.index[2]], mem.derivativemem, mem.squarredmem[mem.index[3]], mem.mwimem[mem.index[4]]);

		update();
		first = 0;
	}
	return 0;
}
