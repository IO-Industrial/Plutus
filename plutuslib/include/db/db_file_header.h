//! \file db_file_header.h
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
#ifndef _DB_FILE_HEADER_H_
#define _DB_FILE_HEADER_H_
#include <stdint.h>
#include <sys/types.h>
#include "db/db_record_pointer.h"

/*
FAT32 - 4Gib  
NTFS - 16Eib  
ext2/3 - 16Gib - 2Tib (depends from block size)  
ext4 - 16Gib - 16Tib  
XFS - 9Eib  
ZFS - 16Eib
*/

struct DATA_FILE_RECORD_HEADER
{
    // first available deleted record.
    uint32_t first_record;

    //! next available record position
    uint32_t next_record;
};


//! \brief Data file header
//!
//! This data files contain a file header, followed by random 
//! accessed records.
struct DATA_FILE_HEADER
{
    //! \brief Data file format version
    char version;

    int16_t record_length;

    struct DATA_FILE_RECORD_HEADER recinfo;

    void init(uint16_t length)
    {
        version = 1;
        recinfo.first_record = 0;
        recinfo.next_record = 1;
        record_length = length;
    }

    inline
    off_t locate_record(RPTR record_number)
    {
        return sizeof(struct DATA_FILE_HEADER) +
                (
                    (record_number - 1) * record_length);
    }

    //! \brief Record number sanity check
    //!
    //! This function will do a bounds check to see if our
    //! logical record number is past the end of the file.
    //!
    //! \returns
    //! \retval false 
    //!     The supplied logical record number is out of bounds.
    //! \retval true  
    //!     The supplied logical record number is in bounds.
    inline bool isValidRecordNumber(RPTR record_number)
    {
        if (record_number > recinfo.next_record)
        {
            return false;
        }
        return true;
    }
};

#endif
