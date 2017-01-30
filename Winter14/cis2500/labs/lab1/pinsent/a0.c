#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 100

int main(void)
{
    /*Variable declarations*/
    char userWeight[MAXSIZE];
    char userNum[MAXSIZE] = "";
    float convMeas;
    int i;

    
    printf("For measurements, type...\n'k' for kilograms into pounds \n'lb' for pounds into kilograms,\n");
    printf("'oz' for ounces into grams\n'g' for grams into ounces. \nType 'q' to quit.\n\n");
    
    do
    {
        /*User Weight Input*/
        printf("Please enter a weight and measurement to be converted. (eg. 100 lb)\n");
        printf("> ");
        fgets(userWeight,MAXSIZE,stdin);

        /*Number Extractor*/
        for (i=0; i<MAXSIZE; i++)
        {
            if (isdigit(userWeight[i]))
            {
                userNum[i] = userWeight[i]; /*userNum is the number the user entered*/
            }   
        }
    
        /*Weight Conversions*/
        if (strchr(userWeight, 'k')) /*Converts kg into lb*/
        {
            convMeas = (float)atoi(userNum) * 2.2046;
            printf("%.4fkg = %.4flbs\n", (float)atof(userWeight), convMeas);
        }
        else if (strchr(userWeight, 'l') && strchr(userWeight, 'b')) /*Converts lb into kg*/
        {
            convMeas = (float)atof(userNum) / 2.204;
            printf("%.4flbs = %.4fkg\n", (float)atof(userWeight), convMeas);
        }
        else if (strchr(userWeight, 'o') && strchr(userWeight, 'z')) /*Converts oz into g*/
        {
            convMeas = (float)atof(userNum) / 0.035274;
            printf("%.4foz = %.4fg\n", (float)atof(userWeight), convMeas);
        }
        else if (strchr(userWeight, 'g')) /*Converts g into oz*/
        {
            convMeas = (float)atof(userNum) * 0.035274;
            printf("%.4fg = %.4foz\n", (float)atof(userWeight), convMeas);
        }
        else if (strchr(userWeight, 'q')) /*User Quits*/
        {
            printf("Have a nice day!\n");
        }
        else /*User Proofing*/
        {
            printf("\nFor measurements, type...\n'k' for kilograms into pounds \n'lb' for pounds into kilograms,\n");
            printf("'oz' for ounces into grams\n'g' for grams into ounces. \nType 'q' to quit.\n\n");
        }
    }
    while (!strchr(userWeight, 'q'));
       
    return 0;
}