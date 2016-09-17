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
#ifndef __OPENVX_CPP_IMRECT_H__
#define __OPENVX_CPP_IMRECT_H__

#include "common.h"

namespace ovx
{
	class openvxdll imrect : public vx_rectangle_t
	{
	public:
		imrect(void) noexcept;
		imrect(vx_uint32 left, vx_uint32 top, vx_uint32 right, vx_uint32 bottom) noexcept;
		vx_uint32 width(void) const;
		vx_uint32 height(void) const;
		vx_uint32 area(void) const;
	};
}

#endif // !__OPENVX_CPP_IMRECT_H__
