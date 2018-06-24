// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com
// Original code is licensed as follows:
/*
 * Copyright 2006 Jeremias Maerki
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

#include "xfa/fxbarcode/datamatrix/BC_SymbolInfo.h"

#include "xfa/fxbarcode/BC_Dimension.h"
#include "xfa/fxbarcode/common/BC_CommonBitMatrix.h"
#include "xfa/fxbarcode/datamatrix/BC_DataMatrixSymbolInfo144.h"
#include "xfa/fxbarcode/datamatrix/BC_Encoder.h"
#include "xfa/fxbarcode/datamatrix/BC_SymbolShapeHint.h"

namespace {

const size_t kSymbolsCount = 30;

CBC_SymbolInfo* g_symbols[kSymbolsCount] = {
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
    nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

}  // namespace

void CBC_SymbolInfo::Initialize() {
  g_symbols[0] = new CBC_SymbolInfo(FALSE, 3, 5, 8, 8, 1);
  g_symbols[1] = new CBC_SymbolInfo(FALSE, 5, 7, 10, 10, 1);
  g_symbols[2] = new CBC_SymbolInfo(TRUE, 5, 7, 16, 6, 1);
  g_symbols[3] = new CBC_SymbolInfo(FALSE, 8, 10, 12, 12, 1);
  g_symbols[4] = new CBC_SymbolInfo(TRUE, 10, 11, 14, 6, 2);
  g_symbols[5] = new CBC_SymbolInfo(FALSE, 12, 12, 14, 14, 1);
  g_symbols[6] = new CBC_SymbolInfo(TRUE, 16, 14, 24, 10, 1);
  g_symbols[7] = new CBC_SymbolInfo(FALSE, 18, 14, 16, 16, 1);
  g_symbols[8] = new CBC_SymbolInfo(FALSE, 22, 18, 18, 18, 1);
  g_symbols[9] = new CBC_SymbolInfo(TRUE, 22, 18, 16, 10, 2);
  g_symbols[10] = new CBC_SymbolInfo(FALSE, 30, 20, 20, 20, 1);
  g_symbols[11] = new CBC_SymbolInfo(TRUE, 32, 24, 16, 14, 2);
  g_symbols[12] = new CBC_SymbolInfo(FALSE, 36, 24, 22, 22, 1);
  g_symbols[13] = new CBC_SymbolInfo(FALSE, 44, 28, 24, 24, 1);
  g_symbols[14] = new CBC_SymbolInfo(TRUE, 49, 28, 22, 14, 2);
  g_symbols[15] = new CBC_SymbolInfo(FALSE, 62, 36, 14, 14, 4);
  g_symbols[16] = new CBC_SymbolInfo(FALSE, 86, 42, 16, 16, 4);
  g_symbols[17] = new CBC_SymbolInfo(FALSE, 114, 48, 18, 18, 4);
  g_symbols[18] = new CBC_SymbolInfo(FALSE, 144, 56, 20, 20, 4);
  g_symbols[19] = new CBC_SymbolInfo(FALSE, 174, 68, 22, 22, 4);
  g_symbols[20] = new CBC_SymbolInfo(FALSE, 204, 84, 24, 24, 4, 102, 42);
  g_symbols[21] = new CBC_SymbolInfo(FALSE, 280, 112, 14, 14, 16, 140, 56);
  g_symbols[22] = new CBC_SymbolInfo(FALSE, 368, 144, 16, 16, 16, 92, 36);
  g_symbols[23] = new CBC_SymbolInfo(FALSE, 456, 192, 18, 18, 16, 114, 48);
  g_symbols[24] = new CBC_SymbolInfo(FALSE, 576, 224, 20, 20, 16, 144, 56);
  g_symbols[25] = new CBC_SymbolInfo(FALSE, 696, 272, 22, 22, 16, 174, 68);
  g_symbols[26] = new CBC_SymbolInfo(FALSE, 816, 336, 24, 24, 16, 136, 56);
  g_symbols[27] = new CBC_SymbolInfo(FALSE, 1050, 408, 18, 18, 36, 175, 68);
  g_symbols[28] = new CBC_SymbolInfo(FALSE, 1304, 496, 20, 20, 36, 163, 62);
  g_symbols[29] = new CBC_DataMatrixSymbolInfo144();
}

void CBC_SymbolInfo::Finalize() {
  for (size_t i = 0; i < kSymbolsCount; i++) {
    delete g_symbols[i];
    g_symbols[i] = nullptr;
  }
}

CBC_SymbolInfo::CBC_SymbolInfo(FX_BOOL rectangular,
                               int32_t dataCapacity,
                               int32_t errorCodewords,
                               int32_t matrixWidth,
                               int32_t matrixHeight,
                               int32_t dataRegions) {
  m_rectangular = rectangular;
  m_dataCapacity = dataCapacity;
  m_errorCodewords = errorCodewords;
  m_matrixWidth = matrixWidth;
  m_matrixHeight = matrixHeight;
  m_dataRegions = dataRegions;
  m_rsBlockData = dataCapacity;
  m_rsBlockError = errorCodewords;
}
CBC_SymbolInfo::CBC_SymbolInfo(FX_BOOL rectangular,
                               int32_t dataCapacity,
                               int32_t errorCodewords,
                               int32_t matrixWidth,
                               int32_t matrixHeight,
                               int32_t dataRegions,
                               int32_t rsBlockData,
                               int32_t rsBlockError) {
  m_rectangular = rectangular;
  m_dataCapacity = dataCapacity;
  m_errorCodewords = errorCodewords;
  m_matrixWidth = matrixWidth;
  m_matrixHeight = matrixHeight;
  m_dataRegions = dataRegions;
  m_rsBlockData = rsBlockData;
  m_rsBlockError = rsBlockError;
}
CBC_SymbolInfo::~CBC_SymbolInfo() {}

CBC_SymbolInfo* CBC_SymbolInfo::lookup(int32_t dataCodewords, int32_t& e) {
  return lookup(dataCodewords, FORCE_NONE, TRUE, e);
}
CBC_SymbolInfo* CBC_SymbolInfo::lookup(int32_t dataCodewords,
                                       SymbolShapeHint shape,
                                       int32_t& e) {
  return lookup(dataCodewords, shape, TRUE, e);
}
CBC_SymbolInfo* CBC_SymbolInfo::lookup(int32_t dataCodewords,
                                       FX_BOOL allowRectangular,
                                       FX_BOOL fail,
                                       int32_t& e) {
  SymbolShapeHint shape = allowRectangular ? FORCE_NONE : FORCE_SQUARE;
  return lookup(dataCodewords, shape, fail, e);
}
CBC_SymbolInfo* CBC_SymbolInfo::lookup(int32_t dataCodewords,
                                       SymbolShapeHint shape,
                                       FX_BOOL fail,
                                       int32_t& e) {
  return lookup(dataCodewords, shape, nullptr, nullptr, fail, e);
}
CBC_SymbolInfo* CBC_SymbolInfo::lookup(int32_t dataCodewords,
                                       SymbolShapeHint shape,
                                       CBC_Dimension* minSize,
                                       CBC_Dimension* maxSize,
                                       FX_BOOL fail,
                                       int32_t& e) {
  for (size_t i = 0; i < kSymbolsCount; i++) {
    CBC_SymbolInfo* symbol = g_symbols[i];
    if (shape == FORCE_SQUARE && symbol->m_rectangular) {
      continue;
    }
    if (shape == FORCE_RECTANGLE && !symbol->m_rectangular) {
      continue;
    }
    if (minSize && (symbol->getSymbolWidth(e) < minSize->getWidth() ||
                    symbol->getSymbolHeight(e) < minSize->getHeight())) {
      BC_EXCEPTION_CHECK_ReturnValue(e, nullptr);
      continue;
    }
    if (maxSize && (symbol->getSymbolWidth(e) > maxSize->getWidth() ||
                    symbol->getSymbolHeight(e) > maxSize->getHeight())) {
      BC_EXCEPTION_CHECK_ReturnValue(e, nullptr);
      continue;
    }
    if (dataCodewords <= symbol->m_dataCapacity) {
      return symbol;
    }
  }
  if (fail)
    e = BCExceptionIllegalDataCodewords;
  return nullptr;
}

int32_t CBC_SymbolInfo::getHorizontalDataRegions(int32_t& e) {
  switch (m_dataRegions) {
    case 1:
      return 1;
    case 2:
      return 2;
    case 4:
      return 2;
    case 16:
      return 4;
    case 36:
      return 6;
    default:
      e = BCExceptionCannotHandleThisNumberOfDataRegions;
      return 0;
  }
}
int32_t CBC_SymbolInfo::getVerticalDataRegions(int32_t& e) {
  switch (m_dataRegions) {
    case 1:
      return 1;
    case 2:
      return 1;
    case 4:
      return 2;
    case 16:
      return 4;
    case 36:
      return 6;
    default:
      e = BCExceptionCannotHandleThisNumberOfDataRegions;
      return 0;
  }
}
int32_t CBC_SymbolInfo::getSymbolDataWidth(int32_t& e) {
  return getHorizontalDataRegions(e) * m_matrixWidth;
}
int32_t CBC_SymbolInfo::getSymbolDataHeight(int32_t& e) {
  return getVerticalDataRegions(e) * m_matrixHeight;
}
int32_t CBC_SymbolInfo::getSymbolWidth(int32_t& e) {
  return getSymbolDataWidth(e) + (getHorizontalDataRegions(e) * 2);
}
int32_t CBC_SymbolInfo::getSymbolHeight(int32_t& e) {
  return getSymbolDataHeight(e) + (getVerticalDataRegions(e) * 2);
}
int32_t CBC_SymbolInfo::getCodewordCount() {
  return m_dataCapacity + m_errorCodewords;
}
int32_t CBC_SymbolInfo::getInterleavedBlockCount() {
  return m_dataCapacity / m_rsBlockData;
}
int32_t CBC_SymbolInfo::getDataLengthForInterleavedBlock(int32_t index) {
  return m_rsBlockData;
}
int32_t CBC_SymbolInfo::getErrorLengthForInterleavedBlock(int32_t index) {
  return m_rsBlockError;
}
