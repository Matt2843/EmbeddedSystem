/*Authors: Mathias, Lise & Albert 
29/9/2015
*/
#include <stdio.h>
#ifndef SENSOR_H_
#define SENSOR_H_

int getNextData(FILE *file, int data){
	fscanf(file, "%i", &data);
	return data;
}

#endif
