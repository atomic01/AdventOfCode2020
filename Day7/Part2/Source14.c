#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample  594

int getTotalNumberOfBags(char *);
int recursiveExamination(char *, char *);

int main()
{
	int i = 0, j = 0, done = 0, result = 0;
	char buffer =  '\0' ;
	char rules[sizeOfsample][150] = {'\0'};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 1313) // to get past the text for the puzzle in the txt file where i stored the numbers
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

	result = getTotalNumberOfBags(&rules[0][0]);
	printf("%d\n", result);

	return 0;
}

int getTotalNumberOfBags(char *rules)
{
	char shinyGoldBag[25] = {"shiny gold"};

	return 	recursiveExamination(rules, &shinyGoldBag);
}


int recursiveExamination(char *rules, char *bag)
{
	int bagRuleNumber = 0, spaceCounter = 0;
	int i = 0, j = 0, result = 0, temp = 0;
	char newBag[25] = {'\0'};
	char buffer = '\0';

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
	else
	{
		while(*((rules + bagRuleNumber*150) + i) != '\0' )
		{
			buffer = *((rules + bagRuleNumber*150) + i);
			if( isdigit( buffer) != 0)
			{
				result+=buffer - '0';
				temp = buffer -'0';
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

				result += temp * recursiveExamination(rules, &newBag);
			}
			i++;
		}

		return result;
	}
}
