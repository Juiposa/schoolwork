#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_STRING_LENGTH 100

int numOfSpaces(char * str);
void getLeftSide(char * destination, const char * source);
void getRightSide(char * destination, const char * source);
int setOtherUnit(const char * originalUnit, char * otherUnit);
float convert(float valueToConvert, int convertMethod);
int isFloat(char * str);
void stringToLower(char * str);
void printBadInput(int status);
int checkRightSide(const char * str);
void printHelp();

int main()
{
    char inputString[MAX_STRING_LENGTH];
    char leftSide[100];
    char rightSide[100];
    char convertedUnit[3];
    int quit;
    int convertValue;
    float numToConvert;
    float convertedNumber;
    quit = 0;
    convertValue = 0;
    numToConvert = 0;
    convertedNumber = 0;

    printf("-------Metric <-> Imperial Measurement Converter-------\n");
    printf("\nType \"help\" for details or type \"quit\" to quit.\n");

    do
    {
        printf(">");
        fgets(inputString,MAX_STRING_LENGTH,stdin);
        inputString[strlen(inputString)-1] = '\0';
        stringToLower(inputString);

        if(strcmp(inputString,"help") == 0)
        {
            printHelp();
        }
        else if(strcmp(inputString,"quit") == 0)
        {
            quit = 1;
        }
        else
        {
            if(numOfSpaces(inputString)!= 1)
            {
                printBadInput(1);
                continue;
            }
            else
            {
                getLeftSide(leftSide,inputString);

                numToConvert = isFloat(leftSide);
                if(isFloat(leftSide) == 1)
                {
                    numToConvert = atof(leftSide);

                    getRightSide(rightSide,inputString);
                    if(checkRightSide(rightSide) == 1)
                    {
                        convertValue = setOtherUnit(rightSide,convertedUnit);
                        convertedNumber = convert(numToConvert,convertValue);

                        printf(">>%f %s\n\n",convertedNumber,convertedUnit);
                    }
                    else
                    {
                        printf("This program doesn't support converting from or to \"%s\", sorry.\nType \"help\" for a list of what can be converted.\n\n",rightSide);
                    }
                }
                else
                {
                    printBadInput(numToConvert);
                    continue;
                }
            }
        }


    }while(!quit);




return 0;
}

int numOfSpaces(char * str)
{
    int i;
    int counter;
    counter = 0;

    for (i=0;i<=strlen(str);i++)
    {
        if(str[i]==' ')
        {
            counter++;
        }
    }

    return counter;
}

void getLeftSide(char * destination, const char * source)
/*
Gets the left side of a string seperated by a space.
*/
{
    int i;
    char temp[MAX_STRING_LENGTH];
    strcpy(temp,source);

    for(i=0;i<=strlen(source);i++)
    {
        if(source[i] == ' ')
        {
            break;
        }
    }
    temp[i] = '\0';
    strcpy(destination,temp);
}

void getRightSide(char * destination, const char * source)
/*
Gets the right side of a string seperated by a space.
*/
{
    int i;
    char temp[MAX_STRING_LENGTH];
    int spaceMarker = 0;
    strcpy(temp, source);

    for(i=0;i<=strlen(source);i++)
    {
        if(source[i] == ' ')
        {
            spaceMarker = i+1;
            break;
        }
    }
    for(i=0;i<(strlen(source)-spaceMarker);i++)
    {
        destination[i] = source[spaceMarker+i];
    }
    destination[i] = '\0';
}

int isFloat(char * str)
/*
Checks to see if a given string qualifies as a float.
Return Values  1: String qualifies as a float and is positive.
              -1: Invalid Character.
              -2: Too many periods.
*/
{
    int i;
    int periodCounter;
    int negative;
    periodCounter = 0;
    negative = 0;

    for(i=0;i<strlen(str);i++) /*For every character in the string*/
    {
        if((isdigit(str[i]) == 0) && (str[i] !='.'))/*If it's not a 0-9 digit or a period*/
        {
            if(str[i]=='-' && i==0)/*If a hyphen is the first character*/
            {
                negative = 1;
            }
            else /*If it's an invalid character and not a hyphen at the front*/
            {
                return -1;/*Return an error*/
            }

        }
        else /*If it is a 0-9 digit or a period*/
        {
            if(str[i]=='.')/*If it's a period*/
            {
                periodCounter++;/*Keep track of our periods*/
                if(periodCounter > 1)/*If we've found more than 1 period*/
                {
                    return -2;/*Return an error*/
                }
            }
        }
    }



    return 1; /*Return 1 if we've made it through each character without hitting an error*/
}

void stringToLower(char * str)
{
    int i;

    for(i=0;i<=strlen(str);i++)
    {
        str[i] = tolower(str[i]);
    }

}

void printBadInput(int status)
{
    switch(status)
    {
        case 1:
            printf("Unrecognised format. ");
            break;
        case -1:
            printf("Invalid character found where the number should be.\n");
            break;
        case -2:
            printf("Too many periods in the number.\n");
            break;
        default:
            printf("Unspecified Error.\n");
    }
    printf("Type \"help\" for usage instructions.\n\n");
}

int checkRightSide(const char * str)
{
    int i;
    char acceptedUnits[4][3] = {"lb","k","g","oz"};

    for(i=0;i<4;i++)
    {
        if(strcmp(str,acceptedUnits[i]) == 0)
        {
            return 1;
        }
    }



return 0;
}

int setOtherUnit(const char * originalUnit, char * otherUnit)
{
    if(strcmp(originalUnit,"lb") == 0)
    {
        strcpy(otherUnit,"k");
        return 1;
    }
    else if(strcmp(originalUnit,"k") == 0)
    {
        strcpy(otherUnit,"lb");
        return 2;
    }
    else if(strcmp(originalUnit,"g") == 0)
    {
        strcpy(otherUnit,"oz");
        return 3;
    }
    else if(strcmp(originalUnit,"oz") == 0)
    {
        strcpy(otherUnit,"g");
        return 4;
    }

return 0;
}

float convert(float valueToConvert, int convertMethod)
{
    switch(convertMethod)
    {
        case 1: /*From lb to k*/
            return valueToConvert * .453592;
            break;
        case 2: /* k to lb*/
            return valueToConvert * 2.20462;
            break;
        case 3: /*g to oz*/
            return valueToConvert * .035274;
            break;

        case 4: /*oz to g*/
            return valueToConvert * 28.3495;
            break;
    }

return 0;
}



void printHelp()
{
    printf("\n--Usage Instructions--\nType the number you would like to convert, space, then the abbreviated unit.\nThe program will automatically convert it to the other measurment's equivalent.\nEg \"100 lb\" will convert 100 pounds to kilograms.\n");
    printf("--Conversions---------\nMetric          Imperial\n\nKilograms(k)    Pounds(lb)\nGram(g)         Ounce(oz)\n----------------------\n\n");
}
