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
        None,
        Configuration,
        Instruction,
        Memory
    };

    enum class ErrorDetail {
        //Configuration
        None,
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

        const ErrorCategory category_;
        const ErrorDetail detail_;

        operator bool() const {
            return category_ != ErrorCategory::None;
        }

        Error operator=(const Error& other) {
            return Error(other);
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
