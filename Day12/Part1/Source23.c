#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#define sampleSize 786

int calculateManDistToDestination(char *, int *);
void changeCoordinates(char, int *, char , int);
char changeDirection(char, char, int);

int main()
{
	int i = 0, done = 0, result = 0, number = 0;
	char buffer =  '\0' ;
	int commandNumbers[sampleSize] = {0};
	char commandLetters[sampleSize] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2144) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%c%d", &buffer, &number);
		if(feof(fp))
			done = 1;
		else
		{
			if(buffer=='\n')
				i++;

			else
			{
				commandLetters[i] = buffer;
				commandNumbers[i] = number;
			}
		}
	}

	commandLetters[i] = buffer;
	commandNumbers[i] = number;

	result = calculateManDistToDestination(&commandLetters[0], &commandNumbers[0]);
	printf("%d\n", result);

	return 0;
}

int calculateManDistToDestination(char *letters, int *numbers)
{
	char direction = 'E';
	int coordinates[2] = {0,0};

	for(int i = 0; i < sampleSize; i++)
	{
		if(letters[i] == 'R' || letters[i] == 'L')
			direction = changeDirection(direction, letters[i], numbers[i]);
		else
			changeCoordinates(direction, &coordinates[0], letters[i], numbers[i]);
	}

	return abs(coordinates[0]) + abs(coordinates[1]);
}

void changeCoordinates(char direction, int *coordinates, char letter, int number)
{
	if(letter == 'F')
	{
		if(direction == 'E')
			coordinates[0] += number;
		else if(direction == 'W')
			coordinates[0] -= number;
		else if(direction == 'N')
			coordinates[1] += number;
		else if(direction == 'S')
			coordinates[1] -= number;
	}
	if(letter == 'E')
		coordinates[0] += number;
	else if(letter == 'W')
		coordinates[0] -= number;
	else if(letter == 'N')
		coordinates[1] += number;
	else if(letter == 'S')
		coordinates[1] -= number;
}

char changeDirection(char direction, char letter, int number)
{
	char directions[4] = {'E', 'S', 'W', 'N'};
	int temp = number/90;
	int i = 0;

	for(int j=0; j < 4; j++)
		if(direction == directions[j])
			i = j;

	if(letter == 'R')
		i += temp;
	else if(letter == 'L')
		i -= temp;

	if( i >= 4 )
		i%=4;
	else if(i < 0)
		i+=4;

	return directions[i];
}





