#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define true 1
#define false 0

int main()
{
    char string1[99];
    char string2[99];    
    float weight;
    float convertWeight;   
    int loop = true;
    int digit = false;
    int i;
    
    printf("Please enter the weight and unit (k, lb, oz, g) separated by a space\n");
    
    while (loop == true) /*keeps looping until the user enters a proper number and unit*/
    {
        scanf("%s %s", string1, string2);
        
        printf("\n");       
        
        digit = false;  /*reset condition to false*/
        for(i = 0; i<strlen(string1); i++)    /*check the digits in the user's input*/
        {
            if(isdigit(string1[i]) != true)   /*if the function to check if the input is numerical returns false, prompt user to enter input again*/
            {
                loop = true;    /*loop will loop again*/
                digit = false;   /*condition to check if there's a digit is false*/
                break;          /*break out of for loop*/
            }
        }
        if(digit == false)
        {
            loop = true;
            printf("enter a proper number/unit");
            /*if the user does not enter an accepted number/unit, the loop repeats*/
        }
        else
        {
            if(string2[0] == 'k')
            {
                weight = atof(string1);
                loop = false;
                convertWeight = weight * 2.20462;
                printf("%.2f k is %.2f lb", weight, convertWeight);
            }
            else if((string2[0] == 'l') && (string2[1] == 'b'))
            {
                weight = atof(string1);
                loop = false;
                convertWeight = weight * 0.453592;        
                printf("%.2f lb is %.2f k", weight, convertWeight);     
            }
            else if((string2[0] == 'o') && (string2[1] == 'z'))
            {
                weight = atof(string1);
                loop = false;
                convertWeight = weight * 28.3495;         
                printf("%.2f oz is %.2f g", weight, convertWeight);
            }
            else if(string2[0] == 'g')
            {
                weight = atof(string1);
                loop = false;
                convertWeight = weight * 0.035274;         
                printf("%.2f g is %.2f oz", weight, convertWeight);
            }
            else
            {
                loop = true;
                printf("enter a proper number/unit");
                /*if the user does not enter an accepted number/unit, the loop repeats*/
            }
        }
    }
    
    return 0;
}