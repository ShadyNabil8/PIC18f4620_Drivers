/*
 * File:   mcal_std_types.h
 * Author: Shady Nabil
 *
 * Created on May 7, 2023, 1:57 AM
 */

#ifndef MCAL_STD_TYPES_H
#define MCAL_STD_TYPES_H

/* Includes */
#include "compiler.h"
#include "std_libraries.h"

/* Data types declarations */
typedef unsigned char uint8;
typedef unsigned char flag_t;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;
typedef float sfloat32;
typedef double sfloat64;
typedef uint8 Std_ReturnType;

/* Macro declarations */
#define STD_HIGH 0x01
#define STD_LOW 0x00
#define STD_ON 0x01
#define STD_OFF 0x00
#define STD_ACTIVE 0x01
#define STD_IDLE 0x00
#define E_OK ((Std_ReturnType)0x01)
#define E_NOT_OK ((Std_ReturnType)0x00)

#endif /* MCAL_STD_TYPES_H */
