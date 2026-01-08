#include <stdio.h>

int main(void)
{
	int n;

	printf("정수: ");
	scanf_s("%d", &n);

	if (n > 0)
		printf("양수입니다.");
	else if (n < 0)
		printf("음수입니다.");
	else
		printf("0입니다.");

	return 0;
}