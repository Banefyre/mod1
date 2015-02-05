#ifndef __LANDSCAPE_HPP__
#define __LANDSCAPE_HPP__

#include <cstring>
#include <cstdlib>
#include <vector>
#include "../includes/ModelManager.hpp"

class Landscape : public ModelManager {


public:

    Landscape(void);

    Landscape(std::string file);

    ~Landscape(void);

    Landscape &operator=(Landscape const &ref);

    int getWidth(void) const;

    int getHeight(void) const;

    Vertex3 pushPoint(int x, float y, int z);

    void generatePlan(std::vector<Vertex3> points);

private :
    int _width;
    int _height;
public:
    Vertex3 *vertab;
    unsigned long size;
    int maxHeight;

};

#endif