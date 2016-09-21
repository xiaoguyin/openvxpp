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
#ifndef __NOVX_OPENVX_CPP__DEVICE_HPP__
#define __NOVX_OPENVX_CPP__DEVICE_HPP__

#include "ovxcontext.h"
#include <NVX/nvx.h>

namespace novx
{
	void to_cpu(ovx::ovxcontext &context = ovx::vxcontext);
	void to_gpu(ovx::ovxcontext &context = ovx::vxcontext);
}

inline void novx::to_cpu(ovx::ovxcontext &context)
{
	vx_enum immediate_target = NVX_DEVICE_CPU;
	::vxSetContextAttribute(context, NVX_CONTEXT_ATTRIBUTE_IMMEDIATE_TARGET_DEVICE, &immediate_target, sizeof(immediate_target));
}

inline void novx::to_gpu(ovx::ovxcontext &context)
{
	vx_enum immediate_target = NVX_DEVICE_GPU;
	::vxSetContextAttribute(context, NVX_CONTEXT_ATTRIBUTE_IMMEDIATE_TARGET_DEVICE, &immediate_target, sizeof(immediate_target));
}

#endif // !__NVX_OPENVX_CPP__DEVICE_HPP__
