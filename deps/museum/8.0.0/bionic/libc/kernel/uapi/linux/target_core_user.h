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
#ifndef __TARGET_CORE_USER_H
#define __TARGET_CORE_USER_H
#define _TARGET_CORE_USER_H
#define _TARGET_CORE_USER_H_
#define _UAPI_TARGET_CORE_USER_H
#define _UAPI_TARGET_CORE_USER_H_
#define _UAPI__TARGET_CORE_USER_H
#define _UAPI__TARGET_CORE_USER_H_
#define __TARGET_CORE_USER_H_
#include <museum/8.0.0/bionic/libc/linux/types.h>
#include <museum/8.0.0/bionic/libc/linux/uio.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCMU_VERSION "2.0"
#define TCMU_MAILBOX_VERSION 2
#define ALIGN_SIZE 64
#define TCMU_MAILBOX_FLAG_CAP_OOOC (1 << 0)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct tcmu_mailbox {
  __u16 version;
  __u16 flags;
  __u32 cmdr_off;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  __u32 cmdr_size;
  __u32 cmd_head;
  __u32 cmd_tail __attribute__((__aligned__(ALIGN_SIZE)));
} __packed;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
enum tcmu_opcode {
  TCMU_OP_PAD = 0,
  TCMU_OP_CMD,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct tcmu_cmd_entry_hdr {
  __u32 len_op;
  __u16 cmd_id;
  __u8 kflags;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCMU_UFLAG_UNKNOWN_OP 0x1
  __u8 uflags;
} __packed;
#define TCMU_OP_MASK 0x7
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCMU_SENSE_BUFFERSIZE 96
struct tcmu_cmd_entry {
  struct tcmu_cmd_entry_hdr hdr;
  union {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
    struct {
      uint32_t iov_cnt;
      uint32_t iov_bidi_cnt;
      uint32_t iov_dif_cnt;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
      uint64_t cdb_off;
      uint64_t __pad1;
      uint64_t __pad2;
      struct iovec iov[0];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
    } req;
    struct {
      uint8_t scsi_status;
      uint8_t __pad1;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
      uint16_t __pad2;
      uint32_t __pad3;
      char sense_buffer[TCMU_SENSE_BUFFERSIZE];
    } rsp;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  };
} __packed;
#define TCMU_OP_ALIGN_SIZE sizeof(uint64_t)
enum tcmu_genl_cmd {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  TCMU_CMD_UNSPEC,
  TCMU_CMD_ADDED_DEVICE,
  TCMU_CMD_REMOVED_DEVICE,
  __TCMU_CMD_MAX,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#define TCMU_CMD_MAX (__TCMU_CMD_MAX - 1)
enum tcmu_genl_attr {
  TCMU_ATTR_UNSPEC,
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
  TCMU_ATTR_DEVICE,
  TCMU_ATTR_MINOR,
  __TCMU_ATTR_MAX,
};
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define TCMU_ATTR_MAX (__TCMU_ATTR_MAX - 1)
#endif
