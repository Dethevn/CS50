#include "cs50.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	printf("Please enter your full name: ");
	string name = GetString();

	if (name != NULL)
	{
		if (64 < toupper(name[0]) && toupper(name[0]) < 91)
		{
			printf("%c", name[0]);
			for (int i = 1, n = strlen(name); i < n; i++)
				if (64 < toupper(name[i]) && toupper(name[i]) < 91 && name[i - 1] == ' ')
					printf("%c", toupper(name[i]));
		}
		else if (name[0] == 32)
		{
			for (int i = 0, n = strlen(name); i < n; i++)
				if (64 < toupper(name[i]) && toupper(name[i]) < 91 && name[i - 1] == ' ')
					printf("%c", toupper(name[i]));
		}
	}
	printf("\n");
	return 0;
}