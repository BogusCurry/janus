// Copyright (c) 2018 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=c0bf236fbeef704b6b457df707726714a715a935$
//

#include "libcef_dll/ctocpp/select_client_certificate_callback_ctocpp.h"
#include "libcef_dll/ctocpp/x509certificate_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

void CefSelectClientCertificateCallbackCToCpp::Select(
    CefRefPtr<CefX509Certificate> cert) {
  cef_select_client_certificate_callback_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, select))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: cert

  // Execute
  _struct->select(_struct, CefX509CertificateCToCpp::Unwrap(cert));
}

// CONSTRUCTOR - Do not edit by hand.

CefSelectClientCertificateCallbackCToCpp::
    CefSelectClientCertificateCallbackCToCpp() {}

template <>
cef_select_client_certificate_callback_t*
CefCToCppRefCounted<CefSelectClientCertificateCallbackCToCpp,
                    CefSelectClientCertificateCallback,
                    cef_select_client_certificate_callback_t>::
    UnwrapDerived(CefWrapperType type, CefSelectClientCertificateCallback* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template <>
base::AtomicRefCount CefCToCppRefCounted<
    CefSelectClientCertificateCallbackCToCpp,
    CefSelectClientCertificateCallback,
    cef_select_client_certificate_callback_t>::DebugObjCt ATOMIC_DECLARATION;
#endif

template <>
CefWrapperType CefCToCppRefCounted<
    CefSelectClientCertificateCallbackCToCpp,
    CefSelectClientCertificateCallback,
    cef_select_client_certificate_callback_t>::kWrapperType =
    WT_SELECT_CLIENT_CERTIFICATE_CALLBACK;
