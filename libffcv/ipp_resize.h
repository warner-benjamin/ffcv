////////////////////////////////////////////////////////////////////////////////////////
//
//    From scikit-ipp's own functions for resizing images, that uses
//    Intel(R) Integrated Performance Primitives (Intel(R) IPP)
//
////////////////////////////////////////////////////////////////////////////////////////
#include <stddef.h>
#include <ipp.h>
#include <ippi.h>
#include "_ipp_util.h"

IppStatus resize_ipp(
    IppDataType ippDataType,
    void * pSrc,
    void * pDst,
    int img_width,
    int img_height,
    int dst_width,
    int dst_height,
    int numChannels,
    int antialiasing,
    IppiInterpolationType interpolation,
    IppiBorderType ippBorderType,
    double ippBorderValue);