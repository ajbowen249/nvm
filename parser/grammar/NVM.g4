grammar NVM;
import NVMLexerRules;

program: unit+;

unit: instruction
    ;

instruction: add
           | subtract
           | multiply
           | divide
           | setLiteral
           | jump
           | ret
           | increment
           | decrement
           | read
           | write
           | push
           | pop
           ;

add: 'ADD' Register Register Register NL;
subtract: 'SUB' Register Register Register NL;
multiply: 'MULT' Register Register Register NL;
divide: 'DIV' Register Register Register NL;
setLiteral: 'SET' Register Literal NL;
jump: 'JMP' JumpCondition? 'S'? (Register|Literal) NL;
ret: 'RET' NL;
increment: 'INC' Register NL;
decrement: 'DEC' Register NL;
read: 'RD' Register (Literal|Register|(Register Register)) NL;
write: 'WR' Register (Literal|Register|(Register Register)) NL;
push: 'PUSH' Register NL;
pop: 'POP' Register NL;

