#include <stdio.h>

int main()
{
	int n;

	puts("1~n ÃÑÇÕ ±¸ÇÏ±â");
	printf("n: "); scanf_s("%d", &n);

	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		sum += i;
	}

	printf("ÃÑÇÕ: %d", sum);

	return 0;
}