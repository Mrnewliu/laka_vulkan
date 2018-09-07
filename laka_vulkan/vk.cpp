/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/


#include "vk.h"

using namespace std;

namespace laka {    namespace vk {

    static auto vk_module_handle = load_module_must("vulkan-1.dll");
    Module_handle get_module()
    {
        return vk_module_handle;
    }

    static auto vkGetInstanceProcAddr =
        (PFN_vkGetInstanceProcAddr)load_module_function_must(
            vk_module_handle,
            "vkGetInstanceProcAddr"
        );
    PFN_vkVoidFunction get_instance_proc_address(
        VkInstance instance_, const char* function_name_)
    {
        return vkGetInstanceProcAddr(instance_, function_name_);
    }

    PFN_vkVoidFunction return_vk_api(const char* function_name_)
    {
        return return_vk_api(function_name_, []() {});
    }
    PFN_vkVoidFunction return_vk_api(VkInstance instance_, const char* function_name_)
    {
        return return_vk_api(instance_, function_name_, []() {});
    }

    PFN_vkVoidFunction return_vk_api_must(const char* function_name_)
    {
        return return_vk_api(function_name_, []() {abort(); });
    }
    PFN_vkVoidFunction return_vk_api_must(VkInstance instance_, const char* function_name_)
    {
        return return_vk_api(instance_, function_name_, []() {abort(); });
    }

#define static_declare_load_vk_api(api_name__) \
    static auto api_name__ = \
    (PFN_ ## api_name__)return_vk_api_must(#api_name__);

    table_vk_api_global(static_declare_load_vk_api ZK, , , YK);

#define assert_ret(show_some_thing__) \
    show_debug("{0}:{1}",mean(ret)->c_str(),#show_some_thing__);\
    assert(ret>=0 && #show_some_thing__);
    
    uint32_t get_instance_version()
    {
        init_show;

        uint32_t version;
        auto ret = vkEnumerateInstanceVersion(&version);
        if (ret < 0)
        {
            show_debug("无法获取实例版本");
            return 0;
        }
        return version;
    }

    class Layer_properties {
    public:
        Layer_properties()
        {
            init_show;

            uint32_t count;
            auto ret = vkEnumerateInstanceLayerProperties(&count, nullptr);
            show_result(ret);
            if_show(count >= 0, "vulkan支持的层的数量为:{}", count);

            properties.resize(count);
            ret = vkEnumerateInstanceLayerProperties(&count, &properties[0]);
            show_result(ret);
        }

        vector<VkLayerProperties> properties;
        vector<vector<VkExtensionProperties>> layer_extension_properties;
    };

    static Layer_properties layer_properties;

    class Extension_properties {
    public:
        Extension_properties()
        {
            init_show;
            auto layer_count = layer_properties.properties.size();

            layer_properties.layer_extension_properties.resize(layer_count);

            for (size_t i = 0; i < layer_count; i++)
            {
                uint32_t count = 0;
                auto ret = vkEnumerateInstanceExtensionProperties(
                    layer_properties.properties[i].layerName, &count, nullptr);
                show_result(ret);
                if_show(count >= 0, "{0}层扩展属性数量:{1}",
                    layer_properties.properties[i].layerName, count);

                if (count <= 0)
                {
                    continue;
                }

                layer_properties.layer_extension_properties[i].resize(count);
                ret = vkEnumerateInstanceExtensionProperties(
                    layer_properties.properties[i].layerName,
                    &count,
                    &(layer_properties.layer_extension_properties[i][0])
                );
                show_result(ret);

                show_debug("{0}层所有扩展:", layer_properties.properties[i].layerName);

                for (auto& x : layer_properties.layer_extension_properties[i])
                {
                    show_debug("\t{}", x.extensionName);
                }
            }

            uint32_t count = 0;
            auto ret = vkEnumerateInstanceExtensionProperties(
                nullptr, &count, nullptr);
            show_result(ret);
            if_show(count >= 0, "总扩展属性数量:{}", count);

            properties.resize(count);
            if (count > 0)
            {
                ret = vkEnumerateInstanceExtensionProperties(
                    nullptr, &count, &properties[0]);
                show_result(ret);
            }

            show_debug("所有扩展属性:");
            for (auto& itr : properties)
            {
                show_debug("\t名称:{} 版本:{}", itr.extensionName, itr.specVersion);
            }
        }

        vector<VkExtensionProperties> properties;
    };

    static Extension_properties extension_properties;
    
    Instance::Instance(
        VkInstance handle_, VkAllocationCallbacks* allocator_callbacks_ptr_)
        :handle(handle_)
        , allocator_callbacks_ptr(allocator_callbacks_ptr_ != nullptr ? &allocator_callbacks : nullptr)
    {
        init_show;

        if (allocator_callbacks_ptr != nullptr) allocator_callbacks = *allocator_callbacks_ptr_;

#define load_instance_api(api_name__) \
        api.api_name__ = \
            (PFN_##api_name__)return_vk_api_must(handle,#api_name__); \
        
        table_vk_api_instance(load_instance_api ZK, , , YK);
        table_vk_api_physical_device(load_instance_api ZK, , , YK);
        table_vk_api_physical_device_khr(load_instance_api ZK, , , YK);

        uint32_t count = 0;
        auto ret = api.vkEnumeratePhysicalDevices(handle, &count, nullptr);
        show_result(ret);
        show_debug("物理设备数量:{}", count);
        if (count != 0)
        {
            physical_devices.resize(count);

            vector<VkPhysicalDevice> physical_devices_temp;
            physical_devices_temp.resize(count);
            ret = api.vkEnumeratePhysicalDevices(handle, &count, &physical_devices_temp[0]);
            show_result_assert(ret);

            int i = 0;
            for (auto&& pd_handle : physical_devices_temp)
            {
                physical_devices[i].instance = this;
                physical_devices[i].handle = pd_handle;

                auto qf_sptr = physical_devices[i].get_queue_family_properties();
                physical_devices[i].queue_familys.resize(qf_sptr->size());

                uint32_t index = 0;
                for (auto&& qf : *qf_sptr)
                {
                    physical_devices[i].queue_familys[index].index = index;
                    physical_devices[i].queue_familys[index].properties = qf;
                    index++;
                }

                auto pd_info = physical_devices[i].get_properties();

                show_debug(
                    "设备{0}  api版本:{1} 驱动版本:{2}", 
                    pd_info->deviceName, 
                    version_str(pd_info->apiVersion),
                    version_str(pd_info->driverVersion)
                );
            }
        }
        else
        {
            show_wrn("没有枚举到物理设备");
        }

        count = 0;
        ret = api.vkEnumeratePhysicalDeviceGroups(handle,&count,nullptr);
        show_result(ret);
        show_debug("设备组数量:{}", count);

        vector<VkPhysicalDeviceGroupProperties> physical_device_groups_temp(count);
        physical_device_groups.resize(count);

        if (count>0)
        {
            ret = api.vkEnumeratePhysicalDeviceGroups(handle, &count, &physical_device_groups_temp[0]);
            show_result(ret);

            int i = 0;
            for (auto&& current_pg_ppt : physical_device_groups_temp)
            {
                auto& current_group = physical_device_groups[i];
                current_group.properties = current_pg_ppt;
                current_group.physical_devices.resize(current_pg_ppt.physicalDeviceCount);

                for (int j = 0; j < current_pg_ppt.physicalDeviceCount; j++)
                {
                    auto& handle_temp = current_pg_ppt.physicalDevices[j];
                    show_debug("物理设备组中 物理句柄值:{}", (void*)handle_temp);

                    Physical_device* physical_device_ptr = nullptr;
                    int x = 0; 
                    for (auto&& current_physical_device : physical_devices)
                    {
                        if (current_physical_device.handle == handle_temp)
                        {
                            physical_device_ptr = &physical_devices[x];
                            break;
                        }
                        x++;
                    }

                    if (physical_device_ptr != nullptr)
                    {
                        current_group.physical_devices[i] = physical_device_ptr;
                    }
                    else
                    {
                        show_err("!!!!!!!!!!!在设备组中的物理设备的句柄 与枚举全部设备的句柄不一样");
                    }
                }
                i++;
            }
        }
        else {
            show_wrn("没有枚举出设备组");
        }
    }

    Instance::Sptr Instance::get_new(
        std::vector<const char*>* enabled_extension_names_/* = nullptr*/,
        uint32_t api_version_/* = VK_MAKE_VERSION(1, 1, 82)*/,
        const void* next_/* = nullptr*/,
        VkAllocationCallbacks* allocator_/* = nullptr*/,
        std::vector<const char*>* enabled_layer_names_/* = nullptr*/,
        const char* app_name_/* = "laka::vk"*/,
        uint32_t app_version_/* = VK_MAKE_VERSION(0, 0, 1)*/,
        const char* engine_name_/* = "laka::vk::engine"*/,
        uint32_t engine_version_/* = VK_MAKE_VERSION(0, 0, 1)*/)
    {
        init_show;

        Sptr sptr;

        VkApplicationInfo app_info{
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            nullptr,
            app_name_,
            app_version_,
            engine_name_,
            engine_version_,
            api_version_
        };

        VkInstanceCreateInfo info{
            VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            next_,
            0,
            &app_info,
            static_cast<uint32_t>(enabled_layer_names_ == nullptr ? 0 : enabled_layer_names_->size()),
            enabled_layer_names_ == nullptr ? nullptr : &(*enabled_layer_names_)[0],
            static_cast<uint32_t>(enabled_extension_names_ == nullptr ? 0 : enabled_extension_names_->size()),
            enabled_extension_names_ == nullptr ? nullptr : &(*enabled_extension_names_)[0]
        };

        VkInstance this_handle;
        auto ret = vkCreateInstance(&info, allocator_, &this_handle);
        show_result(ret);
        if (ret < 0)
        {
            show_wrn("创建Instance失败");
            return sptr;
        }

        sptr.reset(new Instance(this_handle, allocator_));

        return sptr;
    }

    Instance::~Instance()
    {
        init_show;
        show_function_name;
        api.vkDestroyInstance(handle, allocator_callbacks_ptr);
    }



#define load_vk_array_ret(handle__,function__,array__,...) \
    count = 0; \
    ret = function__(handle__,&count,nullptr);\
    show_result(ret);if_show(count>0,__VA_ARGS__);\
	array__.resize(count);\
    if(count>0)\
    {\
        ret = function__(handle__,&count,&array__[0]);\
        show_result(ret);\
    }

#define load_vk_array(handle__,function__,array__,...) \
    count = 0; \
    function__(handle__,&count,nullptr);\
    if_show(count>0,__VA_ARGS__);\
	array__.resize(count);\
    if(count>0)\
    {\
        function__(handle__,&count,&array__[0]);\
    }\

    shared_ptr<vector<VkLayerProperties>>
        Physical_device::get_layer_propertiess()
    {
        init_show;
        uint32_t count; VkResult ret;
        auto& array_ref = *new vector<VkLayerProperties>;
        shared_ptr<vector<VkLayerProperties>> sptr(&array_ref);

        load_vk_array_ret(
            handle,
            instance->api.vkEnumerateDeviceLayerProperties,
            array_ref,
            "物理设备 {0} 的层数为 {1}", (void*)handle, count
        );

        return sptr;
    }

    shared_ptr<vector<VkSparseImageFormatProperties2>>
        Physical_device::get_sparse_image_format_properties(
            const VkPhysicalDeviceSparseImageFormatInfo2* format_info_) 
    {
        init_show;
        auto& array = *new vector<VkSparseImageFormatProperties2>;
        shared_ptr<vector<VkSparseImageFormatProperties2>> sptr(&array);

        uint32_t count = 0;
        load_vk_array(
            handle DH format_info_,
            instance->api.vkGetPhysicalDeviceSparseImageFormatProperties2,
            array,
            "物理设备 {0} 的稀疏图像格式属性 数量为:{1}", (void*)handle, count
        );

        return sptr;
    }

    shared_ptr<vector<VkQueueFamilyProperties>>
        Physical_device::get_queue_family_properties()
    {
        init_show;
        auto& array = *new vector<VkQueueFamilyProperties>;
        shared_ptr<vector<VkQueueFamilyProperties>> sptr(&array);
        uint32_t count = 0;
        load_vk_array(
            handle,
            instance->api.vkGetPhysicalDeviceQueueFamilyProperties,
            array,
            "物理设备 {0} 的队列族数量为 {1}", (void*)handle, count
        );
        return sptr;
    }

    shared_ptr<vector<VkExtensionProperties>>
        Physical_device::get_extension_properties(const char* layer_name_)
    {
        init_show;
        auto& array = *new vector<VkExtensionProperties>;
        shared_ptr<vector<VkExtensionProperties>> sptr(&array);
        uint32_t count = 0;
        VkResult ret;

        load_vk_array_ret(
            handle DH layer_name_,
            instance->api.vkEnumerateDeviceExtensionProperties,
            array,
            "物理设备 {0} 的扩展属性数为 {1}", (void*)handle, count
        );

        return sptr;
    }


    shared_ptr<VkPhysicalDeviceFeatures>
        Physical_device::get_features()
    {
        auto& array = *new VkPhysicalDeviceFeatures;
        shared_ptr<VkPhysicalDeviceFeatures> sptr(&array);

        instance->api.vkGetPhysicalDeviceFeatures(handle, &array);

        return sptr;
    }

    shared_ptr<VkPhysicalDeviceProperties>
        Physical_device::get_properties()
    {
        auto& array = *new VkPhysicalDeviceProperties;

        instance->api.vkGetPhysicalDeviceProperties(handle, &array);

        shared_ptr<VkPhysicalDeviceProperties> sptr(&array);
        return sptr;
    }

    shared_ptr<VkPhysicalDeviceMemoryProperties>
        Physical_device::get_memory_properties()
    {
        auto& array = *new VkPhysicalDeviceMemoryProperties;
        shared_ptr<VkPhysicalDeviceMemoryProperties> sptr(&array);

        instance->api.vkGetPhysicalDeviceMemoryProperties(handle, &array);

        return sptr;
    }

    shared_ptr<VkFormatProperties>
        Physical_device::get_format_properties(VkFormat format_)
    {
        auto& array = *new VkFormatProperties;
        shared_ptr<VkFormatProperties> sptr(&array);

        instance->api.vkGetPhysicalDeviceFormatProperties(
            handle,
            format_,
            &array
        );

        return sptr;
    }

    shared_ptr<VkExternalBufferProperties>
        Physical_device::get_external_buffer_properties(
            const VkPhysicalDeviceExternalBufferInfo* external_buffer_info_
        ) {
        auto& array = *new VkExternalBufferProperties;
        shared_ptr<VkExternalBufferProperties> sptr(&array);

        instance->api.vkGetPhysicalDeviceExternalBufferProperties(
            handle,
            external_buffer_info_,
            &array
        );

        return sptr;
    }

    shared_ptr<VkExternalFenceProperties>
        Physical_device::get_external_fence_properties(
            const VkPhysicalDeviceExternalFenceInfo* external_fence_info_
        ) {
        auto& array = *new VkExternalFenceProperties;
        shared_ptr<VkExternalFenceProperties> sptr(&array);

        instance->api.vkGetPhysicalDeviceExternalFenceProperties(
            handle,
            external_fence_info_,
            &array
        );

        return sptr;
    }

    shared_ptr<VkExternalSemaphoreProperties>
        Physical_device::get_external_semphore_properties(
            const VkPhysicalDeviceExternalSemaphoreInfo* external_semaphore_info_
        ) {
        auto& array = *new VkExternalSemaphoreProperties;
        shared_ptr<VkExternalSemaphoreProperties> sptr(&array);

        instance->api.vkGetPhysicalDeviceExternalSemaphoreProperties(
            handle,
            external_semaphore_info_,
            &array
        );

        return sptr;
    }

    shared_ptr<VkImageFormatProperties2>
        Physical_device::get_image_format_properties(
            const VkPhysicalDeviceImageFormatInfo2* image_format_info_
        ) {
        auto& array = *new VkImageFormatProperties2;
        shared_ptr<VkImageFormatProperties2> sptr(&array);

        instance->api.vkGetPhysicalDeviceImageFormatProperties2(
            handle,
            image_format_info_,
            &array
        );
        return sptr;
    }

    shared_ptr<Device_creator> Instance::get_a_device_creator(
        bool(*choose_physical_device_)(Pramater_choose_physical_device& pramater_),
        bool(*choose_queue_family_)(Pramater_choose_queue_family& pramater_),
        VkAllocationCallbacks* allocator_/* = nullptr*/)
    {
        shared_ptr<Device_creator> sptr(
            new Device_creator(
            shared_from_this(),
            choose_physical_device_,
            choose_queue_family_,
            allocator_)
        );

        return sptr;
    }

    Device_creator::Device_creator(
        shared_ptr<Instance> instance_,
        bool(*choose_physical_device_)(Pramater_choose_physical_device& physical_device_),
        bool(*choose_queue_family_)(Pramater_choose_queue_family& parmatwr_),
        const VkAllocationCallbacks* allocator_)
        :instance(instance_)
        ,choose_physical_device_function(choose_physical_device_)
        ,choose_queue_family_function(choose_queue_family_)
        , allocation_callbacks(allocator_ == nullptr ? instance_->allocator_callbacks_ptr : allocator_)
    {   }


    PFN_vkVoidFunction Device::return_api(const char* api_name_)
    {
        init_show;
        //show_function_name;
        auto ret = instance->api.vkGetDeviceProcAddr(handle, api_name_);

        if (ret == nullptr)
        {
            show_wrn("加载{}失败", api_name_);
        }
        else
        {
            show_debug("加载{}成功", api_name_);
        }
        return ret;
    }

    Device::Device(
        shared_ptr<Instance> instance_,
        shared_ptr<Device_creator> device_creator_,
        std::vector<Physical_device*>& physical_devices_,
        VkDevice handle_,
        shared_ptr<vector<Queue_create_info>>& quque_create_info_sptr_)
        :instance(instance_)
        , handle(handle_)
        , device_creator(device_creator_)
        , physical_devices(physical_devices_)
        , allocation_callbacks(device_creator_->allocation_callbacks)
    {
#define load_vk_device_api(api_name__) \
    api.api_name__ = (PFN_##api_name__)return_api(#api_name__);

        table_vk_api_device(load_vk_device_api ZK, , , YK FH);
        table_vk_api_cmd(load_vk_device_api ZK, , , YK FH);
        
        //先不管队列 后边要用再完善

    }

    Device::~Device()
    {
        init_show;
        show_function_name;
        api.vkDestroyDevice(handle, allocation_callbacks);
    }

    //要将队列族信息存入设备对象中.

    std::shared_ptr<Device> Device_creator::get_a_device(
        Physical_device& physical_device_,
        VkDeviceCreateInfo* create_info_)
    {
        init_show;
        shared_ptr<Device> device_sptr;

        Pramater_choose_physical_device p1{ physical_device_ };
        if (choose_physical_device_function(p1) == false)
            return device_sptr;
        
        VkDevice device_handle;
        auto ret = instance->api.vkCreateDevice(
            physical_device_.handle, 
            create_info_, 
            allocation_callbacks, 
            &device_handle
        );
        show_result(ret);
        if (ret < 0) return device_sptr;

        vector<Physical_device*> pds;
        //还需遍历pnext 找出所有物理设备指针放进去.

        device_sptr.reset(
            new Device(
                instance, 
                shared_from_this(), 
                pds,
                device_handle,
                
            ));

        return device_sptr;
    }

    std::shared_ptr<Device> Device_creator::get_a_device(
        Physical_device& physical_device_,
        std::vector<char*>* enabled_extensions_,
        VkPhysicalDeviceFeatures* features_)
    {
        init_show;
        std::shared_ptr<Device> device_sptr;

        Pramater_choose_physical_device p1{ physical_device_ };
        if (choose_physical_device_function(p1) == false)
        {
            show_wrn("此设备不合适");
            return device_sptr;
        }

        auto queue_familys = physical_device_.get_queue_family_properties();

        std::vector<Queue_family_info> my_queue_familys;
        my_queue_familys.resize(queue_familys->size());

        for (size_t i = 0; i < my_queue_familys.size(); i++)
        {
            my_queue_familys[i].index = static_cast<uint32_t>(i);
            my_queue_familys[i].properties = (*queue_familys)[i];
        }
        vector<Queue_create_info> my_queue_create_infos;

        Pramater_choose_queue_family choose_qf_parmater{ my_queue_familys, my_queue_create_infos };

        if (choose_queue_family_function(choose_qf_parmater) == false)
        {
            show_wrn("此设备没有合适的队列族");
            return device_sptr;
        }

        vector<VkDeviceQueueCreateInfo> queue_create_infos(my_queue_create_infos.size());

        auto my_q_info = get_my_queue_create_info(my_queue_create_infos);

        VkDevice device_handle;
        VkDeviceCreateInfo device_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            nullptr,
            0,
            static_cast<uint32_t>(queue_create_infos.size()),
            queue_create_infos.size() > 0 ? &(*my_q_info.queue_create_info)[0] : nullptr,
            0,
            nullptr,
            enabled_extensions_ != nullptr ? static_cast<uint32_t>(enabled_extensions_->size()) : 0,
            enabled_extensions_ != nullptr ? &(*enabled_extensions_)[0] : nullptr,
            features_
        };
        auto ret = instance->api.vkCreateDevice(
            physical_device_.handle,
            &device_create_info,
            allocation_callbacks,
            &device_handle
        );
        show_result(ret);
        if (ret < 0)
        {
            show_wrn("创建设备失败");
            return device_sptr;
        }

        vector<Physical_device*> pds{ &physical_device_ };

        device_sptr.reset(new Device(
            instance, shared_from_this(), pds, device_handle, my_q_info.queue_priorities));

        return device_sptr;
    }


    std::shared_ptr<Device> Device_creator::get_a_device(
        Physical_device_group& physica_device_group_,
        std::vector<char*>* enabled_extensions_,
        VkPhysicalDeviceFeatures* features_)
    {
        init_show;
        show_debug("从设备组创建逻辑设备");

        std::shared_ptr<Device> device_sptr;

        list<Physical_device*> ok_physical_device_list;
        for (auto&& physical_device : physica_device_group_.physical_devices)
        {
            Pramater_choose_physical_device p1{ *physical_device };
            if (choose_physical_device_function(p1) == false)
            {
                show_wrn("一个设备不合适:{}",(void*) p1.if_you_feel_the_physical_device_not_ok_so_return_false.handle);
                continue;
            }
            ok_physical_device_list.push_back(physical_device);
        }
        if (ok_physical_device_list.size() <= 0)
        {
            show_wrn("没有合适的设备");
            return device_sptr;
        }


        vector<VkPhysicalDevice> ok_physical_devices_handle(ok_physical_device_list.size());
        int count = 0;
        for (auto&& physical_device : ok_physical_device_list)
        {
            ok_physical_devices_handle[count++] = physical_device->handle;
        }
        auto queue_familys = ok_physical_device_list.front()->get_queue_family_properties();

        std::vector<Queue_family_info> my_queue_familys;
        my_queue_familys.resize(queue_familys->size());

        for (size_t i = 0; i < my_queue_familys.size(); i++)
        {
            my_queue_familys[i].index = static_cast<uint32_t>(i);
            my_queue_familys[i].properties = (*queue_familys)[i];
        }
        vector<Queue_create_info> my_queue_create_infos;

        Pramater_choose_queue_family choose_qf_parmater{ my_queue_familys, my_queue_create_infos };

        if (choose_queue_family_function(choose_qf_parmater) == false)
        {
            show_wrn("没有合适的队列族");
            return device_sptr;
        }

        vector<VkDeviceQueueCreateInfo> queue_create_infos(my_queue_create_infos.size());

        VkDeviceGroupDeviceCreateInfo device_group_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_GROUP_DEVICE_CREATE_INFO,
            nullptr,
            static_cast<uint32_t>(ok_physical_devices_handle.size()),
            &ok_physical_devices_handle[0]
        };

        auto my_q_info = get_my_queue_create_info(my_queue_create_infos);

        VkDevice device_handle;
        VkDeviceCreateInfo device_create_info = {
            VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            &device_group_create_info,
            0,
            static_cast<uint32_t>(queue_create_infos.size()),
            queue_create_infos.size() > 0 ? &(*my_q_info.queue_create_info)[0] : nullptr,
            0,
            nullptr,
            enabled_extensions_ != nullptr ? static_cast<uint32_t>(enabled_extensions_->size()) : 0,
            enabled_extensions_ != nullptr ? &(*enabled_extensions_)[0] : nullptr,
            features_
        };
        auto ret = instance->api.vkCreateDevice(
            ok_physical_device_list.front()->handle,
            &device_create_info,
            allocation_callbacks,
            &device_handle
        );
        show_result(ret);
        if (ret < 0)
        {
            show_wrn("创建设备失败");
            return device_sptr;
        }

        vector<Physical_device*> pds(ok_physical_device_list.size());
        size_t index_pd = 0;
        for (auto&& node : ok_physical_device_list)
        {
            pds[index_pd++] = node;
        }


        device_sptr.reset(new Device(
            instance,
            shared_from_this(),
            pds,
            device_handle,
            my_q_info.queue_priorities
        ));

        return device_sptr;
    }


    std::shared_ptr <Semaphore> Device::get_a_semaphore(
        const void* next_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Semaphore> semaphore_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkSemaphoreCreateInfo info{
            VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
            next_,
            0
        };

        VkSemaphore semaphore_handle;
        auto ret = api.vkCreateSemaphore(handle, &info, the_allocator, &semaphore_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建Semaphore失败");
            return semaphore_sptr;
        }

        semaphore_sptr.reset(new Semaphore(shared_from_this(),semaphore_handle, the_allocator));

        return semaphore_sptr;
    }

    Semaphore::Semaphore(std::shared_ptr<Device> device_, VkSemaphore handle_, const VkAllocationCallbacks* pAllocator_)
        :device(device_)
        ,handle(handle_)
        ,allocation_callbacks(pAllocator_)
    {   }

    Semaphore::~Semaphore()
    {
        init_show;
        show_function_name;
        device->api.vkDestroySemaphore(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr <Fence> Device::get_a_fence(
        const void* next_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Fence> fence_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkFenceCreateInfo info{
            VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            next_,
            0
        };

        VkFence fence_handle;
        auto ret = api.vkCreateFence(handle, &info, the_allocator, &fence_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建Fence失败");
            return fence_sptr;
        }

        fence_sptr.reset(new Fence(shared_from_this(),fence_handle, the_allocator));

        return fence_sptr;
    }

    Fence::Fence(std::shared_ptr<Device> device_, VkFence handle_, const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {    }

    Fence::~Fence()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyFence(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr <Event> Device::get_a_event(
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Event> event_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkEventCreateInfo info{
            VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            nullptr,
            0
        };

        VkEvent event_handle;
        auto ret = api.vkCreateEvent(handle, &info, the_allocator, &event_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建Event失败");
            return event_sptr;
        }

        event_sptr.reset(new Event(shared_from_this(), event_handle, the_allocator));

        return event_sptr;
    }

    Event::Event(Device::Sptr device_, VkEvent handle_, const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Event::~Event()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyEvent(device->handle, handle, allocation_callbacks);
    }



    std::shared_ptr<Shader_module> Device::get_a_shader_module(
        const uint32_t*     code_ptr_,
        size_t              code_size_,
        const void* next_ /*= nullptr*/,
        const VkAllocationCallbacks* pAllocator_ /*= nullptr*/)
    {
        shared_ptr<Shader_module> shader_module_sptr;

        init_show;
        if (code_size_ <= 0)
        {
            show_wrn("code size 不大于0");
            return shader_module_sptr;
        }

        VkShaderModuleCreateInfo info{
            VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            next_,
            0,
            code_size_,
            code_ptr_
        };

        VkShaderModule shader_module_handle;

        auto ret = api.vkCreateShaderModule(
            handle,
            &info,
            pAllocator_ == nullptr ? allocation_callbacks : pAllocator_,
            &shader_module_handle
        );
        show_result(ret);
        if (ret < 0)
        {
            show_wrn("创建shader moudle 失败");
            return shader_module_sptr;
        }

        shader_module_sptr.reset(
            new Shader_module(
                shared_from_this(),
                shader_module_handle,
                pAllocator_ == nullptr ? allocation_callbacks : pAllocator_)
        );

        return shader_module_sptr;
    }

    Shader_module::Shader_module(
        Device::Sptr device_,
        VkShaderModule handle_, 
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Shader_module::~Shader_module()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyShaderModule(device->handle, handle, allocation_callbacks);
    }



    std::shared_ptr<Device_memory> Device::get_a_device_memory(
        VkDeviceSize memory_size_,
        bool(*choose_memory_type_index_)(
            Pramater_choose_memory_type& pramater_choose_,
            Pramater_choose_result& choose_result_),
        void* create_info_ /* = nullptr */,
        const VkAllocationCallbacks* allocation_callbacks_ /* = nullptr */)
    {
        shared_ptr<Device_memory> device_memroy_sptr;
        
        init_show;
        if (physical_devices.size() == 0)
        {
            show_err("此逻辑设备没有保存创建时所用的物理设备");
            return device_memroy_sptr;
        }

        auto pdev_memory_properties = physical_devices[0]->get_memory_properties();
        Pramater_choose_memory_type memory_properties{
            pdev_memory_properties->memoryTypeCount,
            &pdev_memory_properties->memoryTypes[0]
        };
        Pramater_choose_result choose_result{ 0 };

        if (choose_memory_type_index_(memory_properties, choose_result) == false)
            return device_memroy_sptr;

        const VkAllocationCallbacks* a_cb = allocation_callbacks_ == nullptr ?
            allocation_callbacks : allocation_callbacks_;

        VkMemoryAllocateInfo a_info{
            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            create_info_,
            memory_size_,
            choose_result.memory_type_index
        };

        VkDeviceMemory device_memory_handle;
        auto ret = api.vkAllocateMemory(
            handle, &a_info, a_cb, &device_memory_handle);
        show_result(ret);
        if (ret<0)
        {
            show_wrn("申请device memory 失败");
            return device_memroy_sptr;
        }

        device_memroy_sptr.reset(new Device_memory(
            shared_from_this(),device_memory_handle, allocation_callbacks_));

        return device_memroy_sptr;
    }

    Device_memory::Device_memory(
        Device::Sptr device_,
        VkDeviceMemory handle_,
        const VkAllocationCallbacks* allocation_callbacks_)
        :device(device_)
        , handle(handle_)
        , allocation_callbacks(allocation_callbacks_)
    {   }

    Device_memory::~Device_memory()
    {
        init_show;
        show_function_name;
        device->api.vkFreeMemory(device->handle, handle, allocation_callbacks);
    }



    shared_ptr<Buffer> Device::get_a_buffer(
        VkDeviceSize		buffer_size_,
        Buffer::E_Create    create_flags_,
        Buffer::E_Usage	    usage_flags_,
        VkSharingMode		sharing_mode_,
        std::vector<uint32_t> queue_family_indices_,
        const void* next_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Buffer> buffer_sptr;

        VkBufferCreateInfo info{
            VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            next_,
            create_flags_.flag,
            buffer_size_,
            usage_flags_.flag,
            sharing_mode_,
            static_cast<uint32_t>(queue_family_indices_.size()),
            queue_family_indices_.size() > 0 ? &queue_family_indices_[0] : nullptr
        };

        VkBuffer buffer_handle;

        auto ret = api.vkCreateBuffer(
            handle,
            &info,
            pAllocator_ == nullptr ? allocation_callbacks : pAllocator_,
            &buffer_handle
        );
        show_result(ret);
        if (ret < 0) return buffer_sptr;

        buffer_sptr.reset(new Buffer(
            shared_from_this(),
            buffer_handle,
            pAllocator_ == nullptr ? allocation_callbacks : pAllocator_
        ));

        return buffer_sptr;
    }

    Buffer::Buffer(Device::Sptr device_, VkBuffer handle_, const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    { }

    Buffer::~Buffer()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyBuffer(
            device->handle,
            handle,
            allocation_callbacks
        );
    }

    std::shared_ptr<Buffer_view> Buffer::get_a_buffer_view(
        VkFormat		format_,
        VkDeviceSize	offset_,
        VkDeviceSize	range_,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Buffer_view> buffer_view_sptr;

        VkBufferViewCreateInfo info{
            VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
            NULL,
            0,
            handle,
            format_,
            offset_,
            range_
        };

        auto allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkBufferView buffer_view_handle;

        auto ret = device->api.vkCreateBufferView(
            device->handle,
            &info,
            allocator,
            &buffer_view_handle
        );

        show_result(ret);
        if (ret < 0)
        {
            init_show;
            show_wrn("创建 buffer view 失败");
            return buffer_view_sptr;
        }

        buffer_view_sptr.reset(new Buffer_view(
            shared_from_this(),buffer_view_handle, allocator));

        return buffer_view_sptr;
    }

    Buffer_view::Buffer_view(
        shared_ptr<Buffer> buffer_,
        VkBufferView handle_,
        const VkAllocationCallbacks* pAllocator_)
        : buffer(buffer_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Buffer_view::~Buffer_view()
    {
        init_show;
        show_function_name;
        buffer->device->api.vkDestroyBufferView(buffer->device->handle, handle, allocation_callbacks);
    }




    std::shared_ptr<Image> Device::get_a_image(
        Image::E_Create         create_fb_,
        VkImageType             imageType_,
        VkFormat                format_,
        VkExtent3D              extent_,
        uint32_t                mipLevels_,
        uint32_t                arrayLayers_,
        VkSampleCountFlagBits   samples_,
        Image::E_Usage          usage_fb_,
        VkSharingMode           sharingMode_,
        VkImageTiling           tiling_,
        std::vector<uint32_t>	queue_family_indices_,
        VkImageLayout           initialLayout_,
        const void* next_ /*= nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Image> image_sptr;

        auto allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkImageCreateInfo	info{
            VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            next_,
            create_fb_.flag,
            imageType_,
            format_,
            extent_,
            mipLevels_,
            arrayLayers_,
            samples_,
            tiling_,
            usage_fb_.flag,
            sharingMode_,
            static_cast<uint32_t>(queue_family_indices_.size()),
            queue_family_indices_.size() > 0 ? &queue_family_indices_[0] : nullptr,
            initialLayout_
        };

        VkImage image_handle;
        auto ret = api.vkCreateImage(handle, &info, allocator, &image_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建Image 失败");
            return image_sptr;
        }

        image_sptr.reset(new Image(shared_from_this(),image_handle, allocator));

        return image_sptr;
    }

    Image::Image(Device::Sptr device_, VkImage handle_, const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Image::~Image()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyImage(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Image_view> Image::get_a_image_view(
        VkImageViewType			view_type_,
        VkFormat				format_,
        VkComponentMapping		components_,
        VkImageSubresourceRange subresourceRange_,
        const void* next_ /*= nullptr*/,
        const VkAllocationCallbacks* pAllocator_ /*= nullptr*/)
    {
        shared_ptr<Image_view> image_view_sptr;

        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkImageViewCreateInfo info{
            VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            next_,
            0,
            handle,
            view_type_,
            format_,
            components_,
            subresourceRange_
        };

        VkImageView image_view_handle;
        auto ret = device->api.vkCreateImageView(
            device->handle,
            &info,
            the_allocator,
            &image_view_handle
        );

        show_result(ret);
        if (ret < 0)
        {
            init_show;
            show_wrn("创建 image view 失败");
            return image_view_sptr;
        }

        image_view_sptr.reset(new Image_view(
            shared_from_this() ,image_view_handle, the_allocator));

        return image_view_sptr;
    }

    Image_view::Image_view(
        std::shared_ptr<Image> image_,
        VkImageView handle_,
        const VkAllocationCallbacks* pAllocator_)
        : image(image_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {
    }

    Image_view::~Image_view()
    {
        init_show;
        show_function_name;
        image->device->api.vkDestroyImageView(image->device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Sampler> Device::get_a_sampler(
        VkFilter                magFilter,
        VkFilter                minFilter,
        VkSamplerMipmapMode     mipmapMode,
        VkSamplerAddressMode    addressModeU,
        VkSamplerAddressMode    addressModeV,
        VkSamplerAddressMode    addressModeW,
        float                   mipLodBias,
        VkBool32                anisotropyEnable,
        float                   maxAnisotropy,
        VkBool32                compareEnable,
        VkCompareOp             compareOp,
        float                   minLod,
        float                   maxLod,
        VkBorderColor           borderColor,
        VkBool32                unnormalizedCoordinates,
        const void* next_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Sampler> sampler_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkSamplerCreateInfo info{
            VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            next_,
            0,
            magFilter,
            minFilter,
            mipmapMode,
            addressModeU,
            addressModeV,
            addressModeW,
            mipLodBias,
            anisotropyEnable,
            maxAnisotropy,
            compareEnable,
            compareOp,
            minLod,
            maxLod,
            borderColor,
            unnormalizedCoordinates
        };

        VkSampler sampler_handle;
        auto ret = api.vkCreateSampler(handle, &info, the_allocator, &sampler_handle);
        show_result(ret);

        if (ret < 0) return sampler_sptr;

        sampler_sptr.reset(new Sampler(shared_from_this(),sampler_handle, the_allocator));

        return sampler_sptr;
    }

    Sampler::Sampler(
        Device::Sptr device_,
        VkSampler handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Sampler::~Sampler()
    {
        init_show;
        show_function_name;
        device->api.vkDestroySampler(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Sampler_Ycbcr_conversion> Device::get_a_sampler_ycbcr_conversion(
        VkFormat                        format_,
        VkSamplerYcbcrModelConversion   ycbcrModel,
        VkSamplerYcbcrRange             ycbcrRange,
        VkComponentMapping              components,
        VkChromaLocation                xChromaOffset,
        VkChromaLocation                yChromaOffset,
        VkFilter                        chromaFilter,
        VkBool32                        forceExplicitReconstruction,
        const void*                     next_/* = nullptr*/,
        const VkAllocationCallbacks*    pAllocator_/* = nullptr*/)
    {
        shared_ptr<Sampler_Ycbcr_conversion> sampler_ycbcr_conversion_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkSamplerYcbcrConversionCreateInfo info{
            VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO,
            next_,
            format_,
            ycbcrModel,
            ycbcrRange,
            components,
            xChromaOffset,
            yChromaOffset,
            chromaFilter,
            forceExplicitReconstruction
        };

        VkSamplerYcbcrConversion sampler_handle;
        auto ret = api.vkCreateSamplerYcbcrConversion(handle, &info, the_allocator, &sampler_handle);
        show_result(ret);

        if (ret < 0) return sampler_ycbcr_conversion_sptr;

        sampler_ycbcr_conversion_sptr.reset(new Sampler_Ycbcr_conversion(
            shared_from_this(), sampler_handle, the_allocator));

        return sampler_ycbcr_conversion_sptr;
    }

    Sampler_Ycbcr_conversion::Sampler_Ycbcr_conversion(
        std::shared_ptr<Device> device_,
        VkSamplerYcbcrConversion handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Sampler_Ycbcr_conversion::~Sampler_Ycbcr_conversion()
    {
        init_show;
        show_function_name;
        device->api.vkDestroySamplerYcbcrConversion(device->handle, handle, allocation_callbacks);
    }



    shared_ptr<Command_pool> Device::get_a_command_pool(
        uint32_t                    queueFamilyIndex,
        Command_pool::E_Create      flags_,
        const VkAllocationCallbacks* pAllocator_ /*= nullptr*/)
    {
        shared_ptr<Command_pool> command_pool_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkCommandPoolCreateInfo info{
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            NULL,
            flags_.flag,
            queueFamilyIndex
        };

        VkCommandPool command_pool_handle;
        auto ret = api.vkCreateCommandPool(
            handle, &info, the_allocator, &command_pool_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建Command pool 失败");
            return command_pool_sptr;
        }

        command_pool_sptr.reset(
            new Command_pool(shared_from_this(),command_pool_handle, the_allocator));

        return command_pool_sptr;
    }

    Command_pool::Command_pool(
        shared_ptr<Device>device_,
        VkCommandPool handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Command_pool::~Command_pool()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyCommandPool(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Command_buffer> Command_pool::get_a_command_buffer(
        VkCommandPool           commandPool,
        VkCommandBufferLevel    level)
    {
        shared_ptr<Command_buffer> command_buffer_sptr;

        VkCommandBufferAllocateInfo info{
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            NULL,
            handle,
            level,
            1
        };

        VkCommandBuffer command_buffer_handle;
        auto ret = device->api.vkAllocateCommandBuffers(
            device->handle, &info, &command_buffer_handle);
        show_result(ret);

        if (ret < 0) return command_buffer_sptr;

        command_buffer_sptr.reset(
            new Command_buffer(shared_from_this(),command_buffer_handle));

        return command_buffer_sptr;
    }

    Command_buffer::Command_buffer(
        std::shared_ptr<Command_pool> command_pool_,
        VkCommandBuffer command_buffer_handle)
        :command_pool(command_pool_)
        ,handle(command_buffer_handle)
    {   }

    Command_buffer::~Command_buffer()
    {
        init_show;
        show_function_name;
        command_pool->device->api.vkFreeCommandBuffers(
            command_pool->device->handle, command_pool->handle, 1, &handle);
    }

    std::shared_ptr<Command_buffers> Command_pool::get_a_command_buffers(
        VkCommandPool           commandPool,
        VkCommandBufferLevel    level,
        uint32_t                command_buffer_count_)
    {
        shared_ptr<Command_buffers> command_buffers_sptr;
        VkCommandBufferAllocateInfo info{
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            NULL,
            handle,
            level,
            command_buffer_count_
        };

        vector<VkCommandBuffer> command_buffer_handles(command_buffer_count_);

        auto ret = device->api.vkAllocateCommandBuffers(
            device->handle, &info, &command_buffer_handles[0]
        );
        show_result(ret);
        if (ret < 0) return command_buffers_sptr;

        command_buffers_sptr.reset(new Command_buffers(
            shared_from_this(),command_buffer_handles
        ));

        return command_buffers_sptr;
    }

    Command_buffers::Command_buffers(
        shared_ptr<Command_pool> command_pool_,
        std::vector<VkCommandBuffer>& command_buffer_handles_)
        :command_pool(command_pool_)
        ,handles(command_buffer_handles_)
    {    }

    Command_buffers::~Command_buffers()
    {
        init_show;
        show_function_name;
        command_pool->device->api.vkFreeCommandBuffers(
            command_pool->device->handle,
            command_pool->handle,
            static_cast<uint32_t>(handles.size()),
            &handles[0]
        );
    }


    shared_ptr<Descriptor_pool> Device::get_a_descriptor_pool(
        uint32_t                                max_sets_,
        std::vector<VkDescriptorPoolSize>&     pool_sizes_,
        Descriptor_pool::E_Create               flags_,
        const VkAllocationCallbacks*            pAllocator_/* = nullptr*/)
    {
        shared_ptr<Descriptor_pool> descriptor_pool_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkDescriptorPoolCreateInfo info{
            VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            NULL,
            flags_.flag,
            max_sets_,
            static_cast<uint32_t>(pool_sizes_.size()),
            pool_sizes_.size() > 0 ? &pool_sizes_[0] : nullptr
        };

        VkDescriptorPool descriptor_pool_handle;
        auto ret = api.vkCreateDescriptorPool(
            handle, &info, the_allocator, &descriptor_pool_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建 descriptor pool 失败");
            return descriptor_pool_sptr;
        }

        descriptor_pool_sptr.reset(
            new Descriptor_pool(shared_from_this(),descriptor_pool_handle, the_allocator));

        return descriptor_pool_sptr;
    }

    Descriptor_pool::Descriptor_pool(
        std::shared_ptr<Device> device_, 
        VkDescriptorPool handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Descriptor_pool::~Descriptor_pool()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyDescriptorPool(device->handle, handle, allocation_callbacks);
    }


    shared_ptr<Descriptor_set> Descriptor_pool::get_a_descriptor_set(
        VkDescriptorSetLayout set_layout,
        const void* next_ /* = nullptr */)
    {
        shared_ptr<Descriptor_set> descriptor_sets_sptr;

        VkDescriptorSetAllocateInfo info{
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            next_,
            handle,
            1,
            &set_layout,
        };

        VkDescriptorSet descriptor_sets_handle;
        auto ret = device->api.vkAllocateDescriptorSets(
            device->handle, &info, &descriptor_sets_handle);
        show_result(ret);

        if (ret < 0)
        {
            return descriptor_sets_sptr;
        }

        descriptor_sets_sptr.reset(
            new Descriptor_set(shared_from_this(), descriptor_sets_handle)
        );

        return descriptor_sets_sptr;
    }

    Descriptor_set::Descriptor_set(
        std::shared_ptr<Descriptor_pool> descriptor_pool_,
        VkDescriptorSet handle_)
        : descriptor_pool(descriptor_pool_)
        , handle(handle_)
    {   }

    Descriptor_set::~Descriptor_set()
    {
        init_show;
        show_function_name;
        descriptor_pool->device->api.vkFreeDescriptorSets(descriptor_pool->device->handle, descriptor_pool->handle, 1, &handle);
    }


    std::shared_ptr<Descriptor_sets> Descriptor_pool::get_descriptor_sets(
        std::vector<VkDescriptorSetLayout> set_layouts,
        const void* next_/* = nullptr*/)
    {
        shared_ptr<Descriptor_sets> descriptor_sets_sptr;

        VkDescriptorSetAllocateInfo info{
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            next_,
            handle,
            static_cast<uint32_t>(set_layouts.size()),
            &(set_layouts[0]),
        };

        vector<VkDescriptorSet> descriptor_sets_handles(set_layouts.size());
        auto ret = device->api.vkAllocateDescriptorSets(
            device->handle, &info, &descriptor_sets_handles[0]);
        show_result(ret);

        if (ret < 0) return descriptor_sets_sptr;

        descriptor_sets_sptr.reset(new Descriptor_sets(
            shared_from_this(),descriptor_sets_handles
        ));
        return descriptor_sets_sptr;
    }

    Descriptor_sets::Descriptor_sets(
        shared_ptr<Descriptor_pool> descriptor_pool_,
        std::vector<VkDescriptorSet>& handle_)
        : descriptor_pool(descriptor_pool_)
        , handles(handle_)
    {   }

    Descriptor_sets::~Descriptor_sets()
    {
        init_show;
        show_function_name;
        descriptor_pool->device->api.vkFreeDescriptorSets(
            descriptor_pool->device->handle,
            descriptor_pool->handle,
            static_cast<uint32_t>(handles.size()),
            &handles[0]
        );
    }


    shared_ptr<Query_pool> Device::get_a_query_pool(
        VkQueryType query_type,
        uint32_t    query_count,
        Query_pool::E_Pipeline_statistic queue_pipeline_statistic_flags_,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Query_pool> query_pool_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkQueryPoolCreateInfo info{
            VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
            NULL,
            0,
            query_type,
            query_count,
            queue_pipeline_statistic_flags_.flag
        };

        VkQueryPool query_pool_handle;
        auto ret = api.vkCreateQueryPool(
            handle, &info, the_allocator, &query_pool_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建 Query pool 失败");
            return query_pool_sptr;
        }

        query_pool_sptr.reset(
            new Query_pool(shared_from_this(),query_pool_handle, the_allocator));

        return query_pool_sptr;
    }

    Query_pool::Query_pool(
        shared_ptr<Device> device_, VkQueryPool handle_, const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Query_pool::~Query_pool()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyQueryPool(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Descriptor_set_layout> Device::get_a_descriptor_set_layout(
        std::vector<VkDescriptorSetLayoutBinding>* bindings_,
        Descriptor_set_layout::E_Create flags_,
        const void* next_,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Descriptor_set_layout> descriptor_set_layout_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        uint32_t size =
            bindings_ != nullptr ? static_cast<uint32_t>(bindings_->size()) : 0;

        VkDescriptorSetLayoutBinding* point_temp =
            bindings_ != nullptr ? &((*bindings_)[0]) : nullptr;

        VkDescriptorSetLayoutCreateInfo info{
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
            next_,
            flags_.flag,
            size,
            point_temp
        };

        VkDescriptorSetLayout descriptor_set_layout_handle;
        auto ret = api.vkCreateDescriptorSetLayout(
            handle, &info, the_allocator, &descriptor_set_layout_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建 descriptor setlayout 失败");
            return descriptor_set_layout_sptr;
        }

        descriptor_set_layout_sptr.reset(
            new Descriptor_set_layout(shared_from_this(),descriptor_set_layout_handle, the_allocator));

        return descriptor_set_layout_sptr;
    }

    Descriptor_set_layout::Descriptor_set_layout(
        std::shared_ptr<Device> device_,
        VkDescriptorSetLayout handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Descriptor_set_layout::~Descriptor_set_layout()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyDescriptorSetLayout(
            device->handle, handle, allocation_callbacks);
    }



    std::shared_ptr<Descriptor_update_template> Descriptor_set_layout::get_a_descriptor_update_template(
        std::vector<VkDescriptorUpdateTemplateEntry>& entrys_,
        const VkAllocationCallbacks* pAllocator_)
    {
        shared_ptr<Descriptor_update_template> descriptor_update_template_sptr;

        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        if (entrys_.size() <= 0)  return descriptor_update_template_sptr;

        VkDescriptorUpdateTemplateCreateInfo info{
            VK_STRUCTURE_TYPE_DESCRIPTOR_UPDATE_TEMPLATE_CREATE_INFO,
            NULL,
            0,
            static_cast<uint32_t>(entrys_.size()),
            &(entrys_[0]),
            VK_DESCRIPTOR_UPDATE_TEMPLATE_TYPE_DESCRIPTOR_SET,
            handle,
            /*...*/
        };

        VkDescriptorUpdateTemplate descriptor_update_template_handle;
        auto ret = device->api.vkCreateDescriptorUpdateTemplate(
            device->handle, &info, the_allocator, &descriptor_update_template_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建 descriptor update template 失败");
            return descriptor_update_template_sptr;
        }

        descriptor_update_template_sptr.reset(new Descriptor_update_template(
            shared_from_this(),descriptor_update_template_handle, the_allocator
        ));

        return descriptor_update_template_sptr;
    }

    Descriptor_update_template::Descriptor_update_template(
        shared_ptr<Descriptor_set_layout> descriptor_set_layout_,
        VkDescriptorUpdateTemplate handle_,
        const VkAllocationCallbacks* pAllocator_)
        : descriptor_set_layout(descriptor_set_layout_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Descriptor_update_template::~Descriptor_update_template()
    {
        init_show;
        show_function_name;
        descriptor_set_layout->device->api.vkDestroyDescriptorUpdateTemplate(
            descriptor_set_layout->device->handle,
            handle, 
            allocation_callbacks
        );
    }




    std::shared_ptr<Render_pass> Device::get_a_render_pass(
        std::vector<VkAttachmentDescription>* attachments,
        std::vector<VkSubpassDescription>* subpasses,
        std::vector<VkSubpassDependency>* dependencies,
        const void* next_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Render_pass> render_pass_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkRenderPassCreateInfo info{
            VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            next_,
            0,
            static_cast<uint32_t>(attachments == nullptr ? 0 : attachments->size()),
            attachments == nullptr ? NULL : &(*attachments)[0],

            static_cast<uint32_t>(subpasses == nullptr ? 0 : subpasses->size()),
            subpasses == nullptr ? NULL : &(*subpasses)[0],

            static_cast<uint32_t>(dependencies == nullptr ? 0 : dependencies->size()),
            dependencies == nullptr ? NULL : &(*dependencies)[0],
        };

        VkRenderPass render_pass_handle;
        auto ret = api.vkCreateRenderPass(
            handle, &info, the_allocator, &render_pass_handle);
        show_result(ret);

        if (ret < 0) 
        {
            init_show;
            show_wrn("创建 render pass 失败");
            return render_pass_sptr;
        }

        render_pass_sptr.reset(
            new Render_pass(shared_from_this(),render_pass_handle, the_allocator));

        return render_pass_sptr;
    }

    Render_pass::Render_pass(
        shared_ptr<Device> device_,
        VkRenderPass handle_,
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Render_pass::~Render_pass()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyRenderPass(device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Frame_buffer> Render_pass::get_a_frame_buffer(
        std::vector<VkImageView>* attachments,
        uint32_t width,
        uint32_t height,
        uint32_t layers,
        const VkAllocationCallbacks* pAllocator_ /* = nullptr */)
    {
        shared_ptr<Frame_buffer> frame_buffer_sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        auto attachments_count =
            static_cast<uint32_t>(attachments == nullptr ? 0 : attachments->size());

        auto attachments_ptr = attachments == nullptr ? nullptr : &(*attachments)[0];

        VkFramebufferCreateInfo info{
            VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            NULL,
            0,
            handle,
            attachments_count,
            attachments_ptr,
            width,
            height,
            layers
        };

        VkFramebuffer frame_buffer_handle;
        auto ret = device->api.vkCreateFramebuffer(
            device->handle, &info, the_allocator, &frame_buffer_handle);
        show_result(ret);

        if (ret < 0)
        {
            init_show;
            show_wrn("创建 frame buffer 失败");
            return frame_buffer_sptr;
        }

        frame_buffer_sptr.reset(
            new Frame_buffer(shared_from_this(),frame_buffer_handle, the_allocator));

        return frame_buffer_sptr;
    }

    Frame_buffer::Frame_buffer(
        std::shared_ptr<Render_pass> render_pass_,
        VkFramebuffer handle_,
        const VkAllocationCallbacks* pAllocator_)
        : render_pass(render_pass_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Frame_buffer::~Frame_buffer()
    {
        init_show;
        show_function_name;
        render_pass->device->api.vkDestroyFramebuffer(
            render_pass->device->handle, handle, allocation_callbacks);
    }


    std::shared_ptr<Pipeline_layout> Device::get_a_pipeline_layout(
        std::vector<VkPushConstantRange>* push_constant_ranges_,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Pipeline_layout> pipeline_layout_sptr;

        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        auto ranges_count =
            static_cast<uint32_t>(push_constant_ranges_ == nullptr ? 0 : push_constant_ranges_->size());

        auto ranges_ptr =
            push_constant_ranges_ == nullptr ? nullptr : &(*push_constant_ranges_)[0];

        VkPipelineLayoutCreateInfo info{
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            NULL,
            0,
            0,
            NULL,
            ranges_count,
            ranges_ptr
        };

        VkPipelineLayout pipeline_layout_handle;
        auto ret = api.vkCreatePipelineLayout(
            handle, &info, the_allocator, &pipeline_layout_handle
        );
        show_result(ret);
        if (ret < 0) return pipeline_layout_sptr;

        pipeline_layout_sptr.reset(new Pipeline_layout(
            shared_from_this(), pipeline_layout_handle, the_allocator)
        );

        return pipeline_layout_sptr;
    }

    Pipeline_layout::Pipeline_layout(
        shared_ptr<Device> device_,
        VkPipelineLayout handle_, 
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    { }

    Pipeline_layout::~Pipeline_layout()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyPipelineLayout(
            device->handle, handle, allocation_callbacks);
    }

    std::shared_ptr<Pipeline_cache> Device::get_a_pipeline_cache(
        size_t      initial_data_size /*= 0*/,
        const void* initial_data_/* = nullptr*/,
        const VkAllocationCallbacks* pAllocator_/* = nullptr*/)
    {
        shared_ptr<Pipeline_cache> pipeline_cache_sptr;

        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkPipelineCacheCreateInfo info{
            VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO,
            NULL,
            0,
            initial_data_size,
            initial_data_
        };

        VkPipelineCache pipeline_cache_handle;
        auto ret = api.vkCreatePipelineCache(
            handle, &info, the_allocator, &pipeline_cache_handle);
        show_result(ret);
        if (ret < 0) return pipeline_cache_sptr;

        pipeline_cache_sptr.reset(new Pipeline_cache(
            shared_from_this(),pipeline_cache_handle, the_allocator));

        pipeline_cache_sptr->device = shared_from_this();

        return pipeline_cache_sptr;
    }

    Pipeline_cache::Pipeline_cache(
        shared_ptr<Device> device_,
        VkPipelineCache handle_, 
        const VkAllocationCallbacks* pAllocator_)
        : device(device_)
        , handle(handle_)
        , allocation_callbacks(pAllocator_)
    {   }

    Pipeline_cache::~Pipeline_cache()
    {
        init_show;
        show_function_name;
        device->api.vkDestroyPipelineCache(
            device->handle, handle, allocation_callbacks);
    }



    std::shared_ptr<Compute_pipeline> Pipeline_layout::get_a_compute_pipeline(
        VkPipelineCreateFlags               flags,
        shared_ptr<Pipeline_cache>         pipeline_cache_,
        std::shared_ptr<Shader_module>      module_,
        const char*                         rukou_name_,
        VkShaderStageFlagBits               stage_flags,
        const VkSpecializationInfo* pSpecializationInfo /* = nullptr */, 
        const VkAllocationCallbacks* pAllocator_ /* = nullptr */)
    {
        shared_ptr<Compute_pipeline> sptr;
        auto the_allocator = pAllocator_ == nullptr ? allocation_callbacks : pAllocator_;

        VkComputePipelineCreateInfo info 
        {
            VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
            nullptr,
            flags,
            {
                VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                nullptr,
                0,
                stage_flags,
                module_->handle,
                rukou_name_,
                pSpecializationInfo
            },
            handle,
            VK_NULL_HANDLE,
            -1
        };

        VkPipeline pipeline_handle;

        auto ret = device->api.vkCreateComputePipelines(
            device->handle,
            pipeline_cache_->handle,
            1,
            &info,
            the_allocator,
            &pipeline_handle
        );

        show_result(ret);
        if (ret < 0)
        {
            init_show;
            show_wrn("创建 compute pipelines 失败");
            return sptr;
        }

        sptr.reset(new Compute_pipeline(
            shared_from_this(),
            pipeline_cache_,
            module_,
            pipeline_handle,
            the_allocator
        ));

        return sptr;
    }

    Compute_pipeline::Compute_pipeline(
        std::shared_ptr<Pipeline_layout> pipeline_layout_,
        std::shared_ptr<Pipeline_cache> pipeline_cache_,
        std::shared_ptr<Shader_module> shader_module_,
        VkPipeline handle_,
        const VkAllocationCallbacks* allocation_callbacks_)
        : pipeline_layout(pipeline_layout_)
        , pipeline_cache(pipeline_cache_)
        , shader_module(shader_module_)
        , handle(handle_)
        , allocation_callbacks(allocation_callbacks_)
    {   }

    Compute_pipeline::~Compute_pipeline()
    {
        init_show;
        show_function_name;
        pipeline_layout->device->api.vkDestroyPipeline(
            pipeline_layout->device->handle, handle, allocation_callbacks);
    }


    
}}
