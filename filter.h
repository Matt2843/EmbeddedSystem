#ifndef FILTER_H_
#define FILTER_H_

int lowpass(int x, int x6, int x12, int y1, int y2){
	return 2*y1-y2+(x-2*x6+x12)/32;
}

int highpass(int x, int x16, int x17, int x32, int y1){
	return y1-x/32+x16-x17+x32/32;
}

int derivative(int x, int x1, int x3, int x4){
	return (2*x+x1-x3-2*x4)/8;
}

int squarring(int x){
	return x*x;
}

int mwi(int *a, int length){
	int i = 0, y = 0;
	for(; i < length; i++){
		y += a[i];
	}
	return y/length;
}

#endif /* FILTER_H_ */