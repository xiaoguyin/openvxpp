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
#include "improc.h"
#include "vxexcept.h"
#include <VX/vxu.h>
#include <cmath>


template <typename Target, typename Source>
inline Target ovx_color_convert(const Source &src, const ovx::ovxcontext &context)
{
	Target out(src.width(), src.height());
	ovx::throw_if_failed(::vxuColorConvert(context, src, out));
	return out;
}


template <typename Source>
inline ovx::image_u8 ovx_channel_extract(const Source &src, vx_enum channel, const ovx::ovxcontext &context)
{
	ovx::image_u8 out(src.width(), src.height());
	ovx::throw_if_failed(::vxuChannelExtract(context, src, channel, out));
	return out;
}


template <typename Target, typename Source>
inline Target ovx_channel_combine(const Source &plane1, const Source &plane2, const Source &plane3, const ovx::ovxcontext &context)
{
	Target out(plane1.width(), plane1.height());
	ovx::throw_if_failed(::vxuChannelCombine(context, plane1, plane2, plane3, nullptr, out));
	return out;
}


template <typename Target, typename Source>
inline Target ovx_channel_combine(const Source &plane1, const Source &plane2, const Source &plane3, const Source &plane4, const ovx::ovxcontext &context)
{
	Target out(plane1.width(), plane1.height());
	ovx::throw_if_failed(::vxuChannelCombine(context, plane1, plane2, plane3, plane4, out));
	return out;
}


template <typename T>
inline T ovx_abs_diff(const T &image1, const T &image2, const ovx::ovxcontext &context)
{
	T out(image1.width(), image1.height());
	ovx::throw_if_failed(::vxuAbsDiff(context, image1, image2, out));
	return out;
}


template <typename T>
inline T ovx_add(const T &image1, const T &image2, vx_enum policy, const ovx::ovxcontext &context)
{
	T out(image1.width(), image1.height());
	ovx::throw_if_failed(::vxuAdd(context, image1, image2, policy, out));
	return out;
}


template <typename T>
inline T ovx_subtract(const T &image1, const T &image2, vx_enum policy, const ovx::ovxcontext &context)
{
	T out(image1.width(), image1.height());
	ovx::throw_if_failed(::vxuSubtract(context, image1, image2, policy, out));
	return out;
}


ovx::image_rgb ovx::to_rgb(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgb ovx::to_rgb(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgb ovx::to_rgb(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgb ovx::to_rgb(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgb ovx::to_rgb(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgb ovx::to_rgb(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgb>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_rgb &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_rgbx>(image, context);
}


ovx::image_nv12 ovx::to_nv12(const image_rgb &image, const ovxcontext &context)
{
	return ovx_color_convert<image_nv12>(image, context);
}


ovx::image_nv12 ovx::to_nv12(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_color_convert<image_nv12>(image, context);
}


ovx::image_nv12 ovx::to_nv12(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_color_convert<image_nv12>(image, context);
}


ovx::image_nv12 ovx::to_nv12(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_nv12>(image, context);
}


ovx::image_nv12 ovx::to_nv12(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_nv12>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_rgb &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_iyuv>(image, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_rgb &image, const ovxcontext &context)
{
	return ovx_color_convert<image_yuv4>(image, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_color_convert<image_yuv4>(image, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_yuv4>(image, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_color_convert<image_yuv4>(image, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_color_convert<image_yuv4>(image, context);
}


ovx::image_u8 ovx::to_gray(const image_rgb &image, const ovxcontext &context)
{
	return ovx_color_convert<image_u8>(image, context);
}


ovx::image_u8 ovx::get_channel_r(const image_rgb &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_R, context);
}


ovx::image_u8 ovx::get_channel_r(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_R, context);
}


ovx::image_u8 ovx::get_channel_g(const image_rgb &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_G, context);
}


ovx::image_u8 ovx::get_channel_g(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_G, context);
}


ovx::image_u8 ovx::get_channel_b(const image_rgb &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_B, context);
}


ovx::image_u8 ovx::get_channel_b(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_B, context);
}


ovx::image_u8 ovx::get_channel_a(const image_rgbx &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_A, context);
}


ovx::image_u8 ovx::get_channel_y(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_y(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_y(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_y(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_y(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_y(const image_yuv4 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_Y, context);
}


ovx::image_u8 ovx::get_channel_u(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_u(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_u(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_u(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_u(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_u(const image_yuv4 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_U, context);
}


ovx::image_u8 ovx::get_channel_v(const image_nv12 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_u8 ovx::get_channel_v(const image_nv21 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_u8 ovx::get_channel_v(const image_uyvy &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_u8 ovx::get_channel_v(const image_yuyv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_u8 ovx::get_channel_v(const image_iyuv &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_u8 ovx::get_channel_v(const image_yuv4 &image, const ovxcontext &context)
{
	return ovx_channel_extract(image, VX_CHANNEL_V, context);
}


ovx::image_rgb ovx::to_rgb(const image_u8 &r, const image_u8 &g, const image_u8 &b, const ovxcontext &context)
{
	return ovx_channel_combine<image_rgb>(r, g, b, context);
}


ovx::image_rgbx ovx::to_rgbx(const image_u8 &r, const image_u8 &g, const image_u8 &b, const image_u8 &a, const ovxcontext &context)
{
	return ovx_channel_combine<image_rgbx>(r, g, b, a, context);
}


ovx::image_nv12 ovx::to_nv12(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context)
{
	return ovx_channel_combine<image_nv12>(y, u, v, context);
}


ovx::image_nv21 ovx::to_nv21(const image_u8 &y, const image_u8 &v, const image_u8 &u, const ovxcontext &context)
{
	return ovx_channel_combine<image_nv21>(y, v, u, context);
}


ovx::image_uyvy ovx::to_uyvy(const image_u8 &u0, const image_u8 &y0, const image_u8 &v0, const image_u8 &y1, const ovxcontext &context)
{
	return ovx_channel_combine<image_uyvy>(u0, y0, v0, y1, context);
}


ovx::image_yuyv ovx::to_yuyv(const image_u8 &y0, const image_u8 &u0, const image_u8 &y1, const image_u8 &v0, const ovxcontext &context)
{
	return ovx_channel_combine<image_yuyv>(y0, u0, y1, v0, context);
}


ovx::image_iyuv ovx::to_iyuv(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context)
{
	return ovx_channel_combine<image_iyuv>(y, u, v, context);
}


ovx::image_yuv4 ovx::to_yuv4(const image_u8 &y, const image_u8 &u, const image_u8 &v, const ovxcontext &context)
{
	return ovx_channel_combine<image_yuv4>(y, u, v, context);
}


ovx::image_u8 ovx::absdiff(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context)
{
	return ovx_abs_diff(image1, image2, context);
}


ovx::image_s16 ovx::absdiff(const image_s16 &image1, const image_s16 &image2, const ovxcontext &context)
{
	return ovx_abs_diff(image1, image2, context);
}


void ovx::accumulate(image_s16 &accum, const image_u8 &input)
{
	throw_if_failed(::vxuAccumulateImage(vxcontext, input, accum));
}


void ovx::square_accumulate(image_s16 &accum, const image_u8 &input, vx_uint32 shift)
{
	std::shared_ptr<_vx_scalar> scalar(::vxCreateScalar(vxcontext, VX_TYPE_UINT32, &shift), [](vx_scalar p)
	{
		::vxReleaseScalar(&p);
	});
	throw_if_failed(vxGetStatus(scalar.get()));
	throw_if_failed(::vxuAccumulateSquareImage(vxcontext, input, scalar.get(), accum));
}


void ovx::weight_accumulate(image_u8 &accum, const image_u8 &input, vx_float32 scale)
{
	std::shared_ptr<_vx_scalar> scalar(::vxCreateScalar(vxcontext, VX_TYPE_FLOAT32, &scale), [](vx_scalar p)
	{
		::vxReleaseScalar(&p);
	});
	throw_if_failed(vxGetStatus(scalar.get()));
	throw_if_failed(::vxuAccumulateWeightedImage(vxcontext, input, scalar.get(), accum));
}


ovx::image_u8 ovx::add(const image_u8 &image1, const image_u8 &image2, bool saturate, const ovxcontext &context)
{
	return ovx_add(image1, image2, saturate ? VX_CONVERT_POLICY_SATURATE : VX_CONVERT_POLICY_WRAP, context);
}


ovx::image_s16 ovx::add(const image_s16 &image1, const image_s16 &image2, bool saturate, const ovxcontext &context)
{
	return ovx_add(image1, image2, saturate ? VX_CONVERT_POLICY_SATURATE : VX_CONVERT_POLICY_WRAP, context);
}


ovx::image_u8 ovx::subtract(const image_u8 &image1, const image_u8 &image2, bool saturate, const ovxcontext &context)
{
	return ovx_subtract(image1, image2, saturate ? VX_CONVERT_POLICY_SATURATE : VX_CONVERT_POLICY_WRAP, context);
}


ovx::image_s16 ovx::subtract(const image_s16 &image1, const image_s16 &image2, bool saturate, const ovxcontext &context)
{
	return ovx_subtract(image1, image2, saturate ? VX_CONVERT_POLICY_SATURATE : VX_CONVERT_POLICY_WRAP, context);
}


ovx::image_u8 ovx::and(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context)
{
	image_u8 out(image1.width(), image1.height());
	throw_if_failed(::vxuAnd(context, image1, image2, out));
	return out;
}


ovx::image_u8 ovx::or(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context)
{
	image_u8 out(image1.width(), image1.height());
	throw_if_failed(::vxuOr(context, image1, image2, out));
	return out;
}


ovx::image_u8 ovx::xor(const image_u8 &image1, const image_u8 &image2, const ovxcontext &context)
{
	image_u8 out(image1.width(), image1.height());
	throw_if_failed(::vxuXor(context, image1, image2, out));
	return out;
}


ovx::image_u8 ovx::not(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuNot(context, image, out));
	return out;
}


ovx::image_u8 ovx::operator+(const image_u8 &image1, const image_u8 &image2)
{
	return add(image1, image2);
}


void ovx::operator+=(image_u8 &image1, const image_u8 &image2)
{
	image1 = add(image1, image2);
}


ovx::image_u8 ovx::operator-(const image_u8 &image1, const image_u8 &image2)
{
	return subtract(image1, image2);
}


void ovx::operator-=(image_u8 &image1, const image_u8 &image2)
{
	image1 = subtract(image1, image2);
}


ovx::image_u8 ovx::operator*(const image_u8 &image, vx_int32 number)
{
	if (number == 0)
	{
		return subtract(image, image);
	}

	if (number == 1)
	{
		return image;
	}

	if (number == -1)
	{
		return not(image);
	}

	image_u8 out(image.width(), image.height());
	for (vx_int32 i = 1; i < std::abs(number); ++i)
	{
		out = add(image, image);
	}

	return number < 0 ? not(image) : image;
}


void ovx::operator*=(image_u8 &image, vx_int32 number)
{
	image = image * number;
}


ovx::image_u8 ovx::operator&(const image_u8 &image1, const image_u8 &image2)
{
	return and(image1, image2);
}


void ovx::operator&=(image_u8 &image1, const image_u8 &image2)
{
	image1 = and(image1, image2);
}


ovx::image_u8 ovx::operator|(const image_u8 &image1, const image_u8 &image2)
{
	return or(image1, image2);
}


void ovx::operator|=(image_u8 &image1, const image_u8 &image2)
{
	image1 = or(image1, image2);
}


ovx::image_u8 ovx::operator^(const image_u8 &image1, const image_u8 &image2)
{
	return xor(image1, image2);
}


void ovx::operator^=(image_u8 &image1, const image_u8 &image2)
{
	image1 = xor(image1, image2);
}


ovx::image_u8 ovx::operator~(const image_u8 &image)
{
	return not(image);
}


ovx::image_u8 ovx::to_u8(const image_s16 &image, vx_int32 shift, bool saturate, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuConvertDepth(context, image, out, saturate, shift));
	return out;
}


ovx::image_s16 ovx::to_s16(const image_u8 &image, vx_int32 shift, bool saturate, const ovxcontext &context)
{
	image_s16 out(image.width(), image.height());
	throw_if_failed(::vxuConvertDepth(context, image, out, saturate, shift));
	return out;
}


ovx::image_u8 ovx::filter_box(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuBox3x3(context, image, out));
	return out;
}


ovx::image_u8 ovx::filter_gaussian(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuGaussian3x3(context, image, out));
	return out;
}

ovx::image_u8 ovx::filter_median(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuMedian3x3(context, image, out));
	return out;
}


ovx::image_u8 ovx::canny(const image_u8 &image, vx_int32 lower, vx_int32 upper, vx_int32 gradient_size, bool normalization_l1, const ovxcontext &context)
{
	std::shared_ptr<_vx_threshold> thresh(::vxCreateThreshold(vxcontext, VX_THRESHOLD_TYPE_RANGE, VX_TYPE_INT32), [](vx_threshold p)
	{
		::vxReleaseThreshold(&p);
	});
	throw_if_failed(vxGetStatus(thresh.get()));

	throw_if_failed(::vxSetThresholdAttribute(thresh.get(), VX_THRESHOLD_ATTRIBUTE_THRESHOLD_LOWER, &lower, sizeof(lower)));
	throw_if_failed(::vxSetThresholdAttribute(thresh.get(), VX_THRESHOLD_ATTRIBUTE_THRESHOLD_UPPER, &upper, sizeof(upper)));

	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuCannyEdgeDetector(context, image, thresh.get(), gradient_size, normalization_l1 ? VX_NORM_L1 : VX_NORM_L2, out));
	return out;
}


ovx::image_u8 ovx::dilate(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuDilate3x3(context, image, out));
	return out;
}


ovx::image_u8 ovx::erode(const image_u8 &image, const ovxcontext &context)
{
	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuErode3x3(context, image, out));
	return out;
}


ovx::image_u8 ovx::threshold(const image_u8 &image, vx_int32 threshval, const ovxcontext &context)
{
	std::shared_ptr<_vx_threshold> thresh(::vxCreateThreshold(vxcontext, VX_THRESHOLD_TYPE_BINARY, VX_TYPE_INT32), [](vx_threshold p)
	{
		::vxReleaseThreshold(&p);
	});
	throw_if_failed(vxGetStatus(thresh.get()));

	throw_if_failed(::vxSetThresholdAttribute(thresh.get(), VX_THRESHOLD_ATTRIBUTE_THRESHOLD_VALUE, &threshval, sizeof(threshval)));

	image_u8 out(image.width(), image.height());
	throw_if_failed(::vxuThreshold(context, image, thresh.get(), out));
	return out;
}
