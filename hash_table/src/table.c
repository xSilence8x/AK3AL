/*!
 * \file       table.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of functions for HashTable.
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
/*! \addtogroup hashTable
 *  \{
 */
/* Includes --------------------------------------------------------------------------------------*/
#include "table.h"

#include "hash_private.h"
#include "mymalloc.h"

#include <stdio.h>
#include <string.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
bool HashTable_Init(HashTable *table, size_t size, bool deletecontents)
{
  if (table == NULL || size == 0) return false;

  // Alokujeme pole bucketů
  table->buckets = (HashTableNode **)myMalloc(sizeof(HashTableNode *) * size);
  if (table->buckets == NULL) return false;

  // Nastavíme všechny bucket ukazatele na NULL
  memset(table->buckets, 0, sizeof(HashTableNode *) * size);

  table->size = size;
  table->count = 0;
  table->take_ownership = deletecontents;

  return true;
}

void HashTable_Destruct(HashTable *table)
{
  if (table == NULL) return;

  // Nejdřív smažeme všechny položky
  HashTable_Clear(table);

  // Uvolníme pole bucketů
  if (table->buckets != NULL) {
    myFree(table->buckets);
    table->buckets = NULL;
  }
  table->size = 0;
  table->count = 0;
  table->take_ownership = false;
}

bool HashTable_Insert(HashTable *table, Data_t *key, Data_t *value)
{
  if (table == NULL || table->buckets == NULL || key == NULL || value == NULL) return false;

  // Kontrola duplicity klíče
  unsigned idx = hash(table, key);

  //kontrola duplicity klíče
  for (HashTableNode *n = table->buckets[idx]; n != NULL; n = n->next) {
    if (Data_Cmp(n->key, key) == 0) return false;
  }
  // Vytvoříme nový uzel
  HashTableNode *newnode =
    (HashTableNode *)myMalloc(sizeof(HashTableNode));
  if (newnode == NULL) return false;

  // Naplníme uzel
  newnode->key = key;
  newnode->value = value;

  // Vložíme ho na začátek seznamu
  newnode->next = table->buckets[idx];
  table->buckets[idx] = newnode;

  table->count++;
  return true;
}

bool HashTable_Replace(HashTable *table, Data_t *key, Data_t *value)
{
  if (table == NULL || key == NULL || value == NULL || table->buckets == NULL) return false;

  unsigned idx = hash(table, key);

  for (HashTableNode *n = table->buckets[idx]; n!= NULL; n = n->next) {
    // Porovnáváme klíče uložené v tabulce s key parametrem
    if (Data_Cmp(n->key, key) == 0) {
      if (table->take_ownership && n->value != value) {
        Data_Destruct(n->value);
      }
      n->value = value;
      return true;
    }
  }
  return false;
}

bool HashTable_Delete(HashTable *table, Data_t *key)
{
  // Ochrana proti špatným vstupům
  if (table == NULL || table->buckets == NULL || key == NULL) {
    return false;
  }

  // Spočítáme index bucketu, ve kterém se má klíč nacházet
  unsigned idx = hash(table, key);

  // Budeme procházet linked list v bucketu:
  HashTableNode *prev = NULL;
  HashTableNode *n = table->buckets[idx];

  while (n != NULL) {
    // Porovnání klíčů: 0 znamená, že jsou stejné
    if (Data_Cmp(n->key, key) == 0) {

      // 1) Odpojíme uzel ze seznamu
      // Pokud mažeme první uzel v bucketu, posuneme začátek seznamu.
      // Jinak přesměrujeme prev->next přes smazaný uzel.
      if (prev == NULL) {
        table->buckets[idx] = n->next;
      } else {
        prev->next = n->next;
      }

      // 2) Pokud tabulka "vlastní" uložená data, musíme uvolnit i key/value
      // Pozor: uvolňujeme klíč a hodnotu uloženou V UZLU (n->key, n->value),
      // ne argument `key`, který nám přišel do funkce (ten může být jen dočasný).
      if (table->take_ownership) {
        Data_Destruct(n->key);
        Data_Destruct(n->value);
      }
      myFree(n);
      table->count--;
      return true;
    }

    // Posun na další uzel v seznamu
    prev = n;
    n = n->next;
  }

  // Klíč nebyl nalezen => nic se nesmazalo
  return false;
}


Data_t *HashTable_Find(HashTable *table, Data_t *key)
{
  if (table == NULL || table->buckets == NULL || key == NULL) {
    return NULL;
  }

  // Spočítáme index bucketu z klíče pomocí hash funkce
  unsigned idx = hash(table, key);

  // Procházíme všechny položky ve vybraném bucketu (linked list)
  for (HashTableNode *n = table->buckets[idx]; n != NULL; n = n->next) {

    // Pokud vrátí 0, klíče jsou stejné
    if (Data_Cmp(n->key, key) == 0) {
      return n->value;
    }
  }
  return NULL;
}


size_t HashTable_Get_Count(HashTable table)
{
  return table.count;
}

void HashTable_Clear(HashTable *table)
{
  if (table == NULL || table->buckets == NULL) return;

  // Projdeme všechny buckety
  for (size_t i = 0; i < table->size; i++) {
    // Vezmeme začátek seznamu v bucketu
    HashTableNode *node = table->buckets[i];

    while (node != NULL) {
      HashTableNode *next = node->next;
      if (table->take_ownership) {
        Data_Destruct(node->key);
        Data_Destruct(node->value);
      }
      myFree(node);
      node = next;
    }
    table->buckets[i] = NULL;
  }
  table->count = 0;
}

void HashTable_Process(HashTable *table, TableNodeProc proc)
{
  if (table == NULL || table->buckets == NULL || proc == NULL) {
    return;
  }

  // Projdeme všechny buckety v tabulce
  for (size_t i = 0; i < table->size; i++) {

    // V každém bucketu projdeme zřetězený seznam uzlů
    for (HashTableNode *n = table->buckets[i]; n != NULL; n = n->next) {

      // Zavoláme uživatelskou funkci nad každou dvojicí (key, value)
      proc(n->key, n->value);
    }
  }
}


/* Private function definitions ------------------------------------------------------------------*/

/*! \} */