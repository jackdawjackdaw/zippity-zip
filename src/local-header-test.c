#include "stdio.h"
#include "stdlib.h"

#include "zip-headers.h"

#define localSig 0x04034b50

int readLHeader(FILE* stream, struct localHeader *head)
{
	unsigned short int flags[5];
	char *fbuffer;
	//char fname2[128];
	//unsigned int *fbuffer;
	char *exbuffer;
	
	fread(&(head->headSig), sizeof(unsigned int), 1, stream);
	if(head->headSig != localSig){
		fprintf(stderr, "# read bad local sig: %#x\n", head->headSig);
		return -1;
	}
	fprintf(stderr, "# read local sig: %#x\n", head->headSig);
	
	fread(&flags, sizeof(unsigned short int), 5, stream);
	head->minVer = flags[0];
	head->bitFlag = flags[1];
	head->compMethod = flags[2];
	head->lmodT = flags[3];
	head->lmodD = flags[3];
	
	fprintf(stderr, "# minVer: %#x\tbitFlag %#x\tcomp %#x\tlmodT %#x\t lmodD %#x\n",
					head->minVer,
					head->bitFlag,
					head->compMethod,
					head->lmodT,
					head->lmodD);

	fprintf(stderr, "# minVer: %d\tbitFlag %d\tcomp %d\tlmodT %d\t lmodD %d\n",
					head->minVer,
					head->bitFlag,
					head->compMethod,
					head->lmodT,
					head->lmodD);

	
	fread(&(head->checkSum), sizeof(unsigned int), 1, stream);
	fread(&(head->compSize), sizeof(unsigned int), 1, stream);
	fread(&(head->ucompSize), sizeof(unsigned int), 1, stream);
	/* hmm these come out as zero ... */
	fprintf(stderr, "# crc: %#x\tcomp: %#x\tucom: %#x\n",
					head->checkSum,
					head->compSize,
					head->ucompSize);
	
	fread(&head->fnameLenN, sizeof(unsigned short int), 1, stream);
	fread(&head->fnameLenM, sizeof(unsigned short int), 1, stream);
	
	fprintf(stderr, "# N: %d M: %d\n", head->fnameLenN, head->fnameLenM);

	// ooh this isn't working well
	fbuffer = malloc(sizeof(unsigned int)*head->fnameLenN); // oh man alloc space for the terminating 0 also
	exbuffer = malloc(sizeof(char)*head->fnameLenM);
	
	//fread(&fbuffer, sizeof(char), head->fnameLenN, stream);
	fscanf(stream, "%s", &fbuffer);
	
	//fread(&(head->fname), sizeof(char), head->fnameLenN, stream);
	//fread(&(head->extra), sizeof(char), head->fnameLenM, stream);

	//fbuffer[head->fnameLenN-2] = '\0';
	//fprintf(stderr, "# fname: %x\n", fbuffer);
	fprintf(stderr, "# fname: %s\n", fbuffer);
	
	
	return 1;
}

/**
 * open file given as the first argument
 * try and read the first local_header
 * this should be relatively easy
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
