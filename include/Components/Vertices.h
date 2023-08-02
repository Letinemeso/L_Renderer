#ifndef __VERTICES
#define __VERTICES

#include <fstream>

#include <glew.h>

#include <L_Debug/L_Debug.h>

#include <Components/Buffer.h>


namespace LR
{

    class Vertices final : public LR::Buffer
    {
    public:
    Vertices() : LR::Buffer() {}
    ~Vertices();

    void init(const float* const _coords, unsigned int _count);

    public:
    unsigned int vertices_count() const;

    };

}

#endif
