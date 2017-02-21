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
#include <string.h>

double* fileToArray(int num);
void printUsage(void);
double* offset(double* array, double offsetValue);
double* scale(double* array, double scaleValue);
void saveFloatFile(char* filename, double* numArray, double factor);
void saveIntFile(char* filename, double* numArray, double factor);
double maxValue(double* numArray);
double meanValue(double* numArray);

int arrayLength, numMax;

int main(int argc, char* argv[]) {
	double* array;
	int i, stringLength, fileNumber;
	int foundN = 0;
	double offsetValue, scaleValue;
	char arg;
	for(i=0; i<argc; i++){
		if((argv[i][0] == '-')&&(argv[i][1] == 'n')){
			foundN = 1;
			if(atoi(argv[i+1]) <= 11 && atoi(argv[i+1]) >= 1){
				fileNumber = atoi(argv[i+1]);
				array = fileToArray(fileNumber);
			} else {
				printUsage();
				exit(0);
			}
			break;
		}
	}
	if(foundN != 1){
		printUsage();
		exit(0);
	}
	for(i=0; i<argc; i++){
		if(argv[i][0] == '-'){
			arg = argv[i][1];
			switch(arg){
				case 'n':
					break;
				case 'o':{
					if (sscanf(argv[i+1], "%lf", &offsetValue) == 0){ //check that a valid float value was input
						printUsage();
						exit(0);
					}
					double * offsetArray;
					char offsetFilename[20];
					sprintf(offsetFilename, "Offset_data_%02d.txt", fileNumber);
					offsetArray = offset(array, offsetValue);
					saveFloatFile(offsetFilename, offsetArray, offsetValue);
					free(offsetArray);
					break;
				}
				case 's':{
					if (sscanf(argv[i+1], "%lf", &scaleValue) == 0){ //check that a valid float value was input
						printUsage();
						exit(0);
					}
					double * scaleArray;
					char scaleFilename[20];
					sprintf(scaleFilename, "Scaled_data_%02d.txt", fileNumber);
					scaleArray = scale(array, scaleValue);
					saveFloatFile(scaleFilename, scaleArray, scaleValue);
					free(scaleArray);
					break;
				}
				case 'r': {
					stringLength = strlen(argv[i+1]);
					if((argv[i+1][stringLength-1]!='t')||(argv[i+1][stringLength-2]!='x')||(argv[i+1][stringLength-3]!='t')||(argv[i+1][stringLength-4]!='.')){ //Check that a valid .txt filename was entered
						printUsage();
						exit(0);
					}
					saveIntFile(argv[i+1], array, numMax);
					break;
				}

				case 'h':
					printUsage();
					exit(0);
					break;
				case 'S':{
					FILE* sfp;
					char statisticsFilename[25];
					sprintf(statisticsFilename, "Statistics_data_%02d.txt", fileNumber);
					sfp = fopen(statisticsFilename, "w+");
					fprintf(sfp, "%lf %lf", meanValue(array), maxValue(array));
					fclose(sfp);
				}
					break;
				case 'C':
					break;
				case 'N':
					break;
				default:
					printUsage();
					exit(0);
					break;
			}
		}
	}
	free(array);
	return EXIT_SUCCESS;
}

double* fileToArray(int num){
	double* dataArray;
	int x=0;
	FILE *fp;
	char snum[3];
	char filename[16] = "Raw_data_";
	num < 10 ? sprintf(snum, "0%d", num) : sprintf(snum, "%d", num); //convert given integer into string for filename
	strcat(filename, snum);
	strcat(filename, ".txt");
	fp=fopen(filename, "r");
	fscanf(fp, "%d %d\n", &arrayLength, &numMax); //read in number of values and maximum value
	dataArray = calloc(arrayLength, sizeof(double)); //allocate memory for number of integers
	while(fscanf(fp, "%lf", &dataArray[x++]) != EOF){} //scan values into integer array
	fclose(fp);
	return dataArray;
}

void printUsage(){
	printf("\nUsage:\n");
	printf("-n <file number>\tNumber of file to open, between 1 and 11\n");
	printf("-o <offset value>\tOffset the data by the given value\n");
	printf("-s <scale factor>\tScale the data by the given scaling factor\n");
	printf("-r <new filename>\tCreate a copy of the file with the given filename\n");
	printf("-h\t\t\tDisplay usage instructions\n");
	printf("-S\t\t\tDisplay data statistics\n");
	printf("-C\t\t\tCenter the data\n");
	printf("-N\t\t\tNormalize the data\n");
}

double* offset(double* array, double offsetValue){
	int i;
	double* newArray = calloc(arrayLength, sizeof(double));
	for(i=0;i<arrayLength;i++){
		newArray[i] = array[i] + offsetValue;
	}
	return newArray;
}

double* scale(double* array, double scaleValue){
	int i;
	double* newArray = calloc(arrayLength, sizeof(double));
	for(i=0;i<arrayLength;i++){
		newArray[i] = array[i] * scaleValue;
	}
	return newArray;
}

void saveFloatFile(char* newFilename, double* numArray, double factor){
	FILE* fp;
	int i;
	fp = fopen(newFilename, "w+");
	fprintf(fp, "%d %.4lf\n", arrayLength, factor);
	for(i=0;i<arrayLength;i++){
		fprintf(fp, "%.4lf\n", numArray[i]);
	}
	fclose(fp);
}

void saveIntFile(char* newFilename, double* numArray, double factor){
	FILE* fp;
	int i;
	fp = fopen(newFilename, "w+");
	fprintf(fp, "%d %d\n", arrayLength, (int)factor);
	for(i=0;i<arrayLength;i++){
		fprintf(fp, "%d\n", (int)numArray[i]);
	}
	fclose(fp);
}

double maxValue(double* numArray){
	int i;
	double max;
	max = numArray[0];
	for(i=1;i<arrayLength;i++){
		if (numArray[i] > max){
			max = numArray[i];
		}
	}
	return max;
}

double meanValue(double* numArray){
	int i;
	double mean;
	mean = numArray[0];
	for(i=1;i<arrayLength;i++){
		mean += numArray[i];
	}
	return (mean/(double)arrayLength);
}
