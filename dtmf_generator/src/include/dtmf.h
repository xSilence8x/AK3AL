/*!
 * \file       dtmf.h
 * \author     Ondřej Ševčík
 * \date       9/2019
 * \brief      Declaration of the DTMF generator module
 * **************************************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#ifndef DTMF_H
#define DTMF_H
/*! \defgroup dtmf DTMF
 *  \brief Defines API of the DTMF module that generates the tones from the given symbol. This
 * module uses as storage the dynamic array (vector).
 *  \{
 */
/* Includes --------------------------------------------------------------------------------------*/
#include "vector.h"

/* Exported types --------------------------------------------------------------------------------*/
/* Exported macros -------------------------------------------------------------------------------*/
/* Exported variables ----------------------------------------------------------------------------*/
/* Exported functions declarations ---------------------------------------------------------------*/
/*! Generates sin waves lowtone frequency and hightone frequency sin waves and then adds their sum
 * value to the vector.
 *
 * \param[out]  vector  Vector where is sum of two sin waves stored.
 * \param[in]   symbol  The digit that determines lowtone and hightone frequency.
 *
 * \return Returns true if tone was generated, return false otherwise.
 */
bool DTMF_Generate(Vector_t *vector, char symbol);

/*! \} */

#endif  // DTMF_H
