/****************************************************************************************************************************************************
* Copyright 2017 NXP
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*    * Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*
*    * Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*
*    * Neither the name of the NXP. nor the names of
*      its contributors may be used to endorse or promote products derived from
*      this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
****************************************************************************************************************************************************/

#include <Shared/OpenCVExperimental/BasicImageConvert.hpp>
#include <FslBase/Exceptions.hpp>
#include <FslGraphics/Bitmap/BitmapUtil.hpp>
#include <FslGraphics/PixelFormatUtil.hpp>
#include <cassert>
#include <opencv2/opencv.hpp>

namespace Fsl
{
  namespace
  {
    // See http://docs.opencv.org/java/2.4.9/org/opencv/core/CvType.html
    PixelFormat ConvertToPixelFormat(const cv::Mat& src)
    {
      switch (src.type())
      {
      case CV_8UC3:
        // FIX: this is way too simplistic
        return PixelFormat::B8G8R8_UINT;
      default:
        throw NotSupportedException("The cv::mat pixel format is unsupported");
      }
    }
  }

  void BasicImageConvert::Convert(Bitmap& rDst, const cv::Mat& src, const PixelFormat desiredPixelFormat, const BitmapOrigin desiredBitmapOrigin)
  {
    if (!src.isContinuous())
      throw NotSupportedException("The cv::Mat was not continuous");
    if (src.channels() != 3)
      throw NotSupportedException("The cv::Mat did not contain the supported amount of channel");
    if (src.dims != 2)
      throw NotSupportedException("The cv::Mat did not contain a 2D image");
    if(src.depth() != CV_8U)
      throw NotSupportedException("The cv::Mat did contain a supported depth");

    const auto srcPixelFormat = ConvertToPixelFormat(src);
    if( PixelFormatUtil::GetPixelFormatLayout(srcPixelFormat) != PixelFormatLayout::B8G8R8 )
      throw NotSupportedException("Source pixel format is unsupported");

    // FIX: this should verify the 'src' cv::Mat image format
    RawBitmap rawSrcBitmap(src.data, src.cols, src.rows, PixelFormat::B8G8R8_UINT, BitmapOrigin::UpperLeft);

    rDst.Reset(rawSrcBitmap);
    // FIX: ideally this would utilize the demo framework conversion service instead to support more formats
    BitmapUtil::Convert(rDst, desiredPixelFormat);

    if (desiredBitmapOrigin == BitmapOrigin::LowerLeft )
      BitmapUtil::FlipHorizontal(rDst);
  }


  void BasicImageConvert::Convert(cv::Mat& rDst, const Bitmap& src, const PixelFormat desiredPixelFormat, const BitmapOrigin desiredBitmapOrigin)
  {
    if (PixelFormatUtil::GetPixelFormatLayout(desiredPixelFormat) != PixelFormatLayout::B8G8R8)
      throw NotSupportedException("We only support the pixel format PixelFormatLayout::B8G8R8");

    // This method is monster slow :)

    Bitmap imageCopy(src);
    if (imageCopy.GetPixelFormat() != desiredPixelFormat)
    {
      // FIX: ideally this would utilize the demo framework conversion service instead to support more formats
      BitmapUtil::Convert(imageCopy, PixelFormat::B8G8R8_UINT);
    }

    if (imageCopy.GetOrigin() != desiredBitmapOrigin)
      BitmapUtil::FlipHorizontal(imageCopy);

    // FIX: this should ideally support multiple output formats not just B8G8R8_UINT
    rDst.create(imageCopy.Height(), imageCopy.Width(), CV_8UC3);


    RawBitmap srcBitmap;
    Bitmap::ScopedDirectAccess access(imageCopy, srcBitmap);
    RawBitmapEx rawSrcBitmap(rDst.data, rDst.cols, rDst.rows, PixelFormat::B8G8R8_UINT, BitmapOrigin::UpperLeft);

    const uint8_t* pSrc = static_cast<const uint8_t*>(srcBitmap.Content());
    uint8_t* pDst = static_cast<uint8_t*>(rawSrcBitmap.Content());
    const int32_t srcStride = srcBitmap.Stride();
    const int32_t dstStride = rawSrcBitmap.Stride();

    for (uint32_t y = 0; y < srcBitmap.Height(); ++y)
    {
      for (uint32_t x = 0; x < (srcBitmap.Width() * 3); ++x)
      {
        pDst[x + (y * dstStride)] = pSrc[x + (y * srcStride)];
      }
    }
  }


}
