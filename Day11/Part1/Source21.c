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

	while (i < 2637) // to get past the text for the puzzle in the txt file where i stored the numbers
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
	int occupiedSeats = 0, changeMade = 0;

	for(int i = 0; i < sampleRows; i++)
	{
		for(int j = 0; j < sampleColumns; j++)
		{
			for(int x = -1; x < 2; x++)
			{
				for(int y = -1; y < 2; y++)
				{
					if( (i+x > sampleRows -1) ||  (j+y > sampleColumns -1) || (i+x < 0) || (j+y < 0))
						;
					else if( !(x==0 && y==0) && *((layout + (i+x)*sampleColumns) + (j+y)) =='#'  )
						occupiedSeats++;
				}
			}

			if(*((layout + i*sampleColumns) + j)=='L' && occupiedSeats == 0)
			{
				*((updatedLayout + i*sampleColumns) + j) = '#';
				changeMade = 1;
			}
			if(*((layout + i*sampleColumns) + j)=='#' && occupiedSeats >= 4)
			{
				*((updatedLayout + i*sampleColumns) + j) = 'L';
				changeMade = 1;
			}
			occupiedSeats = 0;
		}
	}

	return changeMade;
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


