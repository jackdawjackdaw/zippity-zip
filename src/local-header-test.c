#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "zip-headers.h"

#define localSigBYTES 0x04034b50

int readLHeader(FILE* stream, struct localHeader *head)
{
  uint16_t flags[5];
  unsigned char *fbuffer; // anticipate this actually being ascii encoded
  uint8_t *exbuffer; // no idea what this will hold
  
  fread(&(head->headSig), sizeof(uint32_t), 1, stream);
  if(head->headSig != localSigBYTES){
    fprintf(stderr, "# read bad local sig: %#x\n", head->headSig);
    return -1;
  }
  fprintf(stderr, "# read local sig: %#x\n", head->headSig);
  
  fread(&flags, sizeof(uint16_t), 5, stream);
  head->minVer = flags[0];
  head->bitFlag = flags[1];
  head->compMethod = flags[2];
  // this is MS-DOS time, weird: http://proger.i-forge.net/MS-DOS_date_and_time_format/OFz
  head->lmodT = flags[3];
  head->lmodD = flags[4];
  
  fprintf(stderr, "# minVer: %#x\tbitFlag %#x\tcomp %#x\tlmodT %#x\t lmodD %#x\n",
          head->minVer,
          head->bitFlag,
          head->compMethod,
          head->lmodT,
          head->lmodD);

  fread(&(head->checkSum), sizeof(uint32_t), 1, stream);
  fread(&(head->compSize), sizeof(uint32_t), 1, stream);
  fread(&(head->ucompSize), sizeof(uint32_t), 1, stream);
  /* hmm these come out as zero ... (only for a directory) */
  fprintf(stderr, "# crc: %#x\tcomp: %#x\tucom: %#x\n",
          head->checkSum,
          head->compSize,
          head->ucompSize);
  
  fread(&head->fnameLenN, sizeof(uint16_t), 1, stream);
  fread(&head->fnameLenM, sizeof(uint16_t), 1, stream);
  
  fprintf(stderr, "# N: %u M: %u\n", head->fnameLenN, head->fnameLenM);

  fbuffer = malloc(sizeof(uint8_t)*head->fnameLenN); // oh man alloc space for the terminating 0 also
  exbuffer = malloc(sizeof(uint8_t)*head->fnameLenM);

  // hmm
  fread(fbuffer, sizeof(uint8_t)*head->fnameLenN, 1, stream);
  fread(exbuffer, sizeof(uint8_t), head->fnameLenM, stream);
  
  fbuffer[head->fnameLenN] = '\0'; // stringify properly
  
  //fprintf(stderr, "# %c\n", fbuffer[0]);

  head->fname = malloc(sizeof(uint8_t)*head->fnameLenN);
  memcpy(head->fname, fbuffer, head->fnameLenN);
  
  head->extra = malloc(sizeof(uint8_t)*head->fnameLenM);
  memcpy(head->extra, exbuffer, head->fnameLenM);

  fprintf(stderr, "# %s\n", head->fname);
  //fprintf(stderr, "# %s\n", head->extra);
  
  
  return 1;
}

/**
 * open file given as the first argument
 * try and read the first local_header
 * this should be relatively easy
 *
 * now try and zoop through until we get to the central directory (near the end)
 * and then what/
 */

int main (int argc, char* argv[]){
  FILE *fptr;

  if(argc < 2){
    fprintf(stderr, "# reads first local header in zip file\n");
    fprintf(stderr, "# run with file to process as first argument\n");
    return EXIT_FAILURE;
  }

  localHeader lheader;

  fptr = fopen(argv[1], "r");
  
  readLHeader(fptr, &lheader);
  

  return EXIT_SUCCESS;
}
