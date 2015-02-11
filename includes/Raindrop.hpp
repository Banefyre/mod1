#ifndef __RAINDROP_HPP__
#define __RAINDROP_HPP__
#include "../includes/ModelManager.hpp"

class Raindrop {


public:

    Raindrop(void);
    ~Raindrop(void);
    Raindrop &operator=(Raindrop const &ref);
    void init();
    Vertex3 rainvertab[6];

};

#endif