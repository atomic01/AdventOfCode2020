#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#define sizeOfsample 95

void sortArray(int * );
void editVariationNecesityArray(int *, int *);
long long int calculateVariations(int *, int *);
int pow(int, int);

int main()
{
	int i = 0, done = 0, number = 0;
	long long int result = 0;
	char buffer =  '\0' ;
	int adapterList[sizeOfsample] = {0};
	int variationNecesityArray[sizeOfsample] = {0};
	FILE* fp = fopen("Puzzle.txt", "r+");

	while (i < 2579) // to get past the text for the puzzle in the txt file where i stored the numbers
	{
		fscanf(fp, "%c", &buffer);
		//printf("%c", buffer);
		i++;
	}

	i = 1;
	while (!done)
	{
		fscanf(fp, "%d%c", &number, &buffer);
		if(feof(fp))
			done = 1;
		adapterList[i] = number;
		i++;

	}

	sortArray(&adapterList[0]);
	editVariationNecesityArray(&adapterList[0], &variationNecesityArray[0]);

	result = calculateVariations(&adapterList[0], &variationNecesityArray[0]);
	printf("%lld\n", result);

	return 0;
}

void sortArray(int *array )
{
	int temp = 0;

	for(int i = 0; i < sizeOfsample; i++)
	{
		for(int j = i+1; j < sizeOfsample; j++)
		{
			if(array[j] < array[i])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

void editVariationNecesityArray(int *adapterList, int *variationNecesityArray)
{
	variationNecesityArray[0] = 1;
	variationNecesityArray[sizeOfsample - 1] = 1;

	for(int i = 1; i < sizeOfsample -1; i++)
		if( (adapterList[i+1] - adapterList[i-1]) > 3 )
			variationNecesityArray[i] = 1;
}

long long int calculateVariations(int *adapterList, int *variationNecesityArray)
{
	long long int result = 1;
	int p = 0, q = 1;
	int  zeroCounter = 0, unconsecutiveNumbersCount = 0;

	for(int i = 0; i < sizeOfsample; i++)
	{
		if(variationNecesityArray[i] == 0)
		{
			p = i;
			while(variationNecesityArray[i] != 1)
				i++;
			q = i;

			zeroCounter = q - p;
			for(int j = p; j < q - 1; j++)
				if(adapterList[j+1] > (adapterList[j] +1))
					unconsecutiveNumbersCount++;

			p = pow(2, zeroCounter);
			q = pow(2,unconsecutiveNumbersCount);
			if(zeroCounter > 2)
				result *=(p - q);
			else
				result*=p;
			unconsecutiveNumbersCount = 0;
		}

	}

	return result;
}

int pow(int b, int p)
{
	int x = 1;

	for(int i=0; i < p; i++)
		x*=b;

	return x;
}
