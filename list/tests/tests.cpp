/*!
 * \file       tests.cpp
 * \author     Sevcik, Jurena
 * \date       15. 2. 2022
 * \brief      Unit tests for dijkstra module.
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/

#include "gmock/gmock.h"

#include "gtest/gtest.h"
#include <limits>
#include <vector>

extern "C" {
#include "list.h"
}

static const Data_t mPeoplePool[] = {
  {"John", 23, 70, 150},
  {"Catherine", 35, 78, 176},
  {"Tanner", 47, 83, 178},
};

/* Private types ---------------------------------------------------------------------------------*/
bool operator==(const Data_t &lhs, const Data_t &rhs)
{
  return Data_Cmp(&lhs, &rhs) == 0;
}

bool operator!=(const Data_t &lhs, const Data_t &rhs)
{
  return !(lhs == rhs);
}

class ListTest : public ::testing::Test
{
protected:
  void SetUp() { List_Init(&list); }

  List_t list;
};

/* Private function definitions ------------------------------------------------------------------*/
TEST(List, initialize)
{
  List_t list;
  list.active = (List_Node_Ptr_t)&list.active;
  list.first = (List_Node_Ptr_t)&list.first;

  List_Init(&list);

  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.active, nullptr);
}

TEST(List, initializeWithNull)
{
  List_Init(NULL);
}

TEST_F(ListTest, insertFirst)
{
  List_Insert_First(&list, mPeoplePool[0]);

  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first->next, nullptr);
  ASSERT_EQ(list.first->data, mPeoplePool[0]);

  List_Node_Ptr_t tFirst = list.first;
  List_Insert_First(&list, mPeoplePool[1]);

  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first->next, tFirst);
  ASSERT_EQ(list.first->data, mPeoplePool[1]);
}

TEST(List, insertFirstNull)
{
  List_Insert_First(NULL, mPeoplePool[0]);
}

TEST_F(ListTest, first)
{
  List_Insert_First(&list, mPeoplePool[0]);

  List_First(&list);
  ASSERT_EQ(list.active, list.first);
}

TEST(List, firstNull)
{
  List_First(NULL);
}

TEST_F(ListTest, deleteFirstEmptyList)
{
  List_Delete_First(&list);

  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.active, nullptr);
}

TEST_F(ListTest, deleteFirstWithOneNode)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_First(&list);

  List_Delete_First(&list);
  ASSERT_EQ(list.first, nullptr);
  ASSERT_EQ(list.active, nullptr);
}

TEST_F(ListTest, deleteFirstWithTwoNodes)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_Insert_First(&list, mPeoplePool[1]);

  List_Delete_First(&list);

  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first->data, mPeoplePool[0]);
}

TEST(List, deleteFirstNull)
{
  List_Delete_First(NULL);
}

TEST_F(ListTest, copyFirst)
{
  Data_t dataCopy;

  List_Insert_First(&list, mPeoplePool[0]);

  ASSERT_TRUE(List_Copy_First(list, &dataCopy));
  ASSERT_EQ(mPeoplePool[0], dataCopy);
}

TEST_F(ListTest, copyFirstNullData)
{
  List_Copy_First(list, NULL);
}

TEST_F(ListTest, postDelete)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_Insert_First(&list, mPeoplePool[1]);

  List_First(&list);

  List_Post_Delete(&list);
  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first, list.active);
  ASSERT_EQ(list.first->next, nullptr);

  List_Delete_First(&list);
}

TEST(List, postDeleteNull)
{
  List_Post_Delete(NULL);
}

TEST_F(ListTest, postInsert)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_Post_Insert(&list, mPeoplePool[1]);
  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first->next, nullptr);
  ASSERT_STREQ("John", list.first->data.name);

  List_First(&list);

  List_Post_Insert(&list, mPeoplePool[0]);
  ASSERT_NE(list.first->next, nullptr);
  ASSERT_EQ(mPeoplePool[0], list.first->next->data);
}

TEST(List, postInsertNull)
{
  List_Post_Insert(NULL, mPeoplePool[0]);
}

TEST_F(ListTest, listCopy)
{
  Data_t dataCopy;

  List_Insert_First(&list, mPeoplePool[0]);
  List_First(&list);

  ASSERT_TRUE(List_Copy(list, &dataCopy));
  ASSERT_EQ(mPeoplePool[0], dataCopy);
}

TEST_F(ListTest, listCopyNoActive)
{
  Data_t dataCopy = {"test", 0, 1, 2};

  List_Insert_First(&list, mPeoplePool[0]);

  ASSERT_FALSE(List_Copy(list, &dataCopy));
  ASSERT_EQ(list.active, nullptr);
  ASSERT_NE(list.first, nullptr);
  ASSERT_NE(list.first->data, dataCopy);
}

TEST_F(ListTest, listActiveUpdate)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_First(&list);
  List_Active_Update(&list, mPeoplePool[1]);

  ASSERT_NE(list.first, nullptr);
  ASSERT_NE(list.active, nullptr);
  ASSERT_EQ(list.active->data, mPeoplePool[1]);
}

TEST_F(ListTest, listActiveUpdateNoActive)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_Active_Update(&list, mPeoplePool[1]);

  ASSERT_NE(list.first, nullptr);
  ASSERT_NE(list.first->data, mPeoplePool[1]);
}

TEST(List, listActiveUpdateNull)
{
  List_Active_Update(NULL, mPeoplePool[0]);
}

TEST_F(ListTest, listActiveNext)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_Insert_First(&list, mPeoplePool[1]);
  List_Insert_First(&list, mPeoplePool[2]);

  List_First(&list);

  List_Active_Next(&list);
  ASSERT_NE(list.first, nullptr);
  ASSERT_EQ(list.first->next, list.active);

  List_Active_Next(&list);
  ASSERT_EQ(list.first->next->next, list.active);

  List_Active_Next(&list);
  ASSERT_EQ(list.active, nullptr);

  List_Active_Next(&list);
  ASSERT_EQ(list.active, nullptr);
}

TEST(List, listActiveNextNull)
{
  List_Active_Next(NULL);
}

TEST_F(ListTest, isActiveReturnsFalseWhenItemIsNotActive)
{
  List_Insert_First(&list, mPeoplePool[0]);

  ASSERT_FALSE(List_Is_Active(list));
}

TEST_F(ListTest, isActiveReturnsTrueWhenItemIsActive)
{
  List_Insert_First(&list, mPeoplePool[0]);
  List_First(&list);

  ASSERT_TRUE(List_Is_Active(list));
}