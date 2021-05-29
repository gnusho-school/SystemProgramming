#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int compare(int a, int b) {
	if (a > b)
		return 1;
	else
		return 0;
}


/***************************************************************
define bubble sort that uses pointer to 'compare' function above
***************************************************************/


int main() {
	int n_array[SIZE] = { 2,-9, 10, 15, 1, 3, -12, 5, 4, 1 };

	int (*cc)(int,int) = NULL;
	cc = compare;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (cc(n_array[j], n_array[j+1]))
			{
				int tmp = n_array[j];
				n_array[j] = n_array[j + 1];
				n_array[j + 1] = tmp;
			}
		}
	}

	for (int k =0 ; k < SIZE ; k++) printf("%d\n", n_array[k]);

	return 0;
}
