#include <stdio.h>

int main(void)
{
	int a, b, c;

	printf("세 정수의 합을 구하기.\n");
	printf("a: "); scanf_s("%d", &a);
	printf("b: "); scanf_s("%d", &b);
	printf("c: "); scanf_s("%d", &c);

	int max = a;
	if (b > a) max = b;
	if (c > b) max = c;

	printf("최대값: %d\n", max);

	return 0;
}