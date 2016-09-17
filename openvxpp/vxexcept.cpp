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
#include "vxexcept.h"
#include <stdexcept>


std::exception ovx::exception_from_status(vx_status err) noexcept
{
	vx_status_e error = (vx_status_e)err;

	switch (error)
	{
	case VX_STATUS_MIN:
		return std::out_of_range(R"(The lower bound of status codes in VX.)");
	case VX_ERROR_REFERENCE_NONZERO:
		return std::logic_error(R"(An operation did not complete due to a reference count being non-zero.)");
	case VX_ERROR_MULTIPLE_WRITERS:
		return std::logic_error(R"(The graph has more than one node outputting to the same data object. This is an invalid graph structure.)");
	case VX_ERROR_GRAPH_ABANDONED:
		return std::runtime_error(R"(The graph is stopped due to an error or a callback that abandoned execution.)");
	case VX_ERROR_GRAPH_SCHEDULED:
		return std::invalid_argument(R"(The supplied graph already has been scheduled and may be currently executing.)");
	case VX_ERROR_INVALID_SCOPE:
		return std::invalid_argument(R"(The supplied parameter is from another scope and cannot be used in the current scope.)");
	case VX_ERROR_INVALID_NODE:
		return std::invalid_argument(R"(The supplied node could not be created.)");
	case VX_ERROR_INVALID_GRAPH:
		return std::invalid_argument(R"(The supplied graph has invalid connections (cycles).)");
	case VX_ERROR_INVALID_TYPE:
		return std::invalid_argument(R"(The supplied type parameter is incorrect.)");
	case VX_ERROR_INVALID_VALUE:
		return std::invalid_argument(R"(The supplied parameter has an incorrect value.)");
	case VX_ERROR_INVALID_DIMENSION:
		return std::out_of_range(R"(The supplied parameter is too big or too small in dimension.)");
	case VX_ERROR_INVALID_FORMAT:
		return std::invalid_argument(R"(The supplied parameter is in an invalid format.)");
	case VX_ERROR_INVALID_LINK:
		return std::invalid_argument(R"(The link is not possible as specified. The parameters are incompatible.)");
	case VX_ERROR_INVALID_REFERENCE:
		return std::invalid_argument(R"(The reference provided is not valid.)");
	case VX_ERROR_INVALID_MODULE:
		return std::runtime_error(R"(This is returned from vxLoadKernels when the module does not contain the entry point.)");
	case VX_ERROR_INVALID_PARAMETERS:
		return std::invalid_argument(R"(The supplied parameter information does not match the kernel contract.)");
	case VX_ERROR_OPTIMIZED_AWAY:
		return std::runtime_error(R"(The object refered to has been optimized out of existence.)");
	case VX_ERROR_NO_MEMORY:
		return std::runtime_error(R"(An internal or implicit allocation failed. Typically catastrophic. After detection, deconstruct the context.)");
	case VX_ERROR_NO_RESOURCES:
		return std::runtime_error(R"(An internal or implicit resource can not be acquired (not memory). This is typically catastrophic. After detection, deconstruct the context.)");
	case VX_ERROR_NOT_COMPATIBLE:
		return std::runtime_error(R"(The attempt to link two parameters together failed due to type incompatibilty.)");
	case VX_ERROR_NOT_ALLOCATED:
		return std::runtime_error(R"(To the system that the parameter must be allocated by the system.)");
	case VX_ERROR_NOT_SUFFICIENT:
		return std::runtime_error(R"(The given graph has failed verification due to an insufficient number of required parameters, which cannot be automatically created. Typically this indicates required atomic parameters.)");
	case VX_ERROR_NOT_SUPPORTED:
		return std::runtime_error(R"(The requested set of parameters produce a configuration that cannot be supported. Refer to the supplied documentation on the configured kernels.)");
	case VX_ERROR_NOT_IMPLEMENTED:
		return std::runtime_error(R"(The requested kernel is missing.)");
	case VX_FAILURE:
		return std::runtime_error(R"(A generic error code, used when no other describes the error.)");
	default:
		return std::exception();
	}
}
