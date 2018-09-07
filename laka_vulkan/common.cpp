/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/

#include    "common.h"

using    namespace    spdlog;

class    My_init {
public:
    bool initializing;
    bool initialized;
    std::shared_ptr<logger> console_log;
    std::shared_ptr<logger> file_log;

    My_init()
        :initialized(false)
        , initializing([]() {printf("基础功能初始化开始...\n"); return true; }())
        , console_log(stdout_logger_mt("console"))
        , file_log(basic_logger_mt("file_log", "log.txt"))
    {
        set_level(level::debug);
        console_log->set_pattern("[%Y-%m-%d %T 线程:%t] %v");
        file_log->set_pattern("[%Y-%m-%d %T 线程:%t] %v");

        auto&    console = console_log;

        show_debug("debug");
        show_info("info");
        show_wrn("warring");
        show_err("error");
        critical_show("critical");

        initialized = true;
        printf("基础功能初始化完成\n");
    }

    ~My_init()
    {

        spdlog::drop_all();
        printf("基础功能析构完成\n");
    }
};



static My_init init;

Module_handle load_moudule(const char* module_name_)
{
    return load_moudule(module_name_, []() {});
}

Module_handle load_module_must(const char* module_name_)
{
    return load_moudule(module_name_, []() {abort(); });
}

void* load_module_function(Module_handle    module_handle_, const    char*    function_name_)
{
    return load_module_function(module_handle_, function_name_, []() {});
}

void*    load_module_function_must(Module_handle module_handle_, const char* function_name_)
{
    return load_module_function(module_handle_, function_name_, []() {abort(); });
}