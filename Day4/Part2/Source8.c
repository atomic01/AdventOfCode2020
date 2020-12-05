#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int validatePassport(char * );

int main()
{
	int i = 0, endLineCounter = 0, result = 0, done = 0;
	char buffer =  '\0' ;
	char passportData[100] = {"\0"};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2180) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%c", &buffer);
		if(!feof(fp))
		{
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
		else
		{
			result += validatePassport(&passportData[0]);
			done = 1;
		}
	}

	printf("%d", result);

	return 0;
}



int validatePassport(char passportData[])
{
	char field[13][3] = {"byr","\0", "iyr", "\0", "eyr", "\0", "hgt", "\0", "hcl", "\0", "ecl", "\0", "pid" };
	char allowedCharacters[16] = "0123456789abcdef";
	char eyeColors[28] = "amb blu brn gry grn hzl oth";
	char *fieldLocation = NULL;
	int year = 0, height = 0, digit = 0;
	char heightUnit[3] = {"\0"};
	char buffer[10] = {"\0"};

	for(int i = 0; i < 13; i+=2)
	{
		fieldLocation = strstr(passportData, field[i]);
		if(fieldLocation == NULL)
			return 0;

		if(i<=4)
		{
			strncpy(buffer, fieldLocation + 4*sizeof(char), 4);
			year = atoi(buffer);
			if(i==0 && ( year < 1920 || year > 2002))
					return 0;
			else if(i==2 && ( year < 2010 || year > 2020))
					return 0;
			else if(i==4 && ( year < 2020 || year > 2030))
					return 0;
		}
		else if(i==6)
		{
			strncpy(heightUnit, fieldLocation + 6*sizeof(char), 3);
			if(strstr(heightUnit, "cm") != NULL)
			{
				strncpy(buffer, fieldLocation +  4*sizeof(char), 3);
				height = atoi(buffer);
				if(height < 150 || height > 193)
					return 0;
			}
			else if(strstr(heightUnit, "in") != NULL)
			{
				strncpy(buffer, fieldLocation + 4*sizeof(char), 2);
				height = atoi(buffer);
				if(height < 59 || height > 76)
					return 0;
			}
			else
				return 0;
		}
		else if(i==8)
		{
			strncpy(buffer, fieldLocation +  4*sizeof(char), 7);
			if(buffer[0]!='#')
				return 0;

			for(int j = 1; j < 7; j++)
				if(strchr(allowedCharacters, buffer[j]) == NULL || buffer[j]=="\0")
					return 0;

		}
		else if(i==10)
		{
			strncpy(buffer, fieldLocation +  4*sizeof(char), 3);
			if(strstr(eyeColors, buffer) == NULL || buffer=="\0")
				return 0;
		}
		else if(i==12)
		{
			strncpy(buffer, fieldLocation +  4*sizeof(char), 10);
			if(buffer[9]!=' ' && buffer[9]!='\0' && buffer[9]!='\n')
				return 0;

			for(int j = 0; j < 9; j++)
			{
				digit = buffer[j] - '0';
				if(isdigit(digit))
					return 0;
			}

		}

		memset(buffer, 0, 10*sizeof(char));
	}

	return 1;
}
