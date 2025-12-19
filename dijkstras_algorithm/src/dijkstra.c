/*!
 * \file       dijkstra.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Implementation of function for Dijkstra algorithm
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "dijkstra.h"
#include "heap.h"
#include "mymalloc.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/
bool Dijkstra_Init(tDijkstra *dijkstra, unsigned cityCount, unsigned sourceCityID)
{
  // Zkontrolujeme vstupní podmínky
  if (dijkstra == NULL || cityCount == 0 || sourceCityID >= cityCount) return false;

  // Alokace pole, které říká, jestli bylo město navštíveno
  dijkstra->visited = (bool *)myMalloc(cityCount * sizeof(bool));

  // Alokace pole nejkratších vzdáleností od zdroje
  dijkstra->distances = (unsigned *)myMalloc(cityCount * sizeof(unsigned));

  // Pokud se alokace paměti nezdařila
  if (dijkstra->visited == NULL || dijkstra->distances == NULL) {
    myFree(dijkstra->visited);
    myFree(dijkstra->distances);
    dijkstra->visited = NULL;
    dijkstra->distances = NULL;
    return false;
  }
  // Inicializace polí
  for (unsigned i = 0; i < cityCount; i++) {
    dijkstra->visited[i] = false; // Zatím jsme nikdy nebyli
    dijkstra->distances[i] = INF; // Zatím nekonečno, protože neznáme vzdálenost, dle zadání
  }
  dijkstra->distances[sourceCityID] = 0; // Vzdálenost k sobě samému

  return true;
}

void Dijkstra_Destruct(tDijkstra *dijkstra)
{
  if (dijkstra == NULL) return;

  // Uvolnění alokovaných polí
  myFree(dijkstra->visited);
  myFree(dijkstra->distances);

  // Nastavení pointerů na NULL
  dijkstra->visited = NULL;
  dijkstra->distances = NULL;

}

bool Dijkstra_Dist(Data_t *mapHeap,
                   tDijkstra *dijkstra,
                   unsigned sourceCityID,
                   unsigned destination)
{
  if (dijkstra == NULL || mapHeap == NULL) return false;
  if (dijkstra->visited == NULL || dijkstra->distances == NULL) return false;

  // Pokud je cílová destinace == zdrojové
  if (destination == sourceCityID) return false;

  // Vytvořená priority fronty
  tHeap pq;
  if (!Heap_Init(&pq)) return false;

  // Do haldy vložíme startovní město
  Data_t start = mapHeap[sourceCityID];
  start.distanceToCity = 0;

  // Vložení startu do priority fronty
  (void)Heap_Insert(&pq, start);

  // Hlavní smyčka algoritmu - dokud existuje město s menší vzdáleností
  while (!Heap_Empty(pq)) {
    Data_t current;

    // Vybereme město s nejmenší distanceToCity
    (void)Heap_DeleteMin(&pq, &current);

    //ID města, které právě zpracováváme
    unsigned u = current.id;

    // Pokud už jsme město jednou zpracovali, tak ho ignorujeme
    if (dijkstra->visited[u]) continue;

    // Označíme město jako navštívené
    dijkstra->visited[u] = true;

    // // Pokud jsme dorazili do cíle, tak můžeme skončit
    // if (u == destination) break;

    // Každé město má max 8 silnic
    for (unsigned k = 0; k < 8; k++) {
      // Délka silnice
      unsigned len = mapHeap[u].roadLength[k];

      // Pokud je len = 0, tak silnice neexistuje
      if (len == 0) continue;

      // ID sousedního města
      unsigned v = mapHeap[u].roadCityIndex[k];
      if (dijkstra->visited[v]) continue;

      if (dijkstra->distances[u] == INF) continue;

      unsigned alt = dijkstra->distances[u] + len;

      if (alt < dijkstra->distances[v]) {
        dijkstra->distances[v] = alt;

        //Připravíme kopii souseda pro heap
        Data_t next = mapHeap[v];
        next.distanceToCity = alt;
        (void)Heap_Insert(&pq,next);
      }
    }
  }
  Heap_Destruct(&pq);

  // Pokud vzdálenost není nekonečno, tak cesta existuje
  return (dijkstra->distances[destination] != INF);
}


/* Private function definitions ------------------------------------------------------------------*/
