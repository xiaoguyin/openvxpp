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
#include "ovxcontext.h"
#include "vxexcept.h"
#include <limits>
#include <regex>


namespace ovx
{
	ovxcontext vxcontext;
}


unsigned long long ovx::ovxcontext::ms_context_count = 0;


ovx::ovxcontext::ovxcontext(void)
	: m_context(::vxCreateContext())
{
	throw_if_failed(vxGetStatus(m_context));
	++ms_context_count;
	m_id = ms_context_count;
}


ovx::ovxcontext::~ovxcontext(void) noexcept
{
	::vxReleaseContext(&m_context);
	--ms_context_count;
}


ovx::ovxcontext::ovxcontext(ovxcontext &&contextobj) noexcept
	: m_context(contextobj.m_context)
{
	contextobj.m_context = nullptr;
}


void ovx::ovxcontext::operator=(ovxcontext &&obj) noexcept
{
	::vxReleaseContext(&m_context);
	m_context = obj.m_context;
	obj.m_context = nullptr;
}


ovx::ovxcontext::operator vx_context(void) const noexcept
{
	return m_context;
}


void ovx::ovxcontext::release(void) noexcept
{
	if (m_id > 1)
	{
		::vxReleaseContext(&m_context);
	}
}


vx_uint16 ovx::ovxcontext::vender(void) const
{
	vx_uint16 id = std::numeric_limits<vx_uint16>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_VENDOR_ID, &id, sizeof(id)));
	return id;
}


vx_uint16 ovx::ovxcontext::version(void) const
{
	vx_uint16 ver = std::numeric_limits<vx_uint16>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_VERSION, &ver, sizeof(ver)));
	return ver;
}


vx_uint32 ovx::ovxcontext::unique_kernel_count(void) const
{
	vx_uint32 counts = std::numeric_limits<vx_uint32>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_UNIQUE_KERNELS, &counts, sizeof(counts)));
	return counts;
}

std::vector<vx_kernel_info_t> ovx::ovxcontext::unique_kernels(void) const
{
	std::vector<vx_kernel_info_t> kernels(this->unique_kernel_count());
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_UNIQUE_KERNEL_TABLE, kernels.data(), sizeof(vx_kernel_info_t) * kernels.size()));
	return kernels;
}


vx_uint32 ovx::ovxcontext::module_count(void) const
{
	vx_uint32 counts = std::numeric_limits<vx_uint32>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_MODULES, &counts, sizeof(counts)));
	return counts;
}

vx_uint32 ovx::ovxcontext::reference_count(void) const
{
	vx_uint32 counts = std::numeric_limits<vx_uint32>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_REFERENCES, &counts, sizeof(counts)));
	return counts;
}

std::string ovx::ovxcontext::implementation_name(void) const
{
	vx_char name[VX_MAX_IMPLEMENTATION_NAME];
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_IMPLEMENTATION, name, sizeof(name)));
	return name;
}

std::vector<std::string> ovx::ovxcontext::extensions(void) const
{
	vx_size size = std::numeric_limits<vx_size>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_EXTENSIONS_SIZE, &size, sizeof(size)));

	std::vector<vx_char> strext(size);
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_EXTENSIONS, strext.data(), strext.size()));
	
	std::smatch result;
	std::string texts = strext.data();
	std::regex_match(texts, result, std::regex(R"regex([\S]+)regex"));

	std::vector<std::string> exts;
	for (auto &sub : result)
	{
		exts.push_back(sub);
	}

	return exts;
}


vx_size ovx::ovxcontext::convolution_maximum_dimension(void) const
{
	vx_size size = std::numeric_limits<vx_size>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_CONVOLUTION_MAXIMUM_DIMENSION, &size, sizeof(size)));
	return size;
}


vx_size ovx::ovxcontext::optical_flow_window_maximum_dimension(void) const
{
	vx_size size = std::numeric_limits<vx_size>::max();
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_OPTICAL_FLOW_WINDOW_MAXIMUM_DIMENSION, &size, sizeof(size)));
	return size;
}

vx_border_mode_t ovx::ovxcontext::border_mode(void) const
{
	vx_border_mode_t mode{};
	throw_if_failed(::vxQueryContext(m_context, VX_CONTEXT_ATTRIBUTE_IMMEDIATE_BORDER_MODE, &mode, sizeof(mode)));
	return mode;
}

void ovx::ovxcontext::border_mode(const vx_border_mode_t &mode)
{
	throw_if_failed(::vxSetContextAttribute(m_context, VX_CONTEXT_ATTRIBUTE_IMMEDIATE_BORDER_MODE, &mode, sizeof(mode)));
}
