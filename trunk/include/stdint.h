/* include/stdint.h
 * 
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/009695399/basedefs/stdint.h.html
 */

#ifndef _STDINT_H
#define _STDINT_H

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef short               int16_t;
typedef unsigned short      uint16_t;
typedef int                 int32_t;
typedef unsigned            uint32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;

// TODO least, fast, greatest

#endif /* _STDINT_H */