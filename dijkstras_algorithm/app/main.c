/**
 * @file       main.c
 * @author     Ondřej Ševčík
 * @date       6/2019
 * @brief      Main file for Dijkstra algorithm
 * **************************************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

/* Private includes -------------------------------------------------------- */
#include "dijkstra.h"
#include "heap.h"
#include "ioutils.h"
#include "map.h"

#define MAXIMUM_CITIES_LOADED 1024

/* Private function -------------------------------------------------------- */
void Print_Menu()
{
  printf("0 - Load map frop csv file\n"
         "1 - Choose starting city\n"
         "2 - Choose destination\n"
         "3 - Find shortest path\n"
         "M - MENU\n"
         "E - Exit\n");
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Missing argument(map to load)!\n");
    return 0;
  }

  printf("Dijkstra v1.1\n-------------\n\n");

  char userCharInput;
  bool running = true;
  bool initialized = false;
  tDijkstra dijkstra;
  unsigned startingCity = 0;
  unsigned destination = 0;
  unsigned numberOfCities = 0;

  Data_t mapArray[MAXIMUM_CITIES_LOADED];

  Print_Menu();
  while (running) {
    printf("\nYour choice:\n");
    running = io_utils_get_char(&userCharInput);

    switch (userCharInput) {
      case '0':
        printf("Load map frop csv file\n");
        if (!initialized) {
          FILE *mapFile = fopen(argv[1], "r");

          if (mapFile != NULL && (numberOfCities = Map_Read_Map(mapArray, mapFile)) != 0) {
            fclose(mapFile);
            initialized = true;
            printf("Map initialized!\n"
                   "Number of cities loaded: %d\n",
                   numberOfCities);
            Map_Print_Cities(mapArray, numberOfCities);

          } else {
            printf("File %s not found!\n", argv[1]);
          }
        } else {
          printf("Map have been already initialized!\n");
        }
        break;
      case '1':
        printf("Choose starting city\n\n");
        if (initialized) {
          Map_Print_Cities(mapArray, numberOfCities);
          printf("Enter index of city or -1 for default\n");
          int tempVal = 0;
          if (!io_utils_get("%d", &tempVal) || tempVal < 0 || (unsigned)tempVal >= numberOfCities) {
            printf("City with that index not found. Setting starting city to "
                   "default value.\n");
            startingCity = 0;
          } else {
            startingCity = (unsigned)tempVal;
            printf("New starting city is now %s with index of %d\n",
                   mapArray[startingCity].name,
                   startingCity);
          }
        } else {
          printf("Map is not initialized!\n");
        }

        break;
      case '2':
        printf("Choose destination\n\n");
        if (initialized) {
          Map_Print_Cities(mapArray, numberOfCities);
          printf("Enter index of city or -1 for default\n");
          int tempVal = 0;
          if (!io_utils_get("%d", &tempVal) || tempVal < 0 || (unsigned)tempVal >= numberOfCities) {
            printf("City with that index not found. Setting destination to "
                   "default "
                   "value.\n");
            destination = 0;
          } else {
            destination = (unsigned)tempVal;
          }
          printf("New destination is now %s with index of %d\n",
                 mapArray[destination].name,
                 destination);
        } else {
          printf("Map is not initialized!\n");
        }

        break;
      case '3':
        printf("Find shortest path\n\n");
        if (initialized) {
          if (Dijkstra_Init(&dijkstra, numberOfCities, startingCity)) {
            if (Dijkstra_Dist(mapArray, &dijkstra, startingCity, destination)) {
              printf("\nThe shortest path from %s to %s is %d km long\n",
                     mapArray[startingCity].name,
                     mapArray[destination].name,
                     dijkstra.distances[destination]);

              for (unsigned i = 0; i < numberOfCities; i++) {
                printf("To %s [%d] km\n", mapArray[i].name, dijkstra.distances[i]);
              }
              printf("\n");
            } else {
              printf("%s is unreachable\n", mapArray[destination].name);
            }
            Dijkstra_Destruct(&dijkstra);
          }
        } else {
          printf("Map is not initialized!\n");
        }
        break;

      case 'm':
      case 'M':
        Print_Menu();
        break;
      case 'e':
      case 'E':
        printf("Exit\n\nExiting\n");
        running = false;
        break;
    }
  }

  return 0;
}
