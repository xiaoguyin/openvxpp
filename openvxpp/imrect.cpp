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
#include "imrect.h"


ovx::imrect::imrect(void) noexcept
	: vx_rectangle_t({})
{
}


ovx::imrect::imrect(vx_uint32 left, vx_uint32 top, vx_uint32 right, vx_uint32 bottom) noexcept
	: vx_rectangle_t({ left, top, right, bottom })
{
}


vx_uint32 ovx::imrect::width(void) const
{
	return this->end_x - this->start_x;
}


vx_uint32 ovx::imrect::height(void) const
{
	return this->end_y - this->start_y;
}


vx_uint32 ovx::imrect::area(void) const
{
	return this->width() * this->height();
}
