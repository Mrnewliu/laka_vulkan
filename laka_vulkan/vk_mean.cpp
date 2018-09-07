/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/



#include "vk.h"
#include "vk_mean.h"

using namespace std;


static const char* Unknow_mean = "未知的含义";

static char ntz_table[] = {
    32,0,1,12,2,6,00,13,  3,00,7,00,00,00,00,14,
    10,4,00,00,8,00,00,25, 00,00,00,00,00,21,27,15,
    31,11,5,00,00,00,00,00, 9,00,00,24,00,00,20,26,
    30,00,00,00,23,00,19, 29,00,22,18,28,17,16,00
};

inline int ntz(uint32_t x)
{
    x = (x&-x) * 0x450fbaf;
    return ntz_table[x >> 26];
}

#define MEAN_ \
uint32_t e = e_; \
shared_ptr<string> s(new string());\
for (int i = ntz(e); i != 32; i = ntz(e)) \
{ \
    if (i < sizeof(mean_char) / sizeof(const char*)) \
        {*s+=mean_char[i]; *s+="\n";} \
    else \
        {*s+=Unknow_mean; *s+="\n";} \
    e &= ~(0x1 << i); \
}\
return s;

shared_ptr<string> mean(VkAccessFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_ACCESS_INDIRECT_COMMAND_READ_BIT: 读取作为间接绘图或调度命令的一部分读取的间接命令结构的访问。",
        "VK_ACCESS_INDEX_READ_BIT: 对索引缓冲区的读取访问，作为索引绘图命令的一部分,由vkCmdBindIndexBuffer绑定的。",
        "VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT: 指定对顶点缓冲区的读取访问，作为绘图命令的一部分，由vkCmdBindVertexBuffers绑定。",
        "VK_ACCESS_UNIFORM_READ_BIT: 指定对统一缓冲区的读访问权限。",
        "VK_ACCESS_INPUT_ATTACHMENT_READ_BIT: 指定在片段着色期间对渲染通道内的输入附件的读取访问。",
        "VK_ACCESS_SHADER_READ_BIT: 指定对存储缓冲区，均匀纹理缓冲区，存储纹素缓冲区，采样图像或存储图像的读访问。",
        "VK_ACCESS_SHADER_WRITE_BIT: 指定对存储缓冲区，存储纹素缓冲区或存储器映像的写入访问权限。",
        "VK_ACCESS_COLOR_ATTACHMENT_READ_BIT: 指定对颜色附件的读取访问，例如通过混合，逻辑操作或通过某些子通道加载操作。它不包括高级混合操作。",
        "VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT: 指定对颜色的写访问权限，或在渲染过程中或通过某些子通道加载和存储操作解析附件。",
        "VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT: 指定对深度/模板附件的读取访问，通过深度或模板操作或通过某些子通道加载操作。",
        "VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT: 指定对深度/模板附件的写入访问，通过深度或模板操作或通过某些子通道加载和存储操作。",
        "VK_ACCESS_TRANSFER_READ_BIT: 指定在复制操作中对图像或缓冲区的读访问权限。",
        "VK_ACCESS_TRANSFER_WRITE_BIT: 指定在清除或复制操作中对图像或缓冲区的写入权限。",
        "VK_ACCESS_HOST_READ_BIT: 指定主机操作的读取访问。这种类型的访问不是通过资源执行的，而是直接在内存上执行的。",
        "VK_ACCESS_HOST_WRITE_BIT: 通过主机操作指定写访问。这种类型的访问不是通过资源执行的，而是直接在内存上执行的。",
        "VK_ACCESS_MEMORY_READ_BIT: 指定通过非特定实体的读访问。这些实体包括Vulkan设备和主机，但也可能包含Vulkan设备外部的实体，或者不包含Vulkan核心流水线的一部分。当包含在目标访问掩码中时，使所有可用的写入对Vulkan设备已知的所有实体的所有未来读访问都可见。",
        "VK_ACCESS_MEMORY_WRITE_BIT: 通过非特定实体指定写访问。这些实体包括Vulkan设备和主机，但也可能包含Vulkan设备外部的实体，或者不包含Vulkan核心流水线的一部分。当包含在源访问掩码中时，由Vulkan设备已知的实体执行的所有写入都可用。包含在目标访问掩码中时，使所有可用的写入对Vulkan设备已知实体上的所有将来写入访问都可见。",
        "VK_ACCESS_COMMAND_PROCESS_READ_BIT_NVX: 指定从VkBuffer输入读取到vkCmdProcessCommandsNVX",
        "VK_ACCESS_COMMAND_PROCESS_WRITE_BIT_NVX: 指定在vkCmdProcessCommandsNVX中写入目标命令缓冲区。",
        "VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT: 类似于VK_ACCESS_COLOR_ATTACHMENT_READ_BIT，但也包括高级混合操作",
    };
    MEAN_;
}
shared_ptr<string> mean(VkAttachmentDescriptionFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT specifies that the attachment aliases the same device memory as other attachments."
    };
    MEAN_;
}
shared_ptr<string> mean(VkBufferCreateFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_BUFFER_CREATE_SPARSE_BINDING_BIT: 指定缓冲区将使用稀疏内存绑定进行备份。",
        "VK_BUFFER_CREATE_SPARSE_RESIDENCY_BIT: 指定可以使用稀疏内存绑定部分备份缓冲区。使用此标志创建的缓冲区也必须使用VK_BUFFER_CREATE_SPARSE_BINDING_BIT标志创建。",
        "VK_BUFFER_CREATE_SPARSE_ALIASED_BIT: 指定缓冲区将使用稀疏内存绑定与可能同时支持另一个缓冲区（或同一缓冲区的另一部分）的内存范围进行备份。使用此标志创建的缓冲区也必须使用VK_BUFFER_CREATE_SPARSE_BINDING_BIT标志创建。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkBufferUsageFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_BUFFER_USAGE_TRANSFER_SRC_BIT: 指定缓冲区可以用作传输命令的源",
        "VK_BUFFER_USAGE_TRANSFER_DST_BIT: 指定缓冲区可以用作传输命令的目的地。",
        "VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT: 指定缓冲区可用于创建适合占用VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER类型的VkDescriptorSet插槽的VkBufferView。",
        "VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT: 指定该缓冲区可用于创建适合占用VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER类型的VkDescriptorSet插槽的VkBufferView。",
        "VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT: 指定缓冲区可以用在适合于占用VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER或VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC类型的VkDescriptorSet槽的VkDescriptorBufferInfo中。",
        "VK_BUFFER_USAGE_STORAGE_BUFFER_BIT: 指定缓冲区可以用在适合于占用VK_DESCRIPTOR_TYPE_STORAGE_BUFFER或VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC类型的VkDescriptorSet槽的VkDescriptorBufferInfo中。",
        "VK_BUFFER_USAGE_INDEX_BUFFER_BIT: 指定缓冲区适合作为缓冲区参数传递给vkCmdBindIndexBuffer。",
        "VK_BUFFER_USAGE_VERTEX_BUFFER_BIT: 指定缓冲区适合作为pBuffers阵列的元素传递给vkCmdBindVertexBuffers。",
        "VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT: 指定缓冲区适合作为缓冲区参数传递给vkCmdDrawIndirect，vkCmdDrawIndexedIndirect或vkCmdDispatchIndirect。它也适合作为VkIndirectCommandsTokenNVX的缓冲区成员，或者VkCmdProcessCommandsInfoNVX的sequencesCountBuffer或sequencesIndexBuffer成员",
    };
    MEAN_;
}
shared_ptr<string> mean(VkColorComponentFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_COLOR_COMPONENT_R_BIT: 指定将R值写入适当样本的颜色附件中。否则，内存中的值是未修改的。",
        "VK_COLOR_COMPONENT_G_BIT: 指定将G值写入适当样本的颜色附件中。否则，内存中的值是未修改的。",
        "VK_COLOR_COMPONENT_B_BIT: 指定将B值写入适当样本的颜色附件中。否则，内存中的值是未修改的。",
        "VK_COLOR_COMPONENT_A_BIT: 指定将A值写入适当样本的颜色附件中。否则，内存中的值是未修改的。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkCommandBufferResetFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT: 指定当前由命令缓冲区拥有的大部分或全部内存资源应返回到父命​​令池。如果这个标志没有被设置，那么命令缓冲区可以保持内存资源并且在记录命令时重用它们。commandBuffer被移动到初始状态。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkCommandBufferUsageFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT: 指定每个命令缓冲区的记录只提交一次，命令缓冲区将在每次提交之间重新设置并重新记录。",
        "VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT: 指定辅助命令缓冲区被认为完全在渲染过程中。如果这是一个主要的命令缓冲区，那么这个位被忽略。",
        Unknow_mean,
        "VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT: 指定命令缓冲区在处于挂起状态时可以重新提交给队列，并记录到多个主命令缓冲区中。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkCommandPoolCreateFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_COMMAND_POOL_CREATE_TRANSIENT_BIT: 表示从池中分配的命令缓冲区将是短暂的，这意味着它们将在相对较短的时间内重置或释放。该标志可以被实现用来控制池内的存储器分配行为。",
        "VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT: 允许从池中分配的任何命令缓冲区单独复位到初始状态;调用vkResetCommandBuffer，或通过调用vkBeginCommandBuffer时的隐式重置。如果这个标志没有在一个池上设置，那么vkResetCommandBuffer不能被调用来从该池中分配的任何命令缓冲区。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkCommandPoolResetFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT: 指定重置一个命令池将所有资源从命令池回收到系统。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkCullModeFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_CULL_MODE_NONE: 指定不丢弃三角形",
        "VK_CULL_MODE_FRONT_BIT: 指定丢弃正面的三角形",
        "VK_CULL_MODE_BACK_BIT: 指定丢弃后向三角形",
        "VK_CULL_MODE_FRONT_AND_BACK: 指定所有三角形都被丢弃。",
    };

    MEAN_;
}
shared_ptr<string> mean(VkDependencyFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_DEPENDENCY_BY_REGION_BIT: 指定依赖关系将是帧缓冲区本地的。",
        "VK_DEPENDENCY_VIEW_LOCAL_BIT_KHX: 指定子通道具有多个视图。",
        Unknow_mean,
        "VK_DEPENDENCY_DEVICE_GROUP_BIT_KHX: 指定依赖关系是非设备本地依赖关系。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkDescriptorPoolCreateFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT: 指定描述符集可以将它们各自的分配返回给池，即所有的vkAllocateDescriptorSets，vkFreeDescriptorSets和vkResetDescriptorPool都是允许的。否则，从池中分配的描述符集不能单独释放回池中，即只允许使用vkAllocateDescriptorSets和vkResetDescriptorPool。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkDescriptorSetLayoutCreateFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR: 指定不能使用此布局分配描述符集，而描述符则由vkCmdPushDescriptorSetKHR推送。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkFenceCreateFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_FENCE_CREATE_SIGNALED_BIT: 指定围栏对象在信号状态下创建。否则，它是在无信号状态下创建的。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkFormatFeatureFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT: 指定可以从中采样图像视图。",
        "VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT: 指定可以将图像视图用作存储图像",
        "VK_FORMAT_FEATURE_STORAGE_IMAGE_ATOMIC_BIT: 指定图像视图可以用作支持原子操作的存储图像。",
        "VK_FORMAT_FEATURE_UNIFORM_TEXEL_BUFFER_BIT: 指定可以使用该格式创建可以绑定到VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER描述符的缓冲区视图。",
        "VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_BIT: 指定可以使用该格式创建可以绑定到VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER描述符的缓冲区视图。",
        "VK_FORMAT_FEATURE_STORAGE_TEXEL_BUFFER_ATOMIC_BIT: 指定使用此格式在VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER上支持原子操作。",
        "VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT: 指定该格式可以用作顶点属性格式（VkVertexInputAttributeDescription :: format）。",
        "VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT: 指定图像视图可以用作帧缓冲区颜色附件和输入附件。",
        "VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT: 指定图像视图可用作支持混合和作为输入附件的帧缓冲区颜色附件。",
        "VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT: 指定图像视图可以用作帧缓冲深度/模板附件和输入附件。",
        "VK_FORMAT_FEATURE_BLIT_SRC_BIT: 指定可以将图像用作vrcCmdBlitImage命令的srcImage。",
        "VK_FORMAT_FEATURE_BLIT_DST_BIT: 指定可以将图像用作vkCmdBlitImage命令的dstImage。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT: 指定如果还设置了VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT，则可以将图像视图与采样器一起使用，该采样器将magFilter或minFilter设置为VK_FILTER_LINEAR，或将mipmapMode设置为VK_SAMPLER_MIPMAP_MODE_LINEAR。如果还设置了VK_FORMAT_FEATURE_BLIT_SRC_BIT，则可以将图像用作带有VK_FILTER_LINEAR过滤器的srcImage到vkCmdBlitImage。该位必须仅暴露于也支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT或VK_FORMAT_FEATURE_BLIT_SRC_BIT的格式。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_CUBIC_BIT_IMG: VkImage可以与采样器一起使用，该采样器的magFilter或minFilter设置为VK_FILTER_CUBIC_IMG，或者作为滤波器的源图像设置为VK_FILTER_CUBIC_IMG。此位只能用于支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT的格式。如果被查询的格式是深度 / 模板格式，则这只表示深度方面是立方体可过滤的。",
        "VK_FORMAT_FEATURE_TRANSFER_SRC_BIT_KHR: 指定图像可以用作复制命令的源图像。",
        "VK_FORMAT_FEATURE_TRANSFER_DST_BIT_KHR: 指定图像可以用作复制命令和清除命令的目标图像。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_MINMAX_BIT_EXT: 指定VkImage可用作具有最小或最大VkSamplerReductionModeEXT的采样图像。此位只能用于支持VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT的格式。",
        "VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT_KHR: 指定应用程序可使用此格式定义采样器Y'CBCR转换作为源，并且此格式的图像可与VK_CHROMA_LOCATION_MIDPOINT_KHR的VkSamplerYcbcrConversionCreateInfoKHR xChromaOffset和/或yChromaOffset一起使用。否则，xChromaOffset和yChromaOffset都必须是VK_CHROMA_LOCATION_COSITED_EVEN_KHR。如果格式不包含色度下采样（它不是“422”或“420”格式），但实现支持此格式的采样器Y'CBCR转换，则实现必须设置VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT_KHR。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_LINEAR_FILTER_BIT_KHR: 指定格式可以执行线性采样器过滤（min / magFilter），而采样器Y'CBCR转换启用。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_SEPARATE_RECONSTRUCTION_FILTER_BIT_KHR: 指定格式可以具有不同的色度，最小值和最大值滤波器。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_BIT_KHR: 指定重构是明确的，如色度重构中所述。如果这个位不存在，默认情况下重构是隐含的。",
        "VK_FORMAT_FEATURE_SAMPLED_IMAGE_YCBCR_CONVERSION_CHROMA_RECONSTRUCTION_EXPLICIT_FORCEABLE_BIT_KHR: 指定可以通过将VkSamplerYcbcrConversionCreateInfoKHR :: forceExplicitReconstruction设置为VK_TRUE来强制显示重构。",
        "VK_FORMAT_FEATURE_DISJOINT_BIT_KHR: 指定多平面图像在创建图像时可以设置VK_IMAGE_CREATE_DISJOINT_BIT_KHR。一个实现不能为单平面格式设置VK_FORMAT_FEATURE_DISJOINT_BIT_KHR。",
        "VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT_KHR: 指定应用程序可以使用此格式定义采样器Y'CBCR转换作为源，并且此格式的图像可与VK_CHROMA_LOCATION_COSITED_EVEN_KHR的VkSamplerYcbcrConversionCreateInfoKHR xChromaOffset和/或yChromaOffset一起使用。否则，xChromaOffset和yChromaOffset都必须是VK_CHROMA_LOCATION_MIDPOINT_KHR。如果既没有设置VK_FORMAT_FEATURE_COSITED_CHROMA_SAMPLES_BIT_KHR也没有设置VK_FORMAT_FEATURE_MIDPOINT_CHROMA_SAMPLES_BIT_KHR，则应用程序不能将采用此格式的采样器Y'CBCR转换定义为源。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkImageAspectFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_IMAGE_ASPECT_COLOR_BIT: 指定颜色方面。",
        "VK_IMAGE_ASPECT_DEPTH_BIT: 指定深度方面。",
        "VK_IMAGE_ASPECT_STENCIL_BIT: 指定模板方面。",
        "VK_IMAGE_ASPECT_METADATA_BIT: 指定用于稀疏稀疏资源操作的元数据方面。",
        "VK_IMAGE_ASPECT_PLANE_0_BIT_KHR: ",
        "VK_IMAGE_ASPECT_PLANE_1_BIT_KHR: ",
        "VK_IMAGE_ASPECT_PLANE_2_BIT_KHR: ",
    };
    MEAN_;
}
shared_ptr<string> mean(VkImageCreateFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_IMAGE_CREATE_SPARSE_BINDING_BIT: 指定图像将使用稀疏内存绑定进行备份。",
        "VK_IMAGE_CREATE_SPARSE_RESIDENCY_BIT: 指定可以使用稀疏内存绑定部分备份映像。使用此标志创建的图像也必须使用VK_IMAGE_CREATE_SPARSE_BINDING_BIT标志创建。",
        "VK_IMAGE_CREATE_SPARSE_ALIASED_BIT: 指定图像将使用稀疏的内存绑定与可能同时支持另一个图像（或同一图像的另一部分）的内存范围进行备份。使用此标志创建的图像也必须使用VK_IMAGE_CREATE_SPARSE_BINDING_BIT标志创建",
        "VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT: 指定图像可以用来创建一个与图像格式不同的VkImageView。对于多平面格式，VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT指示可以在图像平面上创建VkImageView。",
        "VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT: 指定该图像可用于创建类型为VK_IMAGE_VIEW_TYPE_CUBE或VK_IMAGE_VIEW_TYPE_CUBE_ARRAY的VkImageView。",
        "VK_IMAGE_CREATE_BIND_SFR_BIT_KHX: 指定图像可以与传递给vkBindImageMemory2KHR的VkBindImageMemoryDe​​viceGroupInfoKHX结构的SFRRectCount成员的非零值一起使用。该标志还具有使图像使用标准稀疏图像块尺寸的效果。",
        "VK_IMAGE_CREATE_2D_ARRAY_COMPATIBLE_BIT_KHR: 指定该图像可用于创建类型为VK_IMAGE_VIEW_TYPE_2D或VK_IMAGE_VIEW_TYPE_2D_ARRAY的VkImageView。",
        "VK_IMAGE_CREATE_BLOCK_TEXEL_VIEW_COMPATIBLE_BIT_KHR: 指示具有压缩格式的图像可用于创建具有未压缩格式的VkImageView，其中图像视图中的每个纹理元素对应于图像的压缩纹理元素块。",
        "VK_IMAGE_CREATE_EXTENDED_USAGE_BIT_KHR: 表示可以使用使用标志来创建图像，该使用标志不支持用于创建图像的格式，但支持至少一种从图像创建的VkImageView可以使用的格式。",
        "VK_IMAGE_CREATE_SAMPLE_LOCATIONS_COMPATIBLE_DEPTH_BIT_EXT: 指定具有深度或深度/模板格式的图像在用作深度/模板附件时可以与自定义样本位置一起使用。",
        "VK_IMAGE_CREATE_DISJOINT_BIT_KHR: 表示多平面格式的图像必须将每个平面分别绑定到内存，而不是对整个图像使用单个内存绑定;这个位的存在区分了一个没有这个位设置的图像的不相交图像。",
        "VK_IMAGE_CREATE_ALIAS_BIT_KHR: 表示使用相同的创建参数创建的两个图像以及别名到相同的内存的图像可以一致地解释内存的内容，但要遵守内存别名部分中描述的规则。该标志还指示不相交图像的每个平面可以与单平面图像共享存储器内非线性表示，并且单平面图像可以与多平面图像共享存储器内非线性表示 - 平面不相交的图像，根据多平面格式兼容格式的规则。如果pNext链包括其handleTypes成员不为0的VkExternalMemoryImageCreateInfoKHR或VkExternalMemoryImageCreateInfoNV结构，则好像设置了VK_IMAGE_CREATE_ALIAS_BIT_KHR。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkImageUsageFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_IMAGE_USAGE_TRANSFER_SRC_BIT: 指定图像可以用作传输命令的来源。",
        "VK_IMAGE_USAGE_TRANSFER_DST_BIT: 指定图像可以用作传输命令的目的地。",
        "VK_IMAGE_USAGE_SAMPLED_BIT: 指定该图像可用于创建适合占用VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE或VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER类型的VkDescriptorSet插槽的VkImageView，并由着色器进行采样。",
        "VK_IMAGE_USAGE_STORAGE_BIT: 指定图像可用于创建适合占用VK_DESCRIPTOR_TYPE_STORAGE_IMAGE类型的VkDescriptorSet插槽的VkImageView。",
        "VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT: 指定该图像可用于创建适合用作颜色的VkImageView或解析VkFramebuffer中的附件。",
        "VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT: 指定该图像可用于创建一个适合在VkFramebuffer中用作深度/模板附件的VkImageView。",
        "VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT: 指定绑定到这个图像的内存已经被分配了VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT（更多细节见内存分配）。这个位可以被设置为任何图像，可以用来创建一个适合用作颜色，分辨率，深度/模板或输入附件的VkImageView。",
        "VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT: 指定该图像可用于创建适合占用VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT类型的VkDescriptorSet槽的VkImageView;作为输入附件从着色器中读取;并用作帧缓冲区中的输入附件。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkMemoryHeapFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_MEMORY_HEAP_DEVICE_LOCAL_BIT: 表示该堆对应于设备本地内存。设备本地内存可能具有与主机本地内存不同的性能特征，并可能支持不同的内存属性标志。",
        "VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHX: 表示在代表多个物理设备的逻辑设备中，存在堆内存的每个物理设备实例。默认情况下，来自这样的堆的分配将被复制到每个物理设备的堆实例。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkMemoryPropertyFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT: 位表示以此类型分配的内存对于设备访问而言是最有效的。当且仅当内存类型属于设置了VK_MEMORY_HEAP_DEVICE_LOCAL_BIT的堆时，才会设置此属性。",
        "VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT: 位表示使用vkMapMemory可以将映射到此类型的内存映射到主机访问。",
        "VK_MEMORY_PROPERTY_HOST_COHERENT_BIT: 位指示不需要主机缓存管理命令vkFlushMappedMemoryRanges和vkInvalidateMappedMemoryRanges来刷新主机写入设备或使设备写入分别对主机可见。",
        "VK_MEMORY_PROPERTY_HOST_CACHED_BIT: 位表示以此类型分配的内存被缓存在主机上。主机内存访问未缓存的内存比缓存的内存要慢，但未缓存的内存始终是主机一致的。",
        "VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT: 位表示内存类型只允许设备访问内存。内存类型不得同时设置VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT和VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT。另外，对象的后备存储器可以由Lazily Allocated Memory中规定的懒惰实现来提供。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkPipelineCreateFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT: 指定创建的管道将不会被优化。使用此标志可能会减少创建管道所用的时间。",
        "VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT: 指定要创建的管道被允许为将在随后调用vkCreateGraphicsPipelines或vkCreateComputePipelines时创建的管道的父节点。",
        "VK_PIPELINE_CREATE_DERIVATIVE_BIT: 指定要创建的管道将是先前创建的父管道的子节点。",
        "VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT_KHX: 指定以DeviceIndex形式装饰的任何着色器输入变量都将被赋值，就像它们被装饰为ViewIndex一样。",
        "VK_PIPELINE_CREATE_DISPATCH_BASE_KHX: 指定计算管道可以与vkCmdDispatchBaseKHX一起使用，且具有非零基本工作组。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkPipelineStageFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT: 指定队列最初接收任何命令的管道阶段。",
        "VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT: 指定消耗Draw / DispatchIndirect数据结构的流水线阶段。这个阶段还包括读取由vkCmdProcessCommandsNVX编写的命令。",
        "VK_PIPELINE_STAGE_VERTEX_INPUT_BIT: 指定消耗顶点和索引缓冲区的管道阶段。",
        "VK_PIPELINE_STAGE_VERTEX_SHADER_BIT: 指定顶点着色器阶段。",
        "VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT: 指定镶嵌控制着色器阶段。",
        "VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT: 指定镶嵌评估着色器阶段。",
        "VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT: 指定几何着色器阶段。",
        "VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT: 指定片段着色器阶段。",
        "VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT: 指定执行早期片段测试（片段着色之前的深度和模板测试）的管道阶段。此阶段还包括具有深度/模板格式的帧缓冲附件的子通道加载操作。",
        "VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT: 指定执行后期片段测试（片段着色之后的深度和模板测试）的管道阶段。此阶段还包括具有深度/模板格式的framebuffer附件的subpass存储操作。",
        "VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT: 指定在从管线输出最终颜色值之后混合的管线阶段。此阶段还包括带颜色格式的帧缓冲附件的子通道加载和存储操作以及多重采样解析操作。",
        "VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT: 指定计算着色器的执行。",
        "VK_PIPELINE_STAGE_TRANSFER_BIT: 指定复制命令的执行。这包括所有复制命令产生的操作，清除命令（除vkCmdClearAttachments外）和vkCmdCopyQueryPoolResults。",
        "VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT: 指定管道中由所有命令生成的操作完成执行的最后阶段。",
        "VK_PIPELINE_STAGE_HOST_BIT: 指定在设备存储器的读取/写入的主机上指示执行的伪级。记录在命令缓冲区中的任何命令都不会调用此阶段。",
        "VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT: 指定所有图形流水线阶段的执行，相当于以下逻辑或："
        "VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT|VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT|VK_PIPELINE_STAGE_VERTEX_INPUT_BIT|VK_PIPELINE_STAGE_VERTEX_SHADER_BIT|VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT|VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT|VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT|VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT|VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT|VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT|VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT|VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT",
        "VK_PIPELINE_STAGE_ALL_COMMANDS_BIT: ",
        "VK_PIPELINE_STAGE_COMMAND_PROCESS_BIT_NVX: 指定管道通过vkCmdProcessCommandsNVX处理设备端生成命令的阶段。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkQueryControlFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_QUERY_CONTROL_PRECISE_BIT: 指定遮挡查询的精度。"
    };

    MEAN_;
}
shared_ptr<string> mean(VkQueryPipelineStatisticFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT: 指定由池管理的查询将计算输入组装阶段处理的顶点数量。对应于不完整基元的顶点可能有助于计数。",
        "VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT: 指定由池管理的查询将计算输入组装阶段处理的基元数量。如果启用基本重启，则重启基本拓扑对计数没有影响。不完整的基元可能被计数。",
        "VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT: 指定由池管理的查询将计算顶点着色器调用的数量。每次调用顶点着色器时，该计数器的值都会增加。",
        "VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT: 指定由池管理的查询将计算几何着色器调用的数量。每次调用几何着色器时，该计数器的值都会增加。在实例化几何着色器的情况下，对于每个单独的实例化调用，几何着色器调用计数被递增。",
        "VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT: 指定由池管理的查询将计算由几何着色器调用生成的基元的数量。每次几何着色器发出一个图元时，计数器的值都会增加。使用SPIR-V指令OpEndPrimitive或OpEndStreamPrimitive重新启动基本拓扑对几何着色器输出基元计数没有影响。",
        "VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT: 指定由池管理的查询将计数由流水线的“原始剪切”阶段处理的基元的数量。每当原始图元到达原始的裁剪阶段，计数器的值就会增加。",
        "VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT: 指定由池管理的查询将计数由流水线的“原始剪切”阶段输出的基元数量。每当一个图元通过原始的裁剪阶段时，计数器的值就会增加。特定输入基元的基本裁剪阶段输出的基元的实际数量是依赖于实现的，但是必须满足以下条件：如果输入基元的至少一个顶点位于剪裁体积内，则计数器增加一个或多个。否则，计数器增加0或更多。",
        "VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT: 指定由池管理的查询将计算片段着色器调用的数量。每次调用片段着色器时，计数器的值都会增加。",
        "VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT: 指定池管理的查询将计算镶嵌控制着色器处理的补丁数量。对于调用镶嵌控制着色器的每个补丁，计数器的值会递增一次。",
        "VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT: 指定由池管理的查询将统计镶嵌评估着色器的调用次数。每次镶嵌评估着色器被调用时，计数器的值都会增加。",
        "VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT: 指定由池管理的查询将计算计算着色器调用的数量。每次计算着色器被调用时，计数器的值都会增加。只要渲染结果保持不变，实现可以跳过某些计算着色器调用的执行，或执行额外的计算着色器调用以实现为依据的原因。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkQueryResultFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_QUERY_RESULT_64_BIT: 指定的结果将被写为一个64位无符号整数值的数组。如果未设置该位，则结果将被写为32位无符号整数值的数组。",
        "VK_QUERY_RESULT_WAIT_BIT: 指定Vulkan将在检索其结果之前等待每个查询的状态变为可用状态。",
        "VK_QUERY_RESULT_WITH_AVAILABILITY_BIT: 指定可用性状态伴随结果。",
        "VK_QUERY_RESULT_PARTIAL_BIT: 指定返回的部分结果是可以接受的。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkQueueFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_QUEUE_GRAPHICS_BIT: 指示此队列系列中的队列支持图形操作。",
        "VK_QUEUE_COMPUTE_BIT: 指示此队列系列中的队列支持计算操作。",
        "VK_QUEUE_TRANSFER_BIT: 指示此队列系列中的队列支持传输操作。",
        "VK_QUEUE_SPARSE_BINDING_BIT: 指示此队列系列中的队列支持稀疏内存管理操作（请参阅稀疏资源）。如果启用了任何稀疏资源功能，则至少有一个队列系列必须支持此位。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkSampleCountFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_SAMPLE_COUNT_1_BIT: 指定每像素一个样本的图像。",
        "VK_SAMPLE_COUNT_2_BIT: 指定每像素2个采样的图像。",
        "VK_SAMPLE_COUNT_4_BIT: 指定每像素4个采样的图像。",
        "VK_SAMPLE_COUNT_8_BIT: 指定每像素8个采样的图像。",
        "VK_SAMPLE_COUNT_16_BIT: 指定每像素16个采样的图像。",
        "VK_SAMPLE_COUNT_32_BIT: 指定每像素32个采样的图像。",
        "VK_SAMPLE_COUNT_64_BIT: 指定每像素64个采样的图像。"
    };
    MEAN_;
}
shared_ptr<string> mean(VkShaderStageFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_SHADER_STAGE_VERTEX_BIT: 指定顶点阶段。",
        "VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT: 指定曲面细分控制阶段。",
        "VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT: 指定曲面细分评估阶段。",
        "VK_SHADER_STAGE_GEOMETRY_BIT: 指定几何阶段。",
        "VK_SHADER_STAGE_FRAGMENT_BIT: 指定片段阶段。",
        "VK_SHADER_STAGE_COMPUTE_BIT: 指定计算阶段。",
        "VK_SHADER_STAGE_ALL_GRAPHICS: 是用作速记的位组合，用于指定上面定义的所有图形阶段（不包括计算阶段）。",
        "VK_SHADER_STAGE_ALL: 是用作速记的位的组合，用于指定设备支持的所有着色器阶段，包括由扩展引入的所有附加阶段。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkSparseImageFormatFlagBits e_)
{
    static const char* mean_char[] = {
        "VK_SPARSE_IMAGE_FORMAT_SINGLE_MIPTAIL_BIT: 指定图像对所有阵列层使用单个mip尾部区域。",
        "VK_SPARSE_IMAGE_FORMAT_ALIGNED_MIP_SIZE_BIT: 指定其尺寸不是稀疏图像块的相应尺寸的整数倍的第一个mip级开始mip尾部区域。",
        "VK_SPARSE_IMAGE_FORMAT_NONSTANDARD_BLOCK_SIZE_BIT: 指定图像使用非标准稀疏图像块维度，并且imageGranularity值与给定格式的标准稀疏图像块维度不匹配。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkSparseMemoryBindFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_SPARSE_MEMORY_BIND_METADATA_BIT: 指定被绑定的内存仅用于元数据方面。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkStencilFaceFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_STENCIL_FACE_FRONT_BIT: 指定只有前面的模板状态集被更新。",
        "VK_STENCIL_FACE_BACK_BIT: 指定只更新模板状态的背部集合。",
        "VK_STENCIL_FRONT_AND_BACK: 是VK_STENCIL_FACE_FRONT_BIT和VK_STENCIL_FACE_BACK_BIT的组合，并指定两组模板状态都被更新。",
    };
    MEAN_;
}
shared_ptr<string> mean(VkSubpassDescriptionFlagBits e_)
{
    static const char* mean_char[] = {
        Unknow_mean,
        "VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX: 指定为该子通道编译的着色器在每个顶点处理阶段的单次调用中写入所有视图的属性。对于包含此位的子通道编译的所有流水线，除了非按视图（例如位置）输出外，还必须将每个视图的属性写入代码：* PerViewNV []着色器输出。",
        "VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX: 指定为此子通道编译的着色器使用只在x分量中的值不同的每个视图位置。每个视图视口掩码也可以使用。"
    };
    MEAN_;
}

//
//shared_ptr<string> mean(VkQueueFlags)
//{
//
//}



shared_ptr<string> mean(VkLayerProperties& stru_)
{
    shared_ptr<string> result_string(new string);
    auto& s = *result_string;
    s = s +
        "层名称:" + stru_.layerName +
        "\n图层版本" + laka::vk::version_str(stru_.implementationVersion) +
        "\n写入图层的Vulkan版本:" + laka::vk::version_str(stru_.specVersion) +
        "\n描述:" + stru_.description;

    return result_string;
}

shared_ptr<string> mean(VkExtensionProperties& stru_)
{
    shared_ptr<string> result_string(new string);
    auto& s = *result_string;
    
    s = s +
        "扩展名称:" + stru_.extensionName +
        "扩展的版本:" + laka::vk::version_str(stru_.specVersion);

    return result_string;
}

shared_ptr<string> mean(VkPhysicalDeviceFeatures& stru_)
{
    shared_ptr<string> result_string(new string);
    auto& s = *result_string;

#define mean_bool__(name__) \
#name__ ":" + (stru_.name__?"是":"否") + "\n" + 

#define table_physical_device_features(a ,b) \
 a robustBufferAccess b \
 a fullDrawIndexUint32 b \
 a imageCubeArray b \
 a independentBlend b \
 a geometryShader b \
 a tessellationShader b \
 a sampleRateShading b \
 a dualSrcBlend b \
 a logicOp b \
 a multiDrawIndirect b \
 a drawIndirectFirstInstance b \
 a depthClamp b \
 a depthBiasClamp b \
 a fillModeNonSolid b \
 a depthBounds b \
 a wideLines b \
 a largePoints b \
 a alphaToOne b \
 a multiViewport b \
 a samplerAnisotropy b \
 a textureCompressionETC2 b \
 a textureCompressionASTC_LDR b \
 a textureCompressionBC b \
 a occlusionQueryPrecise b \
 a pipelineStatisticsQuery b \
 a vertexPipelineStoresAndAtomics b \
 a fragmentStoresAndAtomics b \
 a shaderTessellationAndGeometryPointSize b \
 a shaderImageGatherExtended b \
 a shaderStorageImageExtendedFormats b \
 a shaderStorageImageMultisample b \
 a shaderStorageImageReadWithoutFormat b \
 a shaderStorageImageWriteWithoutFormat b \
 a shaderUniformBufferArrayDynamicIndexing b \
 a shaderSampledImageArrayDynamicIndexing b \
 a shaderStorageBufferArrayDynamicIndexing b \
 a shaderStorageImageArrayDynamicIndexing b \
 a shaderClipDistance b \
 a shaderCullDistance b \
 a shaderFloat64 b \
 a shaderInt64 b \
 a shaderInt16 b \
 a shaderResourceResidency b \
 a shaderResourceMinLod b \
 a sparseBinding b \
 a sparseResidencyBuffer b \
 a sparseResidencyImage2D b \
 a sparseResidencyImage3D b \
 a sparseResidency2Samples b \
 a sparseResidency4Samples b \
 a sparseResidency8Samples b \
 a sparseResidency16Samples b \
 a sparseResidencyAliased b \
 a variableMultisampleRate b \
 a inheritedQueries b \

    s = s +
        table_physical_device_features(mean_bool__ ZK, YK) "";

    return result_string;
}

//std::shared_ptr<std::string> mean(VkPhysicalDeviceProperties& stru_)
//{
//    shared_ptr<string> result_string(new string);
//    auto& s = *result_string;
//
//    s = s +
//        "API版本:" + laka::vk::version_str(stru_.apiVersion) +
//        "驱动版本:" + laka::vk::version_str(stru_.driverVersion) +
//        "物理设备的供应商唯一标识符:" + to_string(stru_.vendorID) +
//        "物理设备唯一标识符:" + to_string(stru_.deviceID) +
//        "设备类型:" + mean(stru_.deviceType)->c_str();
//
//    return result_string;
//}
//
//shared_ptr<string> mean(VkPhysicalDeviceType& stru_)
//{
//
//}


shared_ptr<std::string> mean(VkResult e_)
{
    static const char* mean0[] = {
        "VK_SUCCESS: 命令成功完成",
        "VK_NOT_READY: 栅栏或查询尚未完成",
        "VK_TIMEOUT: 等待操作在指定的时间内没有完成",
        "VK_EVENT_SET: 事件发出信号",
        "VK_EVENT_RESET: 事件无信号",
    };

    static const char* mean1[] = {
        "VK_INCOMPLETE: 返回数组对于结果来说太小了",
        "VK_ERROR_OUT_OF_HOST_MEMORY: 主机内存分配失败。",
        "VK_ERROR_OUT_OF_DEVICE_MEMORY: 设备内存分配失败。",
        "VK_ERROR_INITIALIZATION_FAILED: 对于实现特定的原因，无法完成对象的初始化。",
        "VK_ERROR_DEVICE_LOST: 逻辑或物理设备已经丢失。",
        "VK_ERROR_MEMORY_MAP_FAILED: 内存对象映射失败。",
        "VK_ERROR_LAYER_NOT_PRESENT: 请求的图层不存在或无法加载。",
        "VK_ERROR_EXTENSION_NOT_PRESENT: 请求的扩展不受支持。",
        "VK_ERROR_FEATURE_NOT_PRESENT: 所请求的特性不受支持。",
        "VK_ERROR_INCOMPATIBLE_DRIVER: 所请求的Vulkan版本不受驱动程序支持，或者由于特定于实现的原因而不兼容。",
        "VK_ERROR_TOO_MANY_OBJECTS: 类型太多的对象已经被创建。",
        "VK_ERROR_FORMAT_NOT_SUPPORTED: 此设备不支持请求的格式。",
        "VK_ERROR_FRAGMENTED_POOL: 由于池的内存碎片，池分配失败。如果不尝试分配主机或设备内存以适应新的分配，则只能返回这个值。这应优先于VK_ERROR_OUT_OF_POOL_MEMORY_KHR返回，但前提是该实现确定池分配失败是由于碎片造成的。",
    };

    static const char* mean2[] = {
        "VK_ERROR_SURFACE_LOST_KHR: 表面不再可用。",
        "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: 请求的窗口已被Vulkan或其他API使用，防止再次使用该窗口。",
        "VK_SUBOPTIMAL_KHR: 交换链不再精确匹配表面属性，但仍可用于成功呈现到表面。",
        "VK_ERROR_OUT_OF_DATE_KHR: 一个表面已经改变，它不再与交换链兼容，使用交换链的进一步的表示请求将失败。应用程序必须查询新的表面属性，并在他们希望继续呈现到表面时重新创建交换链。",
        "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: 交换链使用的显示器不使用相同的可呈现图像布局，或以防止共享图像的方式不兼容。",
        "VK_ERROR_VALIDATION_FAILED_EXT: ",
        "VK_ERROR_INVALID_SHADER_NV: 一个或多个着色器未能编译或链接。如果启用，更多细节会通过VK_EXT_debug_report报告给应用程序。",
        "VK_ERROR_OUT_OF_POOL_MEMORY_KHR: 池内存分配失败。如果不尝试分配主机或设备内存以适应新的分配，则只能返回这个值。如果失败肯定是由于池的碎片造成的，则应该返回VK_ERROR_FRAGMENTED_POOL。",
        "VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR: 外部句柄不是指定类型的有效句柄。",
        "VK_ERROR_NOT_PERMITTED_EXT: ",
    };

    shared_ptr<string> ret;

    if (e_ >= 0 && e_ <= 5)
    {
        ret.reset(new string(mean0[e_]));
        return ret;
    }
    if (e_ <= -1 && e_ >= -12)
    {

        return shared_ptr<string>(new string(mean1[e_*-1]));
    }

    switch (e_)
    {
    case(VK_ERROR_SURFACE_LOST_KHR):return shared_ptr<string>(new string(mean2[0]));
    case (VK_ERROR_NATIVE_WINDOW_IN_USE_KHR): return shared_ptr<string>(new string(mean2[1]));
    case (VK_SUBOPTIMAL_KHR):return shared_ptr<string>(new string(mean2[2]));
    case(VK_ERROR_OUT_OF_DATE_KHR): return shared_ptr<string>(new string(mean2[3]));
    case (VK_ERROR_INCOMPATIBLE_DISPLAY_KHR):return shared_ptr<string>(new string(mean2[4]));
    case(VK_ERROR_VALIDATION_FAILED_EXT):return shared_ptr<string>(new string(mean2[5]));
    case (VK_ERROR_INVALID_SHADER_NV):return shared_ptr<string>(new string(mean2[6]));
    case(VK_ERROR_OUT_OF_POOL_MEMORY_KHR):return shared_ptr<string>(new string(mean2[7]));
    case (VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR):return shared_ptr<string>(new string(mean2[8]));
    case(VK_ERROR_NOT_PERMITTED_EXT):return shared_ptr<string>(new string(mean2[9]));
    default:
        return shared_ptr<string>(new string(Unknow_mean));
        break;
    }


}

namespace laka { namespace vk {

    std::string version_str(uint32_t version)
    {
        std::string s;
        s += std::to_string(VK_VERSION_MAJOR(version));
        s += ".";
        s += std::to_string(VK_VERSION_MINOR(version));
        s += ".";
        s += std::to_string(VK_VERSION_PATCH(version));
        return s;
    }

    void show_result(VkResult ret_)
    {
        init_show;
        if (ret_ >= 0)
        {
            show_debug("{}", mean(ret_)->c_str());
        }
        else
        {
            show_err("{}", mean(ret_)->c_str());
        }
    }

    void show_result_assert(VkResult ret_)
    {
        init_show;
        if (ret_ > 0)
        {
            show_debug("{}", mean(ret_)->c_str());
        }
        else
        {
            show_err("{}", mean(ret_)->c_str());
            assert(ret_ >= 0);
        }
    }

}}

