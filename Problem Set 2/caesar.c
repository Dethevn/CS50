#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs50.h"
#include <ctype.h>

int main(int argc, string argv[])
{
	// test to ensure there is a command line prompt argument to be used as the key
	if (argc != 2)
	{
		printf("Invalid number of arguments entered at command line. Please specify a key.\n");
		return 1;
	}

	int key = atoi(argv[1]);

	string some_text = GetString();

	for (int i = 0, n = strlen(some_text); i < n; i++)
	{
		if (isalpha(some_text[i])) // test for a character, only want to modify chars
		{
			if (islower(some_text[i])) // case if character is lower case since ascii different
			{
				// if char + key (after modulo 26) does not exceed end of lower case ascii, display
				if (some_text[i] + key % 26 < 123)
					printf("%c", some_text[i] + key % 26);
				// if exceeds, calculate the modulo that exceeds and add to beginning of lower case
				else
					printf("%c", 96 + (some_text[i] + key % 26) % 122);
			}
			else if (isupper(some_text[i])) // case if character is lower case since ascii different
			{
				// similar as for lower case, see explanation
				if (some_text[i] + key % 26 < 91)
					printf("%c", some_text[i] + key % 26);
				else
					printf("%c", 64 + (some_text[i] + key % 26) % 90);
			}
		}
		// print exclamations, spaces, etc.
		else
			printf("%c", some_text[i]);
	}
	printf("\n");

	return 0;
}