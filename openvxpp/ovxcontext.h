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
#ifndef __OPENVX_CPP_VXPPCONTEXT_H__
#define __OPENVX_CPP_VXPPCONTEXT_H__

#include "common.h"
#include <string>
#include <vector>

namespace ovx
{
	class openvxdll ovxcontext final
	{
	public:
		ovxcontext(void);
		ovxcontext(ovxcontext &&contextobj) noexcept;
		ovxcontext(const ovxcontext &) = delete;
		~ovxcontext(void) noexcept;

		void operator=(const ovxcontext &) = delete;
		void operator=(ovxcontext &&obj) noexcept;

		operator vx_context(void) const noexcept;

		void release(void) noexcept;

		vx_uint16 vender(void) const;

		vx_uint16 version(void) const;

		vx_uint32 unique_kernel_count(void) const;

		std::vector<vx_kernel_info_t> unique_kernels(void) const;

		vx_uint32 module_count(void) const;

		vx_uint32 reference_count(void) const;

		std::string implementation_name(void) const;

		std::vector<std::string> extensions(void) const;

		vx_size convolution_maximum_dimension(void) const;

		vx_size optical_flow_window_maximum_dimension(void) const;

		vx_border_mode_t border_mode(void) const;

		void border_mode(const vx_border_mode_t &mode);

	private:
		vx_context m_context;
		unsigned long long m_id;
		static unsigned long long ms_context_count;
	};

	extern openvxdll ovxcontext vxcontext;
}

#endif // !__OPENVX_CPP_VXPPCONTEXT_H__
