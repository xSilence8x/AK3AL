/*!
 * \file       dtmf.c
 * \author     Ondřej Ševčík
 * \date       9/2019
 * \brief      Implementation of DTMF generator module
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "dtmf.h"
#include "wavfile.h"
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define VOLUME 1000

#define UNUSED(x) (void)x
/* Private variables -----------------------------------------------------------------------------*/
static double mSamplesLUT[WAVFILE_SAMPLES_PER_SECOND];

// Definujeme tabulku frekvencí dle zadání
static const int ROW_FREQUENCIES[4] = { 697, 770, 852, 941 };
static const int COL_FREQUENCIES[4] = { 1209, 1336, 1477, 1633 };
static const char DTMF_KEYS[4][4] = {
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'}
};

/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
/* Private function definitions ------------------------------------------------------------------*/

/* Function definition ----------------------------------------------------- */
bool DTMF_Generate(Vector_t *vector, char symbol)
{
  if (vector == NULL) return false;
  // Definujeme statickou proměnnou
  static bool initialized = false;
  // Normalizace znaku: 'a' → 'A', 'b' → 'B', atd.
  symbol = (char)toupper((unsigned char)symbol);
  // Inicializujeme LUT jen 1x
  if (!initialized) {
    // Pro každý vzorek v 1s spočítáme podle vzorce
    for (int i = 0; i < WAVFILE_SAMPLES_PER_SECOND; i++) {
      mSamplesLUT[i] = (double)i / WAVFILE_SAMPLES_PER_SECOND * 2 * M_PI;
    }
    // Označíme, že LUT je připravené a příště už se nebude znovu počítat
    initialized = true;
  }
  // Mezery = ticho; vložíme nulový vzorek (aplituda 0)
  if (symbol == ' ') {
    for (int i = 0; i < WAVFILE_SAMPLES_PER_SECOND; i++) {
      Vector_Append(vector, 0);
    }
    return true;
  }
  // Najdeme frekvence pro symbol
  int freq1 = 0;
  int freq2 = 0;
  // Příznak, jestli jsme symbol našli v tabulce
  bool found = false;
  // Procházíme tabulku a hledáme symbol
  // První procházíme řádky od 1. dál
  for (int i = 0; i < 4 && !found; i++) {
    // Pak procházíme sloupce
    for (int j = 0; j < 4; j++) {
      // Pokud najdeme znak, vezneme hodnotu f ze sloupce a řádku
      if (DTMF_KEYS[i][j] == symbol) {
        freq1 = ROW_FREQUENCIES[i];
        freq2 = COL_FREQUENCIES[j];
        // Označíme, že jsme našli --> true
        found = true;
        break;
      }
    }
  }

  // Pokud jsme symbol nenašli
  if (!found) return false;

  // Generování 1 sekundy DTMF signálu
  for (int k = 0; k < WAVFILE_SAMPLES_PER_SECOND; k++) {
    double s1 = sin(mSamplesLUT[k] * freq1);
    double s2 = sin(mSamplesLUT[k] * freq2);
    // Sečteme obě sinusovky a vynásobíme hlasitostí
    double sample_d = VOLUME * (s1 + s2);

    // Přetypování na datový typ vektoru
    Vector_Append(vector, (Vector_DataType_t)sample_d);
  }

  return true;
}
