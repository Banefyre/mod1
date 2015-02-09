#ifndef __LANDSCAPE_HPP__
#define __LANDSCAPE_HPP__

#include <vector>
#include <string>
#include <ModelManager.hpp>
#include <fstream>

class Landscape
{

public:

    Landscape(void);
    ~Landscape(void);
    Landscape &operator=(Landscape const &ref);
    int getWidth(void) const;
    int getHeight(void) const;
    Vertex3 pushPoint(int x, float y, int z);
    void generatePlan(std::vector<Vertex3> points);
    Vertex3 *vertab;
    unsigned long size;
    float maxHeight;
    std::vector<std::vector<double>> heights;

    void    initMap(std::string file);


private :

    int _width;
    int _height;

};

#endif