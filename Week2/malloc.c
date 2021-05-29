#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char** pp_data = NULL;
	int n;
	int length;
	int i;

	scanf("%d", &n);


	//1. define & dynamic allocation
	pp_data = (char**) malloc(sizeof(char*) * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &length);
		pp_data[i] = (char*)malloc(sizeof(char) * (length+1));
		scanf("%s", pp_data[i]);
	}
	
	//2. print string
	for (int i = 0; i < n; i++) printf("%s\n", pp_data[i]);
	
	//printf("1\n");
	//3. free memory
	for (int i = 0; i < n; i++)
	{
		//printf("%d", i);
		free(pp_data[i]);
	}
	printf("2\n");
	free(pp_data);

	return 0;
}
