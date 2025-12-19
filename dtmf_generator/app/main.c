/*!
 * \file       main.c
 * \author     Ondřej Ševčík
 * \date       9/2019
 * \brief      Main file for DTMF generator
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "dtmf.h"
#include "ioutils.h"
#include "vector.h"
#include "wavfile.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define PATH_FILE "sound.wav"

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
void PrintMenu(void);

/* Exported functions definitions ----------------------------------------------------------------*/
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  printf("DTMF generator\n");
  printf("---------------\n\n");

  bool running = true;
  bool vectorCreated = false;
  unsigned symbolsCount = 0;

  Vector_t *vector = NULL;

  PrintMenu();

  while (running == true) {
    printf("\nYour choice:\n");
    char usersInput;
    io_utils_get_char(&usersInput);

    switch (usersInput) {
      case '0':
        if (vectorCreated == false) {
          vector = Vector_Create(1024, 1024);
          if (vector != NULL) {
            printf("Vector created successfully!\n");
            vectorCreated = true;
          } else {
            printf("Vector not created successfully!\n");
          }
        } else {
          printf("Vector is already created!\n");
        }
        break;

      case '1':
        if (vectorCreated == false) {
          printf("Vector was not created!\n");
          break;
        }
        printf("Please enter a symbol (1-9) or A,B,C,D,*,#, space "
               "means there is a pause between sounds, anything else to exit.\n");
        char toneInput;
        io_utils_get_char(&toneInput);
        while (DTMF_Generate(vector, toneInput) == true) {
          printf("Please enter a symbol (1-9) or A,B,C,D,*,#, space "
                 "means there is a pause between sounds, anything else to "
                 "exit.\n");
          io_utils_get_char(&toneInput);
          symbolsCount++;
        }
        printf("Exit\n");
        break;

      case '2':
        if (vectorCreated == false) {
          printf("Vector was not created!\n");
          break;
        }

        FILE *f = wavfile_open(PATH_FILE);
        if (!f) {
          printf("couldn't open %s", PATH_FILE);
        } else {
          for (size_t i = 0; i < Vector_Length(vector); i++) {
            Vector_DataType_t data;
            if (Vector_At(vector, i, &data)) {
              wavfile_write(f, &data, 1);
            }
          }
          printf("WAV file created successfully!\n");
          wavfile_close(f);
        }
        break;

      case 'm':
      case 'M':
        PrintMenu();
        break;

      case 'E':
      case 'e':
        running = false;
        printf("Ending the program!\n");
        break;

      default:
        printf("Invalid option!\n");
        break;
    }
  }
  Vector_Destroy(&vector);

  return 0;
}

/* Private function definitions ------------------------------------------------------------------*/
void PrintMenu(void)
{
  printf("0 - Vector Create\n"
         "1 - Input chars\n"
         "2 - Write to file\n"
         "M - Menu\n"
         "E - Exit\n");
}
