/*******************************************************************************
* Copyright (c) 2020, Intel Corporation
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of Intel Corporation nor the names of its contributors
*       may be used to endorse or promote products derived from this software
*       without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef _IPP_UTIL_H
#define _IPP_UTIL_H
#include <stddef.h>
#include <ipp.h>
#include <ippi.h>


IppStatus
get_sizeof(
    IppDataType datatype,
    int * sizeof_datatype);


////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeGetSize_<mode> function, where <mode> is:
//    8u, 16u, 16s or 32f.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeGetSize(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    IppiInterpolationType interpolation,
    Ipp32u antialiasing,
    int* pSpecSize,
    int* pInitBufSize);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeGetBufferSize_<mode> function, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeGetBufferSize(
    IppDataType ippDataType,
    const IppiResizeSpec_32f* pSpec,
    IppiSize dstSize,
    Ipp32u numChannels,
    int* pBufSize);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeGetSrcRoi_<mode> function, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeGetSrcRoi(
    IppDataType ippDataType,
    const IppiResizeSpec_32f* pSpec,
    IppiPoint dstRoiOffset,
    IppiSize dstRoiSize,
    IppiPoint* srcRoiOffset,
    IppiSize* srcRoiSize);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeGetBorderSize_<mode> function, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeGetBorderSize(
    IppDataType ippDataType,
    const IppiResizeSpec_32f* pSpec,
    IppiBorderSize* borderSize);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeNearest, ippiResizeLinear and ippiResizeCubic
//    functions.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResize(IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    IppiBorderType border,
    void * pBorderValue,
    IppiInterpolationType interpolation,
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeAntialiasing_<mode> function, where <mode>
//    is: 8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R,
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeAntialiasing(
    IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    IppiBorderType border,
    void * pBorderValue,
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeLinear_<mode> functions, where <mode> is
//    8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeLinear(IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    IppiBorderType border,
    void * pBorderValue,               // TODO
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeNearest_<mode> functions, where <mode> is
//    8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeNearest(IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeCubic_<mode> functions, where <mode> is
//    8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R.
//
//    Note: currently ipp64f is not supported. TODO implement this.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeCubic(IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    IppiBorderType border,
    void * pBorderValue,
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeLanczos_<mode> functions, where <mode> is
//    8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeLanczos(
    IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    IppiBorderType border,
    void * pBorderValue,               // TODO
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeSuper_<mode> functions, where <mode> is
//    8uC1R, 16uC1R, 16sC1R, 32fC1R, 8uC3R, 16uC3R, 16sC3R or 32fC3R, 8uC4R, 16uC4R,
//    16sC4R or 32fC4R.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeSuper(
    IppDataType ippDataType,
    void * pSrc,
    Ipp32s srcStep,
    void * pDst,
    Ipp32s dstStep,
    IppiPoint dstOffset,
    IppiSize dstSize,
    int numChannels,
    const IppiResizeSpec_32f* pSpec,
    Ipp8u* pBuffer);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeNearestInit_<mode> functions, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeNearestInit(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    IppiResizeSpec_32f* pSpec);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeLinearInit_<mode> functions, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeLinearInit(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    IppiResizeSpec_32f* pSpec);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeLanczosInit_<mode> functions, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeLanczosInit(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    Ipp32u numLobes,
    IppiResizeSpec_32f* pSpec,
    Ipp8u* pInitBuf);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeCubicInit_<mode> functions, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeCubicInit(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    Ipp32f valueB,
    Ipp32f valueC,
    IppiResizeSpec_32f* pSpec,
    Ipp8u* pInitBuf);

////////////////////////////////////////////////////////////////////////////////////////
//
//    Adapter for ippiResizeSuperInit_<mode> functions, where <mode>
//    is: 8u, 16u, 16s or 32f.
//
////////////////////////////////////////////////////////////////////////////////////////
IppStatus
ippiResizeSuperInit(
    IppDataType ippDataType,
    IppiSize srcSize,
    IppiSize dstSize,
    IppiResizeSpec_32f* pSpec);
#endif  // _IPP_UTIL_H
