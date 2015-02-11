#include "../includes/Raindrop.hpp"

Raindrop::Raindrop(void) {init();};
Raindrop::~Raindrop(void) {};
Raindrop &Raindrop::operator=(Raindrop const &ref)
{
    (void)ref;
    return *this;
}

void    Raindrop::init()
{
    rainvertab[0].xyz = vec3(-1.0f,-1.0f,-1.0f);
    rainvertab[0].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    rainvertab[1].xyz = vec3(-1.0f,-1.0f, 1.0f);
    rainvertab[1].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    rainvertab[2].xyz = vec3(-1.0f, 1.0f, 1.0f);
    rainvertab[2].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    rainvertab[3].xyz = vec3(1.0f, 1.0f,-1.0f);
    rainvertab[3].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    rainvertab[4].xyz = vec3(-1.0f,-1.0f,-1.0f);
    rainvertab[4].rgba =vec4( 0.153f,0.39f,0.655f, 0.10f);
    rainvertab[5].xyz = vec3(-1.0f, 1.0f,-1.0f);
    rainvertab[5].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

}