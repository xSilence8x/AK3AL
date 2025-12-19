/*!
 * \file       heap.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of the heap module in version min-heap.
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "data.h"
#include "heap.h"
#include "mymalloc.h"
#include <stdlib.h>
#include <string.h>

/* Private macro ---------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private types ---------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
bool Heap_Init(tHeap *heap)
{
  // Zkontrolumeme, jestli je ukazatel platný
  if (heap == NULL) return false;

  // Alokujeme paměť pro pole prvků a následně zkontrolujeme
  heap->array = myMalloc(MAX_ITEMS_START * sizeof(Data_t));
  if (heap->array == NULL) return false;

  // Podle hlavičkového souboru je count = 0 => halda je prázdná
  heap->count = 0;

  // Podle zadání je max kapacita nastavena na konstantu
  heap->maxItems = MAX_ITEMS_START;

  return true;
}

bool Heap_Insert(tHeap *heap, Data_t insertData)
{
  // Zkontrolujeme jestli je ukazatel validní
  if (heap == NULL) return false;

  // Zkontrolujeme, jestli je na haldě ještě místo
  if (heap->count >= heap->maxItems) {
    // Při realokaci je potřeba dle zadání 2* zvětšit haldu
    size_t newMaxItems = heap->maxItems * 2;
    Data_t *tmp = myRealloc(heap->array, (newMaxItems * sizeof(Data_t)));

    // Pokud se realokace nezdaří, vrať NULL
    if (tmp == NULL) return false;
    heap->array = tmp;
    heap->maxItems = newMaxItems;
  }

  // Vložíme prvek na konec haldy
  size_t i = heap->count;
  heap->array[i] = insertData;
  heap->count++;

  // Vybublání prvku nahoru
  while (i > 0) {
    // Jak spočítáme index rodiče
    size_t parent = (i - 1) / 2;

    // Srovnání prvků pomocí fce z knihovny data.h
    if (Data_Cmp(&heap->array[parent], &heap->array[i]) <= 0) break;

    // Prohození rodiče a potomka
    Data_t tmp = heap->array[parent];
    heap->array[parent] = heap->array[i];
    heap->array[i] = tmp;

    // Pokračujeme od rodiče
    i = parent;
  }
    return true;
}

void Heap_Destruct(tHeap *heap)
{
  if (heap == NULL) return;
  myFree(heap->array);
  heap->array = NULL;
  heap->count = 0;
  heap->maxItems = 0;
}

bool Heap_FindMin(tHeap heap, Data_t *value)
{
  // Ověříme, že máme výsledek kam uložit
  if (value == NULL) return false;

  // Ověříme, že halda není prázdná
  if (heap.count == 0) return false;

  // Min-Heap má nejmenší prvek vždy na 0. indexu
  *value = heap.array[0];
  return true;
}

bool Heap_DeleteMin(tHeap *heap, Data_t *deletedValue)
{
  // Ověříme, že v parametrech jsou validní data
  if (heap == NULL || deletedValue == NULL) return false;

  if (heap->count == 0) return false;

  // Když mažeme nejmenší = mažeme 0. prvek
  *deletedValue = heap->array[0];

  // Pokud je na haldě jen 1 prvek
  if (heap->count == 1) {
    heap->count = 0;
    return true;
  }

  // Poslední prvek posuneme na kořen
  heap->array[0] = heap->array[heap->count-1];
  heap->count--;

  size_t i = 0;

  // Probublávání
  while (true) {
    // Vzorce pro výpočet indexů levého a pravého dítěte
    size_t left  = 2 * i + 1;
    size_t right = 2 * i + 2;

    // Pokud nemá levé dítě, tak nemá žádné
    if (left >= heap->count) break;

    // Vyber menší dítě
    size_t smallest = left;

    // Ověříme, jestli pravé dítě existuje a zároveň jestli je pravé dítě menší než levé
    if (right < heap->count && Data_Cmp(&heap->array[right], &heap->array[left]) < 0) {
      smallest = right;
    }

    // Pro srovnání prvků nutné použít Data_Cmp z knihovny data.h
    // leva <= prava --> Data_Cmp(L, P) <= 0
    if (Data_Cmp(&heap->array[i],&heap->array[smallest]) <= 0) break;

    Data_t tmp = heap->array[i];
    heap->array[i] = heap->array[smallest];
    heap->array[smallest] = tmp;

    i = smallest;
  }
  return true;
}


void Heap_Process(tHeap heap, heapProcessCB cb)
{
  // Pokud není callback, tak nemáme co volat
  if (cb == NULL) return;

  // Pokud heap nemá data, není co zpracovat
  if (heap.array == NULL || heap.count == 0) return;

  // Projdeme všechny prvky
  for (size_t i = 0; i < heap.count; i++) {
    cb(i, &heap.array[i]);
  }
}

bool Heap_Empty(tHeap heap)
{
  // Parametrem není ukazatel na haldu, ale hodnota!
  // U hodnot používáme tečkovou notaci, u ukazatelů šipky
  if (heap.count == 0) return true;
  return false;
}

unsigned Heap_Count(tHeap heap)
{
  // Parametrem není ukazatel, ale hodnota
  if (heap.count > 0) return heap.count;
  return 0;
}
/* Private function definitions ------------------------------------------------------------------*/
