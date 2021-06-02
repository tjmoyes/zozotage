/** File Name: Buffer.h
* Version: 1.20.1
* Authors: Jon Liu 040967432, Tyson Moyes 040761903
* Date: Jun 5, 2021
*
* Preprocessor directives, type declarations and prototypes necessary for buffer
implementation
* as required for CST8152-Assignment #1.
* TODO:
* The file is not completed.
* You must add your function declarations (prototypes).
*
* History:
*	* Jon Liu adapted the provided header file to Zozotage
*/

#ifndef BUFFER_H_
#define BUFFER_H_

#include <limits.h>
#include <malloc.h>
#include <stdio.h>

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT)
 * ======================================================
 */

/* Modes (used to create buffer) */
enum BUFFERMODES { MODE_FIXED = 'F', MODE_ADDIT = 'A', MODE_MULTI = 'M' };

#define BUFFER_ERROR (-1) /* General error message */
#define BUFFER_EOF '\0'   /* General EOF */

/** Constants for Zozotage, prefixed by "zz"
 * =========================================
 */

#define ZZ_DEFAULT_SIZE 100     /* default initial buffer capacity */
#define ZZ_DEFAULT_INCREMENT 10 /* default increment factor */

/* You should add your own constant definitions here */
#define ZZ_MAX_SIZE SHRT_MAX - 1 /*maximum capacity*/

/* Bit masks */
#define ZZ_DEFAULT_FLAG 0x3F /* 0011 1111 */
/* Realloced buffer */
#define ZZ_SET_FLAG_RLB 0x80 /* 1000 0000 */
#define ZZ_RST_FLAG_RLB 0x7F /* 0111 1111 */
#define ZZ_CHK_FLAG_RLB 0x80 /* 1000 0000 */
/* End of buffer */
#define ZZ_SET_FLAG_EOB 0x40 /* 0100 0000 */
#define ZZ_RST_FLAG_EOB 0xBF /* 1011 1111 */
#define ZZ_CHK_FLAG_EOB 0x40 /* 0100 0000 */

/* Logical constants - adapt for your language */
#define ZZ_TRUE 1
#define ZZ_FALSE 0

/** Structures for Zozotage, prefixed by "zz"
 * ==========================================
 */

typedef int zz_int;
typedef char zz_char;
typedef unsigned char zz_flags;
typedef char zz_bool;

/* user data type declarations */
typedef struct ZzOffset {
  zz_int addC; /* the offset (in chars) to the add-character location */
  zz_int getC; /* the offset (in chars) to the get-character location */
  zz_int mark; /* the offset (in chars) to the mark location */
} Offset;

/* user data type declarations */
typedef struct ZzBuffer {
  zz_char* string;  /* pointer to the start of char array (char buffer) */
  zz_int size;      /* current byte size allocated to char buffer */
  zz_int increment; /* character array increment factor */
  zz_int mode;      /* operational mode indicator*/
  zz_flags flags;   /* contains character array reallocation flag and
                       end-of-buffer flag */
  Offset offset;
} Buffer, *BufferPointer;

/** Function prototypes
 * ====================
 */

BufferPointer bufferCreate(zz_int, zz_int, zz_int);
BufferPointer bufferAddChar(BufferPointer const, zz_char);
zz_bool bufferRetract(BufferPointer const);
zz_bool bufferRestore(BufferPointer const);
zz_bool bufferRewind(BufferPointer const);
zz_bool bufferClean(BufferPointer const);
zz_bool bufferDestroy(BufferPointer const);

zz_bool bufferSetOffsetMark(BufferPointer const, zz_int);
zz_int bufferPrint(BufferPointer const);
zz_int bufferLoad(BufferPointer const, FILE* const);

zz_bool bufferCheckFull(BufferPointer const);
zz_bool bufferCheckEmpty(BufferPointer const);

zz_int bufferGetSize(BufferPointer const);
zz_int bufferGetOffsetAddC(BufferPointer const);
zz_int bufferGetOffsetMark(BufferPointer const);
zz_int bufferGetOffsetGetC(BufferPointer const);
zz_int bufferGetIncrement(BufferPointer const);
zz_int bufferGetMode(BufferPointer const);
zz_char bufferGetChar(BufferPointer const);
zz_char* bufferGetSubString(BufferPointer const, zz_int);
zz_flags bufferGetFlags(BufferPointer const);

#endif
