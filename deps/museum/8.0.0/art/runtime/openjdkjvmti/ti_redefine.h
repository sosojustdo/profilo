/* Copyright (C) 2016 The Android Open Source Project
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This file implements interfaces from the file jvmti.h. This implementation
 * is licensed under the same terms as the file jvmti.h.  The
 * copyright and license information for the file jvmti.h follows.
 *
 * Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#ifndef ART_RUNTIME_OPENJDKJVMTI_TI_REDEFINE_H_
#define ART_RUNTIME_OPENJDKJVMTI_TI_REDEFINE_H_

#include <museum/8.0.0/external/libcxx/string>

#include <museum/8.0.0/libnativehelper/jni.h>

#include <museum/8.0.0/art/runtime/openjdkjvmti/art_jvmti.h>
#include <museum/8.0.0/art/runtime/art_method.h>
#include <museum/8.0.0/art/runtime/base/array_slice.h>
#include <museum/8.0.0/art/runtime/class_linker.h>
#include <museum/8.0.0/art/runtime/dex_file.h>
#include <museum/8.0.0/art/runtime/gc_root-inl.h>
#include <museum/8.0.0/art/runtime/globals.h>
#include <museum/8.0.0/art/runtime/jni_env_ext-inl.h>
#include "jvmti.h"
#include <museum/8.0.0/art/runtime/linear_alloc.h>
#include <museum/8.0.0/art/runtime/mem_map.h>
#include <museum/8.0.0/art/runtime/mirror/array-inl.h>
#include <museum/8.0.0/art/runtime/mirror/array.h>
#include <museum/8.0.0/art/runtime/mirror/class-inl.h>
#include <museum/8.0.0/art/runtime/mirror/class.h>
#include <museum/8.0.0/art/runtime/mirror/class_loader-inl.h>
#include <museum/8.0.0/art/runtime/mirror/string-inl.h>
#include <museum/8.0.0/art/runtime/oat_file.h>
#include <museum/8.0.0/art/runtime/obj_ptr.h>
#include <museum/8.0.0/art/runtime/scoped_thread_state_change-inl.h>
#include <museum/8.0.0/art/runtime/stack.h>
#include <museum/8.0.0/art/runtime/openjdkjvmti/ti_class_definition.h>
#include <museum/8.0.0/art/runtime/thread_list.h>
#include <museum/8.0.0/art/runtime/openjdkjvmti/transform.h>
#include <museum/8.0.0/art/runtime/utf.h>
#include <museum/8.0.0/art/runtime/utils/dex_cache_arrays_layout-inl.h>

namespace openjdkjvmti {

class RedefinitionDataHolder;
class RedefinitionDataIter;

// Class that can redefine a single class's methods.
class Redefiner {
 public:
  // Redefine the given classes with the given dex data. Note this function does not take ownership
  // of the dex_data pointers. It is not used after this call however and may be freed if desired.
  // The caller is responsible for freeing it. The runtime makes its own copy of the data. This
  // function does not call the transformation events.
  static jvmtiError RedefineClassesDirect(ArtJvmTiEnv* env,
                                          facebook::museum::MUSEUM_VERSION::art::Runtime* runtime,
                                          facebook::museum::MUSEUM_VERSION::art::Thread* self,
                                          const std::vector<ArtClassDefinition>& definitions,
                                          /*out*/std::string* error_msg);

  // Redefine the given classes with the given dex data. Note this function does not take ownership
  // of the dex_data pointers. It is not used after this call however and may be freed if desired.
  // The caller is responsible for freeing it. The runtime makes its own copy of the data.
  static jvmtiError RedefineClasses(ArtJvmTiEnv* env,
                                    EventHandler* event_handler,
                                    facebook::museum::MUSEUM_VERSION::art::Runtime* runtime,
                                    facebook::museum::MUSEUM_VERSION::art::Thread* self,
                                    jint class_count,
                                    const jvmtiClassDefinition* definitions,
                                    /*out*/std::string* error_msg);

  static jvmtiError IsModifiableClass(jvmtiEnv* env, jclass klass, jboolean* is_redefinable);

  static std::unique_ptr<facebook::museum::MUSEUM_VERSION::art::MemMap> MoveDataToMemMap(const std::string& original_location,
                                                       facebook::museum::MUSEUM_VERSION::art::ArraySlice<const unsigned char> data,
                                                       std::string* error_msg);

 private:
  class ClassRedefinition {
   public:
    ClassRedefinition(Redefiner* driver,
                      jclass klass,
                      const facebook::museum::MUSEUM_VERSION::art::DexFile* redefined_dex_file,
                      const char* class_sig,
                      facebook::museum::MUSEUM_VERSION::art::ArraySlice<const unsigned char> orig_dex_file)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // NO_THREAD_SAFETY_ANALYSIS so we can unlock the class in the destructor.
    ~ClassRedefinition() NO_THREAD_SAFETY_ANALYSIS;

    // Move constructor so we can put these into a vector.
    ClassRedefinition(ClassRedefinition&& other)
        : driver_(other.driver_),
          klass_(other.klass_),
          dex_file_(std::move(other.dex_file_)),
          class_sig_(std::move(other.class_sig_)),
          original_dex_file_(other.original_dex_file_) {
      other.driver_ = nullptr;
    }

    facebook::museum::MUSEUM_VERSION::art::mirror::Class* GetMirrorClass() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
    facebook::museum::MUSEUM_VERSION::art::mirror::ClassLoader* GetClassLoader() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    const facebook::museum::MUSEUM_VERSION::art::DexFile& GetDexFile() {
      return *dex_file_;
    }

    facebook::museum::MUSEUM_VERSION::art::mirror::DexCache* CreateNewDexCache(facebook::museum::MUSEUM_VERSION::art::Handle<facebook::museum::MUSEUM_VERSION::art::mirror::ClassLoader> loader)
        REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // This may return nullptr with a OOME pending if allocation fails.
    facebook::museum::MUSEUM_VERSION::art::mirror::Object* AllocateOrGetOriginalDexFile()
        REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void RecordFailure(jvmtiError e, const std::string& err) {
      driver_->RecordFailure(e, class_sig_, err);
    }

    bool FinishRemainingAllocations(/*out*/RedefinitionDataIter* cur_data)
        REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    bool AllocateAndRememberNewDexFileCookie(
        facebook::museum::MUSEUM_VERSION::art::Handle<facebook::museum::MUSEUM_VERSION::art::mirror::ClassLoader> source_class_loader,
        facebook::museum::MUSEUM_VERSION::art::Handle<facebook::museum::MUSEUM_VERSION::art::mirror::Object> dex_file_obj,
        /*out*/RedefinitionDataIter* cur_data)
          REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void FindAndAllocateObsoleteMethods(facebook::museum::MUSEUM_VERSION::art::mirror::Class* art_klass)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Checks that the dex file contains only the single expected class and that the top-level class
    // data has not been modified in an incompatible manner.
    bool CheckClass() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Checks that the contained class can be successfully verified.
    bool CheckVerification(const RedefinitionDataIter& holder)
        REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Preallocates all needed allocations in klass so that we can pause execution safely.
    bool EnsureClassAllocationsFinished(/*out*/RedefinitionDataIter* data)
        REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // This will check that no constraints are violated (more than 1 class in dex file, any changes
    // in number/declaration of methods & fields, changes in access flags, etc.)
    bool CheckRedefinitionIsValid() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Checks that the class can even be redefined.
    bool CheckRedefinable() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Checks that the dex file does not add/remove methods, or change their modifiers or types.
    bool CheckSameMethods() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    // Checks that the dex file does not modify fields types or modifiers.
    bool CheckSameFields() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void UpdateJavaDexFile(facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::Object> java_dex_file,
                           facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::LongArray> new_cookie)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void UpdateFields(facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::Class> mclass)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void UpdateMethods(facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::Class> mclass,
                       facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::DexCache> new_dex_cache,
                       const facebook::museum::MUSEUM_VERSION::art::DexFile::ClassDef& class_def)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void UpdateClass(facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::Class> mclass,
                     facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::DexCache> new_dex_cache,
                     facebook::museum::MUSEUM_VERSION::art::ObjPtr<facebook::museum::MUSEUM_VERSION::art::mirror::Object> original_dex_file)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void RestoreObsoleteMethodMapsIfUnneeded(const RedefinitionDataIter* cur_data)
        REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void ReleaseDexFile() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

    void UnregisterBreakpoints() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

   private:
    Redefiner* driver_;
    jclass klass_;
    std::unique_ptr<const facebook::museum::MUSEUM_VERSION::art::DexFile> dex_file_;
    std::string class_sig_;
    facebook::museum::MUSEUM_VERSION::art::ArraySlice<const unsigned char> original_dex_file_;
  };

  jvmtiError result_;
  facebook::museum::MUSEUM_VERSION::art::Runtime* runtime_;
  facebook::museum::MUSEUM_VERSION::art::Thread* self_;
  std::vector<ClassRedefinition> redefinitions_;
  // Kept as a jclass since we have weird run-state changes that make keeping it around as a
  // mirror::Class difficult and confusing.
  std::string* error_msg_;

  Redefiner(facebook::museum::MUSEUM_VERSION::art::Runtime* runtime,
            facebook::museum::MUSEUM_VERSION::art::Thread* self,
            std::string* error_msg)
      : result_(ERR(INTERNAL)),
        runtime_(runtime),
        self_(self),
        redefinitions_(),
        error_msg_(error_msg) { }

  jvmtiError AddRedefinition(ArtJvmTiEnv* env, const ArtClassDefinition& def)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

  static jvmtiError GetClassRedefinitionError(facebook::museum::MUSEUM_VERSION::art::Handle<facebook::museum::MUSEUM_VERSION::art::mirror::Class> klass,
                                              /*out*/std::string* error_msg)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

  jvmtiError Run() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

  bool CheckAllRedefinitionAreValid() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  bool CheckAllClassesAreVerified(RedefinitionDataHolder& holder)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  bool EnsureAllClassAllocationsFinished(RedefinitionDataHolder& holder)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  bool FinishAllRemainingAllocations(RedefinitionDataHolder& holder)
      REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  void ReleaseAllDexFiles() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  void UnregisterAllBreakpoints() REQUIRES_SHARED(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);
  // Restores the old obsolete methods maps if it turns out they weren't needed (ie there were no
  // new obsolete methods).
  void RestoreObsoleteMethodMapsIfUnneeded(RedefinitionDataHolder& holder)
      REQUIRES(facebook::museum::MUSEUM_VERSION::art::Locks::mutator_lock_);

  void RecordFailure(jvmtiError result, const std::string& class_sig, const std::string& error_msg);
  void RecordFailure(jvmtiError result, const std::string& error_msg) {
    RecordFailure(result, "NO CLASS", error_msg);
  }

  friend struct CallbackCtx;
  friend class RedefinitionDataHolder;
  friend class RedefinitionDataIter;
};

}  // namespace openjdkjvmti

#endif  // ART_RUNTIME_OPENJDKJVMTI_TI_REDEFINE_H_
