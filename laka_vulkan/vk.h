/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/


#pragma once
#include <memory>
#include <vector>
#include <list>
#include <map>

#include "laka_vk_define.h"
#include "vk_bits.h"

table_vk_flag(std::shared_ptr<std::string> mean ZK, , s, YK FH);
table_vk_flag(std::shared_ptr<std::string> mean ZK, , Bits, YK FH);
table_vk_enum(std::shared_ptr<std::string> mean ZK, , , YK FH);

namespace laka { namespace vk {

#include "classes.h"

    Module_handle get_module();
    PFN_vkVoidFunction get_instance_proc_address(
        VkInstance instance_, const char* function_name_);

    void show_result(VkResult ret_);
    void show_result_assert(VkResult ret_);

    std::string version_str(uint32_t version);

    template<typename Execute_function>
    PFN_vkVoidFunction return_vk_api(
        VkInstance instance_,
        const char* function_name_,
        Execute_function excute_
    ) {
        init_show;
        show_debug("加载vulkan函数:{0}", function_name_);
        auto fp = get_instance_proc_address(instance_, function_name_);
        if (fp != NULL)
        {
            show_debug("\t成功获得函数地址:{}", (size_t)fp);
        }
        else
        {
            show_err("\t获取函数地址失败");
            excute_();
        }
        return fp;
    }

    template <typename Execute_function>
    PFN_vkVoidFunction return_vk_api(const char* function_name_, Execute_function excute_)
    {
        return return_vk_api(nullptr, function_name_, excute_);
    }

    PFN_vkVoidFunction return_vk_api(const char* function_name_);
    PFN_vkVoidFunction return_vk_api_must(const char* function_name_);
    PFN_vkVoidFunction return_vk_api(VkInstance instance_, const char* function_name_);
    PFN_vkVoidFunction return_vk_api_must(VkInstance instance_, const char* function_name_);

    uint32_t get_instance_version();



    struct Queue_create_info {
        uint32_t queue_family_index;//想要从index队列族创建队列
        std::vector<float> queue_priorities;//每个队列的优先级
    };

    struct Pramater_choose_physical_device {
        Physical_device& if_you_feel_the_physical_device_not_ok_so_return_false;
    };
    struct Pramater_choose_queue_family {
        std::vector<Queue_family_info> const& give_you_queue_family_info_;
        std::vector<Queue_create_info>& waiting_for_your_filled_info_;
    };


    class Instance
        :public std::enable_shared_from_this<Instance> {
    private:
        Instance(
            VkInstance handle_, 
            VkAllocationCallbacks* allocator_callbacks_ptr_);

        VkAllocationCallbacks allocator_callbacks;
    public:
        ~Instance();

        typedef std::shared_ptr<Instance> Sptr;

        static Sptr get_new(
            std::vector<const char*>* enabled_extension_names_ = nullptr,
            uint32_t api_version_ = VK_MAKE_VERSION(1,1,82),
            const void* next_ = nullptr,
            VkAllocationCallbacks* allocator_ = nullptr,
            std::vector<const char*>* enabled_layer_names_ = nullptr,
            const char* app_name_ = "laka::vk",
            uint32_t app_version_ = VK_MAKE_VERSION(0,0,1),
            const char* engine_name_ = "laka::vk::engine",
            uint32_t engine_version_ = VK_MAKE_VERSION(0,0,1)   );

        std::shared_ptr<Device_creator> get_a_device_creator(
            bool(*choose_physical_device_)(Pramater_choose_physical_device& pramater_),
            bool(*choose_queue_family_)(Pramater_choose_queue_family& pramater_),
            VkAllocationCallbacks* allocator_ = nullptr);

        struct {
            table_vk_api_instance(vk_fun ZK, , , YK FH);
            table_vk_api_physical_device(vk_fun ZK, , , YK FH);
            table_vk_api_physical_device_khr(vk_fun ZK, , , YK FH);
        }api;

        const VkInstance handle;
        const VkAllocationCallbacks* allocator_callbacks_ptr;
        std::vector<Physical_device_group> physical_device_groups;
        std::vector<Physical_device> physical_devices;
    };

    class Physical_device {
    public:
        std::shared_ptr<std::vector<VkLayerProperties>>
            get_layer_propertiess();

        std::shared_ptr<std::vector<VkExtensionProperties>>
            get_extension_properties(const char* layer_name_);

        std::shared_ptr<VkPhysicalDeviceFeatures>
            get_features();

        std::shared_ptr<VkPhysicalDeviceProperties>
            get_properties();

        std::shared_ptr<VkPhysicalDeviceMemoryProperties>
            get_memory_properties();

        std::shared_ptr<std::vector<VkQueueFamilyProperties>>
            get_queue_family_properties();

        std::shared_ptr<VkFormatProperties>
            get_format_properties(VkFormat format_);

        std::shared_ptr<VkExternalBufferProperties>
            get_external_buffer_properties(const VkPhysicalDeviceExternalBufferInfo* external_buffer_info_);

        std::shared_ptr<VkExternalFenceProperties>
            get_external_fence_properties(const VkPhysicalDeviceExternalFenceInfo* external_fence_info_);

        std::shared_ptr<VkExternalSemaphoreProperties>
            get_external_semphore_properties(const VkPhysicalDeviceExternalSemaphoreInfo* external_semaphore_info_);

        std::shared_ptr<VkImageFormatProperties2>
            get_image_format_properties(
                const VkPhysicalDeviceImageFormatInfo2* image_format_info_);

        std::shared_ptr<std::vector<VkSparseImageFormatProperties2>>
            get_sparse_image_format_properties(
                const VkPhysicalDeviceSparseImageFormatInfo2* format_info_);

        Instance* instance;
        VkPhysicalDevice handle;
        std::vector<Queue_family_info> queue_familys;
    };

    class Physical_device_group {
    public:
        Instance * instance;
        VkPhysicalDeviceGroupProperties properties;
        std::vector<Physical_device*> physical_devices;
    };

    struct Queue_family_info {
        uint32_t index;
        VkQueueFamilyProperties properties;
    };

    class Queue_family {
    public:
        uint32_t qf_index;
        VkQueueFamilyProperties properties;
        std::vector<Queue> queues;
    };

    class Queue {
    public:
        //VkDevice device_handle;
        VkQueue handle;
        uint32_t family_index;
        float* priorities_ptr;

        struct {
            table_vk_api_queue(vk_fun ZK, , , YK FH);
        }api;

        VkResult wait_idle();
        VkResult submit();
        VkResult bind_sparse();
    };

    class Device_creator
        : public std::enable_shared_from_this<Device_creator> {
    private:
        friend class Device;
        friend class Instance;

        Device_creator(
            std::shared_ptr<Instance> instance_,
            bool(*choose_physical_device_)(Pramater_choose_physical_device& physical_device_),
            bool(*choose_queue_family_)(Pramater_choose_queue_family& parmater_),
            const VkAllocationCallbacks* allocator_ = nullptr);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Device_creator> Sptr;

        std::shared_ptr<Device> get_a_device(
            Physical_device& physical_device_,
            VkDeviceCreateInfo* create_info_);

        std::shared_ptr<Device> get_a_device(
            Physical_device& physical_device_,
            std::vector<char*>* enabled_extensions_ = nullptr,
            VkPhysicalDeviceFeatures* features_ = nullptr);

        std::shared_ptr<Device> get_a_device(
            Physical_device_group& physica_device_group_,
            std::vector<char*>* enabled_extensions_ = nullptr,
            VkPhysicalDeviceFeatures* features_ = nullptr);

        //std::shared_ptr<Device> get_a_device(
        //	std::list<Physical_device>& physical_devices_,
        //	std::vector<char*>* enabled_extensions_ = nullptr,
        //	VkPhysicalDeviceFeatures* features_ = nullptr);

        std::shared_ptr<Instance> instance;

        bool(*choose_physical_device_function)(Pramater_choose_physical_device& physical_device_);
        bool(*choose_queue_family_function)(Pramater_choose_queue_family& parmatwr_);
    };


    class Buffer_view
        :public std::enable_shared_from_this<Buffer_view> {
    private:
        friend class Buffer;

        Buffer_view(
            std::shared_ptr<Buffer> buffer_,
            VkBufferView handle_,
            const VkAllocationCallbacks* pAllocator_
        );

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Buffer_view> Sptr;

        ~Buffer_view();

        std::shared_ptr<Buffer> buffer;
        VkBufferView handle;
    };

    class Buffer :public std::enable_shared_from_this<Buffer> {
    private:
        friend class Device;

        Buffer(
            std::shared_ptr<Device> device_,
            VkBuffer handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Buffer> Sptr;

        class E_Create {
        public:
            enum Bits {
                E_sparse_binding = VK_BUFFER_CREATE_SPARSE_BINDING_BIT,
                E_sparse_residency = VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT,
                E_sparse_aliased = VK_BUFFER_CREATE_SPARSE_ALIASED_BIT,
                E_protected = VK_BUFFER_CREATE_PROTECTED_BIT
            };

            int flag;
            E_Create(int flag_);
            E_Create operator | (E_Create value_);
            E_Create operator | (Bits value_);
        };
          
        class E_Usage {
        public:
            enum Bits {
                E_transfer_src = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                transfer_dst = VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                E_uniform_texel_buffer = VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT,
                E_storage_texel_buffer = VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
                E_uniform_buffer = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                E_storage_buffer = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
                E_index_buffer = VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                E_vertex_buffer = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                E_indirect_buffer = VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT,
                E_conditional_rendering = VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT,
            };

            int flag;
            E_Usage(int flag_);
            E_Usage operator | (E_Usage value_);
            E_Usage operator | (Bits value_);
        };

        ~Buffer();

        std::shared_ptr<Buffer_view> get_a_buffer_view(
            VkFormat		format_,
            VkDeviceSize	offset_,
            VkDeviceSize	range_,
            const VkAllocationCallbacks* pAllocator_ = nullptr
        );

        VkMemoryRequirements get_memory_requirements();

        std::shared_ptr<Device> device;
        VkBuffer handle;
    };

    class Image_view
        :public std::enable_shared_from_this<Image_view> {
    private:
        friend class Image;

        Image_view(
            std::shared_ptr<Image> image_,
            VkImageView handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;

    public:
        typedef std::shared_ptr<Image_view> Sptr;

        ~Image_view();

        std::shared_ptr<Image> image;
        VkImageView handle;
    };

    class Image
        :public std::enable_shared_from_this<Image> {
    private:
        friend class Device;

        Image(
            std::shared_ptr<Device> device_,
            VkImage handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Image> Sptr;

        class E_Create {
        public:
            enum Bits{
                E_sparse_binding = VK_IMAGE_CREATE_SPARSE_BINDING_BIT,
                E_sparse_residency = VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT,
                E_sparse_aliased = VK_IMAGE_CREATE_SPARSE_ALIASED_BIT,
                E_mutable_format = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT,
                E_cube_compatible = VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT,
                E_alias = VK_IMAGE_CREATE_ALIAS_BIT,
                E_split_instance_bind_regions = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT,
                E_2d_array_compatible = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT,
                E_block_texel_view_compatible = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT,
                E_extended_usage = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT,
                E_protected = VK_IMAGE_CREATE_PROTECTED_BIT,
                E_disjoint = VK_IMAGE_CREATE_DISJOINT_BIT,
                
                E_sample_locations_compatible_depth_ext = VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT,
                E_split_instance_bind_regions_khr = VK_IMAGE_CREATE_SPLIT_INSTANCE_BIND_REGIONS_BIT_KHR,
                E_2d_array_compatible_khr = VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT_KHR,
                E_block_texel_view_compatible_khr = VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR,
                E_extended_usage_khr = VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR,
                E_disjoint_khr = VK_IMAGE_CREATE_DISJOINT_BIT_KHR,
                E_alias_khr = VK_IMAGE_CREATE_ALIAS_BIT_KHR,
            };
            int flag;
            E_Create(int flag_);
            E_Create operator | (E_Create value_);
            E_Create operator | (Bits value_);
        };

        class E_Usage {
        public:
            enum Bits {
                E_transfer_src = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
                E_transfer_dst = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
                E_sampled = VK_IMAGE_USAGE_SAMPLED_BIT,
                E_storage = VK_IMAGE_USAGE_STORAGE_BIT,
                E_color_attachment = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                E_depth_stencil_attachment = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
                E_transient_attachment = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
                E_input_attachment = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
            };
            int flag;
            E_Usage(int flag_);
            E_Usage operator | (E_Usage value_);
            E_Usage operator | (Bits value_);
        };

        ~Image();

        std::shared_ptr<Image_view> get_a_image_view(
            VkImageViewType			view_type_,
            VkFormat				format_,
            VkComponentMapping		components_,
            VkImageSubresourceRange subresourceRange_,
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        VkMemoryRequirements get_image_memory_requirements();

        std::shared_ptr<std::vector<VkSparseImageMemoryRequirements>> get_sparse_memory_requirements();

        std::shared_ptr<Device> device;
        VkImage handle;
    };


    class Sampler
        :public std::enable_shared_from_this<Sampler> {
    private:
        friend class Device;

        Sampler(
            std::shared_ptr<Device> device_,
            VkSampler handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Sampler> Sptr;

        ~Sampler();

        std::shared_ptr<Device> device;
        VkSampler handle;
    };

    class Sampler_Ycbcr_conversion
        :public std::enable_shared_from_this<Sampler_Ycbcr_conversion> {
    private:
        friend class Device;

        Sampler_Ycbcr_conversion(
            std::shared_ptr<Device> device_,
            VkSamplerYcbcrConversion handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Sampler_Ycbcr_conversion> Sptr;

        ~Sampler_Ycbcr_conversion();

        std::shared_ptr<Device> device;
        VkSamplerYcbcrConversion handle;
    };


    class Command_buffer
        :public std::enable_shared_from_this<Command_buffer> {
    private:
        friend class Device;
        friend class Command_pool;

        Command_buffer(
            std::shared_ptr<Command_pool> command_pool_,VkCommandBuffer handle_);
    public:
        typedef std::shared_ptr<Command_buffer> Sptr;

        ~Command_buffer();

        VkResult reset(VkCommandBufferResetFlags flags_);




        std::shared_ptr<Command_pool> command_pool;
        VkCommandBuffer handle;
    };

    class Command_buffers
        :public std::enable_shared_from_this<Command_buffers> {
    private:
        friend class Device;
        friend class Command_pool;

        Command_buffers(
            std::shared_ptr<Command_pool> command_pool_,
            std::vector<VkCommandBuffer>& command_buffer_handles_);
    public:
        typedef std::shared_ptr<Command_buffers> Sptr;

        ~Command_buffers();

        std::shared_ptr<Command_pool> command_pool;
        std::vector<VkCommandBuffer> handles;
    };



    class Command_pool
        :public std::enable_shared_from_this<Command_pool> {
    private:
        friend class Device;

        Command_pool(
            std::shared_ptr<Device> device_,
            VkCommandPool handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Command_pool> Sptr;

        class E_Create {
        public:
            enum Bits{
                E_transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
                E_reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
                E_protected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT
            };
            int flag;
            E_Create(int flag_);
            E_Create operator | (E_Create value_);
            E_Create operator | (Bits value_);
        };

        ~Command_pool();

        std::shared_ptr<Command_buffer> get_a_command_buffer(
            VkCommandPool           commandPool,
            VkCommandBufferLevel    level);

        std::shared_ptr<Command_buffers> get_a_command_buffers(
            VkCommandPool           commandPool,
            VkCommandBufferLevel    level,
            uint32_t                command_buffer_count_);

        VkResult reset(VkCommandPoolResetFlags flags);

        void trim(VkCommandPoolTrimFlags flags);


        std::shared_ptr<Device> device;
        VkCommandPool handle;
    };

    class Descriptor_set
        :public std::enable_shared_from_this<Descriptor_set> {
    private:
        friend class Device;
        friend class Descriptor_pool;

        Descriptor_set(
            std::shared_ptr<Descriptor_pool> descriptor_pool_,
            VkDescriptorSet handle_);

    public:
        typedef std::shared_ptr<Descriptor_set> Sptr;

        ~Descriptor_set();

        void update_with_template(VkDescriptorUpdateTemplate template_, const void* data_);

        std::shared_ptr<Descriptor_pool> descriptor_pool;
        VkDescriptorSet handle;
    };

    class Descriptor_sets
        :public std::enable_shared_from_this<Descriptor_sets> {
    private:
        friend class Device;
        friend class Descriptor_pool;

        Descriptor_sets(
            std::shared_ptr<Descriptor_pool> descriptor_pool_,
            std::vector<VkDescriptorSet>& handle_);
    public:
        typedef std::shared_ptr<Descriptor_sets> Sptr;

        ~Descriptor_sets();


        std::shared_ptr<Descriptor_pool> descriptor_pool;
        std::vector<VkDescriptorSet> handles;
    };


    class Descriptor_pool
        :public std::enable_shared_from_this<Descriptor_pool> {
    private:
        friend class Device;

        Descriptor_pool(
            std::shared_ptr<Device> device_,
            VkDescriptorPool handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Descriptor_pool> Sptr;

        class E_Create {
        public:
            enum Bits {
                E_free_descriptor_set = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
                E_update_after_bind = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT_EXT,
            };
            int flag;
            E_Create(int flag_);
            E_Create operator | (E_Create value_);
            E_Create operator | (Bits value_);
        };

        ~Descriptor_pool();

        std::shared_ptr<Descriptor_set> get_a_descriptor_set(
            VkDescriptorSetLayout set_layout,
            const void* next_ = nullptr);

        std::shared_ptr<Descriptor_sets> get_descriptor_sets(
            std::vector<VkDescriptorSetLayout> set_layouts,
            const void* next_ = nullptr);

        VkResult reset(VkDescriptorPoolResetFlags flags);

        std::shared_ptr<Device> device;
        VkDescriptorPool handle;
    };


    class Query_pool
        :public std::enable_shared_from_this<Query_pool> {
    private:
        friend class Device;

        Query_pool(
            std::shared_ptr<Device> device_,
            VkQueryPool handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Query_pool> Sptr;

        class E_Pipeline_statistic {
        public:
            enum Bits {
                E_input_assembly_vertices = VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT,
                E_input_assmbly_primitives = VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT,
                E_vertex_shader_invocations = VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT,
                E_geometry_shader_invocations =  VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT,
                E_geometry_shader_primitives = VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT,
                E_clipping_invocattions = VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT,
                E_clipping_primitives =  VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT,
                E_fragment_shader_invocations = VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT,
                E_tessellation_control_shader_patches = VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT,
                E_tessellation_evaluation_shader_invocations = VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT,
                E_compute_shader_invocations = VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT,
            };
            int flag;
            E_Pipeline_statistic(int flag_);
            E_Pipeline_statistic operator | (E_Pipeline_statistic value_);
            E_Pipeline_statistic operator | (Bits value_);
        };

        ~Query_pool();

        std::shared_ptr<Device> device;
        VkQueryPool handle;
    };



    class Descriptor_update_template
        :public std::enable_shared_from_this<Descriptor_update_template> {
    private:
        friend class Descriptor_set_layout;

        Descriptor_update_template(
            std::shared_ptr<Descriptor_set_layout> descriptor_set_layout_,
            VkDescriptorUpdateTemplate handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Descriptor_update_template> Sptr;

        ~Descriptor_update_template();



        std::shared_ptr<Descriptor_set_layout> descriptor_set_layout;
        VkDescriptorUpdateTemplate handle;
    };


    class Descriptor_set_layout
        :public std::enable_shared_from_this<Descriptor_set_layout> {
    private:
        friend class Device;

        Descriptor_set_layout(
            std::shared_ptr<Device> device_,
            VkDescriptorSetLayout handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Descriptor_set_layout> Sptr;

        class E_Create {
        public:
            enum Bits{
                E_push_descriptor = VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR,
                E_update_after_bind_pool = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT,
            };
            int flag;
            E_Create(int flag_);
            E_Create operator | (E_Create value_);
            E_Create operator | (Bits value_);
        };

        ~Descriptor_set_layout();

        std::shared_ptr<Descriptor_update_template> get_a_descriptor_update_template(
            std::vector<VkDescriptorUpdateTemplateEntry>& entrys_,
            const VkAllocationCallbacks* pAllocator_);

        std::shared_ptr<Device> device;
        VkDescriptorSetLayout handle;
    };



    class Frame_buffer
        :public std::enable_shared_from_this<Frame_buffer> {
    private:
        friend class Render_pass;

        Frame_buffer(
            std::shared_ptr<Render_pass> render_pass_,
            VkFramebuffer handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Frame_buffer> Sptr;

        ~Frame_buffer();

        std::shared_ptr<Render_pass> render_pass;
        VkFramebuffer handle;
    };

    class Render_pass
        :public std::enable_shared_from_this<Render_pass> {
    private:
        friend class Device;

        Render_pass(
            std::shared_ptr<Device> device_,
            VkRenderPass handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Render_pass> Sptr;

        ~Render_pass();

        std::shared_ptr<Frame_buffer> get_a_frame_buffer(
            std::vector<VkImageView>* attachments,
            uint32_t width,
            uint32_t height,
            uint32_t layers,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<VkExtent2D> get_area_granularity();

        std::shared_ptr<Device> device;
        VkRenderPass handle;
    };



    class Compute_pipeline 
        :public std::enable_shared_from_this<Compute_pipeline>{
    private:
        friend class Pipeline_layout;

        Compute_pipeline(
            std::shared_ptr<Pipeline_layout>    pipeline_layout_,
            std::shared_ptr<Pipeline_cache>     pipeline_cache,
            std::shared_ptr<Shader_module>      shader_module_,
            VkPipeline handle_,
            const VkAllocationCallbacks* allocation_callbacks_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Compute_pipeline> Sptr;

        ~Compute_pipeline();


        std::shared_ptr<Pipeline_layout>    pipeline_layout;
        std::shared_ptr<Pipeline_cache>     pipeline_cache;
        std::shared_ptr<Shader_module>      shader_module;
        VkPipeline  handle;
    };

    //还要做批量创建pipeline

    class Graphics_pipeline
        :public std::enable_shared_from_this<Graphics_pipeline>{
    private:
        friend class Pipeline_cache;

        Graphics_pipeline(
        );

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Graphics_pipeline> Sptr;




        ~Graphics_pipeline();

        std::shared_ptr<Pipeline_cache>     pipeline_cache;
        std::shared_ptr<Pipeline_layout>    pipeline_layout;
        std::shared_ptr<Shader_module>      shader_module;
        std::shared_ptr<Render_pass>        render_pass;

        VkPipeline handle;
    };




    
    class Pipeline_layout
        :public std::enable_shared_from_this<Pipeline_layout> {
    private:
        friend class Device;
        friend class Descriptor_set_layout;

        Pipeline_layout(
            std::shared_ptr<Device> device_,
            VkPipelineLayout handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Pipeline_layout> Sptr;

        ~Pipeline_layout();


        std::shared_ptr<Compute_pipeline> get_a_compute_pipeline(
            VkPipelineCreateFlags               flags,
            std::shared_ptr<Pipeline_cache>    pipeline_cache_,
            std::shared_ptr<Shader_module>      module_,
            const char*                         pName,//shader 入口点名称
            VkShaderStageFlagBits               stage_flags,
            const VkSpecializationInfo*         pSpecializationInfo = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Graphics_pipeline> get_a_graphics_pipeline(
        );


        std::shared_ptr<Device> device;
        VkPipelineLayout handle;
    };

    class Pipeline_cache
        :public std::enable_shared_from_this<Pipeline_cache> {
    private:
        friend  class Device;

        Pipeline_cache(
            std::shared_ptr<Device> device_,
            VkPipelineCache handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Pipeline_cache> Sptr;

        ~Pipeline_cache();

        //std::shared_ptr<std::vector<char>> get_data();

        std::shared_ptr<Device> device;
        VkPipelineCache handle;
    };



    struct Pramater_choose_memory_type {
        uint32_t memory_type_count;
        VkMemoryType* memory_types;
    };
    struct Pramater_choose_result
    {
        uint32_t memory_type_index;
    };

    class Device : public std::enable_shared_from_this<Device> {
    private:
        friend class Device_creator;
        friend class Instance;

        Device(
            std::shared_ptr<Instance> instance_, 
            std::shared_ptr<Device_creator> device_creator_,
            std::vector<Physical_device*>& physical_devices_,
            VkDevice handle_,
            const VkAllocationCallbacks* allocation_callbacks_);
        
        PFN_vkVoidFunction return_api(const char* api_name_);
    public:
        typedef std::shared_ptr<Device> Sptr;

        ~Device();

        struct {
            table_vk_api_device(vk_fun ZK, , , YK FH);
            table_vk_api_cmd(vk_fun ZK, , , YK FH);
        }api;

        const VkAllocationCallbacks* allocation_callbacks;

        //std::vector<Queue> queues;
        std::vector<Queue_family> queue_familys;

        std::shared_ptr<Instance> instance;
        std::shared_ptr<Device_creator> device_creator;
        std::vector<Physical_device*> physical_devices;
        VkDevice handle;



        std::shared_ptr <Semaphore> get_a_semaphore(
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr <Fence> get_a_fence(
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr <Event> get_a_event(
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Shader_module> get_a_shader_module(
            const uint32_t*     code_ptr_,
            size_t              code_size_,
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Device_memory> get_a_device_memory(
            VkDeviceSize memory_size_,
            bool(*choose_memory_type_index_)(
                Pramater_choose_memory_type& pramater_choose_,
                Pramater_choose_result& choose_result_),
            void* next_ = nullptr,
            //todo:pNext还需要做得更方便点
            const VkAllocationCallbacks* allocation_callbacks_ = nullptr);

        std::shared_ptr<Buffer> get_a_buffer(
            VkDeviceSize		buffer_size_,
            Buffer::E_Create    create_flags_,
            Buffer::E_Usage	    usage_flags_,
            VkSharingMode		sharing_mode_,
            std::vector<uint32_t> queue_family_indices_,
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Image> get_a_image(
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
            const void*             next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Sampler> get_a_sampler(
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
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Sampler_Ycbcr_conversion> get_a_sampler_ycbcr_conversion(
            VkFormat                        format_,
            VkSamplerYcbcrModelConversion   ycbcrModel,
            VkSamplerYcbcrRange             ycbcrRange,
            VkComponentMapping              components,
            VkChromaLocation                xChromaOffset,
            VkChromaLocation                yChromaOffset,
            VkFilter                        chromaFilter,
            VkBool32                        forceExplicitReconstruction,
            const void*                     next_ = nullptr,
            const VkAllocationCallbacks*    pAllocator_ = nullptr);

        std::shared_ptr<Command_pool> get_a_command_pool(
            uint32_t                    queueFamilyIndex,
            Command_pool::E_Create      flags_,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Descriptor_pool> get_a_descriptor_pool(
            uint32_t                                maxSets,
            std::vector<VkDescriptorPoolSize>&     poolSizes,
            Descriptor_pool::E_Create               flags_,
            const VkAllocationCallbacks*            pAllocator_ = nullptr);

        std::shared_ptr<Query_pool> get_a_query_pool(
            VkQueryType query_type,
            uint32_t    query_count,
            Query_pool::E_Pipeline_statistic queue_pipeline_statistic_flags_,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Descriptor_set_layout> get_a_descriptor_set_layout(
            std::vector<VkDescriptorSetLayoutBinding>* bindings_,
            Descriptor_set_layout::E_Create flags_,
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Render_pass> get_a_render_pass(
            std::vector<VkAttachmentDescription>* attachments,
            std::vector<VkSubpassDescription>* subpasses,
            std::vector<VkSubpassDependency>* dependencies,
            const void* next_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Pipeline_layout> get_a_pipeline_layout(
            std::vector<VkPushConstantRange>* push_constant_ranges_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);

        std::shared_ptr<Pipeline_cache> get_a_pipeline_cache(
            size_t      initial_data_size = 0,
            const void* initial_data_ = nullptr,
            const VkAllocationCallbacks* pAllocator_ = nullptr);


        


        VkResult wait_idle();
        VkResult wait_for_fences(std::vector<VkFence>& fences_, bool wait_all_, uint64_t timeout_);
    };


    class Semaphore :public std::enable_shared_from_this<Semaphore> {
    private:
        friend class Device;

        Semaphore(
            std::shared_ptr<Device> device_,
            VkSemaphore handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Semaphore> Sptr;

        ~Semaphore();

        std::shared_ptr<Device> device;
        VkSemaphore handle;
    };

    class Fence :public std::enable_shared_from_this<Fence> {
    private:
        friend class Device;

        Fence(
            std::shared_ptr<Device> device_,
            VkFence handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Fence> Sptr;

        ~Fence();

        VkResult reset();
        VkResult get_status();

        std::shared_ptr<Device> device;
        VkFence handle;
    };

    class Event :public std::enable_shared_from_this<Event> {
    private:
        friend class Device;

        Event(
            std::shared_ptr<Device> device_,
            VkEvent handle_,
            const VkAllocationCallbacks* pAllocator_);

        VkResult set();
        VkResult get_event_status();
        void reset();

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Event> Sptr;

        ~Event();

        std::shared_ptr<Device> device;
        VkEvent handle;
    };

    class Shader_module
        :public std::enable_shared_from_this<Shader_module> {
    private:
        friend class Device;

        Shader_module(
            Device::Sptr    device_,
            VkShaderModule handle_,
            const VkAllocationCallbacks* pAllocator_);

        const VkAllocationCallbacks* allocation_callbacks;
    public:
        typedef std::shared_ptr<Shader_module> Sptr;

        ~Shader_module();

        std::shared_ptr<Device> device;
        VkShaderModule handle;
    };



    class Device_memory
        :public std::enable_shared_from_this<Device_memory> {
    private:
        friend class Device;

        const VkAllocationCallbacks* allocation_callbacks;

        Device_memory(
            std::shared_ptr<Device> device_,
            VkDeviceMemory handle_,
            const VkAllocationCallbacks* allocation_callbacks_
        );
    public:
        typedef std::shared_ptr<Device_memory> Sptr;

        ~Device_memory();

        VkDeviceSize get_commitment();
        VkResult map_memory(
            VkDeviceSize                                offset,
            VkDeviceSize                                size,
            VkMemoryMapFlags                            flags);

        void unmap_memory();

        VkDeviceMemory handle;
        std::shared_ptr<Device> device;
    };





}}



