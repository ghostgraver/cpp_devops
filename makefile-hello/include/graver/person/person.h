#pragma once

#include <string>

class Person {
public:
    Person() = default;
    Person(std::string name, int age);
    ~Person() = default;
    inline std::string name() {
        return this->_name;
    }
    inline void name(std::string name) {
        this->_name = std::move(name);
    }

    inline int age() const {
        return this->_age;
    }
    inline void age(int age) {
        this->_age = age;
    }

    std::string sayHello();

private:
    std::string _name;
    int         _age{0};
};
