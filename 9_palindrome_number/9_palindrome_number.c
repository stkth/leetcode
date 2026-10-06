// SPDX-License-Identifier: GPLv2

#define _XOPEN_SOURCE 600
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

#define MAX_DIVISOR 1000000000
#define WRAPAROUND_MULTIPLIER 5


/* Use the base 10 representation of the number,
 * invert the scheme and add up the inversion of
 * the number 
 */
bool isPalindrome(int x)
{
	int pnr = 0;
	int m = 1;
	int r = x;
	int nr;

	if (x < 0)
		return false;

	for (int d = MAX_DIVISOR; d >= 1; d /= 10) {
		nr = r;
		r %= d;

		if (r == x)
			continue;

		if (m == MAX_DIVISOR && nr > WRAPAROUND_MULTIPLIER)
			return false;

		pnr += ((nr - r) / d) * m;

		if (m == MAX_DIVISOR)
			break;

		m *= 10;
	}

	return pnr == x ? true : false;
}

int main()
{
	printf("%d\n", isPalindrome(1000000001));
	printf("%d\n", isPalindrome(1234567899));
	printf("%d\n", isPalindrome(423454324));
	printf("%d\n", isPalindrome(10));
	printf("%d\n", isPalindrome(3663));
}
