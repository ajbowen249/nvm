#include <parser/Parser.h>
#include <fstream>

int main(int argc, char* argv[]) {
    std::ifstream stream;
    stream.open(argv[1]);
    nvm::Parser::parse(stream);
}