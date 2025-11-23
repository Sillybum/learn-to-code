#include <iostream>

// X: 함수 스코프의 a의 참조를 반환한다.
int& getRef() {
    int a = 5;
    return a;
}

int main() {
    int& hey = getRef();
    // Undefined behavior
    std::cout << "hey's value: " << hey << std::endl;
}