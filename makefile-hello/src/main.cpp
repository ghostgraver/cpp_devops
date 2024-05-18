#include <iostream>
#include <memory>

#include "graver/person/person.h"

int main() {
    auto person = std::make_unique<Person>("laolang", 28);
    std::cout << person->sayHello() << std::endl;
    return 0;
}