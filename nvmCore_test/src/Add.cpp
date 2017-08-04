#include <nvmCore_test/TestMacros.h>

MATH_ALL(Add);

//TODO:: Add expectations for flags

INSTANTIATE_TEST_CASE_P(AddUi8,
    AddUi8,
    ::testing::Values(
        AddUi8Params(1, 2, 3),
        AddUi8Params(58, 197, 255),
        AddUi8Params(1, 255, 0),
        AddUi8Params(15, 255, 14)
    )
);

INSTANTIATE_TEST_CASE_P(AddI8,
    AddI8,
    ::testing::Values(
        AddI8Params(1, 2, 3),
        AddI8Params(1, -2, -1),
        AddI8Params(127, -255, -128),
        AddI8Params(127, 1, -128),
        AddI8Params(-128, -1, 127)
    )
);

INSTANTIATE_TEST_CASE_P(AddUi16,
    AddUi16,
    ::testing::Values(
        AddUi16Params(1, 2, 3),
        AddUi16Params(65535, 1, 0),
        AddUi16Params(65279, 512, 255)
    )
);

INSTANTIATE_TEST_CASE_P(AddI16,
    AddI16,
    ::testing::Values(
        AddI16Params(1, 2, 3),
        AddI16Params(123, -23, 100),
        AddI16Params(-15, 16, 1),
        AddI16Params(32767, 1, -32768),
        AddI16Params(-32768, -1, 32767)
    )
);

INSTANTIATE_TEST_CASE_P(AddUi32,
    AddUi32,
    ::testing::Values(
        AddUi32Params(1, 2, 3),
        AddUi32Params(4294967295, 1, 0),
        AddUi32Params(4294967039, 512, 255)
    )
);

INSTANTIATE_TEST_CASE_P(AddI32,
    AddI32,
    ::testing::Values(
        AddI32Params(1, 2, 3),
        AddI32Params(123, -23, 100),
        AddI32Params(2147483647, 1, -2147483648),
        AddI32Params(-2147483648, -1, 2147483647)
    )
);

INSTANTIATE_TEST_CASE_P(AddF32,
    AddF32,
    ::testing::Values(
        AddF32Params(1, 2, 3),
        AddF32Params(1.5, 1.5, 3),
        AddF32Params(10, -20, -10),
        AddF32Params(0, 0, 0)
    )
);

INSTANTIATE_TEST_CASE_P(AddF64,
    AddF64,
    ::testing::Values(
        AddF64Params(1, 2, 3),
        AddF64Params(9007199254740991, -1234, 9007199254739757),
        AddF64Params(1.5, -3, -1.5),
        AddF64Params(0, 0, 0)
    )
);
