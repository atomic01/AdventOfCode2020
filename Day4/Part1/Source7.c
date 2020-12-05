#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int validatePassport(char * );

int main()
{
	int i = 0, endLineCounter = 0, result = 0;
	char buffer =  '\0' ;
	char passportData[100] = {"\0"};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2237) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%c", &buffer);
		if(buffer!='\n')
		{
			passportData[i] = buffer;
			endLineCounter = 0;
			i++;
		}
		else
		{
			passportData[i] = ' ';
			if( endLineCounter == 0)
			{
				endLineCounter++;
				i++;
			}
			else if(endLineCounter == 1)
			{
				result += validatePassport(&passportData[0]);
				memset(passportData, '\0', 100*sizeof(char));
				i = 0;
			}
		}
	}

	if(feof(fp))
		result += validatePassport(&passportData[0]);

	printf("%d", result);

	return 0;
}


int validatePassport(char passportData[])
{
	if(strstr(passportData, "byr") == NULL) return 0;
	if(strstr(passportData, "iyr") == NULL) return 0;
	if(strstr(passportData, "eyr") == NULL) return 0;
	if(strstr(passportData, "hgt") == NULL) return 0;
	if(strstr(passportData, "hcl") == NULL) return 0;
	if(strstr(passportData, "ecl") == NULL) return 0;
	if(strstr(passportData, "pid") == NULL) return 0;

	return 1;
}
