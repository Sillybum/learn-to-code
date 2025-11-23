#include <iostream>

int testFunc(int param)
{
	int result = param * 2;
	return result;
}

int main()
{
	int input = 0;

	std::cout << "Input number: ";
	std::cin >> input;

	// &&는 rValue만 바인딩할 수 있다.
	// 나중에 move semantic에 활용(자원 해제가 아닌 이동을 통한 최적화).
	int&& rData = (input + 5);
	std::cout << "value of rData: " <<  rData << std::endl;

	int&& result = testFunc(10);

	result += 10;
	std::cout << result << std::endl;

	return 0;
}