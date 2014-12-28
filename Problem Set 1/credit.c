#include <stdio.h>
#include "cs50.h"

int main(void) {
	printf("Please enter your credit card number: ");
	long long card_num = GetLongLong();

	// simplify the elseif for mastercard by creating new long long var without 0s for use in if statement (since 5 possible values in if statement)
	long long mast_num = card_num / 100000000000000;
	// use C's typecast of int when dividing by int to test the number of digits and beginning digits (digit for visa) simultaneously
	if ((card_num / 10000000000000) == 37 || (card_num / 10000000000000) == 34)
		printf("AMEX\n");
	else if (mast_num == 51 || mast_num == 52 || mast_num == 53 || mast_num == 54 || mast_num == 55)
		printf("MASTERCARD\n");
	else if ((card_num / 1000000000000000) == 4 || (card_num / 1000000000000) == 4)
		printf("VISA\n");
	else
		printf("INVALID\n");
	return 0;
}