/* include/stdarg.h
 * 
 * Should provide the standard functionality of the stdarg library.
 */

#ifndef _STDARG_H
#define _STDARG_H

//TODO this is OBSOLETE - make it POSIX conform
typedef __builtin_va_list       va_list;
#define va_start(ap, X)         __builtin_va_start(ap, X)
#define va_arg(ap, type)        __builtin_va_arg(ap, type)
#define va_end(ap)              __builtin_va_end(ap)

#endif /* _STDARG_H */