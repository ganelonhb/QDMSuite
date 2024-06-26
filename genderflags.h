#ifndef GENDERFLAGS_H
#define GENDERFLAGS_H

#include <cstdint>

namespace FantasyNameGender {

    using namegenderflags_t = uint8_t;

    const namegenderflags_t All             = 0b1000'0000;
    const namegenderflags_t NoneExplicit    = 0b0100'0000;

    const namegenderflags_t Male            = 0b0000'0001;
    const namegenderflags_t Female          = 0b0000'0010;
    const namegenderflags_t Neuter          = 0b0000'0100;
}

#endif // GENDERFLAGS_H
