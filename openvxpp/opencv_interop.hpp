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
#ifndef _OPENVX_CPP_OPENCV_INTEROP_HPP__
#define _OPENVX_CPP_OPENCV_INTEROP_HPP__

#include "ovxcontext.h"
#include "constructor.h"
#include "nvx_opencv_interop.hpp"
#include "image.hpp"
#include <utility>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <functional>

namespace ovx
{
	class mat_constructor : public constructor
	{
	public:
		explicit mat_constructor(const cv::Mat &mat, const ovxcontext &context = vxcontext);
		explicit mat_constructor(cv::Mat &&mat, const ovxcontext &context = vxcontext);
		mat_constructor(vx_uint32 width, vx_uint32 height, vx_df_image color, const ovxcontext &context = vxcontext);
		mat_constructor(mat_constructor &&obj) noexcept;
		mat_constructor(const mat_constructor &obj) = delete;

		virtual ~mat_constructor(void) noexcept;

		void operator=(const mat_constructor &) = delete;
		void operator=(mat_constructor &&obj) noexcept;

		void release(void) noexcept;
		
	private:
		cv::Mat m_mat;
	};

	image_rgb make_rgb(const cv::Mat &mat);

	image_rgb make_rgb(cv::Mat &&mat);

	image_rgb make_to_rgb(const cv::Mat &mat);

	image_rgb make_to_rgb(cv::Mat &&mat);

	image_u8 make_u8(const cv::Mat &mat);

	image_u8 make_u8(cv::Mat &&mat);

	image_rgbx make_rgbx(const cv::Mat &mat);

	image_rgbx make_rgbx(cv::Mat &&mat);

	image_u16 make_u16(const cv::Mat &mat);

	image_u16 make_u16(cv::Mat &&mat);

	image_s16 make_s16(const cv::Mat &mat);

	image_s16 make_s16(cv::Mat &&mat);

	image_s32 make_s32(const cv::Mat &mat);

	image_s32 make_s32(cv::Mat &&mat);

	image_u32 make_u32(const cv::Mat &mat);

	image_u32 make_u32(cv::Mat &&mat);

	image_yuv4 make_yuv4(const cv::Mat &mat);

	image_yuv4 make_yuv4(cv::Mat &&mat);

	image_iyuv make_iyuv(const cv::Mat &mat);

	image_iyuv make_iyuv(cv::Mat &&mat);

	image_uyvy make_uyvy(const cv::Mat &mat);

	image_uyvy make_uyvy(cv::Mat &&mat);

	image_yuyv make_yuyv(const cv::Mat &mat);

	image_yuyv make_yuyv(cv::Mat &&mat);

	template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
	void lock_to_mat(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, const std::function<void(cv::Mat &mat)> &proc, vx_uint32 plane_index = 0, const vx_rectangle_t *rect = nullptr, vx_enum usage = VX_READ_AND_WRITE, vx_enum memory_type = VX_IMPORT_TYPE_HOST);

	template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
	void lock_to_gpu_mat(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, const std::function<void(cv::cuda::GpuMat &mat)> &proc, vx_uint32 plane_index = 0, const vx_rectangle_t *rect = nullptr, vx_enum usage = VX_READ_AND_WRITE, vx_enum memory_type = VX_IMPORT_TYPE_HOST);
}

namespace cv
{
	template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
	void imshow(const String &winname, const ovx::basic_image<tcolor_type, tpixel_size, tdata_type> &image, vx_uint32 plane_index = 0, const vx_rectangle_t *rect = nullptr);
}

inline ovx::mat_constructor::mat_constructor(const cv::Mat &mat, const ovxcontext &context)
	: m_mat(mat.clone())
{
	m_image = nvx_cv::createVXImageFromCVMat(context, m_mat);

	vx_enum color_space = VX_COLOR_SPACE_BT601_625;
	::vxSetImageAttribute(m_image, VX_IMAGE_ATTRIBUTE_SPACE, &color_space, sizeof(color_space));
}

inline ovx::mat_constructor::mat_constructor(cv::Mat &&mat, const ovxcontext &context)
	: m_mat(std::move(mat))
{
	m_image = nvx_cv::createVXImageFromCVMat(context, m_mat);

	vx_enum color_space = VX_COLOR_SPACE_BT601_625;
	::vxSetImageAttribute(m_image, VX_IMAGE_ATTRIBUTE_SPACE, &color_space, sizeof(color_space));

	mat.release();
}

inline ovx::mat_constructor::mat_constructor(vx_uint32 width, vx_uint32 height, vx_df_image color, const ovxcontext &context)
	: mat_constructor(cv::Mat(height, width, nvx_cv::convertVXImageFormatToCVMatType(color)), context)
{
}

inline ovx::mat_constructor::mat_constructor(mat_constructor &&obj) noexcept
	: m_mat(obj.m_mat)
{
	m_image = obj.m_image;
	obj.m_image = nullptr;
	obj.m_mat.release();
}

inline ovx::mat_constructor::~mat_constructor(void) noexcept
{
	this->release();
}

inline void ovx::mat_constructor::operator=(mat_constructor &&obj) noexcept
{
	this->release();

	m_mat = obj.m_mat;
	m_image = obj.m_image;

	obj.m_image = nullptr;
	obj.m_mat.release();
}

inline void ovx::mat_constructor::release(void) noexcept
{
	::vxReleaseImage(&m_image);
	m_mat.release();
}

inline ovx::image_rgb ovx::make_rgb(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC3)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to RGB OpenVX image.");
	}
	return image_rgb(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_rgb ovx::make_rgb(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC3)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX RGB image.");
	}
	return image_rgb(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_rgb ovx::make_to_rgb(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC3)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX RGB image.");
	}
	cv::cvtColor(mat, mat, cv::ColorConversionCodes::COLOR_BGR2RGB);
	return image_rgb(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_rgb ovx::make_to_rgb(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC3)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX RGB image.");
	}
	cv::cvtColor(mat, mat, cv::ColorConversionCodes::COLOR_BGR2RGB);
	return image_rgb(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_u8 ovx::make_u8(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX U8 image.");
	}
	return image_u8(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_u8 ovx::make_u8(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX U8 image.");
	}
	return image_u8(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_rgbx ovx::make_rgbx(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC4)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX RGBX image.");
	}
	return image_rgbx(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_rgbx ovx::make_rgbx(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC4)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX RGBX image.");
	}
	return image_rgbx(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_u16 ovx::make_u16(const cv::Mat &mat)
{
	if (mat.type() != CV_16UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX U16 image.");
	}
	return image_u16(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_u16 ovx::make_u16(cv::Mat &&mat)
{
	if (mat.type() != CV_16UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX U16 image.");
	}
	return image_u16(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_s16 ovx::make_s16(const cv::Mat &mat)
{
	if (mat.type() != CV_16SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX S16 image.");
	}
	return image_s16(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_s16 ovx::make_s16(cv::Mat &&mat)
{
	if (mat.type() != CV_16SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX S16 image.");
	}
	return image_s16(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_s32 ovx::make_s32(const cv::Mat &mat)
{
	if (mat.type() != CV_32SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX S32 image.");
	}
	return image_s32(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_s32 ovx::make_s32(cv::Mat &&mat)
{
	if (mat.type() != CV_32SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX S32 image.");
	}
	return image_s32(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_u32 ovx::make_u32(const cv::Mat &mat)
{
	if (mat.type() != CV_32SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to U32 OpenVX image.");
	}
	return image_u32(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_u32 ovx::make_u32(cv::Mat &&mat)
{
	if (mat.type() != CV_32SC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX U32 image.");
	}
	return image_u32(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_yuv4 ovx::make_yuv4(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX YUV4 image.");
	}
	return image_yuv4(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_yuv4 ovx::make_yuv4(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX YUV4 image.");
	}
	return image_yuv4(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_iyuv ovx::make_iyuv(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX IYUV image.");
	}
	return image_iyuv(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_iyuv ovx::make_iyuv(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC1)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX IYUV image.");
	}
	return image_iyuv(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_uyvy ovx::make_uyvy(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC2)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX UYVY image.");
	}
	return image_uyvy(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_uyvy ovx::make_uyvy(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC2)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX UYVY image.");
	}
	return image_uyvy(std::make_unique<mat_constructor>(std::move(mat)));
}

inline ovx::image_yuyv ovx::make_yuyv(const cv::Mat &mat)
{
	if (mat.type() != CV_8UC2)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX YUYV image.");
	}
	return image_yuyv(std::make_unique<mat_constructor>(mat));
}

inline ovx::image_yuyv ovx::make_yuyv(cv::Mat &&mat)
{
	if (mat.type() != CV_8UC2)
	{
		CV_Error(CV_StsBadArg, "The type of cv::Mat can't be converted to OpenVX YUYV image.");
	}
	return image_yuyv(std::make_unique<mat_constructor>(std::move(mat)));
}

template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void ovx::lock_to_mat(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, const std::function<void(cv::Mat &mat)> &proc, vx_uint32 plane_index, const vx_rectangle_t *rect, vx_enum usage, vx_enum memory_type)
{
	nvx_cv::VXImageToCVMatMapper mapper(image, plane_index, rect, usage, memory_type);
	auto mat = mapper.getMat();
	proc(mat);
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void ovx::lock_to_gpu_mat(const basic_image<tcolor_type, tpixel_size, tdata_type>& image, const std::function<void(cv::cuda::GpuMat&mat)>& proc, vx_uint32 plane_index, const vx_rectangle_t * rect, vx_enum usage, vx_enum memory_type)
{
	nvx_cv::VXImageToCVMatMapper mapper(image, plane_index, rect, usage, memory_type);
	auto mat = mapper.getGpuMat();
	proc(mat);
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void cv::imshow(const String &winname, const ovx::basic_image<tcolor_type, tpixel_size, tdata_type> &image, vx_uint32 plane_index, const vx_rectangle_t *rect)
{
	nvx_cv::VXImageToCVMatMapper mapper(image, plane_index, rect);
	cv::imshow(winname, mapper.getMat());
}

#endif // !_OPENVX_CPP_OPENCV_INTEROP_HPP__
