/**
 * \file main.cpp
 *
 * This file is part of the Payroll C++ Library
 *
 * Copyright (c) 2020 Joe Turner.  All rights reserved.
 * Unauthorized copying prohibited.
 */
#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

