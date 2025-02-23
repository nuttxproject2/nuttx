/****************************************************************************
 * include/signal.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __INCLUDE_SIGNAL_H
#define __INCLUDE_SIGNAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <nuttx/compiler.h>

#include <stdint.h>
#include <time.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Signal set management definitions and macros. */

#define MIN_SIGNO       1               /* Lowest valid signal number */
#define MAX_SIGNO       63              /* Highest valid signal number */
#define GOOD_SIGNO(s)   ((((unsigned)(s)) <= MAX_SIGNO))

/* Definitions for "standard" signals */

#define SIGSTDMIN       1               /* First standard signal number */
#define SIGSTDMAX       31              /* Last standard signal number */

/* Definitions for "real time" signals */

#define SIGRTMIN        (SIGSTDMAX + 1) /* First real time signal */
#define SIGRTMAX        MAX_SIGNO       /* Last real time signal */
#define _NSIG           (MAX_SIGNO + 1) /* Biggest signal number + 1 */
#define NSIG            _NSIG           /* _NSIG variant commonly used */

/* sigset_t is represented as an array of 32-b unsigned integers.
 * _SIGSET_NELEM is the allocated isze of the array
 */

#define _SIGSET_NELEM   ((_NSIG + 31) >> 5)

/* NuttX does not support all standard signal actions.  NuttX supports what
 * are referred to as "real time" signals.  The default action of all NuttX
 * signals is to simply ignore the signal.  Certain signals can be
 * configured to support there default actions as indicated by NOTEs to the
 * following table.
 *
 * This is not POSIX compliant behavior!  Per OpenGroup.org:  The following
 * signals and default signal actions must be supported on all
 * implementations:
 *
 *   ---------- ------- ----------------------------------------------------
 *   Signal     Default Description
 *   Name       Action
 *   ---------- ------- ----------------------------------------------------
 *   SIGABRT    A       Process abort signal
 *   SIGALRM    T (1)   Alarm clock
 *   SIGBUS     A       Access to an undefined portion of a memory object
 *   SIGCHLD    I       Child process terminated, stopped
 *                      (or continued XSI extension)
 *   SIGCONT    C (2)   Continue executing, if stopped
 *   SIGFPE     A       Erroneous arithmetic operation
 *   SIGHUP     T       Hangup
 *   SIGILL     A       Illegal instruction
 *   SIGINT     T (3)   Terminal interrupt signal
 *   SIGKILL    T (3)   Kill (cannot be caught or ignored)
 *   SIGPIPE    T (7)   Write on a pipe with no one to read it
 *   SIGQUIT    A       Terminal quit signal
 *   SIGSEGV    A       Invalid memory reference
 *   SIGSTOP    S (2)   Stop executing (cannot be caught or ignored)
 *   SIGTERM    T       Termination signal
 *   SIGTSTP    S (2)   Terminal stop signal
 *   SIGTTIN    S       Background process attempting read
 *   SIGTTOU    S       Background process attempting write
 *   SIGUSR1    T (4)   User-defined signal 1
 *   SIGUSR2    T (5)   User-defined signal 2
 *   SIGPOLL    T (6)   Poll-able event (XSI extension)
 *   SIGPROF    T       Profiling timer expired (XSI extension)
 *   SIGSYS     A       Bad system call (XSI extension)
 *   SIGTRAP    A       Trace/breakpoint trap (XSI extension)
 *   SIGURG     I       High bandwidth data is available at a socket
 *   SIGVTALRM  T       Virtual timer expired (XSI extension)
 *   SIGXCPU    A       CPU time limit exceeded (XSI extension)
 *   SIGXFSZ    A       File size limit exceeded (XSI extension)
 *   ---------- ------- ----------------------------------------------------
 *
 * Where default action codes are:
 *
 * T  Abnormal termination of the process.  The process is terminated with
 *    all the consequences of _exit() except that the status made available
 *    to wait() and waitpid() indicates abnormal termination by the
 *    specified signal.
 * A  Abnormal termination of the process.  Additionally with the XSI
 *    extension, implementation-defined abnormal termination actions, such
 *    as creation of a core file, may occur.
 * I  Ignore the signal.
 * S  Stop the process.
 * C  Continue the process, if it is stopped; otherwise, ignore the signal.
 *
 * NOTES:
 * (1)  The default action can be enabled with CONFIG_SIG_SIGALRM_ACTION
 * (2)  The default action can be enabled with CONFIG_SIG_SIGSTOP_ACTION
 * (3)  The default action can be enabled with CONFIG_SIG_SIGKILL_ACTION
 * (4)  The default action can be enabled with CONFIG_SIG_SIGUSR1_ACTION
 * (5)  The default action can be enabled with CONFIG_SIG_SIGUSR2_ACTION
 * (6)  The default action can be enabled with CONFIG_SIG_SIGPOLL_ACTION
 * (7)  The default action can be enabled with CONFIG_SIG_SIGPIPE_ACTION
 */

/* A few of the real time signals are used within the OS.  They have
 * default values that can be overridden from the configuration file. The
 * rest are all standard or user real-time signals.
 *
 * The signal number zero is wasted for the most part.  It is a valid
 * signal number, but has special meaning at many interfaces (e.g., Kill()).
 *
 * These are the semi-standard signal definitions:
 */

#define SIGHUP          1
#define SIGINT          2
#define SIGQUIT         3
#define SIGILL          4
#define SIGTRAP         5
#define SIGABRT         6
#define SIGBUS          7
#define SIGFPE          8
#define SIGKILL         9
#define SIGUSR1         10  /* User signal 1 */
#define SIGSEGV         11
#define SIGUSR2         12  /* User signal 2 */
#define SIGPIPE         13
#define SIGALRM         14  /* Default signal used with POSIX timers (used only */
                            /* no other signal is provided) */
#define SIGTERM         15
#define SIGCHLD         17
#define SIGCONT         18
#define SIGSTOP         19
#define SIGTSTP         20
#define SIGTTIN         21
#define SIGTTOU         22
#define SIGURG          23
#define SIGXCPU         24
#define SIGXFSZ         25
#define SIGVTALRM       26
#define SIGPROF         27
#define SIGPOLL         29

#define SIGIO           SIGPOLL

#define SIGSYS          31

/* sigprocmask() "how" definitions.
 * Only one of the following can be specified:
 */

#define SIG_BLOCK       1  /* Block the given signals */
#define SIG_UNBLOCK     2  /* Unblock the given signals */
#define SIG_SETMASK     3  /* Set the signal mask to the current set */

/* struct sigaction flag values */

#define SA_NOCLDSTOP    (1 << 0) /* Do not generate SIGCHLD when
                                  * children stop (ignored) */
#define SA_SIGINFO      (1 << 1) /* Invoke the signal-catching function
                                  * with 3 args instead of 1
                                  * (always assumed) */
#define SA_NOCLDWAIT    (1 << 2) /* If signo=SIGCHLD, exit status of child
                                  * processes will be discarded */
#define SA_ONSTACK      (1 << 3) /* Indicates that a registered stack_t
                                  * will be used */
#define SA_RESTART      (1 << 4) /* Flag to get restarting signals
                                  * (which were the default long ago) */
#define SA_NODEFER      (1 << 5) /* Prevents the current signal from
                                  * being masked in the handler */
#define SA_RESETHAND    (1 << 6) /* Clears the handler when the signal
                                  * is delivered */
#define SA_KERNELHAND   (1 << 7) /* Invoke the handler in kernel space directly */

/* These are the possible values of the signfo si_code field */

#define SI_USER         0  /* Signal sent from kill, raise, or abort */
#define SI_QUEUE        1  /* Signal sent from sigqueue */
#define SI_TIMER        2  /* Signal is result of timer expiration */
#define SI_ASYNCIO      3  /* Signal is the result of asynch IO completion */
#define SI_MESGQ        4  /* Signal generated by arrival of a message on an */
                           /* empty message queue */
#define CLD_EXITED      5  /* Child has exited (SIGCHLD only) */
#define CLD_KILLED      6  /* Child was killed (SIGCHLD only) */
#define CLD_DUMPED      7  /* Child terminated abnormally (SIGCHLD only) */
#define CLD_TRAPPED     8  /* Traced child has trapped (SIGCHLD only) */
#define CLD_STOPPED     9  /* Child has stopped (SIGCHLD only) */
#define CLD_CONTINUED   10 /* Stopped child had continued (SIGCHLD only) */

/* Values for the sigev_notify field of struct sigevent */

#define SIGEV_NONE      0 /* No asynchronous notification is delivered */
#define SIGEV_SIGNAL    1 /* Notify via signal,with an application-defined value */
#ifdef CONFIG_SIG_EVTHREAD
#  define SIGEV_THREAD  3 /* A notification function is called */
#endif

/* Special values of sa_handler used by sigaction and sigset.  They are all
 * treated like NULL for now.  This is okay for SIG_DFL and SIG_IGN because
 * in NuttX, the default action for all signals is to ignore them.
 */

#define SIG_ERR         ((_sa_handler_t)-1)  /* And error occurred */
#define SIG_IGN         ((_sa_handler_t)0)   /* Ignore the signal */

#ifdef CONFIG_SIG_DEFAULT
#  define SIG_DFL       ((_sa_handler_t)1)   /* Default signal action */
#  define SIG_HOLD      ((_sa_handler_t)2)   /* Used only with sigset() */
#else
#  define SIG_DFL       ((_sa_handler_t)0)   /* Default is SIG_IGN for all signals */
#  define SIG_HOLD      ((_sa_handler_t)1)   /* Used only with sigset() */
#endif

#define tkill(tid, signo)  tgkill((pid_t)-1, tid, signo)

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* This defines a set of 32 signals (numbered 0 through 31).
 * REVISIT: Signal 0 is, however, not generally usable since that value has
 * special meaning in some circumstances (e.g., kill()).
 */

struct sigset_s
{
  uint32_t _elem[_SIGSET_NELEM];
};

typedef struct sigset_s sigset_t; /* Bit set of _NSIG signals */

/* Possibly volatile-qualified integer type of an object that can be accessed
 * as an atomic entity, even in the presence of asynchronous interrupts.
 */

typedef volatile int sig_atomic_t;

/* This defines the type of the siginfo si_value field */

union sigval
{
  int       sival_int;       /* Integer value */
  FAR void *sival_ptr;       /* Pointer value */
};

/* This structure contains elements that define a queue signal.
 * The following is used to attach a signal to a message queue
 * to notify a task when a message is available on a queue.
 */

typedef CODE void (*sigev_notify_function_t)(union sigval value);

struct sigevent
{
  uint8_t      sigev_notify; /* Notification method: SIGEV_SIGNAL, SIGEV_NONE, or SIGEV_THREAD */
  uint8_t      sigev_signo;  /* Notification signal */
  union sigval sigev_value;  /* Data passed with notification */

#ifdef CONFIG_SIG_EVTHREAD
  sigev_notify_function_t sigev_notify_function;      /* Notification function */
  FAR struct pthread_attr_s *sigev_notify_attributes; /* Notification attributes (not used) */
#endif
};

/* The following types is used to pass parameters to/from signal handlers */

struct siginfo
{
  uint8_t      si_signo;     /* Identifies signal */
  uint8_t      si_code;      /* Source: SI_USER, SI_QUEUE, SI_TIMER, SI_ASYNCIO, or SI_MESGQ */
  uint8_t      si_errno;     /* Zero or errno value associated with signal */
  union sigval si_value;     /* Data passed with signal */
#ifdef CONFIG_SCHED_HAVE_PARENT
  pid_t        si_pid;       /* Sending task ID */
  int          si_status;    /* Exit value or signal (SIGCHLD only). */
#endif
#if 0                        /* Not implemented */
  FAR void    *si_addr;      /* Report address with SIGFPE, SIGSEGV, or SIGBUS */
#endif
  FAR void    *si_user;      /* The User info associated with sigaction */
};

typedef struct siginfo siginfo_t;

/* Non-standard convenience definition of signal handling function types.
 * These should be used only internally within the NuttX signal logic.
 */

typedef CODE void (*_sa_handler_t)(int signo);
typedef CODE void (*_sa_sigaction_t)(int signo, FAR siginfo_t *siginfo,
                                     FAR void *context);

/* glibc definition of signal handling function types */

typedef _sa_handler_t sighandler_t;

/* The following structure defines the action to take for given signal */

struct sigaction
{
  union
  {
    _sa_handler_t   _sa_handler;
    _sa_sigaction_t _sa_sigaction;
  } sa_u;
  sigset_t          sa_mask;
  int               sa_flags;
  FAR void         *sa_user;
};

/* Definitions that adjust the non-standard naming */

#define sa_handler   sa_u._sa_handler
#define sa_sigaction sa_u._sa_sigaction

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#ifdef __cplusplus
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

int  kill(pid_t pid, int signo);
int  killpg(pid_t pgrp, int signo);
int  tgkill(pid_t pid, pid_t tid, int signo);
void psignal(int signum, FAR const char *message);
void psiginfo(FAR const siginfo_t *pinfo, FAR const char *message);
int  raise(int signo);
int  sigaction(int signo, FAR const struct sigaction *act,
               FAR struct sigaction *oact);
int  sigaddset(FAR sigset_t *set, int signo);
int  sigandset(FAR sigset_t *dest, FAR const sigset_t *left,
               FAR const sigset_t *right);
int  sigdelset(FAR sigset_t *set, int signo);
int  sigemptyset(FAR sigset_t *set);
int  sigfillset(FAR sigset_t *set);
int  sighold(int signo);
int  sigisemptyset(FAR sigset_t *set);
int  sigismember(FAR const sigset_t *set, int signo);
int  sigignore(int signo);
_sa_handler_t signal(int signo, _sa_handler_t func);
int  sigorset(FAR sigset_t *dest, FAR const sigset_t *left,
              FAR const sigset_t *right);
int  sigpause(int signo);
int  sigpending(FAR sigset_t *set);
int  sigprocmask(int how, FAR const sigset_t *set, FAR sigset_t *oset);
int  sigqueue(int pid, int signo, union sigval value);
int  sigrelse(int signo);
_sa_handler_t sigset(int signo, _sa_handler_t func);
int  sigwait(FAR const sigset_t *set, FAR int *sig);
int  sigtimedwait(FAR const sigset_t *set, FAR struct siginfo *value,
                  FAR const struct timespec *timeout);
int  sigsuspend(FAR const sigset_t *sigmask);
int  sigwaitinfo(FAR const sigset_t *set, FAR struct siginfo *value);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_SIGNAL_H */
