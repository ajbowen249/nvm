# NVM Specification

_Note: This document exists as a scratchpad of ideas as the NVM is developed. It will likely be hard to follow until features are finalized. As such, anything in this document is very likely subject to change._

## Registers
The registers in the NVM are type-safe. That is, there are multiple registers for each primitive type (int, unsigned int, float, etc...). The mnemonic way of referring to a type is as follows:
```
[type code]-[register number]
For example:
ui32-1
f64-12
i8-5
```

Instructions that use registers take an entire byte to refer to them. The first bit flags wether a register is gereal-purpose, or a system register (stack pointer, etc.). The next three bits are the type, and the final four bytes are the register index. Type codes are as follows:
```
i8:   000
ui8:  001
i16:  010
ui16: 011
i32:  100
ui32: 101
f32:  110
f64:  111
```

The types of the registers define how they should be treated in mathematical operations. As such, there should be no legal assembly code with a mismatch of register types. For example,
```
ADD ui32-1 ui32-1 i8-2
```

should not be allowed.

## Flags

### Status Flags
- Negative (N): The result of the previous numeric operation was negative.
- Positive (P): The result of the previous numeric operation was positive.
- Zero     (Z): The result of the previous numeric operation was exactly zero.

## The Stack
There is a stack that grows from the bottom of memory. The stack pointer a system register, SP, of the unsigned type that matches the configured address space. Pushing to or popping from the stack will decrement or increment the stack pointer by the number of bytes required to store the type being pushed. It is also responsible for keeping track of the instruction pointer across subroutine calls.

## Instructions

### No-Op
**Mnemonic**: NOP

**Length**: 1

**Affects Flags**: None

| 0        |
|----------|
| 00000000 |

Literally does nothing.

### Add
**Mnemonic**: ADD

**Length**: 3

**Affects Flags**: NPZ

| 0        | 1                                       | 2                   |
|----------|-----------------------------------------|---------------------|
| 00000001 | tttt rrrr                               | rrrr rrrr           |
|          | type and number of the storage register | numbers of operands |

Adds the values of the two operand registers and stores the result in the storage register, with rollover bahavior defined by the type of the registers.

### Subtract
**Mnemonic**: SUB

**Length**: 3

**Affects Flags**: NPZ

| 0        | 1                                       | 2                   |
|----------|-----------------------------------------|---------------------|
| 00000010 | tttt rrrr                               | rrrr rrrr           |
|          | type and number of the storage register | numbers of operands |

Subtracts the value of the second operand register from the first and stores the result in the storage register, with rollover bahavior defined by the type of the registers.

### Multiply
**Mnemonic**: MULT

**Length**: 3

**Affects Flags**: NPZ

| 0        | 1                                       | 2                   |
|----------|-----------------------------------------|---------------------|
| 00000011 | tttt rrrr                               | rrrr rrrr           |
|          | type and number of the storage register | numbers of operands |

Multiplies the values of the two operand registers and stores the result in the storage register, with rollover bahavior defined by the type of the registers.

### Divide
**Mnemonic**: DIV

**Length**: 3

**Affects Flags**: NPZ

| 0        | 1                                       | 2                   |
|----------|-----------------------------------------|---------------------|
| 00000100 | tttt rrrr                               | rrrr rrrr           |
|          | type and number of the storage register | numbers of operands |

Divides the value of the first operand register by the second and stores the result in the storage register, with rollover bahavior defined by the type of the registers.

### Set Literal
**Mnemonic**: SET

**Length**: variable

**Affects Flags**: NPZ

| 0        | 1                                       | 2..n                |
|----------|-----------------------------------------|---------------------|
| 00000101 | tttt rrrr                               | xxxxxxxx            |
|          | type and number of the storage register | literal value       |

Sets the value of the given value to the literal given value

### Fixed Unconditional Jump
**Mnemonic**: JFR

**Length**: 2

**Affects Flags**: None

| 0        | 1                                       |
|----------|-----------------------------------------|
| 00000110 | tttt rrrr                               |
|          | type and number of the address register |

Jumps the instruction pointer to the address specified by the given register. This will cause an error if a non-integer register type is given. If a signed register is used and has a negative value, the IP will be given a value relative to the end of the address space. For example, if the value is -12 and the max address is 65535, the IP will jump to 65523. Similarly, a register with a value higher than the max address will roll over continually. For example, a 65536 value in the previous example would roll over to 0.

### Fixed Literal Unconditional Jump
**Mnemonic**: JFL

**Length**: 1 + width of address

**Affects Flags**: None

| 0        | 1..n                |
|----------|---------------------|
| 00000111 | xxxxxxxx            |
|          | literal value       |

Jumps the instruction pointer to the literal address value. The literal value is assumed to be an unsigned value of a size equal to that of the internal `address_t`. Unlike register-specified jumps, an error will be produced in an attempt to jump beyond the maximum memory address.

### Fixed Literal Jump If Negative
**Mnemonic**: JFLN

**Length**: 1 + width of address

**Affects Flags**: None

| 0        | 1..n                |
|----------|---------------------|
| 00001000 | xxxxxxxx            |
|          | literal value       |

Jumps the instruction pointer to the literal address value if the (N)egative flag is set.
