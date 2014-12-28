#include "cs50.h"
#include <stdio.h>

int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of command line arguments. Please input 1 command line argument\nindicating selected key.\n");
		return 1;
	}
	else if (argc == 2)
	{
		for (int i = 0, n = strlen(argv[1]); i < n; i++)
			if (!isalpha(argv[1][i]))
			{
				printf("Invalid, key contains non-alphabetical characters.\n");
				return 1;
			}
	}
	
	string key = argv[1]; 
	// set key to lower since capitalization does not affect index, simplifies remainder of code
	for (int i = 0, n = strlen(key); i < n; i++)
	{
		key[i] = tolower(key[i]);
	}

	string some_text = GetString();
	int mod_index = 0; // set up index to loop through the keyword
	int mod_length = strlen(key); // set up the correct modulo length 

	for (int i = 0, n = strlen(some_text); i < n; i++)
	{
		if (isalpha(some_text[i])) // test for char, since only want to add cypher key letter if it is a char (no skipping)
		{
			if (islower(some_text[i]))
			{
				// if adding key does not exceed the last possible alphabet number
				if ((some_text[i] + (key[mod_index % mod_length] - 97)) < 123)
				{
					printf("%c", some_text[i] + (key[mod_index % mod_length] - 97));
					mod_index++; // increment to loop through keyword
				}
				// if adding key does exceed z, then add excess over to 96 (beginning)
				else
				{
					printf("%c", 96 + ((some_text[i]) + ((key[mod_index % mod_length]) - 97)) % 122);
					mod_index++;
				}
			}
			if (isupper(some_text[i]))
				// if adding key does not exceed the last possible alphabet number
				// Note, we do note subtract 65 (instead of 97) b/c we stated above that we are using lower case to loop through the key
				if ((some_text[i] + (key[mod_index % mod_length] - 97)) < 91)
				{
					printf("%c", some_text[i] + (key[mod_index % mod_length] - 97));
					mod_index++; // increment to loop through keyword
				}
			// if adding key does exceed z, then add excess over to 96 (beginning)
				else
				{
					printf("%c", 64 + ((some_text[i]) + ((key[mod_index % mod_length]) - 97)) % 90);
					mod_index++;
				}
		}
		else
			printf("%c", some_text[i]);
	}
	printf("\n");

	return 0;
}