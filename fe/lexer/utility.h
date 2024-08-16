#ifndef parser_utility
#define parser_utility

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token.h"

static const char *getTokenText(enum TokenType tt) {
  return tokenStrings[tt];
}

static void printToken(Token *tok) {
  switch (tok->type) {
    case ID:
      printf("%s", getTokenText(tok->type));
      printf(": %s (%d)\n", tok->lexeme, tok->lineNo);
      return;
    case NUM:
      printf("%s", getTokenText(tok->type));
      printf(": %s (%d)\n", tok->lexeme, tok->lineNo);
      return;
    case ERROR:
      printf("Error on line %d: %s\n", tok->lineNo, tok->errorMsg);
      return;
    default:
      printf("%s (%d)\n", getTokenText(tok->type), tok->lineNo);
  }
}

int currLineNo = 1;
static void reconstructToken(Token *tok) {
  while (tok->lineNo > currLineNo) {
    printf("\n");
    currLineNo++;
  }
  switch (tok->type) {
    case ID:
      printf("%s ", tok->lexeme);
      break;
    case NUM:
      printf("%s ", tok->lexeme);
      break;
    case ERROR:
      printf("%s\n", getTokenText(tok->type));
      printToken(tok);
      break;
    default:
      printf("%s ", getTokenText(tok->type));
  }
}

static void setLexeme(Token *tok, char lexeme[], int lexemeLength) {
  char* s2;
  s2 = (char *) malloc(lexemeLength);
  tok->lexeme = (char*) strcpy(s2, lexeme);
}

int isEOF(char c) {
    return c == EOF;
}

int isWhitespace(char c) {
  if (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
    return 1;
  }
  return 0;
}

int isNonzeroDigit(char c) {
  if (isdigit(c) && c != '0') {
    return 1;
  }
  return 0;
}

int stringMatch() {
}

#endif
