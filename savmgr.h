/* Rosa Knowles
 * 9/22/2025
 * Header for code that manages reading and writing save files
 */

#ifndef SAVMGR_H
#define SAVMGR_H

#include <stdint.h>
#include <stddef.h> // `size_t`
#include <stdio.h>
#include "record_release.h"

// Note:
// RFORMAT and MONTH both have a size of 4 bytes

size_t get_bytearr_rep(uint8_t ** byte_array, const record_release * rr);


#endif