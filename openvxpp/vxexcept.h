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
#ifndef __OPENVX_CPP_VXEXCEPT_H__
#define __OPENVX_CPP_VXEXCEPT_H__

#include "common.h"
#include <exception>

#define vx_throw_if_failed(status)\
{\
	const auto vx_throw_if_failed_result = status;\
	if (vx_throw_if_failed_result != VX_SUCCESS)\
	{\
		throw ::ovx::exception_from_status(vx_throw_if_failed_result);\
	}\
}

namespace ovx
{
	openvxdll std::exception exception_from_status(vx_status err) noexcept;
}

#endif // !__OPENVX_CPP_VXEXCEPT_H__
