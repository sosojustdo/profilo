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

#ifndef _NETINET_IN_H_
#define _NETINET_IN_H_
#define NETINET_IN_H_
#define NETINET_IN_H
#define NDK_ANDROID_SUPPORT_NETINET_IN_H_
#define NDK_ANDROID_SUPPORT_NETINET_IN_H
#define _NETINET_IN_H

#include <museum/6.0.1/bionic/libc/endian.h>
#include <museum/6.0.1/bionic/libc/netinet/in6.h>
#include <museum/6.0.1/bionic/libc/sys/cdefs.h>
#include <museum/6.0.1/bionic/libc/sys/socket.h>

#include <museum/6.0.1/bionic/libc/linux/in.h>
#include <museum/6.0.1/bionic/libc/linux/in6.h>
#include <museum/6.0.1/bionic/libc/linux/ipv6.h>

__BEGIN_DECLS

#define IPPORT_RESERVED  1024

#define INET_ADDRSTRLEN 16

typedef uint16_t in_port_t;
typedef uint32_t in_addr_t;

extern int bindresvport (int sd, struct sockaddr_in *sin);

static const struct in6_addr in6addr_any = IN6ADDR_ANY_INIT;
static const struct in6_addr in6addr_loopback = IN6ADDR_LOOPBACK_INIT;

__END_DECLS

#endif /* _NETINET_IN_H_ */
