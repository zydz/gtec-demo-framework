/****************************************************************************************************************************************************
* Copyright (c) 2016 Freescale Semiconductor, Inc.
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
*    * Neither the name of the Freescale Semiconductor, Inc. nor the names of
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

#include <FslBase/Math/Extent3D.hpp>
#include <FslBase/Exceptions.hpp>
#include <FslBase/Math/Extent2D.hpp>
#include <FslBase/Math/Point2.hpp>
#include <limits>

namespace Fsl
{

  //Extent3D::Extent3D(const int32_t width, const int32_t height, const int32_t depth)
  //  : Width(static_cast<element_type>(width))
  //  , Height(static_cast<element_type>(height))
  //  , Depth(static_cast<element_type>(depth))
  //{
  //  if (width < 0 || width > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("width is out of bounds");
  //  if (height < 0 || height > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("height is out of bounds");
  //  if (depth < 0 || depth > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("height is out of bounds");
  //}


  //Extent3D::Extent3D(const uint32_t width, const uint32_t height, const uint32_t depth)
  //  : Width(static_cast<element_type>(width))
  //  , Height(static_cast<element_type>(height))
  //  , Depth(static_cast<element_type>(depth))
  //{
  //  if (width > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("width is out of bounds");
  //  if (height > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("height is out of bounds");
  //  if (depth > std::numeric_limits<Extent3D::element_type>::max())
  //    throw std::invalid_argument("height is out of bounds");
  //}


  Extent3D::Extent3D(const Point2& value, const element_type depth)
    : Extent3D(value.X, value.Y)
  {
  }

  Extent3D::Extent3D(const Extent2D& extent, const element_type depth)
    : Extent3D(extent.Width, extent.Height, depth)
  {
  }


}
