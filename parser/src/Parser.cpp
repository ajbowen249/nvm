#include "parser/Parser.h"
#include <sstream>
#include <map>

nvm::ParseResult<std::vector<uint8_t>> nvm::Parser::Parse(const char* program) {

    //first parse macros
    bool inMacro;
    std::stringstream currentMacro;
    std::stringstream programStream;
    std::map<std::string, std::string> macros;

    for (unsigned int i = 0; program[i] != '\0'; i++) {
        auto c = program[i];
        if (inMacro) {
            if (c == '#') {
                inMacro = false;
                currentMacro.str("");
                currentMacro.clear();

                auto fullMacro = currentMacro.str();
                auto firstChar = fullMacro.at(0);
                auto macroLength = fullMacro.size();
                if (firstChar == ' ' || firstChar == '\n' || firstChar == '\r') {
                    return nvm::ParseResult<std::vector<uint8_t>>(nvm::ParseError(nvm::ParseErrorType::ExpectedIdentifier, i - macroLength - 1));
                }

                auto nameEnd = fullMacro.find(' ');
                macros[fullMacro.substr(0, nameEnd - 1)] = fullMacro.substr(nameEnd + 1, macroLength - nameEnd - 1);
            } else {
                currentMacro << c;
            }
        }
        else {
            if (c == '#') {
                inMacro = true;
            } else {
                programStream << c;
            }
        }
    }

    auto preprocessedProgram = programStream.str();
    for (const auto &pair : macros) {
        
    }


    
    std::vector<uint8_t> result{ 1, 2, 3 };
    return nvm::ParseResult<std::vector<uint8_t>>(result);
}
