/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef _LINUX_UTIME_H
#define _LINUX_UTIME_H
#define LINUX_UTIME_H
#define LINUX_UTIME_H_
#define NDK_ANDROID_SUPPORT_LINUX_UTIME_H
#define NDK_ANDROID_SUPPORT_LINUX_UTIME_H_
#define NDK_ANDROID_SUPPORT_UAPI_LINUX_UTIME_H
#define NDK_ANDROID_SUPPORT_UAPI_LINUX_UTIME_H_
#define _UAPI_LINUX_UTIME_H
#define _UAPI_LINUX_UTIME_H_
#define _LINUX_UTIME_H_
#include <museum/8.1.0/bionic/libc/linux/types.h>
struct utimbuf {
  __kernel_time_t actime;
  __kernel_time_t modtime;
};
#endif
