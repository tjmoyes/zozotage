/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
* Author: Svillen Ranev - Paulo Sousa, Jon Liu 040967432, Tyson Moyes 040761903
*************************************************************
* File name: Scanner.c
* Compiler: MS Visual Studio 2019
* Course: CST 8152 - Compilers, Lab Section: 013
* Assignment: A22
* Date: July 7, 2021
* Professor: Paulo Sousa
* Purpose: This file contains all functionalities from Scanner.
* Function list:
* - startScanner
* - tokenizer
* - nextState
* - nextClass
* - funcVID
* - funcIL
* - funcFL
* - funcSL
* - funcKW
* - funcErr
*************************************************************/

/* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>  /* standard input / output */
#include <ctype.h>  /* conversion functions */
#include <stdlib.h> /* standard library functions and constants */
#include <string.h> /* string functions */
#include <limits.h> /* integer types constants */
#include <float.h>  /* floating-point types constants */

/* #define NDEBUG        to suppress assert() call */
#include <assert.h> /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Buffer.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable; /* String literal table */
zz_int line;                             /* Current line number of the source code */
extern zz_int errorNumber;               /* Defined in platy_st.c - run-time error number */

extern zz_int stateType[];
extern zz_char *keywordTable[];
extern PTR_ACCFUN finalStateTable[];
extern zz_int transitionTable[][TABLE_COLUMNS];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer; /* pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer; /* pointer to input source buffer */

/*************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ************************************************************/
zz_int startScanner(BufferPointer psc_buf)
{
  if (bufferCheckEmpty(psc_buf) == ZZ_TRUE)
    return EXIT_FAILURE; /*1*/
  /* in case the buffer has been read previously  */
  bufferRewind(psc_buf);
  bufferClean(stringLiteralTable);
  line = 1;
  sourceBuffer = psc_buf;
  return EXIT_SUCCESS; /*0*/
}

/*************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states
 *		in the Transition Diagram).
 ************************************************************/
Token tokenizer(void)
{
  Token currentToken = {0}; /* token to return after pattern recognition. Set all structure members to 0 */
  zz_char c;                /* input symbol */
  zz_int state = 0;         /* initial state of the FSM */
  zz_int lexStart;          /* start offset of a lexeme in the input char buffer (array) */
  zz_int lexEnd;            /* end offset of a lexeme in the input char buffer (array)*/

  zz_int lexLength; /* token length */
  zz_int i;         /* counter */
  zz_char newc;     /* new char */

  while (1)
  { /* endless loop broken by token returns it will generate a warning */
    c = bufferGetChar(sourceBuffer);

    /* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

    /* TODO: 15: All patterns that do not require accepting functions */
    switch (c)
    {

      /* Cases for spaces */
    case ' ':
      break;
    case '\n':
      line++;
      break;
      /* TODO_15A: See all other elements */

      /* Cases for symbols */
    case '(':
      currentToken.code = LPR_T;
      return currentToken;
    case '+':
      newc = bufferGetChar(sourceBuffer);
      if (newc == '+')
      {
        currentToken.code = SCC_OP_T;
        return currentToken;
      }
      bufferRetract(sourceBuffer);
      currentToken.code = ART_OP_T;
      currentToken.attribute.codeType = ADD;
      return currentToken;
      /* TODO_15B: See all other elements */

    case '.':
      /* AND operator */
      bufferSetOffsetMark(sourceBuffer, bufferGetOffsetGetC(sourceBuffer));
      if (bufferGetChar(sourceBuffer) == '&' &&
          bufferGetChar(sourceBuffer) == '.')
      {
        currentToken.code = LOG_OP_T;
        currentToken.attribute.codeType = AND;
        return currentToken;
      }
      else
        bufferRestore(sourceBuffer);
      /* TODO_15C: Other logical operators */

    /* Comments */
    case ';':
      newc = bufferGetChar(sourceBuffer);
      do
      {
        c = bufferGetChar(sourceBuffer);
        if (c == CHARSEOF0 || c == CHARSEOF255)
        {
          bufferRetract(sourceBuffer);
          //return currentToken;
        }
        else if (c == '\n')
        {
          line++;
        }
      } while (c != '@' && c != CHARSEOF0 && c != CHARSEOF255);
      break;

    /* Cases for END OF FILE */
    case CHARSEOF0:
      currentToken.code = SEOF_T;
      currentToken.attribute.seofType = SEOF_0;
      return currentToken;
    case CHARSEOF255:
      currentToken.code = SEOF_T;
      currentToken.attribute.seofType = SEOF_EOF;
      return currentToken;

      /* ------------------------------------------------------------------------
				Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
				Note: Part 2 must follow Part 1 to catch the illegal symbols
				-----------------------------------------------------------------------
			*/

      /* TODO:_16: Adjust / check the logic for your language */

    default: // general case
      state = nextState(state, c);
      lexStart = bufferGetOffsetGetC(sourceBuffer) - 1;
      bufferSetOffsetMark(sourceBuffer, lexStart);
      while (stateType[state] == NOAS)
      {
        c = bufferGetChar(sourceBuffer);
        state = nextState(state, c);
      }
      if (stateType[state] == ASWR)
        bufferRetract(sourceBuffer);
      lexEnd = bufferGetOffsetGetC(sourceBuffer);
      lexLength = lexEnd - lexStart;
      lexemeBuffer = bufferCreate((short)lexLength + 2, 0, MODE_FIXED);
      if (!lexemeBuffer)
      {
        fprintf(stderr, "Scanner error: Can not create buffer\n");
        exit(1);
      }
      bufferRestore(sourceBuffer);
      for (i = 0; i < lexLength; i++)
        bufferAddChar(lexemeBuffer, bufferGetChar(sourceBuffer));
      bufferAddChar(lexemeBuffer, BUFFER_EOF);
      currentToken = (*finalStateTable[state])(bufferGetSubString(lexemeBuffer, 0));
      bufferDestroy(lexemeBuffer);
      return currentToken;
    } // switch

  } //while

} // tokenizer

/*************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUF is used - see the top of the file.
 ************************************************************/
/* TODO: 17: Just change the datatypes */

zz_int nextState(zz_int state, zz_char c)
{
  zz_int col;
  zz_int next;
  col = nextClass(c);
  next = transitionTable[state][col];
  if (DEBUG)
    printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
  assert(next != IS);
  if (DEBUG)
    if (next == IS)
    {
      printf("Scanner Error: Illegal state:\n");
      printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
      exit(1);
    }
  return next;
}

/*************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
************************************************************/
/* TODO: 18: Use your column configuration */

zz_int nextClass(zz_char c)
{
  zz_int val = -1;
  /* Adjust the logic to return next column in TT */
  /*	[A-z](0), [-?!+-/*=](1), [0-9](2), ~(3), .(4), "(5), #(6), EOFS(7) */
  switch (c)
  {
  case CHRCOL2:
    val = 2;
    break;
  case CHRCOL3:
    val = 3;
    break;
  case CHRCOL4:
    val = 4;
    break;
  case CHRCOL5:
    val = 5;
    break;
  case CHRCOL6:
    val = 6;
    break;
  /*case CHRCOL7:
    val = 7;
    break;
    */
  case CHARSEOF0:
  case CHARSEOF255:
    val = 8;
    break;
  default:
    if (isalpha(c))
      val = 0;
    else if (isdigit(c))
      val = 1;
    else
      val = 9;
  } //switch
  return val;
}

/*************************************************************
 * Acceptance State Function VID
 *		In this function, the pattern for IVID must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ************************************************************/
/* TODO:_19A: Adjust the function for VID */
Token funcVID(zz_char lexeme[])
{
  Token currentToken = {0};
  switch (lexeme[0])
  {
  /* TODO: We only use VID, not specific types. This needs to be altered */
  case IVIDPREFIX:
    /* currentToken.code = IVID_T; */
    break;
  case FVIDPREFIX:
    /* currentToken.code = FVID_T; */
    break;
  case SVIDPREFIX:
    /*currentToken.code = SVID_T;*/
    break;
  default:
    currentToken.code = ERR_T;
    break;
  }
  strncpy(currentToken.attribute.vidLexeme, lexeme, VID_LEN);
  currentToken.attribute.vidLexeme[VID_LEN] = CHARSEOF0;
  return currentToken;
}

/*************************************************************
 * Acceptance State Function IL
 *		Function responsible to identify IL (integer literals).
 * - It is necessary respect the limit (ex: 2-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually,
 *   additional three dots (...) should be put in the output.
 ************************************************************/
/* TODO:_19B: Adjust the function for IL */

Token funcIL(zz_char lexeme[])
{
  Token currentToken = {0};
  zz_lng tlong;
  if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN)
  {
    currentToken = (*finalStateTable[ES])(lexeme);
  }
  else
  {
    tlong = atol(lexeme);
    if (tlong >= 0 && tlong <= SHRT_MAX)
    {
      currentToken.code = INL_T;
      currentToken.attribute.intValue = (zz_int)tlong;
    }
    else
    {
      currentToken = (*finalStateTable[ES])(lexeme);
    }
  }
  return currentToken;
}

/*************************************************************
 * Acceptance State Function FPL
 *		Function responsible to identify FPL (float point literals).
 * - It is necessary respect the limit (ex: 4-byte integer in C).
 * - In the case of larger lexemes, error shoul be returned.
 * - Only first ERR_LEN characters are accepted and eventually,
 *   additional three dots (...) should be put in the output.
 ************************************************************/
/* TODO:_19C: Adjust the function for FPL */

Token funcFL(zz_char lexeme[])
{
  Token currentToken = {0};
  zz_dbl tdouble = atof(lexeme);
  if (tdouble == 0.0 || tdouble >= FLT_MIN && tdouble <= FLT_MAX)
  {
    currentToken.code = FPL_T;
    currentToken.attribute.floatValue = (zz_flt)tdouble;
  }
  else
  {
    currentToken = (*finalStateTable[ES])(lexeme);
  }
  return currentToken;
}

/*************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table
 *   (stringLiteralTable). You need to include the literals in
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ************************************************************/
/* TODO:_19D: Adjust the function for SL */

Token funcSL(zz_char lexeme[])
{
  Token currentToken = {0};
  zz_int i = 0, len = (zz_int)strlen(lexeme);
  currentToken.attribute.contentString = bufferGetOffsetAddC(stringLiteralTable);
  for (i = 1; i < len - 1; i++)
  {
    if (lexeme[i] == '\n')
      line++;
    if (!bufferAddChar(stringLiteralTable, lexeme[i]))
    {
      currentToken.code = RTE_T;
      strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
      errorNumber = RTE_CODE;
      return currentToken;
    }
  }
  if (!bufferAddChar(stringLiteralTable, CHARSEOF0))
  {
    currentToken.code = RTE_T;
    strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
    errorNumber = RTE_CODE;
    return currentToken;
  }
  currentToken.code = STR_T;
  return currentToken;
}

/*************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ************************************************************/
/* TODO:_19E: Adjust the function for Keywords */

Token funcKW(zz_char lexeme[])
{
  Token currentToken = {0};
  zz_int kwindex = -1, j = 0;
  for (j = 0; j < KWT_SIZE; j++)
    if (!strcmp(lexeme, &keywordTable[j][0]))
      kwindex = j;
  if (kwindex != -1)
  {
    currentToken.code = KW_T;
    currentToken.attribute.codeType = kwindex;
  }
  else
  {
    currentToken = funcErr(lexeme);
  }
  return currentToken;
}

/*************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ************************************************************/
/* TODO:_19F: Adjust the function for Errors */

Token funcErr(zz_char lexeme[])
{
  Token currentToken = {0};
  zz_int i = 0, len = (zz_int)strlen(lexeme);
  if (len > ERR_LEN)
  {
    strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
    currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
    strcat(currentToken.attribute.errLexeme, "...");
  }
  else
  {
    strcpy(currentToken.attribute.errLexeme, lexeme);
  }
  for (i = 0; i < len; i++)
    if (lexeme[i] == '\n')
      line++;
  currentToken.code = ERR_T;
  return currentToken;
}

/*
TODO:_20: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/
