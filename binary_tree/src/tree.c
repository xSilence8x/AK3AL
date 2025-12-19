/*!
 * \file       tree.c
 * \author     Ondřej Ševčík
 * \date       6/2019
 * \brief      Source file for binary tree
 * **********************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/
#include "tree.h"
#include "mymalloc.h"

/* Private types ---------------------------------------------------------------------------------*/
/* Private macros --------------------------------------------------------------------------------*/
#define UNUSED(x) (void)x

/* Private variables -----------------------------------------------------------------------------*/
/* Private function declarations -----------------------------------------------------------------*/
/* Exported functions definitions ----------------------------------------------------------------*/

bool Tree_Init(Tree *const tree)
{
  if (tree == NULL) return false;

  tree->nodeCount = 0;
  tree->root = NULL;

  return true;
}
void Tree_Clear(Tree *const tree)
{
  if (tree == NULL) return;

  if (tree->root == NULL) {
    tree->nodeCount = 0;
    return;
  }

  // alokujeme zásobník podle počtu uzlů
  TreeNode **stack = (TreeNode **)myMalloc(tree->nodeCount * sizeof(*stack));
  if (stack == NULL) return;

  unsigned int top = 0;
  stack[top++] = tree->root;

  while (top > 0) {
    TreeNode *node = stack[--top];

    if (node->left != NULL)  stack[top++] = node->left;
    if (node->right != NULL) stack[top++] = node->right;

    myFree(node);
  }

  myFree(stack);

  tree->root = NULL;
  tree->nodeCount = 0;
}

bool Tree_Insert(Tree *const tree, const Data_t data)
{
  if (tree == NULL) return false;

  TreeNode *node = (TreeNode *) myMalloc(sizeof(TreeNode));
  if (node == NULL) return false;
  node->data = data;

  // Pokud je kořen prázdný, tak do něj vložíme nový uzel
  if (tree->root == NULL) {

    // Nový uzel, který je kořenový, nemá potomky left ani right
    node->left = NULL;
    node->right = NULL;
    tree->root = node;
    tree->nodeCount++;
    return true;
  }
  // Pokud strom není prázdný
  TreeNode *current = tree->root;
  TreeNode *parent = NULL; // rodič uzlu
  int cmp = 0;

  // Procházíme strom, dokud nenarazíme na NULL=konec
  while (current != NULL) {
    parent = current;
    cmp = Data_Cmp(&data, &current->data);

    // Pokud už data ve stromě jsou, tak vyskočíme z funkce, ptž strom nesmí obsahovat duplicity
    if (cmp == 0) {
      myFree(node);
      return false;
    }

    // Menší jde doleva, větší doprava
    if (cmp < 0)
      current = current->left;
    else
      current = current->right;
  }
  // Když vyskočíme z while smyčky, tak parent ukazuje na uzel, pod kterého dáme nového potomka
  // Current je NULL
  node->left = NULL;
  node->right = NULL;

  // Podle výsledku srovnání uložíme nový uzel podle velikosti
  if (cmp < 0)
    parent->left = node;
  else
    parent->right = node;
  tree->nodeCount++;
  return true;
}

void Tree_Delete(Tree *const tree, const Data_t data)
{
  if (tree == NULL) return;
  if (tree->root == NULL) return;

  // link je ukazatel na proměnnou, která drží ukazatel na aktuální uzel
  // na začátku ukazuje na tree->root
  TreeNode **link = &tree->root;
  TreeNode *node = tree->root; //  Začneme od kořene

  // Procházíme strom, dokud nenarazíme na NULL
  while (node != NULL) {
    int cmp = Data_Cmp(&data, &node->data); // co je větší

    // Pokud jsou stejně velké, našli jsme shodu
    if (cmp == 0) break;

    // Pokud jsou hledaná data menší, pokračujeme vlevo
    if (cmp < 0) {
      link = &node->left; // link ukazuje na proměnnou node->left
      node = node->left;
    } else {
      link = &node->right;
      node = node->right;
    }
  }

  // Pokud jsme nic nenašli, není co mazat
  if (node == NULL) return;

  // Uzel nemá levého potomka
  if (node->left == NULL) {
    // Rodič (nebo root) nyní ukazuje na pravý podstrom mazáného uzlu
    *link = node->right;
    myFree(node);
    tree->nodeCount--;
    return;
  }

  // Uzel nemá pravého potomka
  if (node->right == NULL) {
    // Rodič (nebo root) nyní ukazuje na levý podstrom mazaného uzlu
    *link = node->left;
    myFree(node);
    tree->nodeCount--;
    return;
  }

  // Uzel má pravého i levého potomka
  // succLink je ukazatel na proměnnou, která drží ukazatel na successor
  // začínáme na pravém dítěti mazáného uzlu
  //
  // POZOR: Podle zadání/testů se v tomto případě bere "předchůdce"
  // = největší uzel v LEVÉM podstromu (nejvíc vpravo z node->left).
  TreeNode **succLink = &node->left;

  // succ je inorder predecessor = největší uzel v levém podstromu
  TreeNode *succ = node->left;

  // Jdeme co nejvíce doprava, dokud to jde
  // (hledáme největší uzel v levém podstromu)
  while (succ->right != NULL) {
    succLink = &succ->right;
    succ = succ->right;
  }

  // Zkopírujeme data z předchůdce do mazaného uzlu
  node->data = succ->data;

  // Odpojíme předchůdce ze stromu
  // (předchůdce může mít maximálně levé dítě)
  *succLink = succ->left;

  // Uvolníme uzel předchůdce
  myFree(succ);
  tree->nodeCount--;
}

const Data_t *Tree_Get_Data(const TreeNode *const node)
{
  if (node == NULL) return NULL;

  // Vrátí ukazatel na data uzlu
  return &node->data;
}

TreeNode *Tree_Find_Node(Tree tree, const Data_t data)
{
  // Začneme hledat od kořene
  TreeNode *node = tree.root;

  // Smyčka dokud nenarazíme na konec stromu
  while (node != NULL) {
    int cmp = Data_Cmp(&data, &node->data);

    // Pokud jsou data stejná, našli jme uzel; dle zadání Data_Cmp, kde vrací 0
    if (cmp == 0) return node;

    // Pokud jsou hledaná data menší než data v uzlu, pokračujeme vlevo
    if (cmp < 0)
      node = node->left;
    else
      // Jinak pokračujeme vpravo
      node = node->right;
  }
  return NULL;
}

size_t Tree_Get_Count(Tree tree)
{
  return tree.nodeCount;
}

void Tree_Process(Tree tree, TreeNodeProc proc, TreeProcessMode mode)
{
  if (tree.root == NULL) return;
  if (proc == NULL) return;

  if (mode == PRE_ORDER) {
    proc(tree.root);
  }
  // Vytvoříme dočasný strom
  Tree leftTree;
  leftTree.root = tree.root->left;
  leftTree.nodeCount = 0;

  // Rekurzivně zpracujeme levý podstrom
  Tree_Process(leftTree, proc, mode);

  if (mode == IN_ORDER) {
    proc(tree.root);
  }
  Tree rightTree;
  rightTree.root = tree.root->right;
  rightTree.nodeCount = 0;

  // Rekurzivně zpracujeme pravý podstrom
  Tree_Process(rightTree, proc, mode);

  if (mode == POST_ORDER) {
    proc(tree.root);
  }
}

/* Private function definitions ------------------------------------------------------------------*/
