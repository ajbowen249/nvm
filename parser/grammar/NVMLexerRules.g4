lexer grammar NVMLexerRules;

Register: ('i'|'f'|'ui')('8'|'16'|'32'|'64')'-'[0-9][0-9]?;

Literal: Base10Literal
       | HexLiteral
       | BinaryLiteral
       ;

Base10Literal: '-'?[0-9]+('.'[0-9]+)?;
HexLiteral: '0x'[0-9a-fA-F]+;
BinaryLiteral: 'b'[0-1]+;

JumpCondition: [NZP];

NL: '\r'?'\n';
WS: [ \t]+ -> skip;