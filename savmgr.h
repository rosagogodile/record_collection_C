/* Rosa Knowles
 * 9/22/2025
 * Header for code that manages reading and writing save files
 */

#ifndef SAVMGR_H
#define SAVMGR_H

#include <stdint.h>
#include <stddef.h> // `size_t`
#include "record_release.h"

#define FILE_READ_SUCCESS 1
#define FILE_READ_FAILURE 0

// Note:
// RFORMAT and MONTH both have a size of 4 bytes

// converts a record release to an array of bytes
// will be called when the record releases need to be written to a file
size_t get_bytearr_rep(uint8_t ** byte_array, const record_release * rr);

// converts a byte file into a linked list of record releases
int64_t read_bytearr_file(rr_node ** head, char * filepath, size_t strbuffsize);


#endif