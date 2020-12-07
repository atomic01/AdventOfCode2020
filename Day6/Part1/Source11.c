#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int countVotingData(char *);

int main()
{
	int i = 0, done = 0, endLineCounter = 0, result = 0;
	char votingData[150] = {"\0"};
	char buffer =  '\0' ;
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 1819) // to get past the text for the puzzle in the txt file where i stored the numbers
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
			if(buffer!='\n')
			{
				votingData[i] = buffer;
				endLineCounter = 0;
				i++;
			}
			else
			{
				if( endLineCounter == 0)
					endLineCounter++;
				else if(endLineCounter == 1)
				{
					result += countVotingData(&votingData[0]);
					memset(votingData, '\0', 150*sizeof(char));
					i = 0;
				}
			}
		}
	}

	if(feof(fp))
		result += countVotingData(&votingData[0]);

	printf("%d", result);

	return 0;
}

int countVotingData(char *votingData)
{
	int count = 0;
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

	for(int i = 0; i < 26; i++)
		if( strchr(votingData, alphabet[i]) != NULL )
			count++;

	return count;
}















