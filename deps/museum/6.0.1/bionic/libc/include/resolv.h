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
#ifndef _RESOLV_H_
#define _RESOLV_H_
#define RESOLV_H_
#define RESOLV_H
#define NDK_ANDROID_SUPPORT_RESOLV_H_
#define NDK_ANDROID_SUPPORT_RESOLV_H
#define _RESOLV_H

#include <museum/6.0.1/bionic/libc/sys/param.h>
#include <museum/6.0.1/bionic/libc/sys/types.h>
#include <museum/6.0.1/bionic/libc/sys/cdefs.h>
#include <museum/6.0.1/bionic/libc/sys/socket.h>
#include <museum/6.0.1/bionic/libc/stdio.h>
#include <museum/6.0.1/bionic/libc/arpa/nameser.h>
#include <museum/6.0.1/bionic/libc/netinet/in.h>

__BEGIN_DECLS
#pragma GCC visibility push(default)

struct res_state;

extern struct __res_state *__res_state(void);
#define _res (*__res_state())

#define b64_ntop __b64_ntop
#define b64_pton __b64_pton
extern int b64_ntop(u_char const*, size_t, char*, size_t);
extern int b64_pton(char const*, u_char*, size_t);

#define dn_comp __dn_comp
extern int dn_comp(const char*, u_char*, int, u_char**, u_char**);
extern int dn_expand(const u_char*, const u_char*, const u_char*, char*, int);

#pragma GCC visibility pop
__END_DECLS

#endif /* _RESOLV_H_ */
