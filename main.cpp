#include <iostream>

#include "expected.hpp"

Expected<double> foo(){
    return makeError<std::runtime_error>("run");
}

Expected<int> for1(){
    return std::runtime_error("fun1");
}


Expected<double> bar(){
    return 1.3;
}

int main()
{
    auto&& e = foo();
    std::cout << e.hasValue() << std::endl;
    std::cout << bar().hasValue() << std::endl;
    std::cout << bar().value() << std::endl;

    auto&& b = bar();
    std::cout << b.value() << std::endl;

    return 0;
}
