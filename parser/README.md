# NVM Parser
This is a simple assembler library for parsing strings into NVM programs. This readme is a loose overview of syntax of the NVM assembly language. Like everything else in this project, expect this to fluctuate wildly.

## Basic Instruction Syntax
Instructions are called via their mnemonic followed by their argument lists. Arguments can be registers, special symbols, replaced macros, or literals. For example:
```
SET i8-0 -12
SET i8-1 14
ADD i8-3 i8-0 i8-1
WR i8-3 0x15
```

The above program sets two literal values, adds them, and stores them to memory address 0x15. There are three accepted forms of literal value:
- Plain base 10: (123, 65, 1.234, etc.)
- Hexadecimal: (0x10, 0x2345, 0xDEAD, 0xB33F, etc.)
- Binary: (b0110, b1110000, b0101, etc.)

Hexadecimal and binary values will be left-padded with 0 (not sign-extended). The parser will error out if a literal value given is out of range of its required type.

## Jumps
Jump (JMP) is the most complex instruction to represent in plaintext, as it has many options. It can be conditional (or not), it can be relative(or not), it can be negative (or not), it can be a subroutine jump (or not), and the value can come from a register or a literal. Here are some examples of Jump instructions:
```
JMP Z i8-3     //jump if zero to i8-3
JMP 0x12       //jump unconditionally to address 0x12
JMP N S ui16-3 //jump if negative to the subroutine at ui16-3
JMP P -15      //jump back 15 bytes.
```
In the final example, note that the literal value will be 15 and the negative jump code flag will be set.

## Labels
Labels are abitrary strings with no white space that end in a colon. Using the label's name in context will always be replaced with a literal valueand the jump will be treated as relative. For example:
```
SET i32-0 1
SET i32-1 10
loop:
    ADD i32-0 i32-0 i32-0
    DEC i32-1
    JMP Z loop
```

## Comments
Comments are the basic, inline variety. Everything after a `//` on a line will be ignored.

## Macros
Macros are very basic text-replacement (for now). They are defined starting with a `#` followed by a name, and everything after the name will be the text replacement value. Use macros later on with a `$` followed by the symbol name. For example:
```
#sum i32-1

SET $sum 12
```
will produce
```
SET i32-1 12
```

## Data
Data values will be encorperated into the program by declaring them with a `*`, followed by their type (any of the register types plus `string`). You can then use the address of the first byte of that data as a literal using `&`. For example:
```
*value f64 1.24
SET f64-3 &value
```

Note: you can declare data on any line you want within a file, but the values will always start from the end of the produced binary.
