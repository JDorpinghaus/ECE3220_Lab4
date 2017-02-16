/*
 ============================================================================
 Name        : lab4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

int* fileToArray(int num);

int main(int argc, char* argv[]) {
	int* array;
	array = fileToArray(11);
	return EXIT_SUCCESS;
}

int* filetoArray(int num){
	int* dataArray;
	int numItems, numMax, currentNum;
	int x=0;
	FILE *fp;
	char snum[3];
	char filename[16] = "Raw_data_";
	num < 10 ? sprintf(snum, "0%d", num) : sprintf(snum, "%d", num); //convert given integer into string for filename
	strcat(filename, snum);
	strcat(filename, ".txt");
	fp=fopen(filename, "r");
	fscanf(fp, "%d %d\n", &numItems, &numMax); //read in number of values and maximum value
	dataArray = calloc(numItems, sizeof(int)); //allocate memory for number of integers
	while(fscanf(fp, "%d", &dataArray[x++]) != EOF){} //scan values into integer array
	return dataArray;
}
