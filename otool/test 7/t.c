#include <stdio.h>
int main(int argc, char *argv[])
{
	printf("sal");
	fflush(stdout);
	printf("\033[Cut");
	fflush(stdout);
	return 0;
}
