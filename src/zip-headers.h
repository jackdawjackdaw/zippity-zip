#ifndef __INC_ZIPHEAD__
#include <stdint.h>
/**
 * zip files are laid out:
 * 
 * local_header_1 file_data_1 local_header_2 file_data_2 ... local_header_n directory
 *
 * the central directory lists relative offsets for each of the local
 * headers, the directory is at the end of the file so that additional
 * junk can be smashed in.
 * 
 * i always forget this 
 *  short int    2      16          -32,768 -> +32,767          (16kb)
 *  unsigned short int    2      16                0 -> +65,535          (32Kb)
 *  unsigned int    4      16                0 -> +4,294,967,295   ( 4Gb)
 *           int    4      32   -2,147,483,648 -> +2,147,483,647   ( 2Gb)
 *      long int    4      32   -2,147,483,648 -> +2,147,483,647   ( 2Gb)
 *   signed char    1       8             -128 -> +127
 * unsigned char    1       8                0 -> +255
 * 
 */

/**
 * header for a local file
 * fields are given in order, with their offests listed
 * from a table on: https://en.wikipedia.org/wiki/Zip_(file_format)
 */

typedef struct localHeader{
	uint32_t headSig; /* 0, 0x04034b50 */
	uint16_t minVer; /* 4 */
	uint16_t bitFlag; /* 6 */
	uint16_t compMethod; /* 8 */
	uint16_t lmodT; /* 10 */
	uint16_t lmodD; /* 12 */
	uint32_t checkSum; /* 14, CRC-32 */
	uint32_t compSize; /* 18 */
	uint32_t ucompSize; /* 22 */
	uint16_t fnameLenN; /* 26 */
	uint16_t fnameLenM; /* 28 */
	unsigned char* fname; /* starts offset 30, length n */
	uint8_t * extra; /* starts offset 30+n, length m */

} localHeader;


#endif
