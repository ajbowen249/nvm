#include <nvmCore_test/TestMacros.h>

INCDEC_ALL(Decrement);

INSTANTIATE_TEST_CASE_P(DecrementUi8,
    DecrementUi8,
    ::testing::Values(
        DecrementUi8Params(123, 122, FLAGS(P)),
        DecrementUi8Params(1, 0, FLAGS(Z)),
        DecrementUi8Params(0, 255, FLAGS(P))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementI8,
    DecrementI8,
    ::testing::Values(
        DecrementI8Params(123, 122, FLAGS(P)),
        DecrementI8Params(1, 0, FLAGS(Z)),
        DecrementI8Params(-128, 127, FLAGS(P)),
        DecrementI8Params(0, -1, FLAGS(N))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementUi16,
    DecrementUi16,
    ::testing::Values(
        DecrementUi16Params(1, 0, FLAGS(Z)),
        DecrementUi16Params(123, 122, FLAGS(P)),
        DecrementUi16Params(0, 65535, FLAGS(P))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementI16,
    DecrementI16,
    ::testing::Values(
        DecrementI16Params(1, 0, FLAGS(Z)),
        DecrementI16Params(123, 122, FLAGS(P)),
        DecrementI16Params(-32768, 32767, FLAGS(P)),
        DecrementI16Params(0, -1, FLAGS(N))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementUi32,
    DecrementUi32,
    ::testing::Values(
        DecrementUi32Params(1, 0, FLAGS(Z)),
        DecrementUi32Params(123, 122, FLAGS(P)),
        DecrementUi32Params(0, 4294967295, FLAGS(P))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementI32,
    DecrementI32,
    ::testing::Values(
        DecrementI32Params(1, 0, FLAGS(Z)),
        DecrementI32Params(123, 122, FLAGS(P)),
        DecrementI32Params(-2147483648, 2147483647, FLAGS(P)),
        DecrementI32Params(0, -1, FLAGS(N))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementF32,
    DecrementF32,
    ::testing::Values(
        DecrementF32Params(2.5, 1.5, FLAGS(P)),
        DecrementF32Params(0.5, -0.5, FLAGS(N)),
        DecrementF32Params(1, 0, FLAGS(Z)),
        DecrementF32Params(-0.5, -1.5, FLAGS(N))
    )
);

INSTANTIATE_TEST_CASE_P(DecrementF64,
    DecrementF64,
    ::testing::Values(
        DecrementF64Params(2.5, 1.5, FLAGS(P)),
        DecrementF64Params(0.5, -0.5, FLAGS(N)),
        DecrementF64Params(1, 0, FLAGS(Z)),
        DecrementF64Params(-0.5, -1.5, FLAGS(N))
    )
);
