/**
 * This code is part of libcity library.
 *
 * @file debug.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Basic debuging tools
 *
 */

#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <iostream>

/* Debugging is ON */
#define DEBUG

#ifdef DEBUG
  #define debug(x) std::cerr << "DEBUG: " << x << std::endl
#else
  #define debug(x)
  #define NDEBUG /* Turn off asserts */
#endif

#include <assert.h>

#endif