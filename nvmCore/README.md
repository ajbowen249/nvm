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

Instructions that use registers take an entire byte to refer to them. The first bit is currently reserved, and should always be `0`. The next three bits are the type, and the final four bytes are the register index. Type codes are as follows:
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
ADD ui32-1 ui32-1 i8
```

should not be allowed.