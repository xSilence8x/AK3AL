# ADT List
Naprogramujte ADT List (lineární seznam).

Podrobnější popis jednotlivých funkcí máte v souboru list.h, potřebnou teorii máte ve slajdech přednášky o seznamu.

Ukázka propojení prvků v ADT listu mezi sebou: 

![ADT List](docs/adt_list.png)


## Implementujte následující funkce:

- **List_Init** - Inicializuje list

- **List_Insert_First** - Vloží prvek na první pozici listu

- **List_First** - Nastaví jako aktivní prvek první prvek, který je v listu

- **List_Copy_First** - Zkopíruje data první položky v listu

- **List_Delete_First** - Smaže první prvek v listu

- **List_Post_Delete** - Smaže prvek, který leží za aktivním prvkem. Pokud není aktivní prvek, nic se nestane.

- **List_Post_Insert** - Vloží prvek za právě aktivní prvek, neudělá nic pokud seznam nemá aktivní prvek.

- **List_Copy** - Zkopíruje data aktivního prvku

- **List_Active_Update** - Aktualizuje data aktivního prvku

- **List_Active_Next** - Posune aktivní prvek na prvek, který následuje za právě aktivním prvkem

- **List_Is_Active** - Zkontroluje, zda-li je aktivní prvek

# EN

# ADT List
Pragram ADT List (linear list).

You can find more detailed information about functions in header file list.h, the theory needed for this task you can find in presentation about linear list.

Example how are items connected in ADT list:

![ADT List](docs/adt_list.png)


## Implementujte následující funkce:

- **List_Init** - Initializes the list

- **List_Insert_First** - Inserts new item at first position of the list

- **List_First** - Sets the first item as an active item

- **List_Copy_First** - Copy the data of first item in a list

- **List_Delete_First** - Deletes first item in a list

- **List_Post_Delete** - Deletes item that is after the active item, if there's no active item, nothing happens

- **List_Post_Insert** - Inserts new item after the active item, if there's no active item, nothing happens

- **List_Copy** - Copy the data of active item

- **List_Active_Update** - Updates the data of an active item

- **List_Active_Next** - Shifts the active item to the next one

- **List_Is_Active** - Checks if there is an active item

### Ukázka běhu programu/Example of program:

```
#~/MathLib$ ./a.out 
myMalloc: allocating 16 bytes, memory allocated 16 bytes
myMalloc: allocating 16 bytes, memory allocated 32 bytes
0: Init,
1: Active_Update,
2: Insert_First,
3: First,
4: Copy_First,
5: Delete_First,
6: Post_Delete,
7: Post_Insert,
8: Copy,
9: Active_Next,
A: Is_Active,
M: MENU
E: END
Your choice=0
Active item:
NULL
Content of List:
There is no item in list.

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=2
Insert_First - insert new item in the first position.
Please enter name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 288 bytes, memory allocated 320 bytes
Active item:
NULL
Content of List:
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=2
Insert_First - insert new item in the first position.
Please enter name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 288 bytes, memory allocated 608 bytes
Active item:
NULL
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=2
Insert_First - insert new item in the first position.
Please enter name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 288 bytes, memory allocated 896 bytes
Active item:
NULL
Content of List:
Name=Daniel, age=60.0, weight=80.0, height=195.0
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=3
First - set as an active item the first one.
Active item:
Name=Daniel, age=60.0, weight=80.0, height=195.0
Content of List:
Name=Daniel, age=60.0, weight=80.0, height=195.0
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=5
Delete_First - Deletes first item.
myFree: releasing 288 bytes, memory allocated 608 bytes
Active item:
NULL
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=3
First - set as an active item the first one.
Active item:
Name=Roman, age=50.0, weight=90.0, height=190.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=7
Post_Insert - Insert new item after the active one.
Please enter name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 288 bytes, memory allocated 896 bytes
Active item:
Name=Roman, age=50.0, weight=90.0, height=190.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=3
First - set as an active item the first one.
Active item:
Name=Roman, age=50.0, weight=90.0, height=190.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=9
Active_Next - Shift the active item to the next one.
Active item:
Name=Luke, age=34.0, weight=76.0, height=184.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=7
Post_Insert - Insert new item after the active one.
Please enter name: Enter age, weight and height (separated by Enter):
myMalloc: allocating 288 bytes, memory allocated 1184 bytes
Active item:
Name=Luke, age=34.0, weight=76.0, height=184.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=3
First - set as an active item the first one.
Active item:
Name=Roman, age=50.0, weight=90.0, height=190.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=4
Copy_First - Display first item in list.
Name=Roman, age=50.0, weight=90.0, height=190.0
Active item:
Name=Roman, age=50.0, weight=90.0, height=190.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=9
Active_Next - Shift the active item to the next one.
Active item:
Name=Luke, age=34.0, weight=76.0, height=184.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=9
Active_Next - Shift the active item to the next one.
Active item:
Name=Peter, age=34.0, weight=76.0, height=167.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
Your choice=9
Active_Next - Shift the active item to the next one.
Active item:
Name=Anna, age=23.0, weight=56.0, height=187.0
Content of List:
Name=Roman, age=50.0, weight=90.0, height=190.0
Name=Luke, age=34.0, weight=76.0, height=184.0
Name=Peter, age=34.0, weight=76.0, height=167.0
Name=Anna, age=23.0, weight=56.0, height=187.0

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************

Type char 0-A, EOF(CTRL+Z or CTRL+D)=END, M=MENU:
************************************************************
myFree: releasing 288 bytes, memory allocated 896 bytes
myFree: releasing 288 bytes, memory allocated 608 bytes
myFree: releasing 288 bytes, memory allocated 320 bytes
myFree: releasing 288 bytes, memory allocated 32 bytes
myFree: releasing 16 bytes, memory allocated 16 bytes
myFree: releasing 16 bytes, memory allocated 0 bytes
```
