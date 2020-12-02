#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main()
{
	int i = 0, result = 0, counter = 0;
	char buffer =  '\0' ;
	char password[50] =  "\0" ;
	int policy[2] = {0, 0};
	char letter = '\0';
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 1385) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}



	while (!feof(fp))
	{
		i = 0;
		buffer='\0';

		fscanf(fp, "%d",&policy[0]);
		fscanf(fp, "%c",&buffer);
		fscanf(fp, "%d",&policy[1]);
		fscanf(fp, "%c",&buffer);
		fscanf(fp, "%c",&letter);
		fscanf(fp, "%c",&buffer);
		fscanf(fp, "%c",&buffer);

		while(buffer!='\n' && !feof(fp))
		{
			fscanf(fp, "%c",&buffer);
			password[i] = buffer;
			i++;

		}
		if(!feof(fp))
		{
			counter = 0;
			for(int i = 0; i < 50; i++)
			{
				if(password[i] == letter)
					counter++;
			}

			if(counter >= policy[0] && counter <= policy[1])
				result++;
		}

		memset(password, 0,50*sizeof(char));
	}

	printf("%d\n", result);

	return 0;
}
