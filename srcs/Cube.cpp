
#include <InputManager.hpp>
#include "../includes/Cube.hpp"

Cube::Cube(void) {init();};
Cube::~Cube(void) {};
Cube &Cube::operator=(Cube const &ref)
{
    ModelManager::operator=(ref);
    return *this;
}

void Cube::init()
{

    watervertab[0].xyz = vec3(-1.0f,-1.0f,-1.0f);
    watervertab[0].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[1].xyz = vec3(-1.0f,-1.0f, 1.0f);
    watervertab[1].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[2].xyz = vec3(-1.0f, 1.0f, 1.0f);
    watervertab[2].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[3].xyz = vec3(1.0f, 1.0f,-1.0f);
    watervertab[3].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[4].xyz = vec3(-1.0f,-1.0f,-1.0f);
    watervertab[4].rgba =vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[5].xyz = vec3(-1.0f, 1.0f,-1.0f);
    watervertab[5].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[6].xyz = vec3(1.0f,-1.0f, 1.0f);
    watervertab[6].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[7].xyz = vec3(-1.0f,-1.0f,-1.0f);
    watervertab[7].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[8].xyz = vec3(1.0f,-1.0f,-1.0f);
    watervertab[8].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[9].xyz = vec3(1.0f, 1.0f,-1.0f);
    watervertab[9].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[10].xyz = vec3(1.0f,-1.0f,-1.0f);
    watervertab[10].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[11].xyz = vec3(-1.0f,1.0f,-1.0f);
    watervertab[11].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[12].xyz = vec3(-1.0f,-1.0f,-1.0f);
    watervertab[12].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[13].xyz = vec3(-1.0f, 1.0f, 1.0f);
    watervertab[13].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[14].xyz = vec3(-1.0f, 1.0f,-1.0f);
    watervertab[14].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[15].xyz = vec3(1.0f,-1.0f, 1.0f);
    watervertab[15].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[16].xyz = vec3(-1.0f,-1.0f,1.0f);
    watervertab[16].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[17].xyz = vec3(-1.0f,-1.0f,-1.0f);
    watervertab[17].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[18].xyz = vec3(-1.0f,1.0f, 1.0f);
    watervertab[18].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[19].xyz = vec3(-1.0f,-1.0f,1.0f);
    watervertab[19].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[20].xyz = vec3(1.0f,-1.0f,1.0f);
    watervertab[20].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[21].xyz = vec3(1.0f,1.0f, 1.0f);
    watervertab[21].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[22].xyz = vec3(1.0f,-1.0f,-1.0f);
    watervertab[22].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[23].xyz = vec3(1.0f,1.0f,-1.0f);
    watervertab[23].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[24].xyz = vec3(1.0f,-1.0f, -1.0f);
    watervertab[24].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[25].xyz = vec3(1.0f,1.0f,1.0f);
    watervertab[25].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[26].xyz = vec3(1.0f,-1.0f,1.0f);
    watervertab[26].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[27].xyz = vec3(1.0f,1.0f, 1.0f);
    watervertab[27].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[28].xyz = vec3(1.0f,1.0f,-1.0f);
    watervertab[28].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[29].xyz = vec3(-1.0f,1.0f,-1.0f);
    watervertab[29].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[30].xyz = vec3(1.0f,1.0f, 1.0f);
    watervertab[30].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[31].xyz = vec3(-1.0f,1.0f,-1.0f);
    watervertab[31].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[32].xyz = vec3(-1.0f,1.0f,1.0f);
    watervertab[32].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);

    watervertab[33].xyz = vec3(1.0f,1.0f, 1.0f);
    watervertab[33].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[34].xyz = vec3(-1.0f,1.0f,1.0f);
    watervertab[34].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
    watervertab[35].xyz = vec3(1.0f,-1.0f,1.0f);
    watervertab[35].rgba = vec4( 0.153f,0.39f,0.655f, 0.10f);
}