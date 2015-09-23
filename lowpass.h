#ifndef LOWPASS_H_
#define LOWPASS_H_


int lowpass(int x, int x6, int x12, int y1, int y2){
	return 2*y1-y2+(x-2*x6+x12)/32;
}

#endif /* LOWPASS_H_ */
