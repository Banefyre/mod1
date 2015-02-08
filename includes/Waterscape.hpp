#ifndef __WATERSCAPE_HPP__
#define __WATERSCAPE_HPP__

#include <cstring>
#include <cstdlib>
#include <vector>

class Waterscape
{

public:

    Waterscape(void);
    ~Waterscape(void);
    Waterscape &operator=(Waterscape const &ref);
    int getWidth(void) const;
    int getHeight(void) const;
    std::vector<std::vector<float>> waterHeights;


private :
    int _width;
    int _height;

};

#endif