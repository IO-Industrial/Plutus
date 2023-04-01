//! \file db_file_header_test.cpp
//! \author Joe Turner <joe.turner@io-industrial.com>
//!
//! \copyright
//! Copyright (c) 2023 Joe Turner.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, version 3.
//!
//! This program is distributed in the hope that it will be useful, but
//! WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
//! General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program. If not, see <http://www.gnu.org/licenses/>.
#include "db/db_file_header.h"
#include <gtest/gtest.h>

TEST(db_file_header_tests, test_init)
{
    struct DATA_FILE_HEADER h;
    h.init(100);

    ASSERT_EQ(1, h.version);
    ASSERT_EQ(100, h.record_length);
    ASSERT_EQ(0, h.recinfo.first_record);
    ASSERT_EQ(1, h.recinfo.next_record);
}

TEST(db_file_header_tests, test_locate)
{
    struct DATA_FILE_HEADER h;
    h.init(100);

    ASSERT_EQ(1, h.version);
    ASSERT_EQ(100, h.record_length);
    ASSERT_EQ(0, h.recinfo.first_record);
    ASSERT_EQ(1, h.recinfo.next_record);

    int loc = sizeof(h);
    ASSERT_EQ(loc, h.locate_record(1));
}

TEST(db_file_header_tests, test_isvalid)
{
    struct DATA_FILE_HEADER h;
    h.init(100);

    ASSERT_EQ(1, h.version);
    ASSERT_EQ(100, h.record_length);
    ASSERT_EQ(0, h.recinfo.first_record);
    ASSERT_EQ(1, h.recinfo.next_record);

    ASSERT_EQ(true, h.isValidRecordNumber(1));

    ASSERT_EQ(false, h.isValidRecordNumber(100));

}
