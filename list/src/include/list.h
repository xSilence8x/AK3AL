/*!
 * \file       list.h
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Header file of linear list
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#ifndef LIST_H
#define LIST_H

/* Public includes --------------------------------------------------------- */
#include "data.h"
#include "mymalloc.h"

#include <stdbool.h>

/*! \defgroup list List
 *  \brief The API of the simple linked list for storing the \ref Data_t objects.
 *  \{
 */

/*! Definition of one node in the list. */
typedef struct List_Node_s {
  /*! Nodes data that is stored in it. */
  Data_t data;

  /*! Pointer at next item. */
  struct List_Node_s *next;
} List_Node_t;

/*! Alias for pointer to list node. */
typedef List_Node_t *List_Node_Ptr_t;

/*! Definition of list as a pointer at first and active item. */
typedef struct {
  /*! Pointer at first item in list. */
  List_Node_t *first;

  /*! Pointer at active item in list. */
  List_Node_t *active;
} List_t;

/* Public List_t API ------------------------------------------------------- */
/*! Initializes the list. Inicialization consists of setting NULL to the \ref List_t.first and \ref
 * List_t.active.
 *
 * \param[in]   list    List, which we want to initialize.
 */
void List_Init(List_t *const list);

/*! Creates a new item and puts it at the start of the \a list. Active item is unchanged.
 *
 * \param[in] list  List, where to store the new item.
 * \param[in] data  Data to store in new item.
 */
void List_Insert_First(List_t *const list, Data_t data);

/*! Set active item pointer at the first item in the \a list.
 *
 * \param[in] list  List, with which the operation should be done.
 */
void List_First(List_t *const list);

/*! Gets data of the fist node in the \a list.
 *
 * \param[in]   list[in]  List, with which the operation should be done.
 * \param[out]  data[out] Pointer, where are data being stored.
 *
 * \return Returns true, if the value is read, return false otherwise.
 */
bool List_Copy_First(List_t list, Data_t *data);

/*! Deletes the first item in the \a list. If the FIRST was also the ACTIVE item, the active item is
 * set to NULL. If the \a list is empty, nothing happens.
 *
 * \param[in] list  List, with which the operation should be done.
 */
void List_Delete_First(List_t *const list);

/*! Deletes the item that is after the active item in the \a list. If theres no active item or list
 * is empty, nothing happens.
 *
 * \param[in] list  List, with which the operation should be done.
 */
void List_Post_Delete(List_t *const list);

/*! Inserts new item after the active item in a list. If theres no active item, nothing happens.
 *
 * \param[in] list  List, with which the operation should be done.
 * \param[in] data  Data to store in a list.
 */
void List_Post_Insert(List_t *const list, Data_t data);

/*! Gets data of currently active node.
 *
 * \param[in]   list  List, with which the operation should be done.
 * \param[out]  data  Pointer, where are the data being stored.
 *
 * \return Returns true if the item was copied, otherwise return false.
 */
bool List_Copy(List_t list, Data_t *data);

/*! Updates the data of an active item, if theres no active item, nothing happens.
 *
 * \param[in] list  List, with which the operation should be done.
 * \param[in] data  Data, which are being stored.
 */
void List_Active_Update(const List_t *const list, Data_t data);

/*! Shifts the active item to the next one, if theres no active item, nothing happens.
 *
 * \param[in] list  List, with which the operation should be done.
 */
void List_Active_Next(List_t *const list);

/*! Checks if any node in list is active.
 *
 * \param[in] list  List, with which the operation should be done.
 *
 * \return True if node in list is active, false otherwise.
 */
bool List_Is_Active(List_t list);

#endif /* LIST_H */

/*! \} */