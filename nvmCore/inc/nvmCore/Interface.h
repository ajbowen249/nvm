#ifndef __INTERFACE_H__
#define __INTERFACE_H__

/*
Abstract interface for implementing  IO capabilities per-platform.
*/

#include "TargetConfig.h"
#include <memory>

namespace nvm {
    class Interface {
    public:
        typedef std::shared_ptr<Interface> Ptr;

		template <typename tdata>
		void write(address_t address, tdata data) {
			write(address, (uint8_t*)(&data), sizeof(data));
		}

		template <typename tdata>
		tdata read(address_t address) {
			auto size = sizeof(tdata);
			uint8_t data[size];
			read(address, data, size);
			return *(tdata*)(data);
		}

		virtual address_t getMaxMemory() = 0;

	private:
		virtual void write(address_t address, const uint8_t data[], address_t width) = 0;
		virtual void read(address_t address, uint8_t data[], address_t width) = 0;
    };
}

#endif //__INTERFACE_H__