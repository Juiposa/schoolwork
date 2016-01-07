/****************************
Jeffrey-David Kapp
0832671
CIS3090 A2
11 Novmeber 2015
****************************/

#include "aldo.h"

int numT; //number of threads

char * aldodir;
char * imagedir;
char aldoFileNames[10][15];

long imageID; //_find id for image directory
struct _finddata_t  imageData; //data for a image file

int *** aldos; //3d array of all aldos
int numAldos = 0;
int allAldoRows[100]; //stored dimensions of all the parallaldos
int allAldoCols[100];

pthread_mutex_t mutex_nextFile = PTHREAD_MUTEX_INITIALIZER;

int main( int argc, char * argv[] ) {
	pthread_t tid[16];
	
	long fileID;
	struct _finddata_t fileData;
	FILE * fp;
	int aldoRows = 0, aldoCols = 0; //dimensions of an aldo
	char inStr[10];
	char inChar;
	char * token;
	char dump[100];
	int i = 0, j = 0, k = 0;
	double timeTaken;
	StartTime();
	if( argc != 4 ) {
		printf("Not enough arguments.\n");
		getchar();
	}
	
	numT = atoi(argv[3]);

	aldodir = (char *)malloc(sizeof(char)*strlen(argv[1])+1);
	strcpy(aldodir, argv[1]);
	imagedir = (char *)malloc(sizeof(char)*strlen(argv[2])+1);
	strcpy(imagedir, argv[2]);

	if(_chdir(aldodir)) { 
		printf("Cannot find directory.\n");
		exit(1);
	}

	//constructing the aldos
	//assume there are going to be at most 100 aldos
	aldos = (int***) malloc(sizeof(int**)*100);
	fileID = _findfirst("*.txt", &fileData);
	do {
		strcpy(aldoFileNames[i], fileData.name);
		fp = fopen(fileData.name, "r");

		fgets(inStr, 10, fp);
		token = strtok(inStr, " ");
		aldoRows = atoi(token);
		token = strtok(NULL, " ");
		aldoCols = atoi(token);
		allAldoRows[i] = aldoRows;
		allAldoCols[i] = aldoCols;

		aldos[i] = (int**)malloc(sizeof(int*)*aldoRows);
		for( j = 0; j < aldoRows; j++ ) {
		 aldos[i][j] = (int*)malloc(sizeof(int)*aldoCols);
		}
		
		for( j = 0; j < aldoRows; j++ ) {
			for ( k = 0; k < aldoCols; k++ ) {
				aldos[i][j][k] = fgetc(fp);
			}
			fgets(dump, 100, fp);
		}

		fclose(fp);
		i++;	
	} while (_findnext(fileID, &fileData)==0);
	_findclose(fileID);
	numAldos = i;
	//done constructing aldos
	
	if (_chdir(imagedir)) {
		printf("Cannot open image dir.\n");
		fgetc(stdin);
		exit(1);
	}

	imageID = _findfirst("*.img", &imageData);
	//thread creation
	for( i = 0; i < numT; i++ ) {
		pthread_create(&tid[i], NULL, thread_start, (void *)i);
	}
	//wait for threads to finish
	for ( i=0; i < numT; i++ ) {
		pthread_join(tid[i], NULL);
	}
	printf("Threads exit.\n");
	_findclose(imageID);
	free(aldodir);
	free(imagedir);

	timeTaken = EndTime();
	printf("Time taken: %.2lf\nInput any character to exit.\n", timeTaken);
	fgetc(stdin);
	return 0;
}

void *thread_start(void * index) {
	int ** myImage; //this threads assigned image
	int imgRows = 0, imgCols = 0;
	int aldoLocaRow, aldoLocaCol, aldoRotation; //locations and rotation of an aldo
	int i = 0, j = 0;

	//rotation variables
	int rotation = 0;
	int startRow = 0, startCol = 0;
	int rowMod = 0, colMod = 0;


	char * myFilename; //filename where assigned image is found
	char dump[100]; //dump for the ends of files
	char inStr[10]; //reading file dimensions from the top of the file
	char * token; //strtok ahoy

	FILE * fp;

	myFilename = (char*)malloc(sizeof(char)*13);

	while(1) {
		//exclusive section
		pthread_mutex_lock(&mutex_nextFile);
		fp = fopen(imageData.name, "r" );
		if (fp == NULL) {
			pthread_mutex_unlock(&mutex_nextFile);
			pthread_exit(NULL);
		}
		printf("Filename %s T%d\n", imageData.name,  index);
		if(0!=_findnext(imageID, &imageData)) {
			pthread_mutex_unlock(&mutex_nextFile);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(&mutex_nextFile);
		//END; exclusive section

		fgets(inStr, 10, fp);
		token = strtok(inStr, " ");
		imgRows = atoi(token);
		token = strtok(NULL, " ");
		imgCols = atoi(token);
		
		myImage = (int**)malloc(sizeof(int*)*imgRows);
		for( i = 0; i < imgRows; i++ ) {
			myImage[i] = (int*)malloc(sizeof(int)*imgCols);
		}

		for( i = 0; i < imgRows; i++ ) {
			for ( j = 0; j < imgCols; j++ ) {
				myImage[i][j] = fgetc(fp);
			}
			fgets(dump, 100, fp);
		}
		
		/*while(1 /*match not found) { //search algorithm
			for( i = 0; i < numAldos; i++ ) { //for each aldo
				if ( !(allAldoRows[i] > imgRows) && !(allAldoCols[i] > imgCols) ) { //reject if aldo is larger than image
					for( j = 0; j < 4; j++ ) { //for each 90 degree to rotation
						switch(j) {
							case 0: //0 degrees
								rotation = 0;
								startRow = 0;
								startCol = 0;
								rowMod = 1;
								colMod = 1;
								break;
							case 1: //90 degrees
								rotation = 90;
								startRow = imgRows-1;
								startCol = 0;
								rowMod = -1;
								colMod = 1;
								break;
							case 2: //180 degrees
								rotation = 180;
								startRow = imgRows - 1;
								startCol = imgCols - 1;
								rowMod = -1;
								colMod = -1;
								break;
							case 3: //270 degrees 
								rotation = 270;
								startRow = 0;
								startCol = imgCols - 1;
								rowMod = 1;
								colMod = 1;
								break;
						}
					}
				}
			}
		}*/
		fclose(fp);
		fp = NULL;
		
		for( i = 0; i < imgRows; i++ ) {
			free(myImage[i]);
		}
		free(myImage);
	}
	pthread_exit(NULL);

	return 0;
}