#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <cstdint>

namespace Crunch {

class Texture {
public:
    uint32_t ID;
    bool load(const char* path);
    void bind();
};

}

#endif          // TEXTURE_HPP
