#ifndef __TARGETCONFIG_H__
#define __TARGETCONFIG_H__

/*
Overridable options for targets.
*/

#include <cstdint>

//Declaring these at the global level so they gel with the
//fixed-width interger types and in case they need to be
//changed per-platform/compiler one day
typedef float f32_t;
typedef double f64_t;

#ifndef NUMGPREGS
    #define NUMGPREGS 16
#endif

#define LONGESTINSTRUCTION 9

namespace nvm {
#ifdef AS32
    typedef uint32_t address_t;
#else
    #define AS16
    typedef uint16_t address_t;
#endif
}

#endif //__TARGETCONFIG_H__
