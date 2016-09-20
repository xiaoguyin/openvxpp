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
#ifndef __OPENVX_CPP_IMAGE_DATA_HPP__
#define __OPENVX_CPP_IMAGE_DATA_HPP__

#include "common.h"

namespace ovx
{
	template <typename T> class image_data;

	template <typename T>
	void copy_image_data(image_data<T> &data, vx_image image, vx_uint32 plane_index, vx_enum usage);

	template <typename T>
	class image_data
	{
	public:
		typedef T type;

	public:
		image_data(vx_image image, const vx_rectangle_t &rect, vx_uint32 plane_index, vx_enum usage);
		image_data(const image_data &) = delete;
		image_data(image_data &&) = delete;
		~image_data(void) noexcept;

		void operator=(const image_data &) = delete;
		void operator=(image_data &&) = delete;

		vx_uint32 width(void) const;
		vx_uint32 height(void) const;

		type * at(vx_uint32 n) noexcept;
		const type * at(vx_uint32 n) const noexcept;

		type * at(vx_uint32 x, vx_uint32 y) noexcept;
		const type * at(vx_uint32 x, vx_uint32 y) const noexcept;

	private:
		friend void copy_image_data<T>(image_data<T> &data, vx_image image, vx_uint32 plane_index, vx_enum usage);

	private:
		vx_image m_image;
		void *m_data;
		vx_uint32 m_index;
		std::shared_ptr<vx_imagepatch_addressing_t> m_address;
		std::shared_ptr<vx_rectangle_t> m_rect;
	};
}

template<typename T>
void ovx::copy_image_data(image_data<T> &data, vx_image image, vx_uint32 plane_index, vx_enum usage)
{
	throw_if_failed(::vxAccessImagePatch(image, data.m_rect.get(), plane_index, data.m_address.get(), &data.m_data, usage));
	throw_if_failed(::vxCommitImagePatch(image, data.m_rect.get(), plane_index, data.m_address.get(), &data.m_data));
}

template<typename T>
inline ovx::image_data<T>::image_data(vx_image image, const vx_rectangle_t &rect, vx_uint32 plane_index, vx_enum usage)
	: m_image(image)
	, m_data(nullptr)
	, m_index(plane_index)
	, m_address(std::make_shared<vx_imagepatch_addressing_t>(vx_imagepatch_addressing_t{}))
	, m_rect(std::make_shared<vx_rectangle_t>(rect))
{
	throw_if_failed(::vxAccessImagePatch(image, &rect, plane_index, m_address.get(), &m_data, usage));
}

template<typename T>
inline ovx::image_data<T>::~image_data(void) noexcept
{
	::vxCommitImagePatch(m_image, m_rect.get(), m_index, m_address.get(), m_data);
}

template<typename T>
inline vx_uint32 ovx::image_data<T>::width(void) const
{
	return m_address->dim_x;
}

template<typename T>
inline vx_uint32 ovx::image_data<T>::height(void) const
{
	return m_address->dim_y;
}

template<typename T>
inline typename ovx::image_data<T>::type * ovx::image_data<T>::at(vx_uint32 n) noexcept
{
	return static_cast<type *>(::vxFormatImagePatchAddress1d(m_data, n, m_address.get()));
}

template<typename T>
inline const typename ovx::image_data<T>::type * ovx::image_data<T>::at(vx_uint32 n) const noexcept
{
	return static_cast<const type *>(::vxFormatImagePatchAddress1d(m_data, n, m_address.get()));
}

template<typename T>
inline typename ovx::image_data<T>::type * ovx::image_data<T>::at(vx_uint32 x, vx_uint32 y) noexcept
{
	return static_cast<type *>(::vxFormatImagePatchAddress2d(m_data, x, y, m_address.get()));
}

template<typename T>
inline const typename ovx::image_data<T>::type * ovx::image_data<T>::at(vx_uint32 x, vx_uint32 y) const noexcept
{
	return static_cast<const type *>(::vxFormatImagePatchAddress2d(m_data, x, y, m_address.get()));
}

#endif // !__OPENVX_CPP_IMAGE_DATA_HPP__
