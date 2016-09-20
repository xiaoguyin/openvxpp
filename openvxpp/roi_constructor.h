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
#ifndef _OPENVX_CPP_ROI_CONSTRUCTOR_HPP__
#define _OPENVX_CPP_ROI_CONSTRUCTOR_HPP__

#include "constructor.h"
#include "vxexcept.h"
#include "imrect.h"

namespace ovx
{
	template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type> class basic_image;

	class openvxdll roi_constructor : public constructor
	{
	public:
		template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
		roi_constructor(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, vx_uint32 x, vx_uint32 y, vx_uint32 width, vx_uint32 height);

		template <vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
		roi_constructor(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, const imrect &rect);

		roi_constructor(roi_constructor &&obj) noexcept;
		roi_constructor(const roi_constructor &obj) = delete;

		virtual ~roi_constructor(void) noexcept;

		void operator=(const roi_constructor &) = delete;
		void operator=(roi_constructor &&obj) noexcept;

		void release(void) noexcept;
	};
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::roi_constructor::roi_constructor(const basic_image<tcolor_type, tpixel_size, tdata_type> &image, vx_uint32 x, vx_uint32 y, vx_uint32 width, vx_uint32 height)
{
	vx_rectangle_t rect{ x, y, x + width, y + height };
	m_image = ::vxCreateImageFromROI(image, &rect);
	throw_if_failed(vxGetStatus(m_image));
}

template<vx_df_image tcolor_type, vx_uint32 tpixel_size, typename tdata_type>
inline ovx::roi_constructor::roi_constructor(const basic_image<tcolor_type, tpixel_size, tdata_type>& image, const imrect & rect)
{
	m_image = ::vxCreateImageFromROI(image, &rect);
	throw_if_failed(vxGetStatus(m_image));
}

#endif // !_OPENVX_CPP_ROI_CONSTRUCTOR_HPP__

