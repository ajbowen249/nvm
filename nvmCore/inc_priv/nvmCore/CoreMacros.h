#ifndef __COREMACROS_H__
#define __COREMACROS_H__

#define REGISTER_ARRAY_FUNC(REG_CAT, REG_TYPE, FUNC, ...)   \
{                                                           \
    if (REG_CAT == nvm::RegisterCategory::GeneralPurpose) { \
        switch (REG_TYPE) {                                 \
        case nvm::RegisterType::i8:                         \
            FUNC(i8Registers_, ##__VA_ARGS__);              \
            break;                                          \
        case nvm::RegisterType::ui8:                        \
            FUNC(ui8Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::i16:                        \
            FUNC(i16Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::ui16:                       \
            FUNC(ui16Registers_, ##__VA_ARGS__);            \
            break;                                          \
        case nvm::RegisterType::i32:                        \
            FUNC(i32Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::ui32:                       \
            FUNC(ui32Registers_, ##__VA_ARGS__);            \
            break;                                          \
        case nvm::RegisterType::f32:                        \
            FUNC(f32Registers_, ##__VA_ARGS__);             \
            break;                                          \
        case nvm::RegisterType::f64:                        \
            FUNC(f64Registers_, ##__VA_ARGS__);             \
            break;                                          \
        }                                                   \
    }                                                       \
    else {                                                  \
                                                            \
    }                                                       \
}                                                           \

#define MATH_INSTRUCTION(OPERATION)                                                                             \
nvm::Error nvm::Core::OPERATION(uint8_t instruction[]) {                                                        \
    uint8_t regCategory, regType, destination, operand1, operand2;                                              \
    auto registerError = getTripleRegister(instruction, regCategory, regType, destination, operand1, operand2); \
    if (registerError) return registerError;                                                                    \
    REGISTER_ARRAY_FUNC(regCategory, regType, OPERATION, destination, operand1, operand2);                      \
    return nvm::Error();                                                                                        \
}                                                                                                               \

#endif //__COREMACROS_H__
