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
#ifndef _DB_RECORD_POINTER_H_
#define _DB_RECORD_POINTER_H_
#include <stdint.h>

//! \brief Record pointer
//! 
//! RPTR is defined as a 32-bit number, meaning that
//! we can support 2^32 records in a datafile.
//!
//! This represents teh logical record postition within the data file.
//! The RPTR value is relative to one.
//!
typedef uint32_t       RPTR;

#endif