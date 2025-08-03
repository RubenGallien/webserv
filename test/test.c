#include <stdio.h>

int main(int argc, char ** argv)
{
	int i = 0;
	if (argc && argv[1])
	{
		while (argv[1][i])
		{
			i++;
		}
		printf("%d\n", i);
	}
	return (0);
}
