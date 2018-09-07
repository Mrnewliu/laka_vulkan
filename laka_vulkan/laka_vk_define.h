/*
Copyright (c) 2018 gchihiha

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

*/


#pragma once
#include "common.h"

#define table_handles(a, aa, bb, b)	\
a aa## VkInstance ##bb b \
a aa## VkPhysicalDevice ##bb b \
a aa## VkDevice ##bb b \
a aa## VkDeviceMemory ##bb b \
a aa## VkBuffer ##bb b \
a aa## VkBufferView ##bb b \
a aa## VkImage ##bb b \
a aa## VkImageView ##bb b \
a aa## VkSampler ##bb b \
a aa## VkFramebuffer ##bb b \
a aa## VkCommandPool ##bb b \
a aa## VkCommandBuffer ##bb b \
a aa## VkQueryPool ##bb b \
a aa## VkQueue ##bb b \
a aa## VkDescriptorSetLayout ##bb b \
a aa## VkDescriptorPool ##bb b \
a aa## VkDescriptorSet ##bb b \
a aa## VkSemaphore ##bb b \
a aa## VkFence ##bb b \
a aa## VkEvent ##bb b \
a aa## VkRenderPass ##bb b \
a aa## VkPipelineLayout ##bb b \
a aa## VkPipelineCache ##bb b \
a aa## VkShaderModule ##bb b \
a aa## VkPipeline ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## VkDescriptorUpdateTemplate ##bb b \
a aa## VkSamplerYcbcrConversion ##bb b \

#define table_vk_api_exportd(a, aa, bb, b) \
a aa## vkGetInstanceProcAddr ##bb b \

#define table_vk_api_global(a, aa, bb, b) \
a aa## vkEnumerateInstanceLayerProperties ##bb b \
a aa## vkEnumerateInstanceExtensionProperties ##bb b \
a aa## vkCreateInstance ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## vkEnumerateInstanceVersion ##bb b \


#define table_vk_api_instance(a, aa, bb, b) \
a aa## vkDestroyInstance ##bb b \
a aa## vkGetDeviceProcAddr ##bb b \
a aa## vkEnumeratePhysicalDevices ##bb b \
a aa## vkCreateDevice ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## vkEnumeratePhysicalDeviceGroups ##bb b \


#define table_vk_api_physical_device(a, aa, bb, b) \
a aa## vkEnumerateDeviceLayerProperties ##bb b \
a aa## vkEnumerateDeviceExtensionProperties ##bb b \
a aa## vkGetPhysicalDeviceFeatures ##bb b \
a aa## vkGetPhysicalDeviceProperties  ##bb b \
a aa## vkGetPhysicalDeviceMemoryProperties ##bb b \
a aa## vkGetPhysicalDeviceFormatProperties ##bb b \
a aa## vkGetPhysicalDeviceQueueFamilyProperties ##bb b \
a aa## vkGetPhysicalDeviceImageFormatProperties ##bb b \
a aa## vkGetPhysicalDeviceSparseImageFormatProperties ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## vkGetPhysicalDeviceExternalBufferProperties ##bb b \
a aa## vkGetPhysicalDeviceExternalFenceProperties ##bb b \
a aa## vkGetPhysicalDeviceExternalSemaphoreProperties ##bb b \
a aa## vkGetPhysicalDeviceFeatures2 ##bb b \
a aa## vkGetPhysicalDeviceProperties2 ##bb b \
a aa## vkGetPhysicalDeviceMemoryProperties2 ##bb b \
a aa## vkGetPhysicalDeviceFormatProperties2 ##bb b \
a aa## vkGetPhysicalDeviceImageFormatProperties2 ##bb b \
a aa## vkGetPhysicalDeviceQueueFamilyProperties2 ##bb b \
a aa## vkGetPhysicalDeviceSparseImageFormatProperties2 ##bb b \

#define table_vk_api_physical_device_khr(a, aa, bb, b) \
a aa## vkGetPhysicalDeviceSurfaceSupportKHR ##bb b \

#define table_vk_struct_physical_device(a,aa,bb,b) \
a aa## VkLayerProperties ##bb b \
a aa## VkExtensionProperties ##bb b \
a aa## VkPhysicalDeviceFeatures ##bb b \
a aa## VkPhysicalDeviceProperties ##bb b \
a aa## VkPhysicalDeviceMemoryProperties ##bb b \
a aa## VkFormatProperties ##bb b \
a aa## VkImageFormatProperties ##bb b \
a aa## VkQueueFamilyProperties ##bb b \
a aa## VkSparseImageFormatProperties ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## VkExternalBufferProperties ##bb b \
a aa## VkPhysicalDeviceExternalFenceInfo ##bb b \
a aa## VkExternalFenceProperties ##bb b \
a aa## VkPhysicalDeviceExternalSemaphoreInfo ##bb b \
a aa## VkExternalSemaphoreProperties ##bb b \
a aa## VkPhysicalDeviceFeatures2 ##bb b \
a aa## VkPhysicalDeviceProperties2 ##bb b \
a aa## VkPhysicalDeviceMemoryProperties2 ##bb b \
a aa## VkFormatProperties2 ##bb b \
a aa## VkImageFormatProperties2 ##bb b \
a aa## VkPhysicalDeviceImageFormatInfo2 ##bb b \
a aa## VkQueueFamilyProperties2 ##bb b \
a aa## VkPhysicalDeviceSparseImageFormatInfo2 ##bb b \
a aa## VkSparseImageFormatProperties2 ##bb b \


#define table_vk_api_device(a, aa, bb, b) \
a aa## vkDestroyDevice ##bb b \
a aa## vkGetDeviceQueue ##bb b \
a aa## vkAllocateMemory ##bb b \
a aa## vkFreeMemory ##bb b \
a aa## vkMapMemory ##bb b \
a aa## vkUnmapMemory ##bb b \
a aa## vkFlushMappedMemoryRanges ##bb b \
a aa## vkInvalidateMappedMemoryRanges ##bb b \
a aa## vkGetDeviceMemoryCommitment ##bb b \
a aa## vkCreateBuffer ##bb b \
a aa## vkDestroyBuffer ##bb b \
a aa## vkCreateBufferView ##bb b \
a aa## vkDestroyBufferView ##bb b \
a aa## vkBindBufferMemory ##bb b \
a aa## vkCreateCommandPool ##bb b \
a aa## vkResetCommandPool ##bb b \
a aa## vkDestroyCommandPool ##bb b \
a aa## vkAllocateCommandBuffers ##bb b \
a aa## vkResetCommandBuffer ##bb b \
a aa## vkFreeCommandBuffers ##bb b \
a aa## vkQueueSubmit ##bb b \
a aa## vkCreateEvent ##bb b \
a aa## vkGetEventStatus ##bb b \
a aa## vkResetEvent ##bb b \
a aa## vkSetEvent ##bb b \
a aa## vkDestroyEvent ##bb b \
a aa## vkCreateFence ##bb b \
a aa## vkResetFences ##bb b \
a aa## vkGetFenceStatus ##bb b \
a aa## vkWaitForFences ##bb b \
a aa## vkDestroyFence ##bb b \
a aa## vkCreateSemaphore ##bb b \
a aa## vkDestroySemaphore ##bb b \
a aa## vkQueueWaitIdle ##bb b \
a aa## vkDeviceWaitIdle ##bb b \
a aa## vkBeginCommandBuffer ##bb b \
a aa## vkEndCommandBuffer ##bb b \
a aa## vkCreateQueryPool ##bb b \
a aa## vkGetQueryPoolResults ##bb b \
a aa## vkDestroyQueryPool ##bb b \
a aa## vkCreateFramebuffer ##bb b \
a aa## vkDestroyFramebuffer ##bb b \
a aa## vkCreateSampler ##bb b \
a aa## vkDestroySampler ##bb b \
a aa## vkCreateShaderModule ##bb b \
a aa## vkDestroyShaderModule ##bb b \
a aa## vkGetRenderAreaGranularity ##bb b \
a aa## vkCreateRenderPass ##bb b \
a aa## vkDestroyRenderPass ##bb b \
a aa## vkCreateImage ##bb b \
a aa## vkDestroyImage ##bb b \
a aa## vkCreateImageView ##bb b \
a aa## vkDestroyImageView ##bb b \
a aa## vkBindImageMemory ##bb b \
a aa## vkCreateComputePipelines ##bb b \
a aa## vkCreateGraphicsPipelines ##bb b \
a aa## vkDestroyPipeline ##bb b \
a aa## vkCreatePipelineCache ##bb b \
a aa## vkDestroyPipelineCache ##bb b \
a aa## vkCreatePipelineLayout ##bb b \
a aa## vkDestroyPipelineLayout ##bb b \
a aa## vkGetPipelineCacheData ##bb b \
a aa## vkMergePipelineCaches ##bb b \
a aa## vkCreateDescriptorPool ##bb b \
a aa## vkResetDescriptorPool ##bb b \
a aa## vkDestroyDescriptorPool ##bb b \
a aa## vkAllocateDescriptorSets ##bb b \
a aa## vkUpdateDescriptorSets ##bb b \
a aa## vkFreeDescriptorSets ##bb b \
a aa## vkCreateDescriptorSetLayout ##bb b \
a aa## vkDestroyDescriptorSetLayout ##bb b \
a aa## vkGetBufferMemoryRequirements ##bb b \
a aa## vkGetImageMemoryRequirements ##bb b \
a aa## vkQueueBindSparse ##bb b \
a aa## vkGetImageSparseMemoryRequirements ##bb b \
a aa## vkGetImageSubresourceLayout ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## vkGetDeviceQueue2 ##bb b \
a aa## vkBindBufferMemory2 ##bb b \
a aa## vkBindImageMemory2 ##bb b \
a aa## vkCreateDescriptorUpdateTemplate ##bb b \
a aa## vkUpdateDescriptorSetWithTemplate ##bb b \
a aa## vkDestroyDescriptorUpdateTemplate ##bb b \
a aa## vkCreateSamplerYcbcrConversion ##bb b \
a aa## vkDestroySamplerYcbcrConversion ##bb b \
a aa## vkGetBufferMemoryRequirements2 ##bb b \
a aa## vkGetDescriptorSetLayoutSupport ##bb b \
a aa## vkGetDeviceGroupPeerMemoryFeatures ##bb b \
a aa## vkGetImageMemoryRequirements2 ##bb b \
a aa## vkGetImageSparseMemoryRequirements2 ##bb b \
a aa## vkTrimCommandPool ##bb b \

#define table_vk_api_queue(a, aa, bb, b) \
a aa## vkQueueSubmit ##bb b \
a aa## vkQueueWaitIdle ##bb b \
a aa## vkQueueBindSparse ##bb b \

#define table_vk_api_device_memory(a, aa, bb, b)\
a aa## vkFreeMemory ##bb b \
a aa## vkMapMemory ##bb b \
a aa## vkUnmapMemory ##bb b \
a aa## vkGetDeviceMemoryCommitment ##bb b \


#define table_vk_api_cmd(a, aa, bb, b) \
a aa## vkCmdDispatch ##bb b \
a aa## vkCmdDispatchIndirect ##bb b \
a aa## vkCmdExecuteCommands ##bb b \
a aa## vkCmdWaitEvents ##bb b \
a aa## vkCmdSetEvent ##bb b \
a aa## vkCmdResetEvent ##bb b \
a aa## vkCmdPipelineBarrier ##bb b \
a aa## vkCmdCopyBuffer ##bb b \
a aa## vkCmdFillBuffer ##bb b \
a aa## vkCmdUpdateBuffer ##bb b \
a aa## vkCmdBindDescriptorSets ##bb b \
a aa## vkCmdBindIndexBuffer ##bb b \
a aa## vkCmdBindPipeline ##bb b \
a aa## vkCmdBindVertexBuffers ##bb b \
a aa## vkCmdBeginRenderPass ##bb b \
a aa## vkCmdNextSubpass ##bb b \
a aa## vkCmdEndRenderPass ##bb b \
a aa## vkCmdDraw ##bb b \
a aa## vkCmdDrawIndexed ##bb b \
a aa## vkCmdDrawIndexedIndirect ##bb b \
a aa## vkCmdDrawIndirect ##bb b \
a aa## vkCmdCopyBufferToImage ##bb b \
a aa## vkCmdCopyImageToBuffer ##bb b \
a aa## vkCmdCopyImage ##bb b \
a aa## vkCmdBlitImage ##bb b \
a aa## vkCmdClearDepthStencilImage ##bb b \
a aa## vkCmdClearColorImage ##bb b \
a aa## vkCmdPushConstants ##bb b \
a aa## vkCmdResolveImage ##bb b \
a aa## vkCmdClearAttachments ##bb b \
a aa## vkCmdSetViewport ##bb b \
a aa## vkCmdSetScissor ##bb b \
a aa## vkCmdSetStencilCompareMask ##bb b \
a aa## vkCmdSetStencilWriteMask ##bb b \
a aa## vkCmdSetStencilReference ##bb b \
a aa## vkCmdSetLineWidth ##bb b \
a aa## vkCmdSetDepthBounds ##bb b \
a aa## vkCmdSetBlendConstants ##bb b \
a aa## vkCmdSetDepthBias ##bb b \
a aa## vkCmdBeginQuery ##bb b \
a aa## vkCmdResetQueryPool ##bb b \
a aa## vkCmdCopyQueryPoolResults ##bb b \
a aa## vkCmdWriteTimestamp ##bb b \
a aa## vkCmdEndQuery ##bb b \
/*1.0.62 Above    1.1.81 Below*/\
a aa## vkCmdDispatchBase ##bb b \
a aa## vkCmdSetDeviceMask ##bb b \




//默认开启surface 要关闭就定义DISABLE_VK_WSI
#if !defined(DISABLE_VK_WSI)

#   if defined(LAKA_WIN)
#       define VK_USE_PLATFORM_WIN32_KHR    1
#   elif defined(LAKA_LINUX)
//VK_USE_PLATFORM_WAYLAND_KHR
//VK_USE_PLATFORM_XCB_KHR
//VK_USE_PLATFORM_XLIB_XRANDR_EXT
//VK_USE_PLATFORM_XLIB_KHR
//VK_USE_PLATFORM_MIR_KHR
#   elif defined(LAKA_ANDROID)
#       define VK_USE_PLATFORM_ANDROID_KHR  1
#   elif defined(LAKA_IPHONE)
#       define VK_USE_PLATFORM_IOS_MVK  1
#   elif defined(LAKA_MAC)
#       define VK_USE_PLATFORM_MACOS_MVK    1
#   elif   0 //NN - 任天堂
#       define VK_USE_PLATFORM_VI_NN    1
#   endif


#   if defined(LAKA_APPLE)
#       include "TargetConditionals.h"
#   endif
#endif

#if defined(VK_USE_PLATFORM_WIN32_KHR)

#   define external_memory_spec_version VK_KHR_EXTERNAL_MEMORY_WIN32_SPEC_VERSION
#   define external_memory_extension_name VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateWin32SurfaceKHR #bb b \
a aa## vkGetPhysicalDeviceWin32PresentationSupportKHR #bb b \
a aa## vkGetMemoryWin32HandleKHR #bb b \
a aa## vkGetMemoryWin32HandlePropertiesKHR #bb b \
a aa## vkImportSemaphoreWin32HandleKHR #bb b \
a aa## vkGetSemaphoreWin32HandleKHR #bb b \
a aa## vkImportFenceWin32HandleKHR #bb b \
a aa## vkGetFenceWin32HandleKHR #bb b \

#   define table_vk_api_device_platform(a, aa, bb, b)\
a aa## vkGetMemoryWin32HandleNV #bb b \

//副作用 无法使用WIN32宏
//#undef WIN32

#define platform_Name   win32
#define Platform_Name   Win32
#define WRITER_NAME     KHR
#define PLATFORM_NAME   WIN32

#define wsi_info_T1(a, b) a HINSTANCE b 
#define wsi_info_T2(a, b) a HWND b 
#define wsi_info_V1(a, b) a hinstance b
#define wsi_info_V2(a, b) a hwnd b

#define surface_spec_version VK_KHR_WIN32_SURFACE_SPEC_VERSION
#define surface_extension_name VK_KHR_WIN32_SURFACE_EXTENSION_NAME

#endif

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
#define platform_Name   android
#define Platform_Name   Android
#define WRITER_NAME     KHR
#define PLATFORM_NAME   ANDROID

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateAndroidSurfaceKHR #bb b \
a aa## vkGetAndroidHardwareBufferPropertiesANDROID #bb b \
a aa## vkGetMemoryAndroidHardwareBufferANDROID #bb b \

#define wsi_info_T1(a, b)  a ANativeWindow* b 
#define wsi_info_T2(a, b)    
#define wsi_info_V1(a, b) a window b
#define wsi_info_V2(a, b) 

#endif

#if defined(VK_USE_PLATFORM_IOS_MVK)
#define platform_Name   ios
#define Platform_Name   Ios
#define WRITER_NAME     MVK
#define PLATFORM_NAME   IOS

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateIOSSurfaceMVK ##bb b \

#define wsi_info_T1(a, b) a void* b 
#define wsi_info_T2(a, b) 
#define wsi_info_V1(a, b) a pView b 
#define wsi_info_V2(a, b) 

#endif

#if defined(VK_USE_PLATFORM_MACOS_MVK)
#define platform_Name   macos
#define Platform_Name   Macos
#define WRITER_NAME     MVK
#define PLATFORM_NAME   MACOS

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateMacOSSurfaceMVK ##bb b \

#define wsi_info_T1(a, b) a void* b 
#define wsi_info_T2(a, b) 
#define wsi_info_V1(a, b) a pView b 
#define wsi_info_V2(a, b) 

#endif

#if defined(VK_USE_PLATFORM_MIR_KHR)
#define platform_Name   mir
#define Platform_Name   Mir
#define WRITER_NAME     KHR
#define PLATFORM_NAME   MIR

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateMirSurfaceKHR ##bb b \
a aa## vkGetPhysicalDeviceMirPresentationSupportKHR ##bb b \

#define wsi_info_T1(a, b) a MirConnection* b 
#define wsi_info_T2(a, b) a MirSurface* b 
#define wsi_info_1(a, b) a connection b 
#define wsi_info_2(a, b) a mirSurface b 

#endif

#if defined(VK_USE_PLATFORM_VI_NN)
#define platform_Name   vi
#define Platform_Name   Vi
#define WRITER_NAME     NN
#define PLATFORM_NAME   VI

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateViSurfaceNN ##bb b \

#define wsi_info_T1(a, b) a void* b 
#define wsi_info_T2(a, b) 
#define wsi_info_V1(a, b) a window b 
#define wsi_info_V2(a, b) 

#endif

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
#define platform_Name   wayland
#define Platform_Name   Wayland
#define WRITER_NAME     KHR
#define PLATFORM_NAME   WAYLAND

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateWaylandSurfaceKHR ##bb b \
a aa## vkGetPhysicalDeviceWaylandPresentationSupportKHR ##bb b \

#define wsi_info_T1(a, b) a struct wl_display* b 
#define wsi_info_T2(a, b) a struct wl_surface* b  
#define wsi_info_V1(a, b) a display b 
#define wsi_info_V2(a, b) a surface b 

#endif

#if defined(VK_USE_PLATFORM_XCB_KHR)
#define platform_Name   xcb
#define Platform_Name   Xcb
#define WRITER_NAME     KHR
#define PLATFORM_NAME   XCB

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateXcbSurfaceKHR ##bb b \
a aa## vkGetPhysicalDeviceXcbPresentationSupportKHR ##bb b \

#define wsi_info_T1(a, b) a xcb_connection_t* b 
#define wsi_info_T2(a, b) a xcb_window_t b 
#define wsi_info_V1(a, b) a connection b 
#define wsi_info_V2(a, b) a window b 

#endif

#if defined(VK_USE_PLATFORM_XLIB_KHR)
#define platform_Name   xlib
#define Platform_Name   Xlib
#define WRITER_NAME     KHR
#define PLATFORM_NAME   XLIB

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkCreateXlibSurfaceKHR ##bb b \
a aa## vkGetPhysicalDeviceXlibPresentationSupportKHR ##bb b \

#define wsi_info_T1(a, b) a Display* b 
#define wsi_info_T2(a, b) a Window b 
#define wsi_info_V1(a, b) a dpy b 
#define wsi_info_V2(a, b) a window b 

#endif

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
#define platform_Name   xlib_display
#define Platform_Name   Xlib_display
#define WRITER_NAME     EXT
#define PLATFORM_NAME   XLIB_DISPLAY

#   define table_vk_api_platform(a, aa, bb, b) \
a aa## vkAcquireXlibDisplayEXT ##bb b \
a aa## vkGetRandROutputDisplayEXT ##bb b \


//????

#endif

#if defined(table_vk_api_platform)



#else



#endif


#define table_vk_flag(a, aa, bb, b) \
a aa## VkAccessFlag ##bb b \
a aa## VkAttachmentDescriptionFlag ##bb b \
a aa## VkBufferCreateFlag ##bb b \
a aa## VkBufferUsageFlag ##bb b \
a aa## VkColorComponentFlag ##bb b \
a aa## VkCommandBufferResetFlag ##bb b \
a aa## VkCommandBufferUsageFlag ##bb b \
a aa## VkCommandPoolCreateFlag ##bb b \
a aa## VkCommandPoolResetFlag ##bb b \
a aa## VkCullModeFlag ##bb b \
a aa## VkDependencyFlag ##bb b \
a aa## VkDescriptorPoolCreateFlag ##bb b \
a aa## VkDescriptorSetLayoutCreateFlag ##bb b \
a aa## VkDeviceQueueCreateFlag ##bb b \
a aa## VkExternalFenceFeatureFlag ##bb b \
a aa## VkExternalFenceHandleTypeFlag ##bb b \
a aa## VkExternalMemoryFeatureFlag ##bb b \
a aa## VkExternalMemoryHandleTypeFlag ##bb b \
a aa## VkExternalSemaphoreFeatureFlag ##bb b \
a aa## VkExternalSemaphoreHandleTypeFlag ##bb b \
a aa## VkFenceCreateFlag ##bb b \
a aa## VkFenceImportFlag ##bb b \
a aa## VkFormatFeatureFlag ##bb b \
a aa## VkImageAspectFlag ##bb b \
a aa## VkImageCreateFlag ##bb b \
a aa## VkImageUsageFlag ##bb b \
a aa## VkMemoryAllocateFlag ##bb b \
a aa## VkMemoryHeapFlag ##bb b \
a aa## VkMemoryPropertyFlag ##bb b \
a aa## VkPeerMemoryFeatureFlag ##bb b \
a aa## VkPipelineCreateFlag ##bb b \
a aa## VkPipelineStageFlag ##bb b \
a aa## VkQueryControlFlag ##bb b \
a aa## VkQueryPipelineStatisticFlag ##bb b \
a aa## VkQueryResultFlag ##bb b \
a aa## VkQueueFlag ##bb b \
a aa## VkSampleCountFlag ##bb b \
a aa## VkSemaphoreImportFlag ##bb b \
a aa## VkShaderStageFlag ##bb b \
a aa## VkSparseImageFormatFlag ##bb b \
a aa## VkSparseMemoryBindFlag ##bb b \
a aa## VkStencilFaceFlag ##bb b \
a aa## VkSubgroupFeatureFlag ##bb b \
a aa## VkSubpassDescriptionFlag ##bb b \

#define table_vk_enum(a, aa, bb, b) \
a aa## VkAttachmentLoadOp ##bb b \
a aa## VkAttachmentStoreOp ##bb b \
a aa## VkBlendFactor ##bb b \
a aa## VkBlendOp ##bb b \
a aa## VkBorderColor ##bb b \
a aa## VkChromaLocation ##bb b \
a aa## VkCommandBufferLevel ##bb b \
a aa## VkCompareOp ##bb b \
a aa## VkComponentSwizzle ##bb b \
a aa## VkDescriptorType ##bb b \
a aa## VkDescriptorUpdateTemplateType ##bb b \
a aa## VkDynamicState ##bb b \
a aa## VkFilter ##bb b \
a aa## VkFormat ##bb b \
a aa## VkFrontFace ##bb b \
a aa## VkImageLayout ##bb b \
a aa## VkImageType ##bb b \
a aa## VkImageViewType ##bb b \
a aa## VkIndexType ##bb b \
a aa## VkInternalAllocationType ##bb b \
a aa## VkLogicOp ##bb b \
a aa## VkObjectType ##bb b \
a aa## VkPipelineCacheHeaderVersion ##bb b \
a aa## VkPointClippingBehavior ##bb b \
a aa## VkPolygonMode ##bb b \
a aa## VkPrimitiveTopology ##bb b \
a aa## VkQueryType ##bb b \
a aa## VkResult ##bb b \
a aa## VkSamplerAddressMode ##bb b \
a aa## VkSamplerMipmapMode ##bb b \
a aa## VkSamplerYcbcrModelConversion ##bb b \
a aa## VkSamplerYcbcrRange ##bb b \
a aa## VkSharingMode ##bb b \
a aa## VkStencilOp ##bb b \
a aa## VkStructureType ##bb b \
a aa## VkSubpassContents ##bb b \
a aa## VkSystemAllocationScope ##bb b \
a aa## VkTessellationDomainOrigin ##bb b \
a aa## VkVertexInputRate ##bb b \
a aa## VkPhysicalDeviceType ##bb b \
a aa## VkPipelineBindPoint ##bb b \
/*a aa## VkVendorId ##bb b \*/



#define table_vk_value_extensions_khr(a, aa, bb, b) \
a aa## Vk_KHR_16bit_storage ##bb b \
a aa## Vk_KHR_android_surface ##bb b \
a aa## Vk_KHR_bind_memory2 ##bb b \
a aa## Vk_KHR_dedicated_allocation ##bb b \
a aa## Vk_KHR_descriptor_update_template ##bb b \
a aa## Vk_KHR_device_group ##bb b \
a aa## Vk_KHR_device_group_creation ##bb b \
a aa## Vk_KHR_display ##bb b \
a aa## Vk_KHR_display_swapchain ##bb b \
a aa## Vk_KHR_draw_indirect_count ##bb b \
a aa## Vk_KHR_external_fence ##bb b \
a aa## Vk_KHR_external_fence_capabilities ##bb b \
a aa## Vk_KHR_external_fence_fd ##bb b \
a aa## Vk_KHR_external_fence_win32 ##bb b \
a aa## Vk_KHR_external_memory ##bb b \
a aa## Vk_KHR_external_memory_capabilities ##bb b \
a aa## Vk_KHR_external_memory_fd ##bb b \
a aa## Vk_KHR_external_memory_win32 ##bb b \
a aa## Vk_KHR_external_semaphore ##bb b \
a aa## Vk_KHR_external_semaphore_capabilities ##bb b \
a aa## Vk_KHR_external_semaphore_fd ##bb b \
a aa## Vk_KHR_external_semaphore_win32 ##bb b \
a aa## Vk_KHR_get_display_properties2 ##bb b \
a aa## Vk_KHR_get_memory_requirements2 ##bb b \
a aa## Vk_KHR_get_physical_device_properties2 ##bb b \
a aa## Vk_KHR_get_surface_capabilities2 ##bb b \
a aa## Vk_KHR_image_format_list ##bb b \
a aa## Vk_KHR_incremental_present ##bb b \
a aa## Vk_KHR_maintenance1 ##bb b \
a aa## Vk_KHR_maintenance2 ##bb b \
a aa## Vk_KHR_maintenance3 ##bb b \
a aa## Vk_KHR_mir_surface ##bb b \
a aa## Vk_KHR_multiview ##bb b \
a aa## Vk_KHR_push_descriptor ##bb b \
a aa## Vk_KHR_relaxed_block_layout ##bb b \
a aa## Vk_KHR_sampler_mirror_clamp_to_edge ##bb b \
a aa## Vk_KHR_sampler_ycbcr_conversion ##bb b \
a aa## Vk_KHR_shader_draw_parameters ##bb b \
a aa## Vk_KHR_shared_presentable_image ##bb b \
a aa## Vk_KHR_storage_buffer_storage_class ##bb b \
a aa## Vk_KHR_surface ##bb b \
a aa## Vk_KHR_swapchain ##bb b \
a aa## Vk_KHR_variable_pointers ##bb b \
a aa## Vk_KHR_wayland_surface ##bb b \
a aa## Vk_KHR_win32_keyed_mutex ##bb b \
a aa## Vk_KHR_win32_surface ##bb b \
a aa## Vk_KHR_xcb_surface ##bb b \
a aa## Vk_KHR_xlib_surface ##bb b \
/*a aa## Vk_KHR_8bit_storage ##bb b \
a aa## Vk_KHR_create_renderpass2 ##bb b \*/

#define table_vk_value_extensions_ext(a, aa, bb, b) \
a aa## Vk_EXT_acquire_xlib_display ##bb b \
a aa## Vk_EXT_blend_operation_advanced ##bb b \
a aa## Vk_EXT_conservative_rasterization ##bb b \
a aa## Vk_EXT_debug_marker ##bb b \
a aa## Vk_EXT_debug_report ##bb b \
a aa## Vk_EXT_debug_utils ##bb b \
a aa## Vk_EXT_depth_range_unrestricted ##bb b \
a aa## Vk_EXT_descriptor_indexing ##bb b \
a aa## Vk_EXT_direct_mode_display ##bb b \
a aa## Vk_EXT_discard_rectangles ##bb b \
a aa## Vk_EXT_display_control ##bb b \
a aa## Vk_EXT_display_surface_counter ##bb b \
a aa## Vk_EXT_external_memory_dma_buf ##bb b \
a aa## Vk_EXT_external_memory_host ##bb b \
a aa## Vk_EXT_global_priority ##bb b \
a aa## Vk_EXT_hdr_metadata aa##b \
a aa## Vk_EXT_post_depth_coverage ##bb b \
a aa## Vk_EXT_queue_family_foreign ##bb b \
a aa## Vk_EXT_sample_locations ##bb b \
a aa## Vk_EXT_sampler_filter_minmax ##bb b \
a aa## Vk_EXT_shader_stencil_export ##bb b \
a aa## Vk_EXT_shader_subgroup_ballot ##bb b \
a aa## Vk_EXT_shader_subgroup_vote ##bb b \
a aa## Vk_EXT_shader_viewport_index_layer ##bb b \
a aa## Vk_EXT_swapchain_colorspace ##bb b \
a aa## Vk_EXT_validation_cache ##bb b \
a aa## Vk_EXT_validation_flags ##bb b \
a aa## Vk_EXT_vertex_attribute_divisor ##bb b \
/*a aa## Vk_EXT_conditional_rendering ##bb b \*/

#define table_vk_value_extensions_amd(a, aa, bb, b) \
a aa## Vk_AMD_buffer_marker ##bb b \
a aa## Vk_AMD_draw_indirect_count ##bb b \
a aa## Vk_AMD_gcn_shader ##bb b \
a aa## Vk_AMD_gpu_shader_half_float ##bb b \
a aa## Vk_AMD_gpu_shader_int16 ##bb b \
a aa## Vk_AMD_mixed_attachment_samples ##bb b \
a aa## Vk_AMD_negative_viewport_height ##bb b \
a aa## Vk_AMD_rasterization_order ##bb b \
a aa## Vk_AMD_shader_ballot ##bb b \
a aa## Vk_AMD_shader_core_properties ##bb b \
a aa## Vk_AMD_shader_explicit_vertex_parameter ##bb b \
a aa## Vk_AMD_shader_fragment_mask ##bb b \
a aa## Vk_AMD_shader_image_load_store_lod ##bb b \
a aa## Vk_AMD_shader_info ##bb b \
a aa## Vk_AMD_shader_trinary_minmax ##bb b \
a aa## Vk_AMD_texture_gather_bias_lod ##bb b \

#define table_vk_value_extensions_android(a, aa, bb, b) \
a aa## Vk_ANDROID_external_memory_android_hardware_buffer ##bb b \


#define table_vk_value_extensions_google(a, aa, bb, b) \
a aa## Vk_GOOGLE_display_timing ##bb b \

#define table_vk_value_extensions_img(a, aa, bb, b) \
a aa## Vk_IMG_filter_cubic ##bb b \
a aa## Vk_IMG_format_pvrtc ##bb b \

#define table_vk_value_extensions_mvk(a, aa, bb, b) \
a aa## Vk_MVK_ios_surface ##bb b \
a aa## Vk_MVK_macos_surface ##bb b \

#define table_vk_value_extensions_nn(a, aa, bb, b) \
a aa## Vk_NN_vi_surface##bb b \

#define table_vk_value_extensions_nv(a, aa, bb, b) \
a aa## Vk_NV_clip_space_w_scaling ##bb b \
a aa## Vk_NV_dedicated_allocation ##bb b \
a aa## Vk_NV_external_memory ##bb b \
a aa## Vk_NV_external_memory_capabilities ##bb b \
a aa## Vk_NV_external_memory_win32 ##bb b \
a aa## Vk_NV_fill_rectangle ##bb b \
a aa## Vk_NV_fragment_coverage_to_color ##bb b \
a aa## Vk_NV_framebuffer_mixed_samples ##bb b \
a aa## Vk_NV_geometry_shader_passthrough ##bb b \
a aa## Vk_NV_glsl_shader ##bb b \
a aa## Vk_NV_sample_mask_override_coverage ##bb b \
a aa## Vk_NV_shader_subgroup_partitioned ##bb b \
a aa## Vk_NV_viewport_array2 ##bb b \
a aa## Vk_NV_viewport_swizzle ##bb b \
a aa## Vk_NV_win32_keyed_mutex ##bb b \
/*a aa## Vk_NV_device_diagnostic_checkpoints ##bb b \*/

#define table_vk_value_extensions_nvx(a, aa, bb, b) \
a aa## Vk_NVX_device_generated_commands ##bb b \
a aa## Vk_NVX_multiview_per_view_attributes ##bb b \


#define table_info_vkAllocateMemory(a, aa, bb, b) \
a aa## VkMemoryAllocateInfo ##bb b \
a aa## VkDedicatedAllocationMemoryAllocateInfoNV ##bb b \
a aa## VkExportMemoryAllocateInfo ##bb b \
a aa## VkExportMemoryAllocateInfoNV ##bb b \
a aa## VkExportMemoryWin32HandleInfoKHR ##bb b \
a aa## VkExportMemoryWin32HandleInfoNV ##bb b \
a aa## VkImportMemoryHostPointerInfoEXT ##bb b \
a aa## VkImportMemoryFdInfoKHR ##bb b \
a aa## VkImportMemoryWin32HandleInfoKHR ##bb b \
a aa## VkImportMemoryWin32HandleInfoNV ##bb b \
a aa## VkMemoryAllocateFlagsInfo ##bb b \
a aa## VkMemoryDedicatedAllocateInfo ##bb b \

//a aa## VkImportAndroidHardwareBufferInfoANDROID ##bb b \


#define vk_fun(name) PFN_##name name

#include "vulkan/vulkan.h"