#include "graver/person/person.h"

#include <sstream>
#include <utility>

Person::Person(std::string name, int age) : _name(std::move(name)), _age(age) {}

std::string Person::sayHello() {
    std::stringstream ss;
    ss << "Hi, My name is ";
    ss << this->_name;
    ss << ". I'm ";
    ss << this->_age;
    ss << " old.";
    return ss.str();
}