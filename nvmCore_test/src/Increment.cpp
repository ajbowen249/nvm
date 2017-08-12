#include <nvmCore_test/TestMacros.h>

INCDEC_ALL(Increment);

INSTANTIATE_TEST_CASE_P(IncrementUi8,
    IncrementUi8,
    ::testing::Values(
        IncrementUi8Params(1, 2, FLAGS(P)),
        IncrementUi8Params(255, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementI8,
    IncrementI8,
    ::testing::Values(
        IncrementI8Params(1, 2, FLAGS(P)),
        IncrementI8Params(127, -128, FLAGS(N)),
        IncrementI8Params(-1, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementUi16,
    IncrementUi16,
    ::testing::Values(
       IncrementUi16Params(1, 2, FLAGS(P)),
       IncrementUi16Params(65535, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementI16,
    IncrementI16,
    ::testing::Values(
        IncrementI16Params(1, 2, FLAGS(P)),
        IncrementI16Params(32767, -32768, FLAGS(N)),
        IncrementI16Params(-1, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementUi32,
    IncrementUi32,
    ::testing::Values(
        IncrementUi32Params(1, 2, FLAGS(P)),
        IncrementUi32Params(4294967295, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementI32,
    IncrementI32,
    ::testing::Values(
        IncrementI32Params(1, 2, FLAGS(P)),
        IncrementI32Params(2147483647, -2147483648, FLAGS(N)),
        IncrementI32Params(-1, 0, FLAGS(Z))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementF32,
    IncrementF32,
    ::testing::Values(
        IncrementF32Params(1.5, 2.5, FLAGS(P)),
        IncrementF32Params(-0.5, 0.5, FLAGS(P)),
        IncrementF32Params(-1, 0, FLAGS(Z)),
        IncrementF32Params(-1.5, -0.5, FLAGS(N))
    )
);

INSTANTIATE_TEST_CASE_P(IncrementF64,
    IncrementF64,
    ::testing::Values(
        IncrementF64Params(1.5, 2.5, FLAGS(P)),
        IncrementF64Params(-0.5, 0.5, FLAGS(P)),
        IncrementF64Params(-1, 0, FLAGS(Z)),
        IncrementF64Params(-1.5, -0.5, FLAGS(N))
    )
);
