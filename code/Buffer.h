/*************************************************************
* REPLACE the file header below with your file header (see CST8152_ASSAMG.pdf for details).
* File Name: buffer.h
* Version: 1.20.1
* Author: S^R
* Date: 1 January 2020
* Preprocessor directives, type declarations and prototypes necessary for buffer implementation
* as required for CST8152-Assignment #1.
* The file is not completed.
* You must add your function declarations (prototypes).
* You must also add your constant definitions and macros,if any.
*/

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
	MODE_FIXED = 'F',
	MODE_ADDIT = 'A',
	MODE_MULTI = 'M'
};

/* TO_DO: Adjust all constants to your Language */

#define BUFFER_ERROR (-1)				/* General error message */
#define BUFFER_EOF '\0'					/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

#define SOFIA_DEFAULT_SIZE 100			/* default initial buffer capacity */
#define SOFIA_DEFAULT_INCREMENT 10		/* default increment factor */

/* You should add your own constant definitions here */
#define SOFIA_MAX_SIZE SHRT_MAX-1		/*maximum capacity*/ 

/* Add your bit-masks constant definitions here - Defined for SOFIA */
/**/
#define SOFIA_DEFAULT_FLAG 0xFC 	/* 1111.1100 */
#define SOFIA_SET_FLAG_RLC 0x02		/* 0000.0010 */
#define SOFIA_RST_FLAG_RLC 0xFD		/* 1111.1101 */
#define SOFIA_CHK_FLAG_RLC 0x02		/* 0000.0010 */
#define SOFIA_SET_FLAG_EOB 0x01		/* 0000.0001 */
#define SOFIA_RST_FLAG_EOB 0xFE		/* 1111.1110 */
#define SOFIA_CHK_FLAG_EOB 0x01		/* 0000.0001 */

/* TO_DO: Adjust to operate with MSB */
/*
#define YOURLANG_DEFAULT_FLAG		TO_DEFINE 	
#define YOURLANG_SET_FLAG_RLC		TO_DEFINE	
#define YOURLANG_RST_FLAG_RLC		TO_DEFINE	
#define YOURLANG_CHK_FLAG_RLC		TO_DEFINE	
#define YOURLANG_SET_FLAG_EOB		TO_DEFINE	
#define YOURLANG_RST_FLAG_EOB		TO_DEFINE	
#define YOURLANG_CHK_FLAG_EOB		TO_DEFINE
*/

/* Logical constants - adapt for your language */
#define SOFIA_TRUE 1
#define SOFIA_FALSE 0

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

typedef short			sofia_int;
typedef char			sofia_chr;
typedef unsigned char	sofia_flg;
typedef char			sofia_bol;

/* user data type declarations */
typedef struct OffsetSofia {
	sofia_int addC;      /* the offset (in chars) to the add-character location */
	sofia_int getC;      /* the offset (in chars) to the get-character location */
	sofia_int mark;      /* the offset (in chars) to the mark location */
} Offset;

/* user data type declarations */
typedef struct BufferSofia {
	sofia_chr* string;         /* pointer to the beginning of character array (character buffer) */
	sofia_int size;            /* current dynamic memory size (in bytes) allocated to character buffer */
	sofia_int increment;       /* character array increment factor */
	sofia_int mode;            /* operational mode indicator*/
	sofia_flg flags;  /* contains character array reallocation flag and end-of-buffer flag */
	Offset offset;
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */

/* Function declarations */

BufferPointer bufferCreate(sofia_int, sofia_int, sofia_int);
BufferPointer bufferAddChar(BufferPointer const, sofia_chr);
sofia_bol bufferRetract(BufferPointer const);
sofia_bol bufferRestore(BufferPointer const);
sofia_bol bufferRewind(BufferPointer const);
sofia_bol bufferClean(BufferPointer const);
sofia_bol bufferDestroy(BufferPointer const);

sofia_bol bufferSetOffsetMark(BufferPointer const, sofia_int);
sofia_int bufferPrint(BufferPointer const);
sofia_int bufferLoad(BufferPointer const, FILE* const);

sofia_bol bufferCheckFull(BufferPointer const);
sofia_bol bufferCheckEmpty(BufferPointer const);

sofia_int bufferGetSize(BufferPointer const);
sofia_int bufferGetOffsetAddC(BufferPointer const);
sofia_int bufferGetOffsetMark(BufferPointer const);
sofia_int bufferGetOffsetGetC(BufferPointer const);
sofia_int bufferGetIncrement(BufferPointer const);
sofia_int bufferGetMode(BufferPointer const);
sofia_chr bufferGetChar(BufferPointer const);
sofia_chr* bufferGetSubString(BufferPointer const, sofia_int);
sofia_flg bufferGetFlags(BufferPointer const);


#endif
