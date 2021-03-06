/*************************************************************
 * COMPILERS COURSE - Algonquin College
 * Code version: Fall, 2020
 * This Code is EXCLUSIVE for professors (must not be shared)
 * Author: Svillen Ranev - Paulo Sousa
 *************************************************************
 * File name: Buffer.c
 * Compiler: GCC 9.3, Clang 11
 * Authors: Jon Liu 040967432, Tyson Moyes 040761903
 * Course: CST 8152 - Compilers, Lab Section: 013
 * Assignment: A12
 * Date: Jun 5, 2021
 * Professor: Paulo Sousa
 * Purpose: This file is the main code for Buffer (A1)
 * Function list:
 *  - bufferCreate
 *  - bufferAddChar
 *  - bufferClean
 *  - bufferDestroy
 *  - bufferCheckFull
 *  - bufferGetOffsetAddC
 *  - bufferGetSize
 *  - bufferGetMode
 *  - bufferGetOffsetMark
 *  - bufferSetOffsetMark
 *  - bufferPrint
 *  - bufferLoad
 *  - bufferCheckEmpty
 *  - bufferGetChar
 *  - bufferRewind
 *  - bufferRetract
 *  - bufferRestore
 *  - bufferGetOffsetGetC
 *  - bufferGetIncrement
 *  - bufferGetString
 *  - bufferGetFlags
 *************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

/************************************************************
* Function name: bufferCreate
* Purpose: Creates the buffer according to capacity, increment
	factor and operational mode (F, A, M)
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: Ver 2.0
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to Buffer)
* Algorithm: Allocation of memory according to inicial (default) values.
**************************************************************/

BufferPointer bufferCreate(zz_int size, zz_int increment, zz_int mode)
{
	BufferPointer b;
	if (size < 0 || size > ZZ_MAX_SIZE)
		return NULL;
	if (!size)
	{
		size = ZZ_DEFAULT_SIZE;
		increment = ZZ_DEFAULT_INCREMENT;
	}
	if (!increment)
		mode = MODE_FIXED;
	b = (BufferPointer)calloc(1, sizeof(Buffer));
	if (b == NULL)
		return NULL;
	b->string = (zz_char *)malloc(size);
	if (!b->string)
	{
		free(b);
		return NULL;
	}
	b->mode = mode;
	b->size = size;
	b->increment = increment;
	b->flags = ZZ_DEFAULT_FLAG;
	return b;
}

/************************************************************
* Function name: bufferAddChar
* Purpose: Adds a char to buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   ch = char to be added
* Return value: bPointer (pointer to Buffer)
**************************************************************/
BufferPointer bufferAddChar(BufferPointer const pBuffer, zz_char ch)
{
	zz_char *tempbuf;
	zz_int newSize;
	if (!pBuffer)
		return NULL;
	pBuffer->flags = pBuffer->flags & ZZ_RST_FLAG_RLB;
	if (pBuffer->offset.addC * sizeof(zz_char) == ZZ_MAX_SIZE)
		return NULL;
	if (bufferCheckFull(pBuffer) == ZZ_TRUE)
	{
		switch (pBuffer->mode)
		{
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			newSize = pBuffer->size + pBuffer->increment;
			if (newSize < 0 || newSize <= pBuffer->size)
				return NULL;
			if (DEBUG)
				printf("%s%d%s", "\n................\n* New size: ",
					   newSize, "\n................\n");
			break;
		case MODE_MULTI:
			newSize = pBuffer->size * pBuffer->increment;
			if (newSize < 0 || newSize <= pBuffer->size)
				return NULL;
			if (DEBUG)
				printf("%s%d%s", "\n................\n* New size: ",
					   newSize, "\n................\n");
			break;
		default:
			return NULL;
		}
		tempbuf = (zz_char *)realloc(pBuffer->string, newSize);
		if (!tempbuf)
			return NULL;
		if (tempbuf != pBuffer->string)
		{
			pBuffer->flags = pBuffer->flags | ZZ_SET_FLAG_RLB;
			pBuffer->string = tempbuf;
		}
		pBuffer->size = newSize;
	}
	pBuffer->string[pBuffer->offset.addC++] = ch;
	return pBuffer;
}

/************************************************************
* Function name: bufferClean
* Purpose: Clears the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferClean(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	pBuffer->offset.addC = pBuffer->offset.mark = pBuffer->offset.getC = 0;
	pBuffer->flags = pBuffer->flags & ZZ_RST_FLAG_EOB;
	pBuffer->flags = pBuffer->flags & ZZ_RST_FLAG_RLB;
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferDestroy
* Purpose: Releases the buffer address
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferDestroy(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	free(pBuffer->string);
	free(pBuffer);
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferCheckFull
* Purpose: Checks if buffer is full
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferCheckFull(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	if (pBuffer->size == pBuffer->offset.addC * (zz_int)sizeof(zz_char))
		return ZZ_TRUE;
	return ZZ_FALSE;
}

/************************************************************
* Function name: bufferGetOffsetAddC
* Purpose: Returns the position of char to be added
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: addcPosition value
**************************************************************/
zz_int bufferGetOffsetAddC(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	return pBuffer->offset.addC;
}

/************************************************************
* Function name: bufferGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Size of buffer.
**************************************************************/
zz_int bufferGetSize(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	return pBuffer->size;
}

/************************************************************
* Function name: bufferGetMode
* Purpose: Returns the operational mode
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: operational mode.
**************************************************************/
zz_int bufferGetMode(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return (zz_char)BUFFER_ERROR;
	return pBuffer->mode;
}

/************************************************************
* Function name: bufferGetOffsetMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: mark offset.
**************************************************************/

zz_int bufferGetOffsetMark(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	return pBuffer->offset.mark;
}

/************************************************************
* Function name: bufferSetOffsetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   mark = mark position for char
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferSetOffsetMark(BufferPointer const pBuffer, zz_int mark)
{
	if (!pBuffer || mark < 0 || mark > pBuffer->offset.addC)
		return ZZ_FALSE;
	pBuffer->offset.mark = mark;
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Number of chars printed.
**************************************************************/
zz_int bufferPrint(BufferPointer const pBuffer)
{
	zz_int cont = 0;
	zz_char c;
	if (!pBuffer || !(pBuffer->string))
		return BUFFER_ERROR;
	c = bufferGetChar(pBuffer);
	while (!(pBuffer->flags & ZZ_CHK_FLAG_EOB))
	{
		cont++;
		printf("%c", c);
		c = bufferGetChar(pBuffer);
	}
	return cont;
}

/************************************************************
* Function name: bufferLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   fi = pointer to file descriptor
* Return value: Number of chars read and put in buffer.
**************************************************************/
zz_int bufferLoad(BufferPointer const pBuffer, FILE *const fi)
{
	zz_int size = 0;
	zz_char c;
	if (!fi || !pBuffer)
		return BUFFER_ERROR;
	c = (zz_char)fgetc(fi);
	while (!feof(fi))
	{
		if (!bufferAddChar(pBuffer, c))
		{
			ungetc(c, fi);
			return BUFFER_ERROR;
		}
		c = (char)fgetc(fi);
		size++;
	}
	if (ferror(fi))
		return BUFFER_ERROR;
	return size;
}

/************************************************************
* Function name: bufferCheckEmpty
* Purpose: Checks if buffer is empty.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferCheckEmpty(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	if (pBuffer->offset.addC == 0)
		return ZZ_TRUE;
	return ZZ_FALSE;
}

/************************************************************
* Function name: bufferGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Char in the getC position.
**************************************************************/
zz_char bufferGetChar(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	if (pBuffer->offset.getC == pBuffer->offset.addC)
	{
		pBuffer->flags = pBuffer->flags | ZZ_SET_FLAG_EOB;
		return '\0';
	}
	pBuffer->flags = pBuffer->flags & ZZ_RST_FLAG_EOB;
	return pBuffer->string[pBuffer->offset.getC++];
}

/************************************************************
* Function name: bufferRewind
* Purpose: Rewinds the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferRewind(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	pBuffer->offset.getC = 0;
	pBuffer->offset.mark = 0;
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferRetract(BufferPointer const pBuffer)
{
	if (!pBuffer || pBuffer->offset.getC == 0)
		return ZZ_FALSE;
	pBuffer->offset.getC--;
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferRestore
* Purpose: Resets the buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Boolean value about operation success
**************************************************************/
zz_bool bufferRestore(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return ZZ_FALSE;
	pBuffer->offset.getC = pBuffer->offset.mark;
	return ZZ_TRUE;
}

/************************************************************
* Function name: bufferGetOffsetGetC
* Purpose: Returns the value of getCPosition.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: The getC offset.
**************************************************************/
zz_int bufferGetOffsetGetC(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	return pBuffer->offset.getC;
}

/************************************************************
* Function name: bufferGetIncrement
* Purpose: Returns the buffer increment.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: The Buffer increment.
**************************************************************/
zz_int bufferGetIncrement(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return BUFFER_ERROR;
	return pBuffer->increment;
}

/************************************************************
* Function name: bufferGetString
* Purpose: Returns the pointer to String.
* Parameters:
*   pBuffer = pointer to Buffer Entity
*   pos = position to get the pointer
* Return value: Position of string char.
**************************************************************/
zz_char *bufferGetSubString(BufferPointer const pBuffer, zz_int pos)
{
	if (!pBuffer || pos < 0 || pos > pBuffer->offset.addC)
		return NULL;
	return pBuffer->string + pos;
}

/************************************************************
* Function name: bufferGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   pBuffer = pointer to Buffer Entity
* Return value: Flags from Buffer.
**************************************************************/
#define FLAGS_
#undef FLAGS_
#ifndef FLAGS_
zz_flags bufferGetFlags(BufferPointer const pBuffer)
{
	if (!pBuffer)
		return (unsigned char)BUFFER_ERROR;
	return pBuffer->flags;
}
#else
#define bGetFlags(pBuffer) ((pBuffer) ? (pBuffer->flags) : (RT_FAIL_1))
#endif