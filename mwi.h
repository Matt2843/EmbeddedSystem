/*
 * MWI.h
 *
 *  Created on: 16/09/2015
 *      Author: LiseAndersen
 */

#ifndef MWI_H_
#define MWI_H_

int mwi(int *a, int length){
	int i = 0, y = 0;
	for(; i < length; i++){
		y += a[i];
	}
	return y/length;
}

#endif /* MWI_H_ */
