#include <iostream>

// 함수 템플릿
template <typename T>
T add(T a, T b)
{
	return (a + b);
}
// 빼기 버전
template <typename T>
T sub(T a, T b) {
	return (a - b);
}
// 두 가지 타입
template <typename T, typename C>
T sub(T a, C b) {
	return (a - b);
}

int main()
{
	std::cout << add(3, 4) << std::endl;
	std::cout << add(3.3, 4.4) << std::endl;

	std::cout << sub(100, 1) << std::endl;
	// int 반환
	std::cout << sub(100, 44.4f) << std::endl;
	// float 반환
	std::cout << sub(100.4f, 44) << std::endl;

	return 0;
}
