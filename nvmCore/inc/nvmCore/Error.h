#ifndef __ERROR_H__
#define __ERROR_H__

/*
Basic error code container.
*/

#define RETURN_IF_ERROR(CALL) \
{                             \
    auto err = CALL;          \
    if (err) return err;      \
}                             \

namespace nvm {
    enum class ErrorCategory {
        None = 0,
        Configuration,
        Instruction,
        Memory
    };

    enum class ErrorDetail {
        //Configuration
        None = 0,
        StackSizeGreaterThanMemorySpace,
        BootVectorGreaterThanMemorySpace,
        BootVectorInsideStack,

        //Instruction
        InvalidOpcode,
        UnsupportedRegister,

        //Memory
        AddressOutOfRange
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

        void operator=(const Error& other) {
            category_ = other.category_;
            detail_ = other.detail_;
        };
    };

    template <typename tdata>
    struct ErrorUnion {
        ErrorUnion() { }
        ErrorUnion(const Error error) :
            error_(error),
            data_() { }

        ErrorUnion(const tdata data) :
            error_(),
            data_(data) { }

        const Error error_;
        const tdata data_;
    };
}

#endif //__ERROR_H__
