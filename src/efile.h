/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_EFILE_H_
#define ESKILIB_EFILE_H_

#include <stdint.h>
#include <stdio.h>

int efgets(char* const input_buffer,
	   const size_t size_of_input_buffer,
	   FILE* const restrict file_pointer);

int efgets_delim(char* const input_buffer,
		 const size_t size_of_input_buffer,
		 FILE* const restrict file_pointer,
		 char delimiter);

#endif // ESKILIB_EFILE_H_
