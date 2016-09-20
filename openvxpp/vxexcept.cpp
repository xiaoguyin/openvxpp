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


void ovx::throw_if_failed(vx_status err)
{
	vx_status_e error = (vx_status_e)err;

	switch (error)
	{
	case VX_STATUS_MIN:
		throw std::out_of_range(R"(The lower bound of status codes in VX.)");
		break;
	case VX_ERROR_REFERENCE_NONZERO:
		throw std::logic_error(R"(An operation did not complete due to a reference count being non-zero.)");
		break;
	case VX_ERROR_MULTIPLE_WRITERS:
		throw std::logic_error(R"(The graph has more than one node outputting to the same data object. This is an invalid graph structure.)");
		break;
	case VX_ERROR_GRAPH_ABANDONED:
		throw std::runtime_error(R"(The graph is stopped due to an error or a callback that abandoned execution.)");
		break;
	case VX_ERROR_GRAPH_SCHEDULED:
		throw std::invalid_argument(R"(The supplied graph already has been scheduled and may be currently executing.)");
		break;
	case VX_ERROR_INVALID_SCOPE:
		throw std::invalid_argument(R"(The supplied parameter is from another scope and cannot be used in the current scope.)");
		break;
	case VX_ERROR_INVALID_NODE:
		throw std::invalid_argument(R"(The supplied node could not be created.)");
		break;
	case VX_ERROR_INVALID_GRAPH:
		throw std::invalid_argument(R"(The supplied graph has invalid connections (cycles).)");
		break;
	case VX_ERROR_INVALID_TYPE:
		throw std::invalid_argument(R"(The supplied type parameter is incorrect.)");
		break;
	case VX_ERROR_INVALID_VALUE:
		throw std::invalid_argument(R"(The supplied parameter has an incorrect value.)");
		break;
	case VX_ERROR_INVALID_DIMENSION:
		throw std::out_of_range(R"(The supplied parameter is too big or too small in dimension.)");
		break;
	case VX_ERROR_INVALID_FORMAT:
		throw std::invalid_argument(R"(The supplied parameter is in an invalid format.)");
		break;
	case VX_ERROR_INVALID_LINK:
		throw std::invalid_argument(R"(The link is not possible as specified. The parameters are incompatible.)");
		break;
	case VX_ERROR_INVALID_REFERENCE:
		throw std::invalid_argument(R"(The reference provided is not valid.)");
		break;
	case VX_ERROR_INVALID_MODULE:
		throw std::runtime_error(R"(This is returned from vxLoadKernels when the module does not contain the entry point.)");
		break;
	case VX_ERROR_INVALID_PARAMETERS:
		throw std::invalid_argument(R"(The supplied parameter information does not match the kernel contract.)");
		break;
	case VX_ERROR_OPTIMIZED_AWAY:
		throw std::runtime_error(R"(The object refered to has been optimized out of existence.)");
		break;
	case VX_ERROR_NO_MEMORY:
		throw std::runtime_error(R"(An internal or implicit allocation failed. Typically catastrophic. After detection, deconstruct the context.)");
		break;
	case VX_ERROR_NO_RESOURCES:
		throw std::runtime_error(R"(An internal or implicit resource can not be acquired (not memory). This is typically catastrophic. After detection, deconstruct the context.)");
		break;
	case VX_ERROR_NOT_COMPATIBLE:
		throw std::runtime_error(R"(The attempt to link two parameters together failed due to type incompatibilty.)");
		break;
	case VX_ERROR_NOT_ALLOCATED:
		throw std::runtime_error(R"(To the system that the parameter must be allocated by the system.)");
		break;
	case VX_ERROR_NOT_SUFFICIENT:
		throw std::runtime_error(R"(The given graph has failed verification due to an insufficient number of required parameters, which cannot be automatically created. Typically this indicates required atomic parameters.)");
		break;
	case VX_ERROR_NOT_SUPPORTED:
		throw std::runtime_error(R"(The requested set of parameters produce a configuration that cannot be supported. Refer to the supplied documentation on the configured kernels.)");
		break;
	case VX_ERROR_NOT_IMPLEMENTED:
		throw std::runtime_error(R"(The requested kernel is missing.)");
		break;
	case VX_FAILURE:
		throw std::runtime_error(R"(A generic error code, used when no other describes the error.)");
		break;
	default:
		break;
	}
}
