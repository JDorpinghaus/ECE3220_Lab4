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
void saveFile(char* filename, double* numArray);

int arrayLength;
int numMax;

int main(int argc, char* argv[]) {
	double* array;
	int i, stringLength;
	int foundN = 0;
	double offset, scale;
	for(i=0; i<argc; i++){
		if((argv[i][0] == '-')&&(argv[i][1] == 'n')){
			foundN = 1;
			if(atoi(argv[i+1]) <= 11 && atoi(argv[i+1]) >= 1){
				array = fileToArray(atoi(argv[i+1]));
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
			switch(argv[i][1]){
			case 'n':
				break;
			case 'o':
				if (sscanf(argv[i+1], "%lf", &offset) == 0){ //check that a valid float value was input
					printUsage();
					exit(0);
				}
				double * offsetArray;
				offsetArray = offset(array, offset);

				free(offsetArray);
				break;
			case 's':
				if (sscanf(argv[i+1], "%lf", &scale) == 0){ //check that a valid float value was input
					printUsage();
					exit(0);
				}
				break;
			case 'r':
				stringLength = strlen(argv[i+1]);
				printf("\n\nlen: %d\n\n", stringLength);
				if((argv[i+1][stringLength-1]!='t')||(argv[i+1][stringLength-2]!='x')||(argv[i+1][stringLength-3]!='t')||(argv[i+1][stringLength-4]!='.')){ //Check that a valid .txt filename was entered
					printUsage();
					exit(0);
				}
				break;
			case 'h':
				printUsage();
				exit(0);
				break;
			case 'S':
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
	dataArray = calloc(arrayLength, sizeof(int)); //allocate memory for number of integers
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

void saveFile(char* filename, double* numArray){

}
