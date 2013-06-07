/* time.h
 *
 * This file tries to follow the standardizations specified in the POSIX
 * Programmers Manual wich can be reached through
 * 		http://pubs.opengroup.org/onlinepubs/009696699/basedefs/time.h.html
 * 
 * Copyright (C) 2013 Lasse Schuirmann. All Rights Reserved.
 * Written by Lasse Schuirmann (lasse.schuirmann@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 */

#ifndef _TIME_H
#define _TIME_H

#ifndef NULL
#define NULL 0
#endif /* NULL */

struct tm
{
	int tm_sec,
	int tm_min,
	int tm_hour,
	int tm_mday,
	int tm_mon,
	int tm_year,
	int tm_wday,//0 = Sunday
	int tm_yday,
	int tm_isdst//1: summertime :) 0: winter time :(
				//abs(tm_isdst) != tm_isdst: information unavailable :'(
}

/* POSIX says:

    [CX] [Option Start] Some of the functionality described on this reference page extends the ISO C standard.
    Applications shall define the appropriate feature test macro
    (see the System Interfaces volume of IEEE Std 1003.1-2001, Section 2.2, The Compilation Environment)
    to enable the visibility of these symbols in this header. [Option End]

    The <time.h> header shall define the following symbolic names:

    CLOCKS_PER_SEC
        A number used to convert the value returned by the clock() function into seconds.
    CLOCK_PROCESS_CPUTIME_ID
        [TMR|CPT] [Option Start]
        The identifier of the CPU-time clock associated with the process making a clock() or timer*() function call. [Option End]
    CLOCK_THREAD_CPUTIME_ID
        [TMR|TCT] [Option Start]
        The identifier of the CPU-time clock associated with the thread making a clock() or timer*() function call. [Option End]

    [TMR] [Option Start] The <time.h> header shall declare the structure timespec, which has at least the following members:

    time_t  tv_sec    Seconds. 
    long    tv_nsec   Nanoseconds. 

    The <time.h> header shall also declare the itimerspec structure, which has at least the following members:

    struct timespec  it_interval  Timer period. 
    struct timespec  it_value     Timer expiration. 

    The following manifest constants shall be defined:

    CLOCK_REALTIME
        The identifier of the system-wide realtime clock.
    TIMER_ABSTIME
        Flag indicating time is absolute. For functions taking timer objects, this refers to the clock associated with the timer. [Option End]
    CLOCK_MONOTONIC
        [MON] [Option Start]
        The identifier for the system-wide monotonic clock, which is defined as a clock whose value cannot be set via clock_settime() and which cannot have backward clock jumps. The maximum possible clock jump shall be implementation-defined. [Option End]

    The clock_t, size_t, time_t, [TMR] [Option Start] clockid_t, and timer_t [Option End] types shall be defined as described in <sys/types.h> .

    [XSI] [Option Start] Although the value of CLOCKS_PER_SEC is required to be 1 million on all XSI-conformant systems, it may be variable on other systems, and it should not be assumed that CLOCKS_PER_SEC is a compile-time constant. [Option End]

    [XSI] [Option Start] The <time.h> header shall provide a declaration for getdate_err. [Option End]

    The following shall be declared as functions and may also be defined as macros. Function prototypes shall be provided.

    char      *asctime(const struct tm *);
    [TSF][Option Start]
    char      *asctime_r(const struct tm *restrict, char *restrict);
    [Option End]
    clock_t    clock(void);
    [CPT][Option Start]
    int        clock_getcpuclockid(pid_t, clockid_t *);
    [Option End]
    [TMR][Option Start]
    int        clock_getres(clockid_t, struct timespec *);
    int        clock_gettime(clockid_t, struct timespec *);
    [Option End]
    [CS][Option Start]
    int        clock_nanosleep(clockid_t, int, const struct timespec *,
                   struct timespec *);
    [Option End]
    [TMR][Option Start]
    int        clock_settime(clockid_t, const struct timespec *);
    [Option End]
    char      *ctime(const time_t *);
    [TSF][Option Start]
    char      *ctime_r(const time_t *, char *);
    [Option End]
    double     difftime(time_t, time_t);
    [XSI][Option Start]
    struct tm *getdate(const char *);
    [Option End]
    struct tm *gmtime(const time_t *);
    [TSF][Option Start]
    struct tm *gmtime_r(const time_t *restrict, struct tm *restrict);
    [Option End]
    struct tm *localtime(const time_t *);
    [TSF][Option Start]
    struct tm *localtime_r(const time_t *restrict, struct tm *restrict);
    [Option End]
    time_t     mktime(struct tm *);
    [TMR][Option Start]
    int        nanosleep(const struct timespec *, struct timespec *);
    [Option End]
    size_t     strftime(char *restrict, size_t, const char *restrict,
               const struct tm *restrict);
    [XSI][Option Start]
    char      *strptime(const char *restrict, const char *restrict,
                   struct tm *restrict);
    [Option End]
    time_t     time(time_t *);
    [TMR][Option Start]
    int        timer_create(clockid_t, struct sigevent *restrict,
                   timer_t *restrict);
    int        timer_delete(timer_t);
    int        timer_gettime(timer_t, struct itimerspec *);
    int        timer_getoverrun(timer_t);
    int        timer_settime(timer_t, int, const struct itimerspec *restrict,
                   struct itimerspec *restrict);
    [Option End]
    [CX][Option Start]
    void       tzset(void);
    [Option End]


    The following shall be declared as variables:

    [XSI][Option Start]
    extern int    daylight;
    extern long   timezone;
    [Option End]
    [CX][Option Start]
    extern char  *tzname[];
    [Option End]

    [CX] [Option Start] Inclusion of the <time.h> header may make visible all symbols from the <signal.h> header. [Option End]

The following sections are informative.
APPLICATION USAGE

    The range [0,60] for tm_sec allows for the occasional leap second.

    tm_year is a signed value; therefore, years before 1900 may be represented.

    To obtain the number of clock ticks per second returned by the times() function, applications should call sysconf(_SC_CLK_TCK).

RATIONALE

    The range [0,60] seconds allows for positive or negative leap seconds. The formal definition of UTC does not permit double leap seconds, so all mention of double leap seconds has been removed, and the range shortened from the former [0,61] seconds seen in previous versions of POSIX.

SEE ALSO

    <signal.h>, <sys/types.h>, the System Interfaces volume of IEEE Std 1003.1-2001, asctime(), clock(), clock_getcpuclockid(), clock_getres(), clock_nanosleep(), ctime(), difftime(), getdate(), gmtime(), localtime(), mktime(), nanosleep(), strftime(), strptime(), sysconf(), time(), timer_create(), timer_delete(), timer_getoverrun(), tzname, tzset(), utime()
*/

#endif /* _TIME_H */