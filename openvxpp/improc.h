/*************************************************************************
* Copyright (c) 2016, Gooeen.  All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*************************************************************************/
#ifndef __OPENVX_CPP_IMPROC_HPP__
#define __OPENVX_CPP_IMPROC_HPP__

#include "image.hpp"

namespace ovx
{
	openvxdll image_rgb to_rgb(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 to_gray(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_r(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_r(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_g(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_g(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_b(const image_rgb &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_b(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_a(const image_rgbx &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_y(const image_yuv4 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_u(const image_yuv4 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_nv12 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_nv21 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_uyvy &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_yuyv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_iyuv &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 get_channel_v(const image_yuv4 &image, const ovxcontext &context = vxcontext);

	openvxdll image_rgb to_rgb(const image_u8 &r, const image_u8 &g, const image_u8 &b, const ovxcontext &context = vxcontext);

	openvxdll image_rgbx to_rgbx(const image_u8 &r, const image_u8 &g, const image_u8 &b, const image_u8 &a, const ovxcontext &context = vxcontext);

	openvxdll image_nv12 to_nv12(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context = vxcontext);

	openvxdll image_nv21 to_nv21(const image_u8 &y, const image_u8 &v, const image_u8 &u, const ovxcontext &context = vxcontext);

	openvxdll image_uyvy to_uyvy(const image_u8 &u0, const image_u8 &y0, const image_u8 &v0, const image_u8 &y1, const ovxcontext &context = vxcontext);

	openvxdll image_yuyv to_yuyv(const image_u8 &y0, const image_u8 &u0, const image_u8 &y1, const image_u8 &v0, const ovxcontext &context = vxcontext);

	openvxdll image_iyuv to_iyuv(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context = vxcontext);

	openvxdll image_yuv4 to_yuv4(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context = vxcontext);

	openvxdll image_u8 absdiff(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context = vxcontext);

	openvxdll image_s16 absdiff(const image_s16 &image1, const image_s16 &image2, const ovxcontext &context = vxcontext);

	openvxdll void accumulate(image_s16 &accum, const image_u8 &input);

	openvxdll void square_accumulate(image_s16 &accum, const image_u8 &input, vx_uint32 shift);

	openvxdll void weight_accumulate(image_u8 &accum, const image_u8 &input, vx_float32 scale);

	openvxdll image_u8 add(const image_u8 &image1, const image_u8 &image2, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_s16 add(const image_s16 &image1, const image_s16 &image2, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_u8 subtract(const image_u8 &image1, const image_u8 &image2, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_s16 subtract(const image_s16 &image1, const image_s16 &image2, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_u8 vxand(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context = vxcontext);

	openvxdll image_u8 vxor(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context = vxcontext);

	openvxdll image_u8 vxxor(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context = vxcontext);

	openvxdll image_u8 vxnot(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 operator+(const image_u8 &image1, const image_u8 &image2);

	openvxdll void operator+=(image_u8 &image1, const image_u8 &image2);

	openvxdll image_u8 operator-(const image_u8 &image1, const image_u8 &image2);

	openvxdll void operator-=(image_u8 &image1, const image_u8 &image2);

	openvxdll image_u8 operator*(const image_u8 &image, vx_int32 number);

	openvxdll void operator*=(image_u8 &image, vx_int32 number);

	openvxdll image_u8 operator&(const image_u8 &image1, const image_u8 &image2);

	openvxdll void operator&=(image_u8 &image1, const image_u8 &image2);

	openvxdll image_u8 operator|(const image_u8 &image1, const image_u8 &image2);

	openvxdll void operator|=(image_u8 &image1, const image_u8 &image2);

	openvxdll image_u8 operator^(const image_u8 &image1, const image_u8 &image2);

	openvxdll void operator^=(image_u8 &image1, const image_u8 &image2);

	openvxdll image_u8 operator~(const image_u8 &image);

	openvxdll image_u8 to_u8(const image_s16 &image, vx_int32 shift, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_s16 to_s16(const image_u8 &image, vx_int32 shift, bool saturate = true, const ovxcontext &context = vxcontext);

	openvxdll image_u8 filter_box(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 filter_gaussian(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 filter_median(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 canny(const image_u8 &image, vx_int32 lower, vx_int32 upper, vx_int32 gradient_size = 3, bool normalization_l1 = true, const ovxcontext &context = vxcontext);

	openvxdll image_u8 dilate(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 erode(const image_u8 &image, const ovxcontext &context = vxcontext);

	openvxdll image_u8 threshold(const image_u8 &image, vx_int32 threshval, const ovxcontext &context = vxcontext);
}

#endif // !__OPENVX_CPP_IMPROC_HPP__
