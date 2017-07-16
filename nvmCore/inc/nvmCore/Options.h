#ifndef __OPTIONS_H__
#define __OPTIONS_H__

/*
Runtime-configurable options
*/

#include "TargetConfig.h"
#include "Interface.h"
#include "Error.h"

namespace nvm {
	class Options {
	public:
		typedef std::shared_ptr<Options> Ptr;

		Options();

		address_t getStackSize();
		void setStackSize(address_t stackSize);

		Error validate(Interface::Ptr interface);
	private:
		address_t stackSize_;
	};
}

#endif //__OPTIONS_H__
