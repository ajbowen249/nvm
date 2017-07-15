#ifndef __NVMINTERFACE_H__
#define __NVMINTERFACE_H__

/*
Abstract interface for implementing NVM IO capabilities per-platform.
*/

#include "nvmCore/TargetConfig.h"
#include <memory>

namespace nvm {
    class NVMInterface {
    public:
        typedef std::shared_ptr<NVMInterface> Ptr;

		template <typename tdata>
		void write(_address_t address, tdata data) {
			write(address, (uint8_t*)(&data), sizeof(data));
		}

		template <typename tdata>
		tdata read(_address_t address) {
			auto size = sizeof(tdata);
			uint8_t data[size];
			read(address, data, size);
			return *(tdata*)(data);
		}

	private:
		virtual void write(_address_t address, const uint8_t data[], _address_t width) = 0;
		virtual void read(_address_t address, uint8_t data[], _address_t width) = 0;
    };
}

#endif //__NVMINTERFACE_H__