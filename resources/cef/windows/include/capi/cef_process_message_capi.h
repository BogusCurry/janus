// Copyright (c) 2018 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=5f8cd4eb4e6215cb0f6161b916dc51197e345204$
//

#ifndef CEF_INCLUDE_CAPI_CEF_PROCESS_MESSAGE_CAPI_H_
#define CEF_INCLUDE_CAPI_CEF_PROCESS_MESSAGE_CAPI_H_
#pragma once

#include "include/capi/cef_base_capi.h"
#include "include/capi/cef_values_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

///
// Structure representing a message. Can be used on any process and thread.
///
typedef struct _cef_process_message_t {
  ///
  // Base structure.
  ///
  cef_base_ref_counted_t base;

  ///
  // Returns true (1) if this object is valid. Do not call any other functions
  // if this function returns false (0).
  ///
  int(CEF_CALLBACK* is_valid)(struct _cef_process_message_t* self);

  ///
  // Returns true (1) if the values of this object are read-only. Some APIs may
  // expose read-only objects.
  ///
  int(CEF_CALLBACK* is_read_only)(struct _cef_process_message_t* self);

  ///
  // Returns a writable copy of this object.
  ///
  struct _cef_process_message_t*(CEF_CALLBACK* copy)(
      struct _cef_process_message_t* self);

  ///
  // Returns the message name.
  ///
  // The resulting string must be freed by calling cef_string_userfree_free().
  cef_string_userfree_t(CEF_CALLBACK* get_name)(
      struct _cef_process_message_t* self);

  ///
  // Returns the list of arguments.
  ///
  struct _cef_list_value_t*(CEF_CALLBACK* get_argument_list)(
      struct _cef_process_message_t* self);
} cef_process_message_t;

///
// Create a new cef_process_message_t object with the specified name.
///
CEF_EXPORT cef_process_message_t* cef_process_message_create(
    const cef_string_t* name);

#ifdef __cplusplus
}
#endif

#endif  // CEF_INCLUDE_CAPI_CEF_PROCESS_MESSAGE_CAPI_H_
