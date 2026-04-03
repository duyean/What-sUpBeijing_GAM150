/*!
@file AEVEC2OVERLOAD.hpp
@author Tan Yifeng, Edmund (t.yifengedmund)
@course CSD11451
@section B
@Final Project GAM 150
@date 01/04/26
@brief
This file contains operator overloads for AEVec2
*//*______________________________________________________________________*/

#pragma once
#ifndef _Overload_
#include <iostream>
#include <cstdint>
#include <vector>
#include <crtdbg.h> // To check for memory leaks
#include <mutex>
#include <map>
#include <memory>
#include "AEEngine.h"

/*!***********************************************************************
* \brief
* Adds two AEVec2's together
* \param[in] lhs
* An AEVec2 to add
* \param[in] rhs
* An AEVec2 to add
* \return
* The AEVec2 after adding
*************************************************************************/
AEVec2 operator+(const AEVec2& lhs, const AEVec2& rhs);

/*!***********************************************************************
* \brief
* Subtracts an AEVec2 from another
* \param[in] lhs
* An AEVec2 to subtract from
* \param[in] rhs
* The AEVec2 to subtract
* \return
* The AEVec2 after subtraction
*************************************************************************/
AEVec2 operator-(const AEVec2& lhs, const AEVec2& rhs);

/*!***********************************************************************
* \brief
* Multiplies two AEVec2's together
* \param[in] lhs
* An AEVec2 to multiply
* \param[in] rhs
* An AEVec2 to multiply
* \return
* The AEVec2 after multiplying
*************************************************************************/
AEVec2 operator*(const AEVec2& lhs, const AEVec2& rhs);

/*!***********************************************************************
* \brief
* Multiplies an AEVec2 with a double
* \param[in] lhs
* An AEVec2 to multiply
* \param[in] rhs
* A double to multiply
* \return
* The AEVec2 after multiplying
*************************************************************************/
AEVec2 operator*(const AEVec2& lhs, const f64& rhs);

/*!***********************************************************************
* \brief
* Divides an AEVec2 by another
* \param[in] lhs
* The AEVec2 to divide from
* \param[in] rhs
* The AEVec2 to divide
* \return
* The AEVec2 after division
*************************************************************************/
AEVec2 operator/(const AEVec2& lhs, const AEVec2& rhs);

/*!***********************************************************************
* \brief
* Divides an AEVec2 by a double
* \param[in] lhs
* The AEVec2 to divide from
* \param[in] rhs
* The double to divide
* \return
* The AEVec2 after division
*************************************************************************/
AEVec2 operator/(const AEVec2& lhs, const f64& rhs);

/*!***********************************************************************
* \brief
* Absolutes an AEVec2
* \param[in] lhs
* The AEVec2 to compute
* \return
* The AEVec2 after absoluting
*************************************************************************/
AEVec2 abs(const AEVec2& lhs);


#endif