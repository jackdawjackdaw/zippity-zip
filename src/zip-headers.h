#ifndef __INC_ZIPHEAD__
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
	unsigned int headSig; /* 0, 0x04034b50 */
	unsigned short int minVer; /* 4 */
	unsigned short int bitFlag; /* 6 */
	unsigned short int compMethod; /* 8 */
	unsigned short int lmodT; /* 10 */
	unsigned short int lmodD; /* 12 */
	unsigned int checkSum; /* 14, CRC-32 */
	unsigned int compSize; /* 18 */
	unsigned int ucompSize; /* 22 */
	unsigned short int fnameLenN; /* 26 */
	unsigned short int fnameLenM; /* 28 */
	char* fname; /* starts offset 30, length n */
	char* extra; /* starts offset 30+n, length m */
} localHeader;


#endif
