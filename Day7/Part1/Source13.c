#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample  594

int checkRule(char *, int);
int recursiveExamination(char *, char *);

int main()
{
	int i = 0, j = 0, done = 0, result = 0;
	char buffer =  '\0' ;
	char rules[sizeOfsample][150] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2238) // to get past the text for the puzzle in the txt file where i stored the numbers
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
				rules[j][i] = buffer;
				i++;
			}
			else
			{
				i = 0;
				j++;
			}
		}
	}

	for(i = 0; i < sizeOfsample; i++)
		result += checkRule(&rules[0][0], i);


	printf("%d\n", result);

	return 0;
}

int checkRule(char *rules, int j)
{
	char firstBagInRule[25] = {'\0'};
	int spaceCounter = 0, i = 0;

	while(spaceCounter < 2)
	{
		if( *((rules + j*150) + i)==' ')
			spaceCounter++;
		firstBagInRule[i] = *((rules + j*150) + i);
		i++;
	}
	firstBagInRule[i-1] = '\0';

	return recursiveExamination(rules, &firstBagInRule);
}


int recursiveExamination(char *rules, char *bag)
{
	int bagRuleNumber = 0, spaceCounter = 0;
	int i = 0, j = 0, result = 0;
	char newBag[25] = {'\0'};

	for(int i = 0; i < sizeOfsample; i++)
	{
		if( strncmp( (rules + i*150), bag,  strlen(bag)) == NULL)
		{
			bagRuleNumber = i;
			i = sizeOfsample;
		}
	}
	i = 0;

	if( strstr((rules + bagRuleNumber*150), " no other ")!=NULL )
		return 0;
	else if( strstr((rules + bagRuleNumber*150), " shiny gold")!=NULL )
		return 1;
	else
	{
		while(*((rules + bagRuleNumber*150) + i) != '\0' )
		{
			if( isdigit( *((rules + bagRuleNumber*150) + i)) != 0)
			{
				i += 2;
				j = 0;
				spaceCounter = 0;
				memset(newBag, '\0', 25*sizeof(char));

				while(spaceCounter < 2)
				{
					if( *((rules + bagRuleNumber*150) + i)==' ')
						spaceCounter++;
					newBag[j] = *((rules + bagRuleNumber*150) + i);
					j++;
					i++;
				}
				newBag[j-1] = '\0';

				result = recursiveExamination(rules, &newBag);
				if(result == 1)
					return 1;
			}
			i++;
		}

		return 0;
	}
}
