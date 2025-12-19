/*!
 * \file       list.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementing functions of ATD list defined in a header file
 * list.h
 * ****************************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "list.h"
#include "mymalloc.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/

void List_Init(List_t *const list)
{
  if (list == NULL) return;

  // Podle zadání je first a active při inicializaci NULL
  list->first = NULL;
  list->active = NULL;
}

void List_Insert_First(List_t *const list, Data_t data)
{
  if (list == NULL) return;

  // Založíme 1. uzel, alokujeme paměť, zkotrolujeme alokaci
  List_Node_t *newNode = myMalloc(sizeof(List_Node_t));
  if (newNode == NULL) return;

  // Nový uzel populujeme daty
  newNode->data = data;
  newNode->next = list->first;

  // Nastavíme ukazatel na první prvek v listu na 1. uzel
  list->first = newNode;
}

void List_First(List_t *const list)
{
  // Zkontrolujeme jestli je list validní
  if (list == NULL) return;

  list->active = list->first;
}

bool List_Copy_First(List_t list, Data_t *data)
{
  // Zkontrolujeme, že v parametrech jsou validní data
  if (data == NULL) return false;
  if (list.first == NULL) return false;

  // Předáváme hodnoty (tečková notace)
  *data = list.first->data;
  return true;
}

void List_Delete_First(List_t *const list)
{
  if (list == NULL) return;

  // Zkontrolujeme jestli není list prázdný
  if (list->first == NULL) return;

  // Nesmíme ztratit adresu prvního prvku, uložíme do temporary pointeru
  List_Node_t *tmp = list->first;

  // Pokud byl první prvek aktivní, tak active nastavíme na NULL
  if (list->first == list->active) {
    list->active = NULL;
  }

  // Novým prvním prvkem bude následující prvek původního
  list->first = list->first->next;

  // Uvolníme alokaci paměti pro původní 1. prvek
  myFree(tmp);

}

void List_Post_Delete(List_t *const list)
{
  // Zkontrolujeme jestli mazání můžeme provést
  if (list == NULL) return;
  if (list->active == NULL) return;
  if (list->active->next == NULL) return;

  // Je potřeba založit temporary pointer pro list->active->next
  List_Node_t *tmp = list->active->next;

  // Přepojíme uzly - přeskočíme ob jeden
  list->active->next = tmp->next;

  myFree(tmp);
}

void List_Post_Insert(List_t *const list, Data_t data)
{
  if (list == NULL) return;
  if (list->active == NULL) return;

  // Založíme nový uzel
  List_Node_t *newNode = myMalloc(sizeof(List_Node_t));
  if (newNode == NULL) return;

  newNode->data = data;

  // Nový uzel bude ukazovat na to, kam dosud ukazoval active->next
  newNode->next = list->active->next;

  // A active->next přepneme na nový uzel => tím se nový uzel vloží ZA aktivní
  list->active->next = newNode;
}

bool List_Copy(List_t list, Data_t *data)
{
  if (data == NULL) return false;
  if (list.active == NULL) return false;

  *data = list.active->data;
  return true;
}

void List_Active_Update(const List_t *const list, Data_t data)
{
  if (list == NULL) return;
  if (list->active == NULL) return;

  list->active->data = data;
}

void List_Active_Next(List_t *const list)
{
  if (list == NULL) return;
  if (list->active == NULL) return;

  list->active = list->active->next;
}

bool List_Is_Active(List_t list)
{
  // Zjišťujeme, jestli list.active neobsahuje NULL
  return list.active != NULL;
}

/* Private function definitions ------------------------------------------------------------------*/