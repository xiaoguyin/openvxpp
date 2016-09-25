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
#ifndef __OPENVX_CPP_FIXED_REFERENCE_HPP__
#define __OPENVX_CPP_FIXED_REFERENCE_HPP__

#include <stdexcept>
#include "image_data.hpp"

namespace ovx
{
	template <typename T>
	class fixed_reference
	{
	public:

		typedef T type;

	public:

		fixed_reference(type &ref) noexcept;
		fixed_reference(const fixed_reference &ref) noexcept;
		fixed_reference(type &&) = delete;

		fixed_reference & operator=(const fixed_reference &rhs) noexcept;

		type & operator=(const type &image);

		type & get(void) const noexcept;

		operator type&() const noexcept;

	private:
		T *m_image;
	};

	template <typename T>
	fixed_reference<T> imfix(T &elem) noexcept;

	template <typename T>
	fixed_reference<T> imfix(fixed_reference<T> &x) noexcept;

	template <typename T> void imfix(const T &&) = delete;
}

template<typename T>
inline ovx::fixed_reference<T>::fixed_reference(type &ref) noexcept
	: m_image(&ref)
{
}

template<typename T>
inline ovx::fixed_reference<T>::fixed_reference(const fixed_reference &ref) noexcept
	: m_image(ref.m_image)
{
}

template<typename T>
inline ovx::fixed_reference<T> & ovx::fixed_reference<T>::operator=(const fixed_reference &rhs) noexcept
{
	m_image = rhs.m_image;
	return *this;
}

template<typename T>
inline typename ovx::fixed_reference<T>::type & ovx::fixed_reference<T>::operator=(const type &image)
{
	if (image.width() != m_image->width() || image.height() != m_image->height())
	{
		throw std::invalid_argument("Difference size between two images.");
	}

	auto planes = image.plane_count();

	vx_rectangle_t rect{ 0, 0, image.width(), image.height() };
	for (decltype(planes) index = 0; index < planes; ++index)
	{
		image_data<void *> data(*m_image, rect, index, VX_WRITE_ONLY);
		copy_image_data(data, image, index, VX_READ_ONLY);
	}

	return *m_image;
}

template<typename T>
inline typename ovx::fixed_reference<T>::type & ovx::fixed_reference<T>::get(void) const noexcept
{
	return *m_image;
}

template<typename T>
inline ovx::fixed_reference<T>::operator type&() const noexcept
{
	return *m_image;
}

template<typename T>
ovx::fixed_reference<T> ovx::imfix(T &elem) noexcept
{
	return fixed_reference<T>(elem);
}

template<typename T>
ovx::fixed_reference<T> ovx::imfix(fixed_reference<T> &x) noexcept
{
	return fixed_reference<T>(x);
}

#endif // !__OPENVX_CPP_FIXED_REFERENCE_HPP__

