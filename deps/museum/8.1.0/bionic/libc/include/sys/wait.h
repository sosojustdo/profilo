/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#ifndef _SYS_WAIT_H_
#define _SYS_WAIT_H_
#define SYS_WAIT_H_
#define SYS_WAIT_H
#define NDK_ANDROID_SUPPORT_SYS_WAIT_H_
#define NDK_ANDROID_SUPPORT_SYS_WAIT_H
#define _SYS_WAIT_H

#include <museum/8.1.0/bionic/libc/sys/cdefs.h>
#include <museum/8.1.0/bionic/libc/sys/types.h>
#include <museum/8.1.0/bionic/libc/sys/resource.h>
#include <museum/8.1.0/bionic/libc/linux/wait.h>
#include <museum/8.1.0/bionic/libc/signal.h>

__BEGIN_DECLS

#define WEXITSTATUS(s)  (((s) & 0xff00) >> 8)
#define WCOREDUMP(s)    ((s) & 0x80)
#define WTERMSIG(s)     ((s) & 0x7f)
#define WSTOPSIG(s)     WEXITSTATUS(s)

#define WIFEXITED(s)    (WTERMSIG(s) == 0)
#define WIFSTOPPED(s)   (WTERMSIG(s) == 0x7f)
#define WIFSIGNALED(s)  (WTERMSIG((s)+1) >= 2)
#define WIFCONTINUED(s) ((s) == 0xffff)

#define W_EXITCODE(ret, sig)    ((ret) << 8 | (sig))
#define W_STOPCODE(sig)         ((sig) << 8 | 0x7f)

pid_t wait(int*);
pid_t waitpid(pid_t, int*, int);
#if __ANDROID_API__ >= __ANDROID_API_J_MR2__
pid_t wait4(pid_t, int*, int, struct rusage*) __INTRODUCED_IN(18);
#else
// Implemented as a static inline before 18.
#endif

/* Posix states that idtype_t should be an enumeration type, but
 * the kernel headers define P_ALL, P_PID and P_PGID as constant macros
 * instead.
 */
typedef int idtype_t;

int waitid(idtype_t which, id_t id, siginfo_t* info, int options);

__END_DECLS

#include <museum/8.1.0/bionic/libc/android/legacy_sys_wait_inlines.h>

#endif /* _SYS_WAIT_H_ */
