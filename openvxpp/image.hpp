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
#ifndef __OPENVX_CPP_BASIC_IMAGE_HPP__
#define __OPENVX_CPP_BASIC_IMAGE_HPP__

#include "common.h"
#include "vxexcept.h"
#include "default_constructor.h"
#include "roi_constructor.h"
#include "imrect.h"
#include "image_data.hpp"
#include <memory>
#include <cassert>
#include <functional>
#include <limits>

namespace ovx
{
	template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
	class basic_image
	{
	public:
		typedef tdata_type data_type;

		enum class color_space
		{
			// Use to indicate that no color space is used.
			none = VX_COLOR_SPACE_NONE,

			// Use to indicate that the BT.601 coefficients and SMPTE C primaries are used for conversions.
			bt601_525 = VX_COLOR_SPACE_BT601_525,

			// Use to indicate that the BT.601 coefficients and BTU primaries are used for conversions.
			bt601_625 = VX_COLOR_SPACE_BT601_625,

			// Use to indicate that the BT.709 coefficients are used for conversions.
			bt709 = VX_COLOR_SPACE_BT709,

			// All images in VX are by default BT.709.
			default_space = VX_COLOR_SPACE_DEFAULT
		};

	public:
		basic_image(vx_uint32 width, vx_uint32 height, const ovxcontext &context = vxcontext);

		explicit basic_image(std::unique_ptr<constructor> allocator);

		basic_image(const basic_image &image);

		basic_image(basic_image &&image) noexcept;

		basic_image & operator=(const basic_image &image);

		basic_image & operator=(basic_image &&image) noexcept;

		vx_df_image color_type(void) const noexcept;

		vx_uint32 plane_count(void) const noexcept;

		vx_uint32 width(void) const noexcept;

		vx_uint32 height(void) const noexcept;

		vx_size size(void) const noexcept;

		operator vx_image(void) const noexcept;

		void space(color_space clrspace) noexcept;

		color_space space(void) const noexcept;

		basic_image roi(const imrect &rect) const;

		basic_image roi(vx_uint32 x, vx_uint32 y, vx_uint32 width, vx_uint32 height) const;

		void access(const std::function<void(image_data<tdata_type> &)> &proc);

		void access(vx_uint32 plane, const std::function<void(image_data<tdata_type> &)> &proc);

	private:
		std::unique_ptr<constructor> m_constructor;
	};

	typedef basic_image<VX_DF_IMAGE_RGB, 3, vx_uint8> image_rgb;
	
	typedef basic_image<VX_DF_IMAGE_RGBX, 4, vx_uint8> image_rgbx;

	typedef basic_image<VX_DF_IMAGE_NV12, 1, vx_uint8> image_nv12;

	typedef basic_image<VX_DF_IMAGE_NV21, 1, vx_uint8> image_nv21;

	typedef basic_image<VX_DF_IMAGE_UYVY, 4, vx_uint8> image_uyvy;

	typedef basic_image<VX_DF_IMAGE_YUYV, 4, vx_uint8> image_yuyv;

	typedef basic_image<VX_DF_IMAGE_IYUV, 1, vx_uint8> image_iyuv;

	typedef basic_image<VX_DF_IMAGE_YUV4, 1, vx_uint8> image_yuv4;

	typedef basic_image<VX_DF_IMAGE_U8, 1, vx_uint8> image_u8;

	typedef basic_image<VX_DF_IMAGE_U16, 2, vx_uint16> image_u16;

	typedef basic_image<VX_DF_IMAGE_S16, 2, vx_int16> image_s16;

	typedef basic_image<VX_DF_IMAGE_U32, 4, vx_uint32> image_u32;

	typedef basic_image<VX_DF_IMAGE_S32, 4, vx_int32> image_s32;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::basic_image(vx_uint32 width, vx_uint32 height, const ovxcontext &context)
	: m_constructor(std::make_unique<default_constructor>(width, height, tcolor_type, context))
{
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::basic_image(std::unique_ptr<constructor> allocator)
	: m_constructor(std::move(allocator))
{
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::basic_image(const basic_image &image)
	: m_constructor(std::make_unique<default_constructor>(image.width(), image.height(), tcolor_type, vxcontext))
{
	auto planes = this->plane_count();

	vx_rectangle_t rect{ 0, 0, this->width(), this->height() };
	for (decltype(planes) index = 0; index < planes; ++index)
	{
		image_data<tdata_type> data(this->m_constructor->data(), rect, index, VX_WRITE_ONLY);
		copy_image_data(data, image.m_constructor->data(), index, VX_READ_ONLY);
	}
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::basic_image(basic_image &&image) noexcept
	: m_constructor(std::move(image.m_constructor))
{
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type> & ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::operator=(const basic_image &image)
{
	m_constructor = std::make_unique<default_constructor>(image.width(), image.height(), tcolor_type, vxcontext);

	auto planes = this->plane_count();

	vx_rectangle_t rect{ 0, 0, this->width(), this->height() };
	for (decltype(planes) index = 0; index < planes; ++index)
	{
		image_data<tdata_type> data(this->m_constructor->data(), rect, index, VX_WRITE_ONLY);
		copy_image_data(data, image.m_constructor->data(), index, VX_READ_ONLY);
	}

	return *this;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type> & ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::operator=(basic_image &&image) noexcept
{
	m_constructor = std::move(image.m_constructor);
	return *this;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline vx_df_image ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::color_type(void) const noexcept
{
	return tcolor_type;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline vx_uint32 ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::plane_count(void) const noexcept
{
	vx_uint32 planes = 0;
	::vxQueryImage(m_constructor->data(), VX_IMAGE_ATTRIBUTE_PLANES, &planes, sizeof(planes));
	return planes;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline vx_uint32 ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::width(void) const noexcept
{
	vx_uint32 w = 0;
	::vxQueryImage(m_constructor->data(), VX_IMAGE_ATTRIBUTE_WIDTH, &w, sizeof(w));
	return w;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline vx_uint32 ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::height(void) const noexcept
{
	vx_uint32 h = 0;
	::vxQueryImage(m_constructor->data(), VX_IMAGE_ATTRIBUTE_HEIGHT, &h, sizeof(h));
	return h;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline vx_size ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::size(void) const noexcept
{
	vx_size s = 0;
	::vxQueryImage(m_constructor->data(), VX_IMAGE_ATTRIBUTE_SIZE, &s, sizeof(s));
	return s;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::operator vx_image(void) const noexcept
{
	return m_constructor->data();
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::space(color_space clrspace) noexcept
{
	vx_enum data = static_cast<vx_enum>(clrspace);
	::vxSetImageAttribute(m_constructor->data(), VX_IMAGE_ATTRIBUTE_SPACE, &data, sizeof(data));
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline typename ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::color_space ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::space(void) const noexcept
{
	vx_enum data = std::numeric_limits<vx_enum>::max();
	::vxQueryImage(m_constructor->data(), VX_IMAGE_ATTRIBUTE_SPACE, &data, sizeof(data));
	return data;
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type> ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::roi(const imrect &rect) const
{
	return basic_image(std::make_unique<roi_constructor>(*this, rect));
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::basic_image<tcolor_type, tpixel_size, tdata_type> ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::roi(vx_uint32 x, vx_uint32 y, vx_uint32 width, vx_uint32 height) const
{
	return basic_image(std::make_unique<roi_constructor>(*this, x, y, width, height));
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::access(const std::function<void(image_data<tdata_type>&)> &proc)
{
	this->access(0, proc);
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline void ovx::basic_image<tcolor_type, tpixel_size, tdata_type>::access(vx_uint32 plane, const std::function<void(image_data<tdata_type>&)> &proc)
{
	assert(plane < this->plane_count());

	vx_rectangle_t rect{ 0, 0, this->width(), this->height() };
	image_data<tdata_type> data(this->m_constructor->data(), rect, plane, VX_READ_AND_WRITE);

	proc(data);
}

#endif // !__OPENVX_CPP_BASIC_IMAGE_HPP__
