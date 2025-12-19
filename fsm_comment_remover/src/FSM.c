/*!
 * \file       FSM.c
 * \author     Horak, Jurena
 * \date       2019.6
 * \brief      Implementation of function.h header file
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/* Includes ------------------------------------------------------------------*/
#include "FSM.h"

/* Private types -------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Exported functions definitions --------------------------------------------*/
typedef enum { START, LOMITKO, JEDNORADKOVA, VICERADKOVA, MOZNA_KONEC, RETEZEC, BACKSLASH, APOSTROF, BACKSLASH_APOSTROF } state_t;
void FSM_RemoveNotes(FILE* input, FILE* output) {
  //puts("Tonda rekl: \"Ahoj Karle\"");
  state_t stav = START;
  int znak;
  while ((znak = fgetc(input)) != EOF) {
    switch (stav) {
      case START:
        if (znak == '/') {
          stav = LOMITKO;
        } else if (znak == '"') {
          stav = RETEZEC;
          fputc('"', output);
        } else if (znak == '\'') {
          stav = APOSTROF;
          fputc(znak, output);
        } else {
          fputc(znak, output);
        }
        break;
      case LOMITKO:
        if (znak == '/') {
          stav = JEDNORADKOVA;
        } else if (znak == '*') {
          stav = VICERADKOVA;
        } else {
          fputc('/', output);
          fputc(znak, output);
          stav = START;
        }
        break;
      case JEDNORADKOVA:
        if (znak == '\n') {
          stav = START;
          fputc('\n', output);
        }
        break;
      case VICERADKOVA:
        if (znak == '*') {
          stav = MOZNA_KONEC;
        }
        break;
      case MOZNA_KONEC:
        if (znak == '/') {
          stav = START;
        } else {
          stav = VICERADKOVA;
        }
        break;
      case RETEZEC:
        if (znak == '"') {
          stav = START;
          fputc('"', output);
        } else if (znak == '\\') {
          stav = BACKSLASH;
          fputc('\\', output);
        } else {
          fputc(znak, output);
        }
        break;
      case BACKSLASH:
        fputc(znak, output);
        stav = RETEZEC;
        break;
      case APOSTROF:
        if (znak == '\'') {
          stav = START;
        } else if (znak == '\\') {
          stav = BACKSLASH_APOSTROF;
        }
        fputc(znak, output);
        break;
      case BACKSLASH_APOSTROF:
        fputc(znak, output);
        stav = APOSTROF;
        break;
    }
  }
}

/* Private function definitions ----------------------------------------------*/
