

#include <stdio.h>
#include <stdlib.h>

#define PADCHAR 0

enum { FALSE, TRUE };

int BufferInputFile(char *filename, long *insize, char *buf)
{
	FILE *fptr;
	unsigned long count;
	unsigned long size;

	// Open for read
	if( (fptr  = fopen( filename, "rb" )) == NULL )
		return FALSE;
	
	// Get file size
	fseek(fptr, 0, SEEK_END);
	size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	// Cycle until end of file reached
	size = 0;
	while( !feof( fptr ) )
	{
		// Attempt to read in 1000 bytes
		count = fread( buf+size, sizeof( char ), 1000, fptr );
		if( ferror( fptr ) )   
			return FALSE;

		// Total up actual bytes read
		size += count;
	}

	// Close file
	if( fclose( fptr ) )
		return FALSE;

	//return size
	*insize = size;

	return TRUE;
}

unsigned long InsertBlock(char *iname, unsigned long insize, FILE *ofptr)
{
	unsigned long  ofwrcnt = 0, i,padsize;
	
	long ifsize;
	unsigned char *buf;
	
	
	buf = (unsigned char*)malloc(insize);
	if(buf==NULL)
	{
		printf("malloc input file %s error\n",iname);
		return FALSE;
	}

	//buffer input file content
	if( !BufferInputFile( iname, &ifsize, (char *)buf))
	{
		printf("buffer input file %s error\n",iname);
		return FALSE;
	}

	ofwrcnt += ifsize;

	//Padding
	if((padsize = insize-ifsize) < 0 )
		return FALSE;

	for( i=0; i<padsize; i++ )
		buf[ofwrcnt++] = PADCHAR;

	//Write checksum
	fwrite ( buf, sizeof(char), insize, ofptr );

	free(buf);
	return insize;
}

#if 1
int main(int argc, char **argv)
{
	FILE *fptr;
        unsigned long count;
        unsigned long size;
	int i;
	if(argc == 1)
	{
		printf("usage:makeflash destFile orgFile1 orgFile1size ...\r\n");
		return 1;
	}
	if( (fptr  = fopen(argv[1], "w+" )) == NULL )
	{
		printf("Can't create file %s", argv[1]);
		return 1;
	}
	for(i=0; i<(argc-2)/2; i++)
	{
		size = strtol(argv[i*2+3],NULL,16);
		printf("%s", argv[i*2+3]);
		printf("add %s, size %ld\r\n", argv[i*2+2], size);
		InsertBlock(argv[i*2+2], size, fptr);
	}
	return 0;
	
}

#else
int main(int argc, char **argv)
{
	FILE *fptr;
	unsigned long count;
	unsigned long size;

	// Open for read
	if( (fptr  = fopen("9331.bin", "w+" )) == NULL )
		return FALSE;

	InsertBlock("u-boot.bin", 0x50000, fptr);
	InsertBlock("tozedcpe-squashfs", 0x300000-0x50000, fptr);
	InsertBlock("vmlinux.lzma.uImage", 0xf0000, fptr);
	InsertBlock("art.bin", 0x10000, fptr);
	fclose(fptr);
	return 0;
}
#endif
