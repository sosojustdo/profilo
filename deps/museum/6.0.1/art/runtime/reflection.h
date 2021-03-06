/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_RUNTIME_REFLECTION_H_
#define ART_RUNTIME_REFLECTION_H_

#include <museum/6.0.1/art/runtime/base/mutex.h>
#include <museum/6.0.1/libnativehelper/jni.h>
#include <museum/6.0.1/art/runtime/primitive.h>

namespace facebook { namespace museum { namespace MUSEUM_VERSION { namespace art {
namespace mirror {
  class Class;
  class Object;
}  // namespace mirror
class ArtField;
class ArtMethod;
union JValue;
class ScopedObjectAccessAlreadyRunnable;
class ShadowFrame;

mirror::Object* BoxPrimitive(Primitive::Type src_class, const JValue& value)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);
bool UnboxPrimitiveForField(mirror::Object* o, mirror::Class* dst_class, ArtField* f,
                            JValue* unboxed_value)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);
bool UnboxPrimitiveForResult(mirror::Object* o, mirror::Class* dst_class, JValue* unboxed_value)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

ALWAYS_INLINE bool ConvertPrimitiveValue(bool unbox_for_result,
                                         Primitive::Type src_class, Primitive::Type dst_class,
                                         const JValue& src, JValue* dst)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

JValue InvokeWithVarArgs(const ScopedObjectAccessAlreadyRunnable& soa, jobject obj, jmethodID mid,
                         va_list args)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

JValue InvokeWithJValues(const ScopedObjectAccessAlreadyRunnable& soa, jobject obj, jmethodID mid,
                         jvalue* args)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

JValue InvokeVirtualOrInterfaceWithJValues(const ScopedObjectAccessAlreadyRunnable& soa,
                                           jobject obj, jmethodID mid, jvalue* args)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

JValue InvokeVirtualOrInterfaceWithVarArgs(const ScopedObjectAccessAlreadyRunnable& soa,
                                           jobject obj, jmethodID mid, va_list args)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

// num_frames is number of frames we look up for access check.
jobject InvokeMethod(const ScopedObjectAccessAlreadyRunnable& soa, jobject method, jobject receiver,
                     jobject args, size_t num_frames = 1)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

ALWAYS_INLINE bool VerifyObjectIsClass(mirror::Object* o, mirror::Class* c)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

bool VerifyAccess(Thread* self, mirror::Object* obj, mirror::Class* declaring_class,
                  uint32_t access_flags, mirror::Class** calling_class, size_t num_frames)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

// This version takes a known calling class.
bool VerifyAccess(Thread* self, mirror::Object* obj, mirror::Class* declaring_class,
                  uint32_t access_flags, mirror::Class* calling_class)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

// Get the calling class by using a stack visitor, may return null for unattached native threads.
mirror::Class* GetCallingClass(Thread* self, size_t num_frames)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

void InvalidReceiverError(mirror::Object* o, mirror::Class* c)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

void UpdateReference(Thread* self, jobject obj, mirror::Object* result)
    SHARED_LOCKS_REQUIRED(Locks::mutator_lock_);

} } } } // namespace facebook::museum::MUSEUM_VERSION::art

#endif  // ART_RUNTIME_REFLECTION_H_
