#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include "../includes/ModelManager.hpp"

class Cube : public ModelManager {


public:

    Cube(void);
    ~Cube(void);
    Cube &operator=(Cube const &ref);
    void init();
    Vertex3 watervertab[36];

};

#endif