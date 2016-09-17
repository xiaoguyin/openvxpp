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
#ifndef __OPENVX_CPP_DEFAULT_CONSTRUCTOR_H__
#define __OPENVX_CPP_DEFAULT_CONSTRUCTOR_H__

#include "ovxcontext.h"
#include "constructor.h"

namespace ovx
{
	class openvxdll default_constructor : public constructor
	{
	public:
		default_constructor(vx_uint32 width, vx_uint32 height, vx_df_image color, const ovxcontext &context = vxcontext);
		default_constructor(default_constructor &&obj) noexcept;
		default_constructor(const default_constructor &obj) = delete;

		virtual ~default_constructor(void) noexcept;

		void operator=(const default_constructor &) = delete;
		void operator=(default_constructor &&obj) noexcept;

		void release(void) noexcept;
	};
}

#endif // !__OPENVX_CPP_DEFAULT_CONSTRUCTOR_H__

