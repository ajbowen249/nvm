#ifndef __ERROR_H__
#define __ERROR_H__

/*
Basic error code container.
*/

namespace nvm {
	enum class ErrorCategory {
		None,
		Configuration
	};

	enum class ErrorDetail {
		//Configuration
		None,
		StackSizeGreaterThanMemorySpace,
		BootVectorGreaterThanMemorySpace,
		BootVectorInsideStack
	};

	struct Error {
		Error() : 
			category_(ErrorCategory::None), 
			detail_(ErrorDetail::None) { }

		Error(ErrorCategory category, ErrorDetail detail) :
			category_(category),
			detail_(detail) { }

		ErrorCategory category_;
		ErrorDetail detail_;

		operator bool() const {
			return category_ != ErrorCategory::None;
		}
	};
}

#endif //__ERROR_H__
