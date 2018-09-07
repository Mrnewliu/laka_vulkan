/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/

#include "vk.h"

using namespace laka::vk;
using namespace std;

//Buffer::Create_flags::Create_flags(int flag_) :flag(flag_) {};
//
//Buffer::Create_flags Buffer::Create_flags::operator|(Create_flags value_)
//{
//    return Create_flags(flag | value_.flag);
//}
//
//Buffer::Create_flags Buffer::Create_flags::operator|(Bits value_)
//{
//    return Create_flags(flag | value_);
//}

#define define_flags(name0__,name1__) \
name0__::name1__::name1__(int flag_):flag(flag_){};\
name0__::name1__ name0__::name1__::operator|(name1__ value_)\
{return name1__(flag|value_.flag);}\
name0__::name1__ name0__::name1__::operator|(Bits value_)\
{return name1__(flag|value_);}

define_flags(Buffer, E_Create);
define_flags(Buffer, E_Usage);

define_flags(Image, E_Create);
define_flags(Image, E_Usage);

define_flags(Command_pool, E_Create);

define_flags(Descriptor_pool, E_Create);

define_flags(Query_pool, E_Pipeline_statistic);

define_flags(Descriptor_set_layout, E_Create);



