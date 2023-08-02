#ifndef COLORS_H
#define COLORS_H

#include <fstream>

#include <glew.h>

#include <L_Debug/L_Debug.h>

#include <Components/Buffer.h>


namespace LR
{

    class Colors final : public LR::Buffer
    {
    public:
        Colors() : LR::Buffer() {}
        ~Colors();

        void init(const float* const _coords, unsigned int _count);

    public:
        unsigned int vertices_count() const;

    };

}

#endif // COLORS_H
