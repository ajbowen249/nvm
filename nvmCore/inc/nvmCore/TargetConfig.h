#ifndef __TARGETCONFIG_H__
#define __TARGETCONFIG_H__

/*
Overridable options for targets.
*/

#include "nvmCore/NumericConfig.h"

namespace nvm {
    #ifdef ARCH32X32
    typedef _ui32_t _uword_t;
    typedef _i32_t _word_t;
    typedef _ui32_t _address_t;
    #else
    #define ARCH8X16
    typedef _ui8_t _uword_t;
    typedef _i8_t _word_t;
    typedef _ui16_t _address_t;
    #endif
}

#endif //__TARGETCONFIG_H__
