// 02_rangeFor.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

int main()
{
	int list[] = { 10, 20, 30, 40, 50 };

	for (int i = 0; i < 5; ++i)
		std::cout << list[i] << ' ';
	std::cout << std::endl;

	for (auto element : list)
		std::cout << element << ' ';
	std::cout << std::endl;

	// 원본 편집
	for(int i = 0; i < 5; i++) {
		list[i] = 0;
	}

	// 복사 -> 원본은 변화 없음
	for (auto element : list) {
		element = 5;
	}

	// 원본 편집
	for (auto& element : list) {
		element = 10;
	}

	// 원본 읽기 전용
	for (const auto& element : list)
		std::cout << element << ' ';
	std::cout << std::endl;

	return 0;
}