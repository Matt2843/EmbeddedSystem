/*
 * High-Pass.h
 *
 *  Created on: 16/09/2015
 *      Author: LiseAndersen
 */

#ifndef HIGHPASS_H_
#define HIGHPASS_H_

int highpass(int x, int x16, int x17, int x32, int y1){
	return y1-x/32+x16-x17+x32/32;
}

#endif /* HIGHPASS_H_ */
