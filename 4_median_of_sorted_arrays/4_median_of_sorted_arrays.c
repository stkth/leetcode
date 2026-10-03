// SPDX-License-Identifier: GPLv2

#define _XOPEN_SOURCE 600
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
			      int nums2Size)
{
	int medarray[nums1Size + nums2Size];
	int i = 0, j = 0, m = 0;

	while (1) {
		if ((i < nums1Size) && (j < nums2Size)) {
			if (nums1[i] < nums2[j])
				medarray[m] = nums1[i++];
			else
				medarray[m] = nums2[j++];
		} else if (j < nums2Size)
			medarray[m] = nums2[j++];
		else if (i < nums1Size)
			medarray[m] = nums1[i++];
		else {
			m--;
			break;
		}
		m++;
	}

	if (m % 2 == 0)
		return (double)medarray[m / 2];
	else {
		int index = (m + 1) / 2;
		return (double)(medarray[index] + medarray[index - 1]) / 2;
	}
}

/* Approach: Take the ordering as given, assume that running to half of the array is enough */
double findMedianSortedArraysAlternative1(int *nums1, int nums1Size, int *nums2,
					  int nums2Size)
{
	int elements = nums1Size + nums2Size;
	int index = elements % 2 ? (elements - 1) / 2 : elements / 2;
	int odd = elements % 2;
	int i = 0, j = 0, m = 0;
	int medarray[index + 1];

	while (1) {
		if ((i < nums1Size) && (j < nums2Size)) {
			if (nums1[i] < nums2[j])
				medarray[m] = nums1[i++];
			else
				medarray[m] = nums2[j++];
		} else if (j < nums2Size)
			medarray[m] = nums2[j++];
		else if (i < nums1Size)
			medarray[m] = nums1[i++];
		else
			return 0;

		if (m == index) {
			if (odd)
				return (double)medarray[m];
			else
				return (double)(medarray[m] + medarray[m - 1]) /
				       2;
		}

		m++;
	}
}

int main()
{
	struct timespec start, end;
	long runtimefMSA = 0, runtimefMSA1;
	int num1[10] = { 1, 3, 5, 6, 7, 8, 9, 10, 11, 12 };
	int num2[10] = { 2, 4, 6, 12, 13, 14, 15, 16, 17, 18 };

	for (int i = 0; i < 10; i++) {
		runtimefMSA = 0;
		runtimefMSA1 = 0;

		clock_gettime(TIME_MONOTONIC, &start);
		double fMSA = findMedianSortedArrays(
			num1, sizeof(num1) / sizeof(int), num2,
			sizeof(num2) / sizeof(int));
		clock_gettime(TIME_MONOTONIC, &end);

		runtimefMSA = end.tv_nsec - start.tv_nsec;
		printf("fMSA : %ldns\n", runtimefMSA);

		clock_gettime(TIME_MONOTONIC, &start);
		double fMSA1 = findMedianSortedArraysAlternative1(
			num1, sizeof(num1) / sizeof(int), num2,
			sizeof(num2) / sizeof(int));
		clock_gettime(TIME_MONOTONIC, &end);

		runtimefMSA1 = end.tv_nsec - start.tv_nsec;
		printf("fMSA1 : %ldns\n", runtimefMSA1);

		printf("fMSA : %f\n", fMSA);
		printf("fMSA1: %f\n", fMSA1);
		printf("fMSA/fMSA1: %f\n",
		       ((double)(runtimefMSA) / (double)(runtimefMSA1)));
	}
}
