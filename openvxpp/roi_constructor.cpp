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
#include "roi_constructor.h"


ovx::roi_constructor::roi_constructor(roi_constructor &&obj) noexcept
{
	m_image = obj.m_image;
	obj.m_image = nullptr;
}


ovx::roi_constructor::~roi_constructor(void) noexcept
{
	this->release();
}


void ovx::roi_constructor::operator=(roi_constructor &&obj) noexcept
{
	this->release();
	m_image = obj.m_image;
	obj.m_image = nullptr;
}


void ovx::roi_constructor::release(void) noexcept
{
	::vxReleaseImage(&m_image);
}
