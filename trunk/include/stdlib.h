/* stdint.h
 * 
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/009695399/basedefs/stdlib.h.html
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#ifndef NULL
#define NULL 0
#endif /* NULL */

#endif /* _STDLIB_H */


/*DESCRIPTION

    [CX] [Option Start] Some of the functionality described on this reference page extends the ISO C standard. Applications shall define the appropriate feature test macro (see the System Interfaces volume of IEEE Std 1003.1-2001, Section 2.2, The Compilation Environment) to enable the visibility of these symbols in this header. [Option End]

    The <stdlib.h> header shall define the following macros:

    EXIT_FAILURE
        Unsuccessful termination for exit(); evaluates to a non-zero value.
    EXIT_SUCCESS
        Successful termination for exit(); evaluates to 0.
    {RAND_MAX}
        Maximum value returned by rand(); at least 32767.
    {MB_CUR_MAX}
        Integer expression whose value is the maximum number of bytes in a character specified by the current locale.

    The following data types shall be defined through typedef:

    div_t
        Structure type returned by the div() function.
    ldiv_t
        Structure type returned by the ldiv() function.
    lldiv_t
        Structure type returned by the lldiv() function.
    size_t
        As described in <stddef.h>.
    wchar_t
        As described in <stddef.h>.

    In addition, the following symbolic names and macros shall be defined as in <sys/wait.h> , for use in decoding the return value from system():


    [XSI] [Option Start]
    WNOHANG
    WUNTRACED
    WEXITSTATUS
    WIFEXITED
    WIFSIGNALED
    WIFSTOPPED
    WSTOPSIG
    WTERMSIG
    [Option End]

    The following shall be declared as functions and may also be defined as macros. Function prototypes shall be provided.

    void          _Exit(int);
    [XSI][Option Start]
    long          a64l(const char *);
    [Option End]
    void          abort(void);
    int           abs(int);
    int           atexit(void (*)(void));
    double        atof(const char *);
    int           atoi(const char *);
    long          atol(const char *);
    long long     atoll(const char *);
    void         *bsearch(const void *, const void *, size_t, size_t,
                      int (*)(const void *, const void *));
    void         *calloc(size_t, size_t);
    div_t         div(int, int);
    [XSI][Option Start]
    double        drand48(void);
    char         *ecvt(double, int, int *restrict, int *restrict); (LEGACY )
    double        erand48(unsigned short[3]);
    [Option End]
    void          exit(int);
    [XSI][Option Start]
    char         *fcvt(double, int, int *restrict, int *restrict); (LEGACY )
    [Option End]
    void          free(void *);
    [XSI][Option Start]
    char         *gcvt(double, int, char *); (LEGACY )
    [Option End]
    char         *getenv(const char *);
    [XSI][Option Start]
    int           getsubopt(char **, char *const *, char **);
    int           grantpt(int);
    char         *initstate(unsigned, char *, size_t);
    long          jrand48(unsigned short[3]);
    char         *l64a(long);
    [Option End]
    long          labs(long);
    [XSI][Option Start]
    void          lcong48(unsigned short[7]);
    [Option End]
    ldiv_t        ldiv(long, long);
    long long     llabs(long long);
    lldiv_t       lldiv(long long, long long);
    [XSI][Option Start]
    long          lrand48(void);
    [Option End]
    void         *malloc(size_t);
    int           mblen(const char *, size_t);
    size_t        mbstowcs(wchar_t *restrict, const char *restrict, size_t);
    int           mbtowc(wchar_t *restrict, const char *restrict, size_t);
    [XSI][Option Start]
    char         *mktemp(char *); (LEGACY )
    int           mkstemp(char *);
    long          mrand48(void);
    long          nrand48(unsigned short[3]);
    [Option End]
    [ADV][Option Start]
    int           posix_memalign(void **, size_t, size_t);
    [Option End]
    [XSI][Option Start]
    int           posix_openpt(int);
    char         *ptsname(int);
    int           putenv(char *);
    [Option End]
    void          qsort(void *, size_t, size_t, int (*)(const void *,
                      const void *));
    int           rand(void);
    [TSF][Option Start]
    int           rand_r(unsigned *);
    [Option End]
    [XSI][Option Start]
    long          random(void);
    [Option End]
    void         *realloc(void *, size_t);
    [XSI][Option Start]
    char         *realpath(const char *restrict, char *restrict);
    unsigned short seed48(unsigned short[3]);
    [Option End]
    [CX][Option Start]
    int           setenv(const char *, const char *, int);
    [Option End]
    [XSI][Option Start]
    void          setkey(const char *);
    char         *setstate(const char *);
    [Option End]
    void          srand(unsigned);
    [XSI][Option Start]
    void          srand48(long);
    void          srandom(unsigned);
    [Option End]
    double        strtod(const char *restrict, char **restrict);
    float         strtof(const char *restrict, char **restrict);
    long          strtol(const char *restrict, char **restrict, int);
    long double   strtold(const char *restrict, char **restrict);
    long long     strtoll(const char *restrict, char **restrict, int);
    unsigned long strtoul(const char *restrict, char **restrict, int);
    unsigned long long
                  strtoull(const char *restrict, char **restrict, int);
    int           system(const char *);
    [XSI][Option Start]
    int           unlockpt(int);
    [Option End]
    [CX][Option Start]
    int           unsetenv(const char *);
    [Option End]
    size_t        wcstombs(char *restrict, const wchar_t *restrict, size_t);
    int           wctomb(char *, wchar_t);

    [XSI] [Option Start] Inclusion of the <stdlib.h> header may also make visible all symbols from <stddef.h>, <limits.h>, <math.h>, and <sys/wait.h>. [Option End]

The following sections are informative.
APPLICATION USAGE

    None.

RATIONALE

    None.

FUTURE DIRECTIONS

    None.

SEE ALSO

    <limits.h>, <math.h>, <stddef.h>, <sys/types.h>, <sys/wait.h>, the System Interfaces volume of IEEE Std 1003.1-2001, _Exit(), a64l(), abort(), abs(), atexit(), atof(), atoi(), atol(), atoll(), bsearch(), calloc(), div(), drand48(), erand48(), exit(), free(), getenv(), getsubopt(), grantpt(), initstate(), jrand48(), l64a(), labs(), lcong48(), ldiv(), llabs(), lldiv(), lrand48(), malloc(), mblen(), mbstowcs(), mbtowc(), mkstemp(), mrand48(), nrand48(), posix_memalign(), ptsname(), putenv(), qsort(), rand(), realloc(), realpath(), setstate(), srand(), srand48(), srandom(), strtod(), strtof(), strtol(), strtold(), strtoll(), strtoul(), strtoull(), unlockpt(), wcstombs(), wctomb()

CHANGE HISTORY

    First released in Issue 3.

Issue 5

    The DESCRIPTION is updated for alignment with the POSIX Threads Extension.

    The ttyslot() and valloc() functions are marked LEGACY.

    The type of the third argument to initstate() is changed from int to size_t. The type of the return value from setstate() is changed from char to char *, and the type of the first argument is changed from char * to const char *.

Issue 6

    The Open Group Corrigendum U021/1 is applied, correcting the prototype for realpath() to be consistent with the reference page.

    The Open Group Corrigendum U028/13 is applied, correcting the prototype for putenv() to be consistent with the reference page.

    The rand_r() function is marked as part of the Thread-Safe Functions option.

    Function prototypes for setenv() and unsetenv() are added.

    The posix_memalign() function is added for alignment with IEEE Std 1003.1d-1999.

    This reference page is updated to align with the ISO/IEC 9899:1999 standard.

    The ecvt(), fcvt(), gcvt(), and mktemp() functions are marked LEGACY.

    The ttyslot() and valloc() functions are removed as they were previously marked LEGACY.

    Extensions beyond the ISO C standard are marked.
    */