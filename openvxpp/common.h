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
#ifndef __OPENVX_CPP_COMMON_H__
#define __OPENVX_CPP_COMMON_H__

#include <VX/vx.h>
#include <memory>

#ifdef _MSC_VER

#ifdef OPENVXPP_EXPORTS
#define openvxdll __declspec(dllexport)
#else
#define openvxdll __declspec(dllimport)
#endif // OPENVXPP_EXPORTS

#else

#define openvxdll

#ifndef NOT_SUPPORT_CPP14
namespace std
{
	template <typename T, typename ...Args>
	inline std::unique_ptr<T> make_unique(Args && ...params)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(params)...));
	}
}
#endif // !NOT_SUPPORT_CPP14

#endif // _MSC_VER

namespace ovx
{
	template <typename T>
	vx_status vxGetStatus(T t) noexcept;
}

template<typename T>
vx_status ovx::vxGetStatus(T t) noexcept
{
	return ::vxGetStatus(reinterpret_cast<vx_reference>(t));
}

#endif // !__OPENVX_CPP_COMMON_H__