/*!
 * \file       vector.c
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
/* Includes --------------------------------------------------------------------------------------*/
#include "vector.h"
#include "mymalloc.h"
#include <assert.h>
//#include <c++/stdlib.h>
#include <stdlib.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/

/**
 * @brief Creates and initializes a new Vector_t structure.
 * @param initial_size
 * @param alloc_step
 * @return Returns vector if created otherwise returns NULL.
 */
Vector_t *Vector_Create(size_t initial_size, size_t alloc_step)
{
  //Vector_DataType_t *ptr = malloc(initial_size * sizeof(Vector_DataType_t));
  // Alokuje paměť pro samotnou strukturu Vector_t
  Vector_t * v = myMalloc(sizeof(Vector_t));

  //assert(v != NULL);

  // Ověření alokace paměti; pokud malloc selže, vrátíme NULL
  if (v == NULL) return NULL;

  // Alokace paměti pro položky items.
  v->items = myMalloc(initial_size * sizeof(Vector_DataType_t));
  // assert(v->items != NULL);

  // Pokud 2. alokace selže, uvolníme paměť pro v a vrátíme NULL
  if (v->items == NULL) {
    myFree(v);
    return NULL;
  }
  // Nastavení počátečních hodnot
  v->alloc_step = alloc_step; // Krok pro zvětšení
  v->size = initial_size; // Celková kapacita pole
  v->next = v->items; // Ukazatel na další volné místo

  return v;
}

/**
 * Udělá hlubokou kopii vektoru
 * @param original
 * @return
 */
Vector_t *Vector_Copy(const Vector_t *const original)
{
  if (original == NULL) return NULL;

  Vector_t *copy = myMalloc(sizeof(Vector_t));
  if (!copy) return NULL;

  copy->alloc_step = original->alloc_step;
  copy->size = original->size;

  if (original->items == NULL || original->size == 0)
  {
    copy->items = NULL;
    copy->next = NULL;
    return copy;
  }

  copy->items = myMalloc(original->size * sizeof(Vector_DataType_t));
  if (!copy->items)
  {
    myFree(copy);
    return NULL;
  }

  size_t length = original->next - original->items;
  for (size_t i = 0; i < length; i++)
    copy->items[i] = original->items[i];

  copy->next = copy->items + length;
  return copy;
}
/**
 * Clears vector; Erases the content of a vector, allocated memory for \ref Vector_t.items is freed,
 * the * Vector_t.size of a vector is set to 0, Vector_t.items and \ref Vector_t.next pointers are
 * set to NULL. The \ref Vector_t.alloc_step remains unchanged.
 * @param vector
 */
void Vector_Clear(Vector_t *const vector)
{
  if (vector == NULL) return;
  // Uvolnění dat = items
  myFree(vector->items);

  // Vynulování ukazatelů
  vector->items = NULL;
  vector->next = NULL;

  // Vynulování kapacity
  vector->size = 0;

}

/**
 * Vrací počet prvků ve vektoru
 * @param vector
 * @return
 */
size_t Vector_Length(const Vector_t *const vector)
{
  if (vector == NULL) {
    return SIZE_MAX;
  }
  // Rozdíl první volné místo za posledním přidaným - začátek pole = Počet
  return vector->next - vector->items;
}

/**
 * Vrací prvek na indexu position přes ukazatel value a vrací true pokud position < length,
 * jinak vrátí false.
 * @param vector
 * @param position
 * @param value
 * @return
 */
bool Vector_At(const Vector_t *const vector, size_t position, Vector_DataType_t *const value)
{
  // if (vector == NULL || position >= vector->size || value == NULL)
  //   return false;
  // Zkontrolujeme ukazatele
  if (vector == NULL || value == NULL) return false;

  // Spočítáme délku
  size_t length = vector->next - vector->items;

  if (position >= length) return false;

  *value = vector->items[position];
  return true;
}

/**
 * Removes item on position.
 * @param vector
 * @param position
 * @return
 */
bool Vector_Remove(Vector_t *const vector, size_t position)
{
  // UNUSED(vector);
  // UNUSED(position);
  // Zkontrolujeme, jestli vektor existuje
  if (vector == NULL) return false;

  // Opět spočítáme délku
  size_t length = vector->next - vector->items;
  if (position >= length) return false;

  // Posuneme na position, který mažeme, item z pos+1
  for (size_t i = position; i < length - 1; i++) {
    vector->items[i] = vector->items[i + 1];
  }
  // Next=volná buňka bude o jedno dříve
  vector->next--;

  return true;
}

/**
 * Appends a value in Vector.
 * @param vector
 * @param value
 * @return
 */
size_t Vector_Append(Vector_t *vector, Vector_DataType_t value)
{
  // Ověření platnosti
  if (vector == NULL) return SIZE_MAX;

  // Kontrola, zdali je vektor plný
  if (vector->next >= vector->items + vector->size) {

    // Uložíme si aktuální délku struktury
    size_t current_length = vector->next - vector->items;

    // Realokace
    Vector_DataType_t * newPtr = myRealloc(vector->items,
      sizeof(Vector_DataType_t)*(vector->alloc_step + vector->size));
    //assert(newPtr != NULL);
    if (newPtr == NULL) return SIZE_MAX;

    // Aktualizace ukazatele
    vector->items = newPtr;
    // Přepočítáme next na základě nové adresy items
    vector->next = vector->items + current_length;
    // Aktualizace celkové kapacity
    vector->size += vector->alloc_step;
  }
  // Délka je novým indexem kam vkládáme položku
  size_t index_of_insertion = vector->next - vector->items;

  *vector->next = value;
  vector->next++;

  // Vrátíme novou hodnotu délky
  return index_of_insertion;
}
/**
 * Void func sets/changes value on a position.
 * @param vector
 * @param position
 * @param value
 */
void Vector_Set(Vector_t *const vector, size_t position, Vector_DataType_t value)
{
  // Ověříme, že vector existuje, jinak vyskočíme z funkce
  if (vector == NULL) return;

  size_t length = vector->next - vector->items;

  if (position >= length) return;

  // Když je vše OK, změníme hodnotu ve vektoru na pozici.
  vector->items[position] = value;
}
/**
 * Checks if vector contains a value.
 * @param vector
 * @param value
 * @return Returns true if vector contains value otherwise returns false.
 */
bool Vector_Contains(const Vector_t *const vector, Vector_DataType_t value)
{
  // UNUSED(vector);
  // UNUSED(value);
  if (vector == NULL) return false;
  size_t length = vector->next - vector->items;

  for (size_t i = 0; i < length; i++) {
    if (vector->items[i] == value) return true;
  }

  return false;
}

/**
 * Searches for value from a given position.
 * @param vector
 * @param value
 * @param from
 * @return Returns index of value if position was searched otherwise returns SIZE_MAX.
 */
size_t Vector_IndexOf(const Vector_t *const vector, Vector_DataType_t value, size_t from)
{
  if (vector == NULL) return SIZE_MAX;

  size_t length = vector->next - vector->items;

  // Ověření platnosti from, pokud je >= length, je mimo platný rozsah
  if (from >= length) return SIZE_MAX;

  // Hledáme ze zadané pozice from
  for (size_t i = from; i < length; i++) {
    if (value == vector->items[i]) return i;
  }
  // Pokud jsme nic nenašli, tak vracíme SIZE_MAX
  return SIZE_MAX;
}

/**
 * Fills a value into specified position range.
 * @param vector
 * @param value
 * @param start_position
 * @param end_position
 */
void Vector_Fill(const Vector_t *const vector,
                 Vector_DataType_t value,
                 size_t start_position,
                 size_t end_position)
{
  if (vector == NULL) return;
  size_t length = vector->next - vector->items;
  // Ověříme jestli není vector prázdný
  if (length == 0) return;

  if (start_position >= length) return;
  // Zjistíme poslední index
  size_t last_index = length - 1;
  // Pokud je uživatelův end_pos > last_in
  if (end_position > last_index) {
    end_position = last_index;
  }

  for (size_t i = start_position; i <= end_position; i++) {
    vector->items[i] = value;
  }

}

/**
 * Deletes Vector and frees structure.
 * @param vector
 */
void Vector_Destroy(Vector_t **const vector)
{
  if (vector == NULL || *vector == NULL) return;
  myFree((*vector)->items); // Uvolníme pole s daty
  myFree(*vector); // Uvolníme strukturu
  *vector = NULL; // Vynulování ukazatele
}

/* Private function definitions ------------------------------------------------------------------*/