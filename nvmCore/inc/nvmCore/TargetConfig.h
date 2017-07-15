#ifndef __TARGETCONFIG_H__
#define __TARGETCONFIG_H__

/*
Overridable options for targets.
*/

#include <cstdint>

namespace nvm {
    #ifdef AS32
	typedef uint32_t _address_t;
#else
    #define AS16
    typedef uint16_t _address_t;
    #endif
}

#endif //__TARGETCONFIG_H__
