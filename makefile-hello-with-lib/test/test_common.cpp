#include <iostream>
#include <memory>

#include "doctest/doctest.h"
#include "graver/person/person.h"

TEST_SUITE("test_common") {
    TEST_CASE("test_common_one") {
        std::cout << "test_common_one start" << std::endl;

        auto person = std::make_unique<Person>("laolang", 28);
        std::cout << person->sayHello() << std::endl;

        std::cout << "test_common_one end" << std::endl;
    }
}