#include "class.h"
#include <string>

StanfordID::StanfordID(std::string name, std::string sunet, int idNumber) {
    this->name = name;
    this->sunet = sunet;
    if (this->idNumber > 0) {
        this->idNumber = idNumber;
    }
}

std::string StanfordID::getInitialName(std::string name) {
    std::stringstream ss;
    ss << name;
    std::string first;
    std::string last;
    ss >> first >> last;
    std::string res;
    res += first[0];
    res += last[0];
    return res;
}

StanfordID::StanfordID() {
    this->name = "YuTaki X";
    this->sunet = "172@60";
    this->idNumber = 190;
}

const std::string StanfordID::getName() {
    return this->name;
}

const std::string StanfordID::getSunet() {
    return this->sunet;
}

const int StanfordID::getIdNumber() {
    return this->idNumber;
}

void StanfordID::setName(std::string name) {
    this->name = name;
}