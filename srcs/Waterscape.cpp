#include <iostream>
#include <InputManager.hpp>
#include "../includes/Waterscape.hpp"

Waterscape::Waterscape(void) : _width(50), _height(50) {

    waterHeights.resize(_height);
    for(int i = 0; i < 50 ; i++)
    {
        waterHeights[i].resize(_width, 0.0f);
    }
}


Waterscape::~Waterscape(void) {

}

Waterscape &Waterscape::operator=(Waterscape const &ref) {
    this->_width = ref.getWidth();
    this->_height = ref.getHeight();
    return *this;

}

int Waterscape::getWidth(void) const {
    return this->_width;
}

int Waterscape::getHeight(void) const {
    return this->_height;
}
