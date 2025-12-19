/*!
 * \file       main.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Main file
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"
#include "ioutils.h"
#include "list.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
static void menu(void);
static void Vypis_Seznam(List_t list);

/* Exported functions definitions ----------------------------------------------------------------*/
int main()
{
  // Eclipse console bug workaround:
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  printf("List test program\n");
  List_t seznam;
  Data_t data;
  List_Init(&seznam); /*kdyby uzivatel zapomel na zacatku iniciovat seznam... */
  menu();
  bool running = true;
  char c;

  while (running) {
    running = io_utils_get_char(&c);

    if (!running) {
      continue;
    }

    printf("Your choice=%c\n", c); /* kontrola pri praci se presmerovanym vstupem */

    switch (toupper(c)) {
      case '0':
        printf("Init - list initialization\n");
        List_Init(&seznam);
        break;

      case '1':
        printf("Active_Update - Updates the data of an active item\n");
        running = Data_Get(&data);

        if (running) {
          List_Active_Update(&seznam, data);
        }

        break;

      case '2':
        printf("Insert_First - insert new item in the first position\n");
        running = Data_Get(&data);

        if (running) {
          List_Insert_First(&seznam, data);
        }

        break;

      case '3':
        printf("First - set as an active item the first one\n");
        List_First(&seznam);
        break;

      case '4':
        printf("Copy_First - Display first item in list\n");

        if (List_Copy_First(seznam, &data)) {
          Data_Print(&data);
        }

        break;

      case '5':
        printf("Delete_First - Deletes first item\n");
        List_Delete_First(&seznam);
        break;

      case '6':
        printf("Post_Delete - Deletes item that is located after active item\n");
        List_Post_Delete(&seznam);
        break;

      case '7':
        printf("Post_Insert - Insert new item after the active one\n");
        running = Data_Get(&data);

        if (running) {
          List_Post_Insert(&seznam, data);
        }

        break;

      case '8':
        printf("Copy - Gets the values of the active item \n");

        if (List_Copy(seznam, &data)) {
          Data_Print(&data);
        }

        break;

      case '9':
        printf("Active_Next - Shift the active item to the next one\n");
        List_Active_Next(&seznam);
        break;

      case 'A':
        printf("Is_Active - Check, if theres an active item\n");

        if (List_Is_Active(seznam)) {
          printf("Is_Active=true\n");
        } else {
          printf("Is_Active=false\n");
        }

        break;

      case 'M':
      case 'm':

        menu();
        break;

      default:
        printf("Unknown option\n");
        menu();
        break;
    }

    Vypis_Seznam(seznam);
    printf("Type char 0-A, EOF(tj. CTRL+Z nebo CTRL+D)=Konec, M=Menu:\n");
    printf("************************************************************\n");
  }

  List_First(&seznam);

  while (List_Is_Active(seznam)) {
    List_Active_Next(&seznam);
    List_Delete_First(&seznam);
  }

  return 0;
}

/* Private function definitions ------------------------------------------------------------------*/
static void menu(void)
{
  printf("Type char 0-A for one of the following options:\n"
         "0: Init,\n"
         "1: Active_Update,\n"
         "2: Insert_First,\n"
         "3: First,\n"
         "4: Copy_First,\n"
         "5: Delete_First,\n"
         "6: Post_Delete,\n"
         "7: Post_Insert,\n"
         "8: Copy,\n"
         "9: Active_Next,\n"
         "A: Is_Active,\n"
         "M: Print menu\n"
         "CTRL+Z (Win) or CTRL+D (Unix): END\n");
}

static void Vypis_Seznam(List_t list)
{
  Data_t data;
  int cislo = 1;
  printf("Active item:\n");

  if (List_Is_Active(list)) {
    if (List_Copy(list, &data)) {
      Data_Print(&data);
    }
  } else {
    printf("NULL\n");
  }

  List_First(&list);
  printf("Content of List:\n");

  while (List_Is_Active(list)) {
    if (List_Copy(list, &data)) {
      printf("%d. item: ", cislo++);
      Data_Print(&data);
    }

    List_Active_Next(&list);
  }

  printf("\n");
}