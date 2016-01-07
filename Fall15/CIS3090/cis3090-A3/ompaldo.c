/****************************
Jeffrey-David Kapp
0832671
CIS3090 A2
11 Novmeber 2015
****************************/

#include "ompaldo.h"

int numT; //number of threads

char * aldodir;
char * imagedir;
char aldoFileNames[100][20];

long imageID; //_find id for image directory
struct _finddata_t  imageData; //data for a image file

int *** aldos; //3d array of all aldos
int *** aldos90; 
int *** aldos180;
int *** aldos270;
int numAldos = 0;
int allAldoRows[100]; //stored dimensions of all the parallaldos
int allAldoCols[100];

int main( int argc, char * argv[] ) {
	
	long fileID;
	struct _finddata_t fileData;
	FILE * fp;
	int aldoRows = 0, aldoCols = 0; //dimensions of an aldo
	char inStr[10];
	char * token;
	char dump[100];
	int i = 0, j = 0, k = 0;
	double timeTaken = 0.0;
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
	aldos90 = (int***) malloc(sizeof(int**)*100);
	aldos180 = (int***) malloc(sizeof(int**)*100);
	aldos270 = (int***) malloc(sizeof(int**)*100);
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

		//0 and 180
		aldos[i] = (int**)malloc(sizeof(int*)*aldoRows);
		aldos180[i] = (int**)malloc(sizeof(int*)*aldoRows);
		for( j = 0; j < aldoRows; j++ ) {
			aldos[i][j] = (int*)malloc(sizeof(int)*aldoCols);
			aldos180[i][j] = (int*)malloc(sizeof(int)*aldoCols);
		}

		//90 and 270
		aldos90[i] = (int**)malloc(sizeof(int*)*aldoCols);
		aldos270[i] = (int**)malloc(sizeof(int*)*aldoCols);
		for( j = 0; j < aldoCols; j++ ) {
			aldos90[i][j] = (int*)malloc(sizeof(int)*aldoRows);
			aldos270[i][j] = (int*)malloc(sizeof(int)*aldoRows);
		}

		for( j = 0; j < aldoRows; j++ ) {
			for ( k = 0; k < aldoCols; k++ ) {
				aldos[i][j][k] = fgetc(fp) - '0';
				aldos90[i][k][aldoRows-j-1] = aldos[i][j][k];
				aldos180[i][aldoRows-j-1][aldoCols-k-1] = aldos[i][j][k];
				aldos270[i][aldoCols-k-1][j] = aldos[i][j][k];
			}
			fgets(dump, 100, fp);
		}

		//debug output
		/*printf("Rotation 0\n");
		for( j = 0; j < aldoRows; j++ ) {
			for( k = 0; k < aldoCols; k++ ) {
				printf("%d", aldos[i][j][k]);
			}
			printf("\n");
		}

		printf("Rotation 90\n");
		for( j = 0; j < aldoCols; j++ ) {
			for( k = 0; k < aldoRows; k++ ) {
				printf("%d", aldos90[i][j][k]);
			}
			printf("\n");
		}

		printf("Rotation 180\n");
		for( j = 0; j < aldoRows; j++ ) {
			for( k = 0; k < aldoCols; k++ ) {
				printf("%d", aldos180[i][j][k]);
			}
			printf("\n");
		}

		printf("Rotation 270\n");
		for( j = 0; j < aldoCols; j++ ) {
			for( k = 0; k < aldoRows; k++ ) {
				printf("%d", aldos270[i][j][k]);
			}
			printf("\n");
		}*/



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
	
	//call to omp
	#pragma omp parallel for private(i)
	for(i = 0; i < numT; i++ ) {
		imageSearch(i);
	}
	

	_findclose(imageID);
	free(aldodir);
	free(imagedir);

	timeTaken = EndTime();
	printf("Time taken: %.2lf\nInput any character to exit.\n", timeTaken);
	fgetc(stdin);
	return 0;
}

void imageSearch(int index) {
	int ** myImage; //this threads assigned image
	int ** activeAldo; //aldo rotation being searched
	int imgRows = 0, imgCols = 0;
	int i = 0, j = 0, k = 0, l = 0;

	int inImgRow = 0, inImgCol = 0; //current point from which search is being completed
	int rowMod = 0, colMod = 0; //modifiers for row/col for output, depending on rotation
	int activeRow = 0, activeCol = 0; //working dimensions; 
	int rotation = 0;
	int found; //if an aldo has been found in an image or not
	int noImagesLeft = 0;

	char myFilename[20]; //filename where assigned image is found
	char dump[100]; //dump for the ends of files
	char inStr[10]; //reading file dimensions from the top of the file
	char * token; //strtok ahoy

	FILE * fp;

	while(1) { //not actually infinite
		found = 0;
		//exclusive section


		#pragma omp critical
		{
			strcpy(myFilename, imageData.name);
			fp = fopen(myFilename, "r" );
			printf("Filename %s T%d\n", myFilename, index);
			if (fp == NULL) {
				noImagesLeft = 1;
			}
			if (0!=_findnext(imageID, &imageData)) {
				noImagesLeft = 1;
			}
		}
		//END; exclusive section

		if( noImagesLeft == 1 ) 
			return;

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
				myImage[i][j] = fgetc(fp) - '0';
			}
			fgets(dump, 100, fp);
		}
		
		//search
		for( i = 0; i < numAldos; i++ ) { //for each aldo
			if ( !(allAldoRows[i] > imgRows) && !(allAldoCols[i] > imgCols) ) { //reject if aldo is larger than image
				for( j = 0; j < 4; j++ ) { //for each 90 degree to rotation
					switch(j) { //setting up rotation dependant variables 
						case 0: //0 degrees 
							activeRow = allAldoRows[i]; activeCol = allAldoCols[i];
							colMod = 0; rowMod = 0;
							rotation = 0;
							activeAldo = aldos[i];
							break;
						case 1: //90 degrees
							activeRow = allAldoCols[i]; activeCol = allAldoRows[i];
							colMod = allAldoCols[i]; rowMod = 0;
							rotation = 90;
							activeAldo = aldos90[i];
							break;
						case 2: //180 degrees
							activeRow = allAldoRows[i]; activeCol = allAldoCols[i];
							colMod = allAldoCols[i]; rowMod = allAldoRows[i];
							rotation = 180;
							activeAldo = aldos180[i];
							break;
						case 3: //270 degrees
							activeRow = allAldoCols[i]; activeCol = allAldoRows[i];
							colMod = 0; rowMod = allAldoRows[i];
							rotation = 270;
							activeAldo = aldos[i];
							break;
					}
					for( inImgRow = 0; inImgRow < imgRows - activeRow; inImgRow++ ) { //from each cell in an image
					for( inImgCol = 0; inImgCol < imgCols - activeCol; inImgCol++ ) {
						k = 0; l = 0;
						while( k < activeRow && inImgRow + k < imgRows - 1 && myImage[inImgRow + k][inImgCol + l] == activeAldo[k][l] ) { //search for aldo at given cell
							l++;
							if( l == allAldoCols[i] - 1 ) { //if weve reached the end of a row
								if( k == allAldoRows[i] - 1 ) { //and weve exhausted the supply of rows
									//******MATCH FOUND******//
									//print results
									printf("$%s %s (%d,%d,%d)\n", aldoFileNames[i], myFilename, inImgRow + rowMod + 1, inImgCol + colMod + 1, rotation ); 
									found = 1;
									break;
								}					
								k++;
								l = 0;
							}

							if(found == 1) break;
						}
						if(found == 1) break;
						//else printf("%s %s Not here row: %d col: %d\n", myFilename, aldoFileNames[i], inImgRow, inImgCol);
					}
					if(found == 1) break;
					}
					if(found == 1) break;
				}
			}
			if(found == 1) break;
		}
		
		fclose(fp);
		fp = NULL;
		
		for( i = 0; i < imgRows; i++ ) {
			free(myImage[i]);
		}
		free(myImage);
	}
	return;
}