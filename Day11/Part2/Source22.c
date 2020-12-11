#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define sampleRows 93
#define sampleColumns 97

int updateLayout(char *, char *);
void copyLayout(char *, char *);
int countOccupiedSeats(char *);

int main()
{
	int i = 0, j = 0, done = 0, result = 1;
	char buffer =  '\0' ;
	char layout[sampleRows][sampleColumns] = {"\0"};
	char updatedLayout[sampleRows][sampleColumns] = {"\0"};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2254) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 0;
	while (!done)
	{
		fscanf(fp, "%c", &buffer);
		if(feof(fp))
			done = 1;
		else
		{
			if(buffer=='\n')
			{
				i++;
				j=0;
			}
			else
			{
				layout[i][j] = buffer;
				updatedLayout[i][j] = buffer;
				j++;
			}
		}
	}

	while(result!=0)
	{
		result = updateLayout(&layout[0], &updatedLayout[0]);
		copyLayout(&layout[0], &updatedLayout[0]);
	}

	result = countOccupiedSeats(&layout[0]);
	printf("%d\n", result);

	return 0;
}

int updateLayout(char *layout, char *updatedLayout)
{
	int changeMade = 0;

	for(int i = 0; i < sampleRows; i++)
		for(int j = 0; j < sampleColumns; j++)
			changeMade+=updateSeat(&layout[0], &updatedLayout[0], i, j);

	return changeMade;
}

int updateSeat(char *layout, char *updatedLayout, int i, int j)
{
	int occupiedSeats = 0;
	int occupancy[8] = {0};//UP,DOWN,LEFT,RIGHT, UP-LEFT, UP-RIGHT, DOWN-LEFT, DOWN-RIGHT
	int max = sampleRows;

	if(sampleRows < sampleColumns)
		max = sampleColumns;

	for(int x = 1; x < max; x++)
	{
		if( i-x>=0 )							         //UP
		{
			if(occupancy[0] == 0)			            //straight
			{
				if(*((layout + (i - x)*sampleColumns) + j) =='#')
					occupancy[0] = 1;
				else if (*((layout + (i - x)*sampleColumns) + j) =='L')
					occupancy[0] = -1;
			}

			if(occupancy[4] == 0 && j-x>=0)			    //up-LEFT
			{
				if(*((layout + (i - x)*sampleColumns) + j-x) =='#')
					occupancy[4] = 1;
				else if (*((layout + (i - x)*sampleColumns) + j-x) =='L')
					occupancy[4] = -1;
			}

			if(occupancy[5] == 0 && j+x<sampleColumns )	//up-RIGHT
			{
				if(*((layout + (i - x)*sampleColumns) + j+x) =='#')
					occupancy[5] = 1;
				else if (*((layout + (i - x)*sampleColumns) + j+x) =='L')
					occupancy[5] = -1;
			}
		}

		if( i+x<sampleRows )							//DOWN
		{
			if(occupancy[1] == 0)						//straight
			{
				if(*((layout + (i + x)*sampleColumns) + j) =='#')
					occupancy[1] = 1;
				else if (*((layout + (i + x)*sampleColumns) + j) =='L')
					occupancy[1] = -1;
			}

			if(occupancy[6] == 0 && j-x>=0 )			//down-LEFT
			{
				if(*((layout + (i + x)*sampleColumns) + j-x) =='#')
					occupancy[6] = 1;
				else if (*((layout + (i + x)*sampleColumns) + j-x) =='L')
					occupancy[6] = -1;
			}

			if(occupancy[7] == 0 && j+x<sampleColumns)	//down-RIGHT
			{
				if(*((layout + (i + x)*sampleColumns) + j+x) =='#')
					occupancy[7] = 1;
				else if (*((layout + (i + x)*sampleColumns) + j+x) =='L')
					occupancy[7] = -1;
			}
		}

		if(occupancy[2] == 0 && j-x>=0 )				//LEFT
		{
			if(*((layout + i*sampleColumns) + j-x) =='#')
				occupancy[2] = 1;
			else if (*((layout + i*sampleColumns) + j-x) =='L')
				occupancy[2] = -1;
		}
		if(occupancy[3] == 0 && j+x<sampleColumns ) 	//RIGHT
		{
			if(*((layout + i*sampleColumns) + j+x) =='#')
				occupancy[3] = 1;
			else if (*((layout + i*sampleColumns) + j+x) =='L')
				occupancy[3] = -1;
		}
	}

	for(int i = 0; i < 8; i++)
		if(occupancy[i] > -1)
			occupiedSeats+=occupancy[i];

	if(*((layout + i*sampleColumns) + j)=='L' && occupiedSeats == 0)
	{
		*((updatedLayout + i*sampleColumns) + j) = '#';
		return 1;
	}
	if(*((layout + i*sampleColumns) + j)=='#' && occupiedSeats >= 5)
	{
		*((updatedLayout + i*sampleColumns) + j) = 'L';
		return 1;
	}


	return 0;
}

void copyLayout(char *layout, char *updatedLayout)
{
	for(int i = 0; i < sampleRows; i++)
		for(int j = 0; j < sampleColumns; j++)
			*((layout + i*sampleColumns) + j) = *((updatedLayout + i*sampleColumns) + j);
}

int countOccupiedSeats(char *layout)
{
	int occupiedSeats = 0;

	for(int i = 0; i < sampleRows; i++)
		for(int j = 0; j < sampleColumns; j++)
			if( *((layout + i*sampleColumns) + j) == '#')
				occupiedSeats++;

	return occupiedSeats;
}
