#include <stdio.h>

int main()
{
	int n;

	puts("1부터 n까지의 총합 구하기.");
	printf("n: ");
	scanf_s("%d", &n);

	int sum = 0;
	int i = 1;

	while (i <= n)
	{
		sum += i;
		i++;
	}

	printf("1부터 %d까지의 총합: %d", n, sum);

	return 0;
}