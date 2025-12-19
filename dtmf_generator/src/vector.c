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
# include <stdlib.h>
#include "vector.h"
#include "mymalloc.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
/**
 * Vytváří nový vektor
 * @param initial_size = kolik prvků se má alokovat
 * @param alloc_step = o kolik se bude vektor zvětšovat
 * @return Vrací nově vytvořený vektor (ukazatel); pokud se vektor
 * nevytvoří, vrací NULL
 */
Vector_t *Vector_Create(size_t initial_size, size_t alloc_step)
{
  // Alokace paměti pro samotnou strukturu vektoru
  Vector_t *v = myMalloc(sizeof(Vector_t));
  // Pokud alokace selže, vrať NULL
  if (v == NULL) return NULL;
  // Uložení kroku realokace
  v->alloc_step = alloc_step;
  // Uložení počáteční kapacity vektoru
  v->size = initial_size;
  // Speciální případ: vektor se vytváří s nulovou kapacitou
  // zatím se nealokuje žádné pole prvků
  if (initial_size == 0) {
    v->items = NULL;  // pole prvků zatím neexistuje
    v->next = NULL;   // neexistuje ani ukazatel na další volné místo
    return v;         // vracíme platný, ale prázdný vektor
  }

  // Alokace paměti pro pole prvků vektoru
  v->items = myMalloc(initial_size * sizeof(Vector_DataType_t));
  // Pokud alokace pole prvků selže, uvolníme strukturu vektoru
  if (v->items == NULL) {
    myFree(v);
    return NULL;
  }
  // Nastavení ukazatele na první volné místo ve vektoru
  // Na začátku je vektor prázdný, takže next ukazuje na items
  v->next = v->items;
  return v;
}

/**
 * Vytvoří deep copy (samostatně nezávislou) kopii vektoru
 * @param original = kopírovaný vektor
 * @return Vrací nově vytvořenou kopii vektoru
 */
Vector_t *Vector_Copy(const Vector_t *const original)
{
  // Zkontroluje jestli original existuje
  if (original == NULL) return NULL;

  Vector_t *copy = myMalloc(sizeof(Vector_t));
  // Pokud se alokace nepovedla, tak vrátíme NULL
  if (!copy) return NULL;

  copy->alloc_step = original->alloc_step;
  copy->size = original->size;
  // Pokud originální vektor nemá alokovaná data nebo má kapacitu
  // 0, tak vytvoříme prázdnou kopii bez dat
  if (original->items == NULL || original->size == 0) {
    copy->items = NULL;
    copy->next = NULL;
    return copy;
  }
  // Pokud Items existují, tak alokujeme stejnou velikost paměti
  copy->items = myMalloc(original->size * sizeof(Vector_DataType_t));
  // Pokud alokace selže, tak uvolni paměť pro kopii
  if (!copy->items) {
    free(copy);
    return NULL;
  }
  // Vypočítáme, kolik prvků je uloženo;
  // original->next = ukazuje za poslední volný prvek
  // original->items = ukazuje na první prvek
  size_t length = original->next - original->items;
  // Zkopírujeme všechny prvky original --> copy
  for (size_t i = 0; i < length; i++) {
    copy->items[i] = original->items[i];
  }
  // Potřebujeme vypočítat, kde leží copy next:
  // adresa copy->next + počet obsazených prvků ve vektoru
  copy->next = copy->items + length;
  return copy;
}

/**
 * Maže obsah vektoru a uvolňuje paměť. Nezničí vektor jako takový.
 * @param vector = Vstupem je ukazatel na vektor
 */
void Vector_Clear(Vector_t *const vector)
{
  if (vector == NULL) return;
  // Uvolnění dat = Items
  free(vector->items);
  // Vynulování pointerů
  vector->items = NULL;
  vector->next = NULL;
  // Vynulování kapacity
  vector->size = 0;
}

/**
 * Počítá počet prvků ve vektoru.
 * @param vector
 * @return Vrací počet prvků.
 */
size_t Vector_Length(const Vector_t *const vector)
{
  // SIZE_MAX je konstanta v C, je to prakticky hodnota,
  // která nemůže být nikdy validní pro počet prvků vektoru
  if (vector == NULL) return SIZE_MAX;
  // Vrací rozdíl: první volné místo za posledním přidaným prvkem
  // minus
  // ukazatel na začátek pole (vektoru) = počet
  return vector->next - vector->items;
}

/**
 * Zjišťuje, jestli na indexu (position) máme prvek a ten vrací na adrese value.
 * @param vector = ukazatel na vektor
 * @param position = index prvku, který chceme
 * @param value = místo, kam se má uložit získaná hodnota z indexu
 * @return Vrací true, pokud je value na position, jinak false.
 */
bool Vector_At(const Vector_t *const vector, size_t position, Vector_DataType_t *const value)
{
  // Kontrola platných adres
  if (vector == NULL || value == NULL) return false;
  size_t length = vector->next - vector->items;
  // Pokud je position větší než celkový počet prvků, vrať NULL
  if (position >= length) return false;
  // Pokud nalezneme na indexu výsledek, uložíme ho na adresu paměti value
  *value = vector->items[position];
  return true;
}

/**
 * Maže prvek z indexu (position)
 * @param vector
 * @param position
 * @return Vrací true, pokud je prvek smazán, jinak false.
 */
bool Vector_Remove(Vector_t *const vector, size_t position)
{
  if (vector == NULL) return false;
  size_t length = vector->next - vector->items;
  if (position >= length) return false;
  // Pokud budeme mazat prvek z indexu position, tak je potřeba
  // posunout na volné místo prvky o indexu i+1
  for (size_t i = position; i < length; i++) {
    vector->items[i] = vector->items[i+1];
  }
  // První volná buňka za posledním prvkem bude o jedno dřív
  vector->next--;
  return true;
}
/**
 * Vloží nový prvek na konec vektoru.
 * @param vector
 * @param value
 */
void Vector_Append(Vector_t *vector, Vector_DataType_t value)
{
  if (vector == NULL) return;
  // Pokud vektor ještě nemá alokované pole prvků
  // (např. byl vytvořen s initial_size == 0)
  if (vector->items == NULL || vector->size == 0) {
    // Pokud je krok realokace nulový, nelze vektor rozšiřovat
    if (vector->alloc_step == 0) return;
    // Alokace (nebo realokace) paměti pro první blok prvků
    // realloc(NULL, size) funguje stejně jako malloc(size)
    vector->items = myRealloc(vector->items, vector->alloc_step * sizeof(Vector_DataType_t));
    // Pokud alokace selhala, ukončíme funkci bez vložení hodnoty
    if (vector->items == NULL) return;
    // Nastavení nové kapacity vektoru
    vector->size = vector->alloc_step;
    // Nastavení ukazatele na první volné místo (zatím žádné prvky)
    vector->next = vector->items;
  }
  // Kontrola, zda je vektor plný (next ukazuje za poslední alokovaný prvek)
  if (vector->next >= vector->items + vector->size) {
    // Uložíme si aktuální počet prvků ve vektoru
    size_t current_length = (size_t)(vector->next - vector->items);
    // Realokace paměti – zvětšení kapacity o alloc_step
    Vector_DataType_t *newPtr =
        myRealloc(vector->items,
                sizeof(Vector_DataType_t) * (vector->size + vector->alloc_step));
    // Pokud realokace selhala, vektor zůstává beze změny
    if (newPtr == NULL) return;
    // Aktualizace ukazatele na pole prvků (mohla se změnit adresa)
    vector->items = newPtr;
    // Přepočítání ukazatele next na základě nové adresy items
    vector->next = vector->items + current_length;
    // Aktualizace celkové kapacity vektoru
    vector->size += vector->alloc_step;
  }
  // Uložení nové hodnoty na pozici next (konec vektoru)
  *vector->next = value;
  // Posunutí ukazatele next na další volné místo
  vector->next++;
}

/**
 * Zjišťuje, zdali vektor obsahuje prvek
 * @param vector
 * @param value
 * @return Vrací true, pokud je prvek nalezen, jinak false.
 */
bool Vector_Contains(const Vector_t *const vector, Vector_DataType_t value)
{
  if (vector == NULL) return false;
  size_t length = vector->next - vector->items;

  for (size_t i = 0; i < length; i++) {
    if (vector->items[i] == value) return true;
  }
  return false;
}

/**
 * Hledá prvek ve vektoru od zadaného indexu.
 * @param vector
 * @param value
 * @param from
 * @return Vrací index nalezeného prvku, jinak vrátí SIZE_MAX
 */
size_t Vector_IndexOf(const Vector_t *const vector, Vector_DataType_t value, size_t from)
{
  if (vector == NULL) return SIZE_MAX;
  size_t length = vector->next - vector->items;

  if (from >= length) return SIZE_MAX;

  for (size_t i = 0; i < length; i++) {
    if (value == vector->items[i]) return i;
  }
  return SIZE_MAX;
}

/**
 * Vkládá prvek do určitého rozmezí.
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
  if (length == 0) return;

  if (start_position >= length) return;
  // Hledá se poslední platný index.
  size_t last_index = length - 1;

  if (end_position > last_index) {
    end_position = last_index;
  }

  for (size_t i = start_position; i <= end_position; i++) {
    vector->items[i] = value;
  }
}

/**
 * Maže vektor a uvolňuje paměť. Zničí celý vektor jako takový.
 * @param vector
 */
void Vector_Destroy(Vector_t **const vector)
{
  if (vector == NULL || *vector == NULL) return;
  myFree((*vector)->items);
  myFree(*vector);
  // Nastavení ukazatele na NULL
  *vector = NULL;
}

/* Private function definitions ------------------------------------------------------------------*/