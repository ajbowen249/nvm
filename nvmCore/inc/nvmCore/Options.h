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
		typedef std::shared_ptr<const Options> Ptr;

		Options();

		address_t getStackSize() const;
		void setStackSize(address_t stackSize);

		address_t getBootVector() const;
		void setBootVector(address_t bootVector);

		Error validate(Interface::Ptr interface) const;
	private:
		address_t stackSize_;
		address_t bootVector_;
	};
}

#endif //__OPTIONS_H__
