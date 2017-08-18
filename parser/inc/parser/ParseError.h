#ifndef __PARSEERROR_H__
#define __PARSEERROR_H__

namespace nvm {
    enum ParseErrorType {
        None = 0x00,
        UnexpectedEOF = 0x01,
        ExpectedIdentifier = 0x02
    };

    struct ParseError {
        ParseError(ParseErrorType error, unsigned int position) : 
            error_(error),
            position_(position) {}

        operator bool() const {
            return error_ != ParseErrorType::None;
        }

        void operator=(const ParseError& other) {
            error_ = other.error_;
        };

        ParseErrorType error_;
        unsigned int position_;
    };

    template <typename resType>
    struct ParseResult {
        ParseResult() { }
        ParseResult(const ParseError error) :
            error_(error),
            data_() { }

        ParseResult(const tdata data) :
            error_(),
            data_(data) { }

        const ParseError error_;
        const tdata data_;
    };
}

#endif //__PARSEERROR_H__
