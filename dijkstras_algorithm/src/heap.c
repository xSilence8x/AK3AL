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
#include "heap.h"
#include "mymalloc.h"
#include "data.h"
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
  if (heap == NULL) return false;

  heap->array = myMalloc(MAX_ITEMS_START * sizeof(Data_t));
  if (heap->array == NULL) return false;

  heap->count = 0;
  heap->maxItems = MAX_ITEMS_START;
  return true;
}

bool Heap_Insert(tHeap *heap, Data_t insertData)
{
  if (heap == NULL) return false;

  if (heap->count >= heap->maxItems) {
    size_t newMaxItems = 2 * heap->maxItems;
    Data_t *tmp = myRealloc(heap->array, newMaxItems * sizeof(Data_t));
    if (tmp == NULL) return false;

    heap->array = tmp;
    heap->maxItems = newMaxItems;
  }

  size_t i = heap->count;
  heap->array[i] = insertData;
  heap->count++;

  while (i > 1) {
    size_t parent = (i - 1) / 2;
    if (Data_Cmp(&heap->array[parent], &heap->array[i]) <= 0) break;

    Data_t tmp = heap->array[parent];
    heap->array[parent] = heap->array[i];
    heap->array[i] = tmp;
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
  if (value == NULL) return false;
  if (heap.count == 0) return false;

  *value = heap.array[0];
  return true;
}

bool Heap_DeleteMin(tHeap *heap, Data_t *deletedValue)
{
  if (deletedValue == NULL || heap == NULL) return false;
  if (heap->count == 0) return false;

  *deletedValue = heap->array[0];

  if (heap->count == 1) {
    heap->count = 0;
    return true;
  }

  heap->array[0] = heap->array[heap->count - 1];
  heap->count--;

  size_t i = 0;

  while (true) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left >= heap->count) break;

    size_t smallest = left;
    if (right < heap->count && Data_Cmp(&heap->array[right], &heap->array[left]) < 0) {
      smallest = right;
    }

    if (Data_Cmp(&heap->array[i], &heap->array[smallest]) <= 0) break;

    Data_t tmp = heap->array[i];
    heap->array[i] = heap->array[smallest];
    heap->array[smallest] = tmp;
    i = smallest;
  }
  return true;
}

void Heap_Process(tHeap heap, heapProcessCB cb)
{
  if (cb == NULL) return;
  if (heap.array == NULL || heap.count == 0) return;

  for (size_t i = 0; i < heap.count; i++) {
    cb(i, &heap.array[i]);
  }
}

bool Heap_Empty(tHeap heap)
{
  if (heap.count == 0) return true;
  return false;
}

unsigned Heap_Count(tHeap heap)
{
  return heap.count;
}
/* Private function definitions ------------------------------------------------------------------*/
