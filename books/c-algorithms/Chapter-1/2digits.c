#include <stdio.h>

int main()
{
	int no;

	printf("2자리의 양수를 입력하세요.\n");

	do {
		printf("입력: ");
		scanf_s("%d", &no);
	} while (no < 10 || no > 99);

	printf("입력한 값: %d", no);

	return 0;
}