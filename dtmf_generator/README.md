# DTMF generátor tónů

Vaším úkolem je vytvořit program, který uživateli vygeneruje WAV soubor s libovolným množstvím DTMF tónů, které uživatel zadá z klávesnice. 
Každý symbol se generuje jako krátké písknutí, ve kterém se mísí dva tóny (vlny sinus) , nižší a vyšší (Frekvence ke každému symbolu viz tabulka níže).

|   | 1209 Hz | 1336 Hz | 1477 Hz | 1633 Hz |
|---|---------|---------|---------|---------|
| 697 Hz | 1 | 2 | 3 | A |
| 770 Hz | 4 | 5 | 6 | B |
| 852 Hz | 7 | 8 | 9 | C |
| 941 Hz | * | 0 | # | D |

Číslice **2** by tedy byla kombinací dvou tónů 697 Hz a 1336 Hz.

Jednotlivé tóny se počítají podle vzorce **sin(2 * π * i/8000 * f)**, kde i jsou čísla od 0 do 8000 \[Hz\] (8000 Hz používáme, jelikož je to vzorkovací frekvence pro telefony), tyto hodnoty
pak dále násobíme proměnnou **VOLUME**, aby výsledný soubor byl lépe slyšitelný. **f** je zde frekvence dle zadaného symbolu.

Tento výsledný tón uložte do dynamického pole z úkolu Vektor

Ukázkový výsledný soubor můžete najít ve složce **test_files** pod názvem [**sound.wav**](test_files/sound.wav).

# DTMF tone generator

Your rask is to create a program that generates WAV file with any amount of DTMF tones from stdin. Symbols are generated as a short 'beep', in which there are mixed two tones (sine waves) with
short and high frequency (Frequencies to each symbols are listed in table below).

|   | 1209 Hz | 1336 Hz | 1477 Hz | 1633 Hz |
|---|---------|---------|---------|---------|
| 697 Hz | 1 | 2 | 3 | A |
| 770 Hz | 4 | 5 | 6 | B |
| 852 Hz | 7 | 8 | 9 | C |
| 941 Hz | * | 0 | # | D |

The symbol **2** would be the mixture of tones with frequency of 697 Hz and 1336 Hz.

Each tone is generated like this **sin(2 * π * i/8000 * f)**, where i is a number 0 to 8000 \[Hz\] (8000 because sampling rate of telephone is 8000 Hz),
those values are multipled by variable **VOLUME**, so the output file has higher volume. **f** is frequency of symbol.

Final values are stored in dynamic array from task Vector

Example of output file is located in [**test_files/sound.wav**](test_files/sound.wav).

## Ukázkový běh programu / Example of program

```bash
0 - Vector Create
1 - Input chars
2 - Write to file
M - Menu
E - Exit
0
Vector created successfully!
1
Please enter a symbol (1-9) or A,B,C,D,*,#, space means there is a pause between sounds, anything else to exit.
1
2
3
e
Symbols added to the vector!
2
WAV file created successfully!
e
Ending the program!
```
