#ifndef GENDERFLAGS_H
#define GENDERFLAGS_H

#include <QtTypes>

namespace FantasyNameGender {

    using namegenderflags_t = qint8;
    using namegenderflags = namegenderflags_t;

    const namegenderflags All             = 0b1000'0000;
    const namegenderflags NoneExplicit    = 0b0100'0000;

    const namegenderflags Male            = 0b0000'0001;
    const namegenderflags Female          = 0b0000'0010;
    const namegenderflags Neuter          = 0b0000'0100;
}

#endif // GENDERFLAGS_H
