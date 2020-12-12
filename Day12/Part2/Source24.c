#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

#define sampleSize 786

void rotateWaypoint(int *, char , int );
int calculateManDistToDestination(char *, int *);
void moveWaypoint(int *, char , int );

int main()
{
	int i = 0, done = 0, result = 0, number = 0;
	char buffer =  '\0' ;
	int commandNumbers[sampleSize] = {0};
	char commandLetters[sampleSize] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2160) // to get past the text for the puzzle in the txt file where i stored the numbers
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
	int waypointInfo[6] = {10,1,  1,0,0,1};
	int shipInfo[6] = {0,0,  1,0,0,1};		//coordinates,, E , S , W , N booleans

	for(int i = 0; i < sampleSize; i++)
	{
		if(letters[i] == 'R' || letters[i] == 'L')
			rotateWaypoint(&waypointInfo[0], letters[i], numbers[i]);
		else if(letters[i] == 'F' )
			moveShip(&shipInfo[0], &waypointInfo[0], numbers[i]);
		else
			moveWaypoint(&waypointInfo[0], letters[i], numbers[i]);
	}

	return shipInfo[0] + shipInfo[1];
}

void rotateWaypoint(int *waypointInfo, char letter, int number)
{
	int count = number/90;
	int i = 0, temp = 0, newCordsI = 0;
	int newCoordinates[2] = {0,0};

	for(int j = 2; j < 6; j++)
	{
		if(waypointInfo[j] == 1)
		{
			if(letter == 'R')
				i = j + count;
			else if(letter == 'L')
				i = j - count;

			if(i > 5)
				i = i%6 + 2;
			else if(i < 2)
				i += 4;

			newCoordinates[newCordsI] = i;
			newCordsI++;
			waypointInfo[j] = 0;
		}
	}

	waypointInfo[newCoordinates[0]] = 1;
	waypointInfo[newCoordinates[1]] = 1;

	if(count%2==1)
	{
		temp = waypointInfo[0];
		waypointInfo[0] = waypointInfo[1];
		waypointInfo[1] = temp;
	}
}

void moveWaypoint(int *waypointInfo, char letter, int number)
{
	int temp = 0;
	char directions[4] = {'E', 'S', 'W', 'N'};

	for(int i = 0;  i < 4; i++)
	{
		if(letter==directions[i] && waypointInfo[i+2] == 1)
			waypointInfo[i%2]+= number;
		else if (letter==directions[i] && waypointInfo[i+2] == 0)
			waypointInfo[i%2]-= number;
	}

	for(int i = 0; i < 2; i++)
	{
		if(waypointInfo[i] < 0)
		{
			waypointInfo[i] = abs(waypointInfo[i]);
			temp = waypointInfo[i+2];
			waypointInfo[i+2] = waypointInfo[i+4];
			waypointInfo[i+4] = temp;
		}
	}
}

void moveShip(int *shipInfo, int *waypointInfo, int number)
{
	int temp = 0;

	for(int i = 0; i < 2; i++)
	{
		if(shipInfo[i+2] == waypointInfo[i+2])
			shipInfo[i] += number * waypointInfo[i];
		else
			shipInfo[i] -= number * waypointInfo[i];
	}

	for(int i = 0; i < 2; i++)
	{
		if(shipInfo[i] < 0)
		{
			shipInfo[i] = abs(shipInfo[i]);
			temp = shipInfo[i+2];
			shipInfo[i+2] = shipInfo[i+4];
			shipInfo[i+4] = temp;
		}
	}
}
