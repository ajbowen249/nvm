#include <parser/Parser.h>

#include "antlr4-runtime.h"
#include "NVMLexer.h"
#include "NVMParser.h"
#include "NVMBaseListener.h"

void nvm::Parser::parse(std::ifstream& programStream) {
    antlr4::ANTLRInputStream input(programStream);
    antlrGenerated::NVMLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    antlrGenerated::NVMParser parser(&tokens);

    class TreeShapeListener : public antlrGenerated::NVMBaseListener {
    public:
        void enterInstruction(antlrGenerated::NVMParser::InstructionContext *ctx) override {
            auto chstream = ctx->start->getInputStream();
            auto text = chstream->getText(antlr4::misc::Interval(ctx->start->getStartIndex(), ctx->stop->getStopIndex()));
            std::cout << "Instruction. " << text << std::endl;
        }
    };

    TreeShapeListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, parser.program());
}
