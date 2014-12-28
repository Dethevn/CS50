#include "cs50.h"
#include <stdio.h>

int main(void)
{
	printf("Height: ");
	int pyr_height = GetInt();

	while (pyr_height < 24)
	{
		for (int i = 0; i < pyr_height; i++)
		{
			for (int j = 0; j < (pyr_height - i - 1); j++)
				printf(" ");
			for (int k = 0; k < (i + 1); k++)
				printf("#");
			printf("  ");
			for (int l = 0; l < (i + 1); l++)
				printf("#");
			printf("\n");
		}
		printf("Enter a new height: ");
		pyr_height = GetInt();
	}
	printf("Invalid, cannot have height greater than 23.\n");
	return 0;
}