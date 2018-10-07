// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See vktrace_file_generator.py for modifications


/***************************************************************************
 *
 * Copyright (c) 2015-2017 The Khronos Group Inc.
 * Copyright (c) 2015-2017 Valve Corporation
 * Copyright (c) 2015-2017 LunarG, Inc.
 * Copyright (c) 2015-2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Tobin Ehlis <tobin@lunarg.com>
 * Author: Peter Lohrmann <peterl@valvesoftware.com>
 * Author: David Pinedo <david@lunarg.com>
 *
 ****************************************************************************/

#pragma once
#include "vulkan/vulkan.h"
#include "vktrace_trace_packet_utils.h"

typedef struct packet_vkApiVersion {
    vktrace_trace_packet_header* header;
    uint32_t version;
} packet_vkApiVersion;

static packet_vkApiVersion* interpret_body_as_vkApiVersion(vktrace_trace_packet_header* pHeader) {
    packet_vkApiVersion* pPacket = (packet_vkApiVersion*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCreateInstance {
    vktrace_trace_packet_header* header;
    const VkInstanceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkInstance* pInstance;
    VkResult result;
} packet_vkCreateInstance;

static packet_vkCreateInstance* interpret_body_as_vkCreateInstance(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateInstance* pPacket = (packet_vkCreateInstance*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = interpret_VkInstanceCreateInfo(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pInstance = (VkInstance*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInstance);
    return pPacket;
}

typedef struct packet_vkDestroyInstance {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyInstance;

static packet_vkDestroyInstance* interpret_body_as_vkDestroyInstance(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyInstance* pPacket = (packet_vkDestroyInstance*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkEnumeratePhysicalDevices {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    uint32_t* pPhysicalDeviceCount;
    VkPhysicalDevice* pPhysicalDevices;
    VkResult result;
} packet_vkEnumeratePhysicalDevices;

static packet_vkEnumeratePhysicalDevices* interpret_body_as_vkEnumeratePhysicalDevices(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumeratePhysicalDevices* pPacket = (packet_vkEnumeratePhysicalDevices*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPhysicalDeviceCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPhysicalDeviceCount);
    pPacket->pPhysicalDevices = (VkPhysicalDevice*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPhysicalDevices);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFeatures {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures* pFeatures;
} packet_vkGetPhysicalDeviceFeatures;

static packet_vkGetPhysicalDeviceFeatures* interpret_body_as_vkGetPhysicalDeviceFeatures(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFeatures* pPacket = (packet_vkGetPhysicalDeviceFeatures*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFeatures = (VkPhysicalDeviceFeatures*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFeatures);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFormatProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkFormatProperties* pFormatProperties;
} packet_vkGetPhysicalDeviceFormatProperties;

static packet_vkGetPhysicalDeviceFormatProperties* interpret_body_as_vkGetPhysicalDeviceFormatProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFormatProperties* pPacket = (packet_vkGetPhysicalDeviceFormatProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFormatProperties = (VkFormatProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceImageFormatProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkImageType type;
    VkImageTiling tiling;
    VkImageUsageFlags usage;
    VkImageCreateFlags flags;
    VkImageFormatProperties* pImageFormatProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceImageFormatProperties;

static packet_vkGetPhysicalDeviceImageFormatProperties* interpret_body_as_vkGetPhysicalDeviceImageFormatProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceImageFormatProperties* pPacket = (packet_vkGetPhysicalDeviceImageFormatProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImageFormatProperties = (VkImageFormatProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties* pProperties;
} packet_vkGetPhysicalDeviceProperties;

static packet_vkGetPhysicalDeviceProperties* interpret_body_as_vkGetPhysicalDeviceProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceProperties* pPacket = (packet_vkGetPhysicalDeviceProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pProperties = (VkPhysicalDeviceProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceQueueFamilyProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pQueueFamilyPropertyCount;
    VkQueueFamilyProperties* pQueueFamilyProperties;
} packet_vkGetPhysicalDeviceQueueFamilyProperties;

static packet_vkGetPhysicalDeviceQueueFamilyProperties* interpret_body_as_vkGetPhysicalDeviceQueueFamilyProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceQueueFamilyProperties* pPacket = (packet_vkGetPhysicalDeviceQueueFamilyProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pQueueFamilyPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyPropertyCount);
    pPacket->pQueueFamilyProperties = (VkQueueFamilyProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceMemoryProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties* pMemoryProperties;
} packet_vkGetPhysicalDeviceMemoryProperties;

static packet_vkGetPhysicalDeviceMemoryProperties* interpret_body_as_vkGetPhysicalDeviceMemoryProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceMemoryProperties* pPacket = (packet_vkGetPhysicalDeviceMemoryProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryProperties = (VkPhysicalDeviceMemoryProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryProperties);
    return pPacket;
}

typedef struct packet_vkGetInstanceProcAddr {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const char* pName;
    PFN_vkVoidFunction result;
} packet_vkGetInstanceProcAddr;

static packet_vkGetInstanceProcAddr* interpret_body_as_vkGetInstanceProcAddr(vktrace_trace_packet_header* pHeader) {
    packet_vkGetInstanceProcAddr* pPacket = (packet_vkGetInstanceProcAddr*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pName = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pName);
    return pPacket;
}

typedef struct packet_vkGetDeviceProcAddr {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const char* pName;
    PFN_vkVoidFunction result;
} packet_vkGetDeviceProcAddr;

static packet_vkGetDeviceProcAddr* interpret_body_as_vkGetDeviceProcAddr(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceProcAddr* pPacket = (packet_vkGetDeviceProcAddr*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pName = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pName);
    return pPacket;
}

typedef struct packet_vkCreateDevice {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkDeviceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDevice* pDevice;
    VkResult result;
} packet_vkCreateDevice;

static packet_vkCreateDevice* interpret_body_as_vkCreateDevice(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDevice* pPacket = (packet_vkCreateDevice*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = interpret_VkDeviceCreateInfo(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pDevice = (VkDevice*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDevice);
    return pPacket;
}

typedef struct packet_vkDestroyDevice {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDevice;

static packet_vkDestroyDevice* interpret_body_as_vkDestroyDevice(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDevice* pPacket = (packet_vkDestroyDevice*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkEnumerateInstanceExtensionProperties {
    vktrace_trace_packet_header* header;
    const char* pLayerName;
    uint32_t* pPropertyCount;
    VkExtensionProperties* pProperties;
    VkResult result;
} packet_vkEnumerateInstanceExtensionProperties;

static packet_vkEnumerateInstanceExtensionProperties* interpret_body_as_vkEnumerateInstanceExtensionProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumerateInstanceExtensionProperties* pPacket = (packet_vkEnumerateInstanceExtensionProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pLayerName = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pLayerName);
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkExtensionProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkEnumerateDeviceExtensionProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const char* pLayerName;
    uint32_t* pPropertyCount;
    VkExtensionProperties* pProperties;
    VkResult result;
} packet_vkEnumerateDeviceExtensionProperties;

static packet_vkEnumerateDeviceExtensionProperties* interpret_body_as_vkEnumerateDeviceExtensionProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumerateDeviceExtensionProperties* pPacket = (packet_vkEnumerateDeviceExtensionProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pLayerName = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pLayerName);
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkExtensionProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkEnumerateInstanceLayerProperties {
    vktrace_trace_packet_header* header;
    uint32_t* pPropertyCount;
    VkLayerProperties* pProperties;
    VkResult result;
} packet_vkEnumerateInstanceLayerProperties;

static packet_vkEnumerateInstanceLayerProperties* interpret_body_as_vkEnumerateInstanceLayerProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumerateInstanceLayerProperties* pPacket = (packet_vkEnumerateInstanceLayerProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkLayerProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkEnumerateDeviceLayerProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkLayerProperties* pProperties;
    VkResult result;
} packet_vkEnumerateDeviceLayerProperties;

static packet_vkEnumerateDeviceLayerProperties* interpret_body_as_vkEnumerateDeviceLayerProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumerateDeviceLayerProperties* pPacket = (packet_vkEnumerateDeviceLayerProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkLayerProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetDeviceQueue {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t queueFamilyIndex;
    uint32_t queueIndex;
    VkQueue* pQueue;
} packet_vkGetDeviceQueue;

static packet_vkGetDeviceQueue* interpret_body_as_vkGetDeviceQueue(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceQueue* pPacket = (packet_vkGetDeviceQueue*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pQueue = (VkQueue*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueue);
    return pPacket;
}

typedef struct packet_vkQueueSubmit {
    vktrace_trace_packet_header* header;
    VkQueue queue;
    uint32_t submitCount;
    const VkSubmitInfo* pSubmits;
    VkFence fence;
    VkResult result;
} packet_vkQueueSubmit;

static packet_vkQueueSubmit* interpret_body_as_vkQueueSubmit(vktrace_trace_packet_header* pHeader) {
    packet_vkQueueSubmit* pPacket = (packet_vkQueueSubmit*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSubmits = (const VkSubmitInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubmits);
    if (pPacket->pSubmits != NULL) {
        uint32_t i;
        for (i = 0; i < pPacket->submitCount; i++) {
           VkCommandBuffer** ppCBs = (VkCommandBuffer**)&pPacket->pSubmits[i].pCommandBuffers;
           *ppCBs = (VkCommandBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubmits[i].pCommandBuffers);
           VkSemaphore** ppSems = (VkSemaphore**)&pPacket->pSubmits[i].pWaitSemaphores;
           *ppSems = (VkSemaphore*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubmits[i].pWaitSemaphores);
           ppSems = (VkSemaphore**)&pPacket->pSubmits[i].pSignalSemaphores;
           *ppSems = (VkSemaphore*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubmits[i].pSignalSemaphores);
           VkPipelineStageFlags** ppStageMask = (VkPipelineStageFlags**)&pPacket->pSubmits[i].pWaitDstStageMask;
           *ppStageMask = (VkPipelineStageFlags*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubmits[i].pWaitDstStageMask);
           vktrace_interpret_pnext_pointers(pHeader, (void *)&pPacket->pSubmits[i]);
}
    }
    return pPacket;
}

typedef struct packet_vkQueueWaitIdle {
    vktrace_trace_packet_header* header;
    VkQueue queue;
    VkResult result;
} packet_vkQueueWaitIdle;

static packet_vkQueueWaitIdle* interpret_body_as_vkQueueWaitIdle(vktrace_trace_packet_header* pHeader) {
    packet_vkQueueWaitIdle* pPacket = (packet_vkQueueWaitIdle*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkDeviceWaitIdle {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkResult result;
} packet_vkDeviceWaitIdle;

static packet_vkDeviceWaitIdle* interpret_body_as_vkDeviceWaitIdle(vktrace_trace_packet_header* pHeader) {
    packet_vkDeviceWaitIdle* pPacket = (packet_vkDeviceWaitIdle*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkAllocateMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkMemoryAllocateInfo* pAllocateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDeviceMemory* pMemory;
    VkResult result;
} packet_vkAllocateMemory;

static packet_vkAllocateMemory* interpret_body_as_vkAllocateMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkAllocateMemory* pPacket = (packet_vkAllocateMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocateInfo = (const VkMemoryAllocateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocateInfo);
    if (pPacket->pAllocateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pAllocateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pMemory = (VkDeviceMemory*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemory);
    return pPacket;
}

typedef struct packet_vkFreeMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceMemory memory;
    const VkAllocationCallbacks* pAllocator;
} packet_vkFreeMemory;

static packet_vkFreeMemory* interpret_body_as_vkFreeMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkFreeMemory* pPacket = (packet_vkFreeMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkMapMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceMemory memory;
    VkDeviceSize offset;
    VkDeviceSize size;
    VkMemoryMapFlags flags;
    void** ppData;
    VkResult result;
} packet_vkMapMemory;

static packet_vkMapMemory* interpret_body_as_vkMapMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkMapMemory* pPacket = (packet_vkMapMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->ppData = (void**)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppData);
    return pPacket;
}

typedef struct packet_vkUnmapMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceMemory memory;
    void* pData;
} packet_vkUnmapMemory;

static packet_vkUnmapMemory* interpret_body_as_vkUnmapMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkUnmapMemory* pPacket = (packet_vkUnmapMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkFlushMappedMemoryRanges {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t memoryRangeCount;
    const VkMappedMemoryRange* pMemoryRanges;
    void** ppData;
    VkResult result;
} packet_vkFlushMappedMemoryRanges;

static packet_vkFlushMappedMemoryRanges* interpret_body_as_vkFlushMappedMemoryRanges(vktrace_trace_packet_header* pHeader) {
    packet_vkFlushMappedMemoryRanges* pPacket = (packet_vkFlushMappedMemoryRanges*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryRanges = (const VkMappedMemoryRange*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRanges);
    pPacket->ppData = (void**)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppData);
    if (pPacket->ppData != NULL) {
        uint32_t i = 0;
        for (i = 0; i < pPacket->memoryRangeCount; i++) {
            pPacket->ppData[i] = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppData[i]);
        }
    }
    return pPacket;
}

typedef struct packet_vkInvalidateMappedMemoryRanges {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t memoryRangeCount;
    const VkMappedMemoryRange* pMemoryRanges;
    void** ppData;
    VkResult result;
} packet_vkInvalidateMappedMemoryRanges;

static packet_vkInvalidateMappedMemoryRanges* interpret_body_as_vkInvalidateMappedMemoryRanges(vktrace_trace_packet_header* pHeader) {
    packet_vkInvalidateMappedMemoryRanges* pPacket = (packet_vkInvalidateMappedMemoryRanges*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryRanges = (const VkMappedMemoryRange*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRanges);
    pPacket->ppData = (void**)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppData);
    if (pPacket->ppData != NULL) {
        uint32_t i = 0;
        for (i = 0; i < pPacket->memoryRangeCount; i++) {
            pPacket->ppData[i] = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppData[i]);
        }
    }
    return pPacket;
}

typedef struct packet_vkGetDeviceMemoryCommitment {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceMemory memory;
    VkDeviceSize* pCommittedMemoryInBytes;
} packet_vkGetDeviceMemoryCommitment;

static packet_vkGetDeviceMemoryCommitment* interpret_body_as_vkGetDeviceMemoryCommitment(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceMemoryCommitment* pPacket = (packet_vkGetDeviceMemoryCommitment*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCommittedMemoryInBytes = (VkDeviceSize*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCommittedMemoryInBytes);
    return pPacket;
}

typedef struct packet_vkBindBufferMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkBuffer buffer;
    VkDeviceMemory memory;
    VkDeviceSize memoryOffset;
    VkResult result;
} packet_vkBindBufferMemory;

static packet_vkBindBufferMemory* interpret_body_as_vkBindBufferMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkBindBufferMemory* pPacket = (packet_vkBindBufferMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkBindImageMemory {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImage image;
    VkDeviceMemory memory;
    VkDeviceSize memoryOffset;
    VkResult result;
} packet_vkBindImageMemory;

static packet_vkBindImageMemory* interpret_body_as_vkBindImageMemory(vktrace_trace_packet_header* pHeader) {
    packet_vkBindImageMemory* pPacket = (packet_vkBindImageMemory*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetBufferMemoryRequirements {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkBuffer buffer;
    VkMemoryRequirements* pMemoryRequirements;
} packet_vkGetBufferMemoryRequirements;

static packet_vkGetBufferMemoryRequirements* interpret_body_as_vkGetBufferMemoryRequirements(vktrace_trace_packet_header* pHeader) {
    packet_vkGetBufferMemoryRequirements* pPacket = (packet_vkGetBufferMemoryRequirements*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryRequirements = (VkMemoryRequirements*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetImageMemoryRequirements {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImage image;
    VkMemoryRequirements* pMemoryRequirements;
} packet_vkGetImageMemoryRequirements;

static packet_vkGetImageMemoryRequirements* interpret_body_as_vkGetImageMemoryRequirements(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageMemoryRequirements* pPacket = (packet_vkGetImageMemoryRequirements*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryRequirements = (VkMemoryRequirements*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetImageSparseMemoryRequirements {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImage image;
    uint32_t* pSparseMemoryRequirementCount;
    VkSparseImageMemoryRequirements* pSparseMemoryRequirements;
} packet_vkGetImageSparseMemoryRequirements;

static packet_vkGetImageSparseMemoryRequirements* interpret_body_as_vkGetImageSparseMemoryRequirements(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageSparseMemoryRequirements* pPacket = (packet_vkGetImageSparseMemoryRequirements*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSparseMemoryRequirementCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirementCount);
    pPacket->pSparseMemoryRequirements = (VkSparseImageMemoryRequirements*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSparseImageFormatProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkImageType type;
    VkSampleCountFlagBits samples;
    VkImageUsageFlags usage;
    VkImageTiling tiling;
    uint32_t* pPropertyCount;
    VkSparseImageFormatProperties* pProperties;
} packet_vkGetPhysicalDeviceSparseImageFormatProperties;

static packet_vkGetPhysicalDeviceSparseImageFormatProperties* interpret_body_as_vkGetPhysicalDeviceSparseImageFormatProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSparseImageFormatProperties* pPacket = (packet_vkGetPhysicalDeviceSparseImageFormatProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkSparseImageFormatProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkQueueBindSparse {
    vktrace_trace_packet_header* header;
    VkQueue queue;
    uint32_t bindInfoCount;
    const VkBindSparseInfo* pBindInfo;
    VkFence fence;
    VkResult result;
} packet_vkQueueBindSparse;

static packet_vkQueueBindSparse* interpret_body_as_vkQueueBindSparse(vktrace_trace_packet_header* pHeader) {
    packet_vkQueueBindSparse* pPacket = (packet_vkQueueBindSparse*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBindInfo = (const VkBindSparseInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBindInfo);
    return pPacket;
}

typedef struct packet_vkCreateFence {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkFenceCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFence* pFence;
    VkResult result;
} packet_vkCreateFence;

static packet_vkCreateFence* interpret_body_as_vkCreateFence(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateFence* pPacket = (packet_vkCreateFence*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkFenceCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pFence = (VkFence*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFence);
    return pPacket;
}

typedef struct packet_vkDestroyFence {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkFence fence;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyFence;

static packet_vkDestroyFence* interpret_body_as_vkDestroyFence(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyFence* pPacket = (packet_vkDestroyFence*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkResetFences {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t fenceCount;
    const VkFence* pFences;
    VkResult result;
} packet_vkResetFences;

static packet_vkResetFences* interpret_body_as_vkResetFences(vktrace_trace_packet_header* pHeader) {
    packet_vkResetFences* pPacket = (packet_vkResetFences*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFences = (const VkFence*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFences);
    return pPacket;
}

typedef struct packet_vkGetFenceStatus {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkFence fence;
    VkResult result;
} packet_vkGetFenceStatus;

static packet_vkGetFenceStatus* interpret_body_as_vkGetFenceStatus(vktrace_trace_packet_header* pHeader) {
    packet_vkGetFenceStatus* pPacket = (packet_vkGetFenceStatus*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkWaitForFences {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t fenceCount;
    const VkFence* pFences;
    VkBool32 waitAll;
    uint64_t timeout;
    VkResult result;
} packet_vkWaitForFences;

static packet_vkWaitForFences* interpret_body_as_vkWaitForFences(vktrace_trace_packet_header* pHeader) {
    packet_vkWaitForFences* pPacket = (packet_vkWaitForFences*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFences = (const VkFence*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFences);
    return pPacket;
}

typedef struct packet_vkCreateSemaphore {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSemaphoreCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSemaphore* pSemaphore;
    VkResult result;
} packet_vkCreateSemaphore;

static packet_vkCreateSemaphore* interpret_body_as_vkCreateSemaphore(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSemaphore* pPacket = (packet_vkCreateSemaphore*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkSemaphoreCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSemaphore = (VkSemaphore*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSemaphore);
    return pPacket;
}

typedef struct packet_vkDestroySemaphore {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSemaphore semaphore;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySemaphore;

static packet_vkDestroySemaphore* interpret_body_as_vkDestroySemaphore(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySemaphore* pPacket = (packet_vkDestroySemaphore*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateEvent {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkEventCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkEvent* pEvent;
    VkResult result;
} packet_vkCreateEvent;

static packet_vkCreateEvent* interpret_body_as_vkCreateEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateEvent* pPacket = (packet_vkCreateEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkEventCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pEvent = (VkEvent*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pEvent);
    return pPacket;
}

typedef struct packet_vkDestroyEvent {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkEvent event;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyEvent;

static packet_vkDestroyEvent* interpret_body_as_vkDestroyEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyEvent* pPacket = (packet_vkDestroyEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetEventStatus {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkEvent event;
    VkResult result;
} packet_vkGetEventStatus;

static packet_vkGetEventStatus* interpret_body_as_vkGetEventStatus(vktrace_trace_packet_header* pHeader) {
    packet_vkGetEventStatus* pPacket = (packet_vkGetEventStatus*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkSetEvent {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkEvent event;
    VkResult result;
} packet_vkSetEvent;

static packet_vkSetEvent* interpret_body_as_vkSetEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkSetEvent* pPacket = (packet_vkSetEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkResetEvent {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkEvent event;
    VkResult result;
} packet_vkResetEvent;

static packet_vkResetEvent* interpret_body_as_vkResetEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkResetEvent* pPacket = (packet_vkResetEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCreateQueryPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkQueryPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkQueryPool* pQueryPool;
    VkResult result;
} packet_vkCreateQueryPool;

static packet_vkCreateQueryPool* interpret_body_as_vkCreateQueryPool(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateQueryPool* pPacket = (packet_vkCreateQueryPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkQueryPoolCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pQueryPool = (VkQueryPool*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueryPool);
    return pPacket;
}

typedef struct packet_vkDestroyQueryPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkQueryPool queryPool;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyQueryPool;

static packet_vkDestroyQueryPool* interpret_body_as_vkDestroyQueryPool(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyQueryPool* pPacket = (packet_vkDestroyQueryPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetQueryPoolResults {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
    size_t dataSize;
    void* pData;
    VkDeviceSize stride;
    VkQueryResultFlags flags;
    VkResult result;
} packet_vkGetQueryPoolResults;

static packet_vkGetQueryPoolResults* interpret_body_as_vkGetQueryPoolResults(vktrace_trace_packet_header* pHeader) {
    packet_vkGetQueryPoolResults* pPacket = (packet_vkGetQueryPoolResults*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkCreateBuffer {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkBufferCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkBuffer* pBuffer;
    VkResult result;
} packet_vkCreateBuffer;

static packet_vkCreateBuffer* interpret_body_as_vkCreateBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateBuffer* pPacket = (packet_vkCreateBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkBufferCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        uint32_t** ppQueueFamilyIndices = (uint32_t**)&(pPacket->pCreateInfo->pQueueFamilyIndices);
        *ppQueueFamilyIndices = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pQueueFamilyIndices);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pBuffer = (VkBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBuffer);
    return pPacket;
}

typedef struct packet_vkDestroyBuffer {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkBuffer buffer;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyBuffer;

static packet_vkDestroyBuffer* interpret_body_as_vkDestroyBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyBuffer* pPacket = (packet_vkDestroyBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateBufferView {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkBufferViewCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkBufferView* pView;
    VkResult result;
} packet_vkCreateBufferView;

static packet_vkCreateBufferView* interpret_body_as_vkCreateBufferView(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateBufferView* pPacket = (packet_vkCreateBufferView*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkBufferViewCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pView = (VkBufferView*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pView);
    return pPacket;
}

typedef struct packet_vkDestroyBufferView {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkBufferView bufferView;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyBufferView;

static packet_vkDestroyBufferView* interpret_body_as_vkDestroyBufferView(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyBufferView* pPacket = (packet_vkDestroyBufferView*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateImage {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkImage* pImage;
    VkResult result;
} packet_vkCreateImage;

static packet_vkCreateImage* interpret_body_as_vkCreateImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateImage* pPacket = (packet_vkCreateImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkImageCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        uint32_t** ppQueueFamilyIndices = (uint32_t**)&(pPacket->pCreateInfo->pQueueFamilyIndices);
        *ppQueueFamilyIndices = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pQueueFamilyIndices);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pImage = (VkImage*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImage);
    return pPacket;
}

typedef struct packet_vkDestroyImage {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImage image;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyImage;

static packet_vkDestroyImage* interpret_body_as_vkDestroyImage(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyImage* pPacket = (packet_vkDestroyImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetImageSubresourceLayout {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImage image;
    const VkImageSubresource* pSubresource;
    VkSubresourceLayout* pLayout;
} packet_vkGetImageSubresourceLayout;

static packet_vkGetImageSubresourceLayout* interpret_body_as_vkGetImageSubresourceLayout(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageSubresourceLayout* pPacket = (packet_vkGetImageSubresourceLayout*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSubresource = (const VkImageSubresource*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSubresource);
    pPacket->pLayout = (VkSubresourceLayout*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pLayout);
    return pPacket;
}

typedef struct packet_vkCreateImageView {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageViewCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkImageView* pView;
    VkResult result;
} packet_vkCreateImageView;

static packet_vkCreateImageView* interpret_body_as_vkCreateImageView(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateImageView* pPacket = (packet_vkCreateImageView*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkImageViewCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pView = (VkImageView*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pView);
    return pPacket;
}

typedef struct packet_vkDestroyImageView {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkImageView imageView;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyImageView;

static packet_vkDestroyImageView* interpret_body_as_vkDestroyImageView(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyImageView* pPacket = (packet_vkDestroyImageView*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateShaderModule {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkShaderModuleCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkShaderModule* pShaderModule;
    VkResult result;
} packet_vkCreateShaderModule;

static packet_vkCreateShaderModule* interpret_body_as_vkCreateShaderModule(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateShaderModule* pPacket = (packet_vkCreateShaderModule*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkShaderModuleCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        void** ppCode = (void**)&(pPacket->pCreateInfo->pCode);
        *ppCode = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pCode);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pShaderModule = (VkShaderModule*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pShaderModule);
    return pPacket;
}

typedef struct packet_vkDestroyShaderModule {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkShaderModule shaderModule;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyShaderModule;

static packet_vkDestroyShaderModule* interpret_body_as_vkDestroyShaderModule(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyShaderModule* pPacket = (packet_vkDestroyShaderModule*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreatePipelineCache {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkPipelineCacheCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkPipelineCache* pPipelineCache;
    VkResult result;
} packet_vkCreatePipelineCache;

static packet_vkCreatePipelineCache* interpret_body_as_vkCreatePipelineCache(vktrace_trace_packet_header* pHeader) {
    packet_vkCreatePipelineCache* pPacket = (packet_vkCreatePipelineCache*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkPipelineCacheCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        ((VkPipelineCacheCreateInfo *)pPacket->pCreateInfo)->pInitialData = (const void*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pInitialData);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pPipelineCache = (VkPipelineCache*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPipelineCache);
    return pPacket;
}

typedef struct packet_vkDestroyPipelineCache {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineCache pipelineCache;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyPipelineCache;

static packet_vkDestroyPipelineCache* interpret_body_as_vkDestroyPipelineCache(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyPipelineCache* pPacket = (packet_vkDestroyPipelineCache*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetPipelineCacheData {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineCache pipelineCache;
    size_t* pDataSize;
    void* pData;
    VkResult result;
} packet_vkGetPipelineCacheData;

static packet_vkGetPipelineCacheData* interpret_body_as_vkGetPipelineCacheData(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPipelineCacheData* pPacket = (packet_vkGetPipelineCacheData*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDataSize = (size_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDataSize);
    pPacket->pData = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkMergePipelineCaches {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineCache dstCache;
    uint32_t srcCacheCount;
    const VkPipelineCache* pSrcCaches;
    VkResult result;
} packet_vkMergePipelineCaches;

static packet_vkMergePipelineCaches* interpret_body_as_vkMergePipelineCaches(vktrace_trace_packet_header* pHeader) {
    packet_vkMergePipelineCaches* pPacket = (packet_vkMergePipelineCaches*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSrcCaches = (const VkPipelineCache*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSrcCaches);
    return pPacket;
}

typedef struct packet_vkCreateGraphicsPipelines {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineCache pipelineCache;
    uint32_t createInfoCount;
    const VkGraphicsPipelineCreateInfo* pCreateInfos;
    const VkAllocationCallbacks* pAllocator;
    VkPipeline* pPipelines;
    VkResult result;
} packet_vkCreateGraphicsPipelines;

static packet_vkCreateGraphicsPipelines* interpret_body_as_vkCreateGraphicsPipelines(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateGraphicsPipelines* pPacket = (packet_vkCreateGraphicsPipelines*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfos = (const VkGraphicsPipelineCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos);
    if (pPacket->pCreateInfos != NULL) {
        uint32_t i;
        uint32_t j;
        for (i=0; i<pPacket->createInfoCount; i++) {
        if (pPacket->pCreateInfos[i].sType == VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO) {
        // need to make a non-const pointer to the pointer so that we can properly change the original pointer to the interpretted one
        VkGraphicsPipelineCreateInfo* pNonConst = (VkGraphicsPipelineCreateInfo*)&(pPacket->pCreateInfos[i]);
        // shader stages array
        pNonConst->pStages = (VkPipelineShaderStageCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pStages);
        for (j = 0; j < pPacket->pCreateInfos[i].stageCount; j++) {
            interpret_VkPipelineShaderStageCreateInfo(pHeader, (VkPipelineShaderStageCreateInfo*)&pPacket->pCreateInfos[i].pStages[j]);
        }
        // Vertex Input State
        pNonConst->pVertexInputState = (VkPipelineVertexInputStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pVertexInputState);
        VkPipelineVertexInputStateCreateInfo* pNonConstVIState = (VkPipelineVertexInputStateCreateInfo*)pNonConst->pVertexInputState;
        if (pNonConstVIState) {
            pNonConstVIState->pVertexBindingDescriptions = (const VkVertexInputBindingDescription*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pVertexInputState->pVertexBindingDescriptions);
            pNonConstVIState->pVertexAttributeDescriptions = (const VkVertexInputAttributeDescription*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pVertexInputState->pVertexAttributeDescriptions);
        }
        // Input Assembly State
        pNonConst->pInputAssemblyState = (const VkPipelineInputAssemblyStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pInputAssemblyState);
        // Tesselation State
        pNonConst->pTessellationState = (const VkPipelineTessellationStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pTessellationState);
        // Viewport State
        pNonConst->pViewportState = (const VkPipelineViewportStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pViewportState);
        // Raster State
        pNonConst->pRasterizationState = (const VkPipelineRasterizationStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pRasterizationState);
        // MultiSample State
        pNonConst->pMultisampleState = (const VkPipelineMultisampleStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pMultisampleState);
        // DepthStencil State
        pNonConst->pDepthStencilState = (const VkPipelineDepthStencilStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pDepthStencilState);
        // DynamicState State
        pNonConst->pDynamicState = (const VkPipelineDynamicStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pDynamicState);
        VkPipelineDynamicStateCreateInfo* pNonConstDyState = (VkPipelineDynamicStateCreateInfo*)pNonConst->pDynamicState;
        if (pNonConstDyState) {
            pNonConstDyState->pDynamicStates = (const VkDynamicState*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pDynamicState->pDynamicStates);
        }
        // ColorBuffer State
        pNonConst->pColorBlendState = (const VkPipelineColorBlendStateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pColorBlendState);
        VkPipelineColorBlendStateCreateInfo* pNonConstCbState = (VkPipelineColorBlendStateCreateInfo*)pNonConst->pColorBlendState;
        if (pNonConstCbState)
            pNonConstCbState->pAttachments = (const VkPipelineColorBlendAttachmentState*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos[i].pColorBlendState->pAttachments);
        } else {
            // This is unexpected.
            vktrace_LogError("CreateGraphicsPipelines must have CreateInfo stype of VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO.");
            pPacket->header = NULL;
        }
        }

    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pPipelines = (VkPipeline*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPipelines);
    return pPacket;
}

typedef struct packet_vkCreateComputePipelines {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineCache pipelineCache;
    uint32_t createInfoCount;
    const VkComputePipelineCreateInfo* pCreateInfos;
    const VkAllocationCallbacks* pAllocator;
    VkPipeline* pPipelines;
    VkResult result;
} packet_vkCreateComputePipelines;

static packet_vkCreateComputePipelines* interpret_body_as_vkCreateComputePipelines(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateComputePipelines* pPacket = (packet_vkCreateComputePipelines*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfos = (const VkComputePipelineCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos);
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pPipelines = (VkPipeline*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPipelines);
    return pPacket;
}

typedef struct packet_vkDestroyPipeline {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipeline pipeline;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyPipeline;

static packet_vkDestroyPipeline* interpret_body_as_vkDestroyPipeline(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyPipeline* pPacket = (packet_vkDestroyPipeline*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreatePipelineLayout {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkPipelineLayoutCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkPipelineLayout* pPipelineLayout;
    VkResult result;
} packet_vkCreatePipelineLayout;

static packet_vkCreatePipelineLayout* interpret_body_as_vkCreatePipelineLayout(vktrace_trace_packet_header* pHeader) {
    packet_vkCreatePipelineLayout* pPacket = (packet_vkCreatePipelineLayout*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkPipelineLayoutCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        VkPipelineLayoutCreateInfo* pInfo = (VkPipelineLayoutCreateInfo*)pPacket->pCreateInfo;
        pInfo->pSetLayouts = (VkDescriptorSetLayout*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pSetLayouts);
        pInfo->pPushConstantRanges = (VkPushConstantRange*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pPushConstantRanges);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pPipelineLayout = (VkPipelineLayout*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPipelineLayout);
    return pPacket;
}

typedef struct packet_vkDestroyPipelineLayout {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipelineLayout pipelineLayout;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyPipelineLayout;

static packet_vkDestroyPipelineLayout* interpret_body_as_vkDestroyPipelineLayout(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyPipelineLayout* pPacket = (packet_vkDestroyPipelineLayout*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateSampler {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSamplerCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSampler* pSampler;
    VkResult result;
} packet_vkCreateSampler;

static packet_vkCreateSampler* interpret_body_as_vkCreateSampler(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSampler* pPacket = (packet_vkCreateSampler*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkSamplerCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSampler = (VkSampler*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSampler);
    return pPacket;
}

typedef struct packet_vkDestroySampler {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSampler sampler;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySampler;

static packet_vkDestroySampler* interpret_body_as_vkDestroySampler(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySampler* pPacket = (packet_vkDestroySampler*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateDescriptorSetLayout {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorSetLayout* pSetLayout;
    VkResult result;
} packet_vkCreateDescriptorSetLayout;

static packet_vkCreateDescriptorSetLayout* interpret_body_as_vkCreateDescriptorSetLayout(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDescriptorSetLayout* pPacket = (packet_vkCreateDescriptorSetLayout*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDescriptorSetLayoutCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSetLayout = (VkDescriptorSetLayout*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSetLayout);
    return pPacket;
}

typedef struct packet_vkDestroyDescriptorSetLayout {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorSetLayout descriptorSetLayout;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDescriptorSetLayout;

static packet_vkDestroyDescriptorSetLayout* interpret_body_as_vkDestroyDescriptorSetLayout(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDescriptorSetLayout* pPacket = (packet_vkDestroyDescriptorSetLayout*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateDescriptorPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorPool* pDescriptorPool;
    VkResult result;
} packet_vkCreateDescriptorPool;

static packet_vkCreateDescriptorPool* interpret_body_as_vkCreateDescriptorPool(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDescriptorPool* pPacket = (packet_vkCreateDescriptorPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDescriptorPoolCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        VkDescriptorPoolCreateInfo* pInfo = (VkDescriptorPoolCreateInfo*)pPacket->pCreateInfo;
        pInfo->pPoolSizes = (VkDescriptorPoolSize*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo->pPoolSizes);
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pDescriptorPool = (VkDescriptorPool*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorPool);
    return pPacket;
}

typedef struct packet_vkDestroyDescriptorPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorPool descriptorPool;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDescriptorPool;

static packet_vkDestroyDescriptorPool* interpret_body_as_vkDestroyDescriptorPool(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDescriptorPool* pPacket = (packet_vkDestroyDescriptorPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkResetDescriptorPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorPool descriptorPool;
    VkDescriptorPoolResetFlags flags;
    VkResult result;
} packet_vkResetDescriptorPool;

static packet_vkResetDescriptorPool* interpret_body_as_vkResetDescriptorPool(vktrace_trace_packet_header* pHeader) {
    packet_vkResetDescriptorPool* pPacket = (packet_vkResetDescriptorPool*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkAllocateDescriptorSets {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorSetAllocateInfo* pAllocateInfo;
    VkDescriptorSet* pDescriptorSets;
    VkResult result;
} packet_vkAllocateDescriptorSets;

static packet_vkAllocateDescriptorSets* interpret_body_as_vkAllocateDescriptorSets(vktrace_trace_packet_header* pHeader) {
    packet_vkAllocateDescriptorSets* pPacket = (packet_vkAllocateDescriptorSets*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocateInfo = (const VkDescriptorSetAllocateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocateInfo);
    if (pPacket->pAllocateInfo != NULL) {
        VkDescriptorSetLayout **ppDescSetLayout = (VkDescriptorSetLayout **) &pPacket->pAllocateInfo->pSetLayouts;
        *ppDescSetLayout = (VkDescriptorSetLayout *) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pAllocateInfo->pSetLayouts));
    }
    if (pPacket->pAllocateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pAllocateInfo);
    }
    pPacket->pDescriptorSets = (VkDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorSets);
    return pPacket;
}

typedef struct packet_vkFreeDescriptorSets {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorPool descriptorPool;
    uint32_t descriptorSetCount;
    const VkDescriptorSet* pDescriptorSets;
    VkResult result;
} packet_vkFreeDescriptorSets;

static packet_vkFreeDescriptorSets* interpret_body_as_vkFreeDescriptorSets(vktrace_trace_packet_header* pHeader) {
    packet_vkFreeDescriptorSets* pPacket = (packet_vkFreeDescriptorSets*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDescriptorSets = (const VkDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorSets);
    return pPacket;
}

typedef struct packet_vkUpdateDescriptorSets {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t descriptorWriteCount;
    const VkWriteDescriptorSet* pDescriptorWrites;
    uint32_t descriptorCopyCount;
    const VkCopyDescriptorSet* pDescriptorCopies;
} packet_vkUpdateDescriptorSets;

static packet_vkUpdateDescriptorSets* interpret_body_as_vkUpdateDescriptorSets(vktrace_trace_packet_header* pHeader) {
    packet_vkUpdateDescriptorSets* pPacket = (packet_vkUpdateDescriptorSets*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDescriptorWrites = (const VkWriteDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites);
    if (pPacket->pDescriptorWrites != NULL) {
        uint32_t i;
        for (i = 0; i < pPacket->descriptorWriteCount; i++) {
            vktrace_interpret_pnext_pointers(pPacket->header, (void *)&pPacket->pDescriptorWrites[i]);
            switch (pPacket->pDescriptorWrites[i].descriptorType) {
            case VK_DESCRIPTOR_TYPE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT: {
                    VkDescriptorImageInfo** ppImageInfo = (VkDescriptorImageInfo**)&pPacket->pDescriptorWrites[i].pImageInfo;
                    *ppImageInfo = (VkDescriptorImageInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pImageInfo);
                }                break;            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER: {
                    VkBufferView** ppTexelBufferView = (VkBufferView**)&pPacket->pDescriptorWrites[i].pTexelBufferView;
                    *ppTexelBufferView = (VkBufferView*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pTexelBufferView);
                }                break;            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC: {
                    VkDescriptorBufferInfo** ppBufferInfo = (VkDescriptorBufferInfo**)&pPacket->pDescriptorWrites[i].pBufferInfo;
                    *ppBufferInfo = (VkDescriptorBufferInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pBufferInfo);
                }
                break;
            default:
                break;
            }
        }
        for (i = 0; i < pPacket->descriptorCopyCount; i++) {
            vktrace_interpret_pnext_pointers(pPacket->header, (void *)&pPacket->pDescriptorCopies[i]);
        }
    }
    pPacket->pDescriptorCopies = (const VkCopyDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorCopies);
    return pPacket;
}

typedef struct packet_vkCreateFramebuffer {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkFramebufferCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFramebuffer* pFramebuffer;
    VkResult result;
} packet_vkCreateFramebuffer;

static packet_vkCreateFramebuffer* interpret_body_as_vkCreateFramebuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateFramebuffer* pPacket = (packet_vkCreateFramebuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkFramebufferCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        VkImageView** ppAV = (VkImageView**)&(pPacket->pCreateInfo->pAttachments);
        *ppAV = (VkImageView*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pCreateInfo->pAttachments));
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pFramebuffer = (VkFramebuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFramebuffer);
    return pPacket;
}

typedef struct packet_vkDestroyFramebuffer {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkFramebuffer framebuffer;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyFramebuffer;

static packet_vkDestroyFramebuffer* interpret_body_as_vkDestroyFramebuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyFramebuffer* pPacket = (packet_vkDestroyFramebuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateRenderPass {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkRenderPassCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkRenderPass* pRenderPass;
    VkResult result;
} packet_vkCreateRenderPass;

static packet_vkCreateRenderPass* interpret_body_as_vkCreateRenderPass(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateRenderPass* pPacket = (packet_vkCreateRenderPass*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkRenderPassCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        VkRenderPassCreateInfo* pInfo = (VkRenderPassCreateInfo*)pPacket->pCreateInfo;
        uint32_t i = 0;
        VkAttachmentDescription **ppAD = (VkAttachmentDescription **)&(pInfo->pAttachments);
        *ppAD = (VkAttachmentDescription*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pAttachments);
        VkSubpassDescription** ppSP = (VkSubpassDescription**)&(pInfo->pSubpasses);
        *ppSP = (VkSubpassDescription*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses);
        for (i=0; i<pInfo->subpassCount; i++) {
            VkAttachmentReference** pAR = (VkAttachmentReference**)&(pInfo->pSubpasses[i].pInputAttachments);
            *pAR = (VkAttachmentReference*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses[i].pInputAttachments);
            pAR = (VkAttachmentReference**)&(pInfo->pSubpasses[i].pColorAttachments);
            *pAR = (VkAttachmentReference*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses[i].pColorAttachments);
            pAR = (VkAttachmentReference**)&(pInfo->pSubpasses[i].pResolveAttachments);
            *pAR = (VkAttachmentReference*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses[i].pResolveAttachments);
            pAR = (VkAttachmentReference**)&(pInfo->pSubpasses[i].pDepthStencilAttachment);
            *pAR = (VkAttachmentReference*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses[i].pDepthStencilAttachment);
            pAR = (VkAttachmentReference**)&(pInfo->pSubpasses[i].pPreserveAttachments);
            *pAR = (VkAttachmentReference*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pSubpasses[i].pPreserveAttachments);
        }
        VkSubpassDependency** ppSD = (VkSubpassDependency**)&(pInfo->pDependencies);
        *ppSD = (VkSubpassDependency*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pInfo->pDependencies);

    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pRenderPass = (VkRenderPass*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRenderPass);
    return pPacket;
}

typedef struct packet_vkDestroyRenderPass {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkRenderPass renderPass;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyRenderPass;

static packet_vkDestroyRenderPass* interpret_body_as_vkDestroyRenderPass(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyRenderPass* pPacket = (packet_vkDestroyRenderPass*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetRenderAreaGranularity {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkRenderPass renderPass;
    VkExtent2D* pGranularity;
} packet_vkGetRenderAreaGranularity;

static packet_vkGetRenderAreaGranularity* interpret_body_as_vkGetRenderAreaGranularity(vktrace_trace_packet_header* pHeader) {
    packet_vkGetRenderAreaGranularity* pPacket = (packet_vkGetRenderAreaGranularity*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGranularity = (VkExtent2D*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGranularity);
    return pPacket;
}

typedef struct packet_vkCreateCommandPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkCommandPoolCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkCommandPool* pCommandPool;
    VkResult result;
} packet_vkCreateCommandPool;

static packet_vkCreateCommandPool* interpret_body_as_vkCreateCommandPool(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateCommandPool* pPacket = (packet_vkCreateCommandPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkCommandPoolCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pCommandPool = (VkCommandPool*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCommandPool);
    return pPacket;
}

typedef struct packet_vkDestroyCommandPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkCommandPool commandPool;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyCommandPool;

static packet_vkDestroyCommandPool* interpret_body_as_vkDestroyCommandPool(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyCommandPool* pPacket = (packet_vkDestroyCommandPool*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkResetCommandPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandPoolResetFlags flags;
    VkResult result;
} packet_vkResetCommandPool;

static packet_vkResetCommandPool* interpret_body_as_vkResetCommandPool(vktrace_trace_packet_header* pHeader) {
    packet_vkResetCommandPool* pPacket = (packet_vkResetCommandPool*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkAllocateCommandBuffers {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkCommandBufferAllocateInfo* pAllocateInfo;
    VkCommandBuffer* pCommandBuffers;
    VkResult result;
} packet_vkAllocateCommandBuffers;

static packet_vkAllocateCommandBuffers* interpret_body_as_vkAllocateCommandBuffers(vktrace_trace_packet_header* pHeader) {
    packet_vkAllocateCommandBuffers* pPacket = (packet_vkAllocateCommandBuffers*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocateInfo = (const VkCommandBufferAllocateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocateInfo);
    if (pPacket->pAllocateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pAllocateInfo);
    }
    pPacket->pCommandBuffers = (VkCommandBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCommandBuffers);
    return pPacket;
}

typedef struct packet_vkFreeCommandBuffers {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkCommandPool commandPool;
    uint32_t commandBufferCount;
    const VkCommandBuffer* pCommandBuffers;
} packet_vkFreeCommandBuffers;

static packet_vkFreeCommandBuffers* interpret_body_as_vkFreeCommandBuffers(vktrace_trace_packet_header* pHeader) {
    packet_vkFreeCommandBuffers* pPacket = (packet_vkFreeCommandBuffers*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCommandBuffers = (const VkCommandBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCommandBuffers);
    return pPacket;
}

typedef struct packet_vkBeginCommandBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkCommandBufferBeginInfo* pBeginInfo;
    VkResult result;
} packet_vkBeginCommandBuffer;

static packet_vkBeginCommandBuffer* interpret_body_as_vkBeginCommandBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkBeginCommandBuffer* pPacket = (packet_vkBeginCommandBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBeginInfo = (const VkCommandBufferBeginInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBeginInfo);
    if (pPacket->pBeginInfo != NULL) {
        VkCommandBufferBeginInfo* pInfo = (VkCommandBufferBeginInfo*) pPacket->pBeginInfo;
        pInfo->pInheritanceInfo = (VkCommandBufferInheritanceInfo*) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBeginInfo->pInheritanceInfo);

    }
    if (pPacket->pBeginInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pBeginInfo);
    }
    return pPacket;
}

typedef struct packet_vkEndCommandBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkResult result;
} packet_vkEndCommandBuffer;

static packet_vkEndCommandBuffer* interpret_body_as_vkEndCommandBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkEndCommandBuffer* pPacket = (packet_vkEndCommandBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkResetCommandBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkCommandBufferResetFlags flags;
    VkResult result;
} packet_vkResetCommandBuffer;

static packet_vkResetCommandBuffer* interpret_body_as_vkResetCommandBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkResetCommandBuffer* pPacket = (packet_vkResetCommandBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdBindPipeline {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineBindPoint pipelineBindPoint;
    VkPipeline pipeline;
} packet_vkCmdBindPipeline;

static packet_vkCmdBindPipeline* interpret_body_as_vkCmdBindPipeline(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBindPipeline* pPacket = (packet_vkCmdBindPipeline*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetViewport {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t firstViewport;
    uint32_t viewportCount;
    const VkViewport* pViewports;
} packet_vkCmdSetViewport;

static packet_vkCmdSetViewport* interpret_body_as_vkCmdSetViewport(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetViewport* pPacket = (packet_vkCmdSetViewport*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pViewports = (const VkViewport*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pViewports);
    return pPacket;
}

typedef struct packet_vkCmdSetScissor {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t firstScissor;
    uint32_t scissorCount;
    const VkRect2D* pScissors;
} packet_vkCmdSetScissor;

static packet_vkCmdSetScissor* interpret_body_as_vkCmdSetScissor(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetScissor* pPacket = (packet_vkCmdSetScissor*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pScissors = (const VkRect2D*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pScissors);
    return pPacket;
}

typedef struct packet_vkCmdSetLineWidth {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    float lineWidth;
} packet_vkCmdSetLineWidth;

static packet_vkCmdSetLineWidth* interpret_body_as_vkCmdSetLineWidth(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetLineWidth* pPacket = (packet_vkCmdSetLineWidth*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetDepthBias {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    float depthBiasConstantFactor;
    float depthBiasClamp;
    float depthBiasSlopeFactor;
} packet_vkCmdSetDepthBias;

static packet_vkCmdSetDepthBias* interpret_body_as_vkCmdSetDepthBias(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetDepthBias* pPacket = (packet_vkCmdSetDepthBias*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetBlendConstants {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const float blendConstants[4];
} packet_vkCmdSetBlendConstants;

static packet_vkCmdSetBlendConstants* interpret_body_as_vkCmdSetBlendConstants(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetBlendConstants* pPacket = (packet_vkCmdSetBlendConstants*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetDepthBounds {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    float minDepthBounds;
    float maxDepthBounds;
} packet_vkCmdSetDepthBounds;

static packet_vkCmdSetDepthBounds* interpret_body_as_vkCmdSetDepthBounds(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetDepthBounds* pPacket = (packet_vkCmdSetDepthBounds*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetStencilCompareMask {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t compareMask;
} packet_vkCmdSetStencilCompareMask;

static packet_vkCmdSetStencilCompareMask* interpret_body_as_vkCmdSetStencilCompareMask(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetStencilCompareMask* pPacket = (packet_vkCmdSetStencilCompareMask*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetStencilWriteMask {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t writeMask;
} packet_vkCmdSetStencilWriteMask;

static packet_vkCmdSetStencilWriteMask* interpret_body_as_vkCmdSetStencilWriteMask(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetStencilWriteMask* pPacket = (packet_vkCmdSetStencilWriteMask*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdSetStencilReference {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkStencilFaceFlags faceMask;
    uint32_t reference;
} packet_vkCmdSetStencilReference;

static packet_vkCmdSetStencilReference* interpret_body_as_vkCmdSetStencilReference(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetStencilReference* pPacket = (packet_vkCmdSetStencilReference*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdBindDescriptorSets {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineBindPoint pipelineBindPoint;
    VkPipelineLayout layout;
    uint32_t firstSet;
    uint32_t descriptorSetCount;
    const VkDescriptorSet* pDescriptorSets;
    uint32_t dynamicOffsetCount;
    const uint32_t* pDynamicOffsets;
} packet_vkCmdBindDescriptorSets;

static packet_vkCmdBindDescriptorSets* interpret_body_as_vkCmdBindDescriptorSets(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBindDescriptorSets* pPacket = (packet_vkCmdBindDescriptorSets*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDescriptorSets = (const VkDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorSets);
    pPacket->pDynamicOffsets = (const uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDynamicOffsets);
    return pPacket;
}

typedef struct packet_vkCmdBindIndexBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkIndexType indexType;
} packet_vkCmdBindIndexBuffer;

static packet_vkCmdBindIndexBuffer* interpret_body_as_vkCmdBindIndexBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBindIndexBuffer* pPacket = (packet_vkCmdBindIndexBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdBindVertexBuffers {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t firstBinding;
    uint32_t bindingCount;
    const VkBuffer* pBuffers;
    const VkDeviceSize* pOffsets;
} packet_vkCmdBindVertexBuffers;

static packet_vkCmdBindVertexBuffers* interpret_body_as_vkCmdBindVertexBuffers(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBindVertexBuffers* pPacket = (packet_vkCmdBindVertexBuffers*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBuffers = (const VkBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBuffers);
    pPacket->pOffsets = (const VkDeviceSize*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pOffsets);
    return pPacket;
}

typedef struct packet_vkCmdDraw {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t firstVertex;
    uint32_t firstInstance;
} packet_vkCmdDraw;

static packet_vkCmdDraw* interpret_body_as_vkCmdDraw(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDraw* pPacket = (packet_vkCmdDraw*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDrawIndexed {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t firstIndex;
    int32_t vertexOffset;
    uint32_t firstInstance;
} packet_vkCmdDrawIndexed;

static packet_vkCmdDrawIndexed* interpret_body_as_vkCmdDrawIndexed(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDrawIndexed* pPacket = (packet_vkCmdDrawIndexed*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDrawIndirect {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    uint32_t drawCount;
    uint32_t stride;
} packet_vkCmdDrawIndirect;

static packet_vkCmdDrawIndirect* interpret_body_as_vkCmdDrawIndirect(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDrawIndirect* pPacket = (packet_vkCmdDrawIndirect*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDrawIndexedIndirect {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    uint32_t drawCount;
    uint32_t stride;
} packet_vkCmdDrawIndexedIndirect;

static packet_vkCmdDrawIndexedIndirect* interpret_body_as_vkCmdDrawIndexedIndirect(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDrawIndexedIndirect* pPacket = (packet_vkCmdDrawIndexedIndirect*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDispatch {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t groupCountX;
    uint32_t groupCountY;
    uint32_t groupCountZ;
} packet_vkCmdDispatch;

static packet_vkCmdDispatch* interpret_body_as_vkCmdDispatch(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDispatch* pPacket = (packet_vkCmdDispatch*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDispatchIndirect {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
} packet_vkCmdDispatchIndirect;

static packet_vkCmdDispatchIndirect* interpret_body_as_vkCmdDispatchIndirect(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDispatchIndirect* pPacket = (packet_vkCmdDispatchIndirect*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdCopyBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer srcBuffer;
    VkBuffer dstBuffer;
    uint32_t regionCount;
    const VkBufferCopy* pRegions;
} packet_vkCmdCopyBuffer;

static packet_vkCmdCopyBuffer* interpret_body_as_vkCmdCopyBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdCopyBuffer* pPacket = (packet_vkCmdCopyBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkBufferCopy*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdCopyImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageCopy* pRegions;
} packet_vkCmdCopyImage;

static packet_vkCmdCopyImage* interpret_body_as_vkCmdCopyImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdCopyImage* pPacket = (packet_vkCmdCopyImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkImageCopy*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdBlitImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageBlit* pRegions;
    VkFilter filter;
} packet_vkCmdBlitImage;

static packet_vkCmdBlitImage* interpret_body_as_vkCmdBlitImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBlitImage* pPacket = (packet_vkCmdBlitImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkImageBlit*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdCopyBufferToImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer srcBuffer;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkBufferImageCopy* pRegions;
} packet_vkCmdCopyBufferToImage;

static packet_vkCmdCopyBufferToImage* interpret_body_as_vkCmdCopyBufferToImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdCopyBufferToImage* pPacket = (packet_vkCmdCopyBufferToImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkBufferImageCopy*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdCopyImageToBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkBuffer dstBuffer;
    uint32_t regionCount;
    const VkBufferImageCopy* pRegions;
} packet_vkCmdCopyImageToBuffer;

static packet_vkCmdCopyImageToBuffer* interpret_body_as_vkCmdCopyImageToBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdCopyImageToBuffer* pPacket = (packet_vkCmdCopyImageToBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkBufferImageCopy*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdUpdateBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize dataSize;
    const void* pData;
} packet_vkCmdUpdateBuffer;

static packet_vkCmdUpdateBuffer* interpret_body_as_vkCmdUpdateBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdUpdateBuffer* pPacket = (packet_vkCmdUpdateBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkCmdFillBuffer {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize size;
    uint32_t data;
} packet_vkCmdFillBuffer;

static packet_vkCmdFillBuffer* interpret_body_as_vkCmdFillBuffer(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdFillBuffer* pPacket = (packet_vkCmdFillBuffer*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdClearColorImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage image;
    VkImageLayout imageLayout;
    const VkClearColorValue* pColor;
    uint32_t rangeCount;
    const VkImageSubresourceRange* pRanges;
} packet_vkCmdClearColorImage;

static packet_vkCmdClearColorImage* interpret_body_as_vkCmdClearColorImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdClearColorImage* pPacket = (packet_vkCmdClearColorImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pColor = (const VkClearColorValue*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pColor);
    pPacket->pRanges = (const VkImageSubresourceRange*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRanges);
    return pPacket;
}

typedef struct packet_vkCmdClearDepthStencilImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage image;
    VkImageLayout imageLayout;
    const VkClearDepthStencilValue* pDepthStencil;
    uint32_t rangeCount;
    const VkImageSubresourceRange* pRanges;
} packet_vkCmdClearDepthStencilImage;

static packet_vkCmdClearDepthStencilImage* interpret_body_as_vkCmdClearDepthStencilImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdClearDepthStencilImage* pPacket = (packet_vkCmdClearDepthStencilImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDepthStencil = (const VkClearDepthStencilValue*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDepthStencil);
    pPacket->pRanges = (const VkImageSubresourceRange*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRanges);
    return pPacket;
}

typedef struct packet_vkCmdClearAttachments {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t attachmentCount;
    const VkClearAttachment* pAttachments;
    uint32_t rectCount;
    const VkClearRect* pRects;
} packet_vkCmdClearAttachments;

static packet_vkCmdClearAttachments* interpret_body_as_vkCmdClearAttachments(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdClearAttachments* pPacket = (packet_vkCmdClearAttachments*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAttachments = (const VkClearAttachment*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAttachments);
    pPacket->pRects = (const VkClearRect*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRects);
    return pPacket;
}

typedef struct packet_vkCmdResolveImage {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkImage srcImage;
    VkImageLayout srcImageLayout;
    VkImage dstImage;
    VkImageLayout dstImageLayout;
    uint32_t regionCount;
    const VkImageResolve* pRegions;
} packet_vkCmdResolveImage;

static packet_vkCmdResolveImage* interpret_body_as_vkCmdResolveImage(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdResolveImage* pPacket = (packet_vkCmdResolveImage*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRegions = (const VkImageResolve*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRegions);
    return pPacket;
}

typedef struct packet_vkCmdSetEvent {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkEvent event;
    VkPipelineStageFlags stageMask;
} packet_vkCmdSetEvent;

static packet_vkCmdSetEvent* interpret_body_as_vkCmdSetEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetEvent* pPacket = (packet_vkCmdSetEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdResetEvent {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkEvent event;
    VkPipelineStageFlags stageMask;
} packet_vkCmdResetEvent;

static packet_vkCmdResetEvent* interpret_body_as_vkCmdResetEvent(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdResetEvent* pPacket = (packet_vkCmdResetEvent*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdWaitEvents {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t eventCount;
    const VkEvent* pEvents;
    VkPipelineStageFlags srcStageMask;
    VkPipelineStageFlags dstStageMask;
    uint32_t memoryBarrierCount;
    const VkMemoryBarrier* pMemoryBarriers;
    uint32_t bufferMemoryBarrierCount;
    const VkBufferMemoryBarrier* pBufferMemoryBarriers;
    uint32_t imageMemoryBarrierCount;
    const VkImageMemoryBarrier* pImageMemoryBarriers;
} packet_vkCmdWaitEvents;

static packet_vkCmdWaitEvents* interpret_body_as_vkCmdWaitEvents(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdWaitEvents* pPacket = (packet_vkCmdWaitEvents*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pEvents = (const VkEvent*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pEvents);
    pPacket->pMemoryBarriers = (const VkMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryBarriers);
    pPacket->pBufferMemoryBarriers = (const VkBufferMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBufferMemoryBarriers);
    pPacket->pImageMemoryBarriers = (const VkImageMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageMemoryBarriers);
    return pPacket;
}

typedef struct packet_vkCmdPipelineBarrier {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineStageFlags srcStageMask;
    VkPipelineStageFlags dstStageMask;
    VkDependencyFlags dependencyFlags;
    uint32_t memoryBarrierCount;
    const VkMemoryBarrier* pMemoryBarriers;
    uint32_t bufferMemoryBarrierCount;
    const VkBufferMemoryBarrier* pBufferMemoryBarriers;
    uint32_t imageMemoryBarrierCount;
    const VkImageMemoryBarrier* pImageMemoryBarriers;
} packet_vkCmdPipelineBarrier;

static packet_vkCmdPipelineBarrier* interpret_body_as_vkCmdPipelineBarrier(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdPipelineBarrier* pPacket = (packet_vkCmdPipelineBarrier*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryBarriers = (const VkMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryBarriers);
    pPacket->pBufferMemoryBarriers = (const VkBufferMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBufferMemoryBarriers);
    pPacket->pImageMemoryBarriers = (const VkImageMemoryBarrier*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageMemoryBarriers);
    return pPacket;
}

typedef struct packet_vkCmdBeginQuery {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
    VkQueryControlFlags flags;
} packet_vkCmdBeginQuery;

static packet_vkCmdBeginQuery* interpret_body_as_vkCmdBeginQuery(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBeginQuery* pPacket = (packet_vkCmdBeginQuery*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdEndQuery {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t query;
} packet_vkCmdEndQuery;

static packet_vkCmdEndQuery* interpret_body_as_vkCmdEndQuery(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdEndQuery* pPacket = (packet_vkCmdEndQuery*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdResetQueryPool {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
} packet_vkCmdResetQueryPool;

static packet_vkCmdResetQueryPool* interpret_body_as_vkCmdResetQueryPool(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdResetQueryPool* pPacket = (packet_vkCmdResetQueryPool*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdWriteTimestamp {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineStageFlagBits pipelineStage;
    VkQueryPool queryPool;
    uint32_t query;
} packet_vkCmdWriteTimestamp;

static packet_vkCmdWriteTimestamp* interpret_body_as_vkCmdWriteTimestamp(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdWriteTimestamp* pPacket = (packet_vkCmdWriteTimestamp*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdCopyQueryPoolResults {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkQueryPool queryPool;
    uint32_t firstQuery;
    uint32_t queryCount;
    VkBuffer dstBuffer;
    VkDeviceSize dstOffset;
    VkDeviceSize stride;
    VkQueryResultFlags flags;
} packet_vkCmdCopyQueryPoolResults;

static packet_vkCmdCopyQueryPoolResults* interpret_body_as_vkCmdCopyQueryPoolResults(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdCopyQueryPoolResults* pPacket = (packet_vkCmdCopyQueryPoolResults*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdPushConstants {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineLayout layout;
    VkShaderStageFlags stageFlags;
    uint32_t offset;
    uint32_t size;
    const void* pValues;
} packet_vkCmdPushConstants;

static packet_vkCmdPushConstants* interpret_body_as_vkCmdPushConstants(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdPushConstants* pPacket = (packet_vkCmdPushConstants*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pValues = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pValues);
    return pPacket;
}

typedef struct packet_vkCmdBeginRenderPass {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkRenderPassBeginInfo* pRenderPassBegin;
    VkSubpassContents contents;
} packet_vkCmdBeginRenderPass;

static packet_vkCmdBeginRenderPass* interpret_body_as_vkCmdBeginRenderPass(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdBeginRenderPass* pPacket = (packet_vkCmdBeginRenderPass*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRenderPassBegin = (const VkRenderPassBeginInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRenderPassBegin);
    if (pPacket->pRenderPassBegin != NULL) {
        VkClearValue** ppCV = (VkClearValue**)&(pPacket->pRenderPassBegin->pClearValues);
        *ppCV = (VkClearValue*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pRenderPassBegin->pClearValues));
    }
    if (pPacket->pRenderPassBegin != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pRenderPassBegin);
    }
    return pPacket;
}

typedef struct packet_vkCmdNextSubpass {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkSubpassContents contents;
} packet_vkCmdNextSubpass;

static packet_vkCmdNextSubpass* interpret_body_as_vkCmdNextSubpass(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdNextSubpass* pPacket = (packet_vkCmdNextSubpass*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdEndRenderPass {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
} packet_vkCmdEndRenderPass;

static packet_vkCmdEndRenderPass* interpret_body_as_vkCmdEndRenderPass(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdEndRenderPass* pPacket = (packet_vkCmdEndRenderPass*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdExecuteCommands {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t commandBufferCount;
    const VkCommandBuffer* pCommandBuffers;
} packet_vkCmdExecuteCommands;

static packet_vkCmdExecuteCommands* interpret_body_as_vkCmdExecuteCommands(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdExecuteCommands* pPacket = (packet_vkCmdExecuteCommands*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCommandBuffers = (const VkCommandBuffer*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCommandBuffers);
    return pPacket;
}

typedef struct packet_vkBindBufferMemory2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindBufferMemoryInfo* pBindInfos;
    VkResult result;
} packet_vkBindBufferMemory2;

static packet_vkBindBufferMemory2* interpret_body_as_vkBindBufferMemory2(vktrace_trace_packet_header* pHeader) {
    packet_vkBindBufferMemory2* pPacket = (packet_vkBindBufferMemory2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBindInfos = (const VkBindBufferMemoryInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBindInfos);
    return pPacket;
}

typedef struct packet_vkBindImageMemory2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindImageMemoryInfo* pBindInfos;
    VkResult result;
} packet_vkBindImageMemory2;

static packet_vkBindImageMemory2* interpret_body_as_vkBindImageMemory2(vktrace_trace_packet_header* pHeader) {
    packet_vkBindImageMemory2* pPacket = (packet_vkBindImageMemory2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBindInfos = (const VkBindImageMemoryInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBindInfos);
    return pPacket;
}

typedef struct packet_vkGetDeviceGroupPeerMemoryFeatures {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t heapIndex;
    uint32_t localDeviceIndex;
    uint32_t remoteDeviceIndex;
    VkPeerMemoryFeatureFlags* pPeerMemoryFeatures;
} packet_vkGetDeviceGroupPeerMemoryFeatures;

static packet_vkGetDeviceGroupPeerMemoryFeatures* interpret_body_as_vkGetDeviceGroupPeerMemoryFeatures(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceGroupPeerMemoryFeatures* pPacket = (packet_vkGetDeviceGroupPeerMemoryFeatures*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPeerMemoryFeatures = (VkPeerMemoryFeatureFlags*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPeerMemoryFeatures);
    return pPacket;
}

typedef struct packet_vkCmdSetDeviceMask {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t deviceMask;
} packet_vkCmdSetDeviceMask;

static packet_vkCmdSetDeviceMask* interpret_body_as_vkCmdSetDeviceMask(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetDeviceMask* pPacket = (packet_vkCmdSetDeviceMask*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDispatchBase {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t baseGroupX;
    uint32_t baseGroupY;
    uint32_t baseGroupZ;
    uint32_t groupCountX;
    uint32_t groupCountY;
    uint32_t groupCountZ;
} packet_vkCmdDispatchBase;

static packet_vkCmdDispatchBase* interpret_body_as_vkCmdDispatchBase(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDispatchBase* pPacket = (packet_vkCmdDispatchBase*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkEnumeratePhysicalDeviceGroups {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    uint32_t* pPhysicalDeviceGroupCount;
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties;
    VkResult result;
} packet_vkEnumeratePhysicalDeviceGroups;

static packet_vkEnumeratePhysicalDeviceGroups* interpret_body_as_vkEnumeratePhysicalDeviceGroups(vktrace_trace_packet_header* pHeader) {
    packet_vkEnumeratePhysicalDeviceGroups* pPacket = (packet_vkEnumeratePhysicalDeviceGroups*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPhysicalDeviceGroupCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPhysicalDeviceGroupCount);
    pPacket->pPhysicalDeviceGroupProperties = (VkPhysicalDeviceGroupProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPhysicalDeviceGroupProperties);
    if (pPacket->pPhysicalDeviceGroupProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pPhysicalDeviceGroupProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetImageMemoryRequirements2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
} packet_vkGetImageMemoryRequirements2;

static packet_vkGetImageMemoryRequirements2* interpret_body_as_vkGetImageMemoryRequirements2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageMemoryRequirements2* pPacket = (packet_vkGetImageMemoryRequirements2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkImageMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pMemoryRequirements = (VkMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetBufferMemoryRequirements2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkBufferMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
} packet_vkGetBufferMemoryRequirements2;

static packet_vkGetBufferMemoryRequirements2* interpret_body_as_vkGetBufferMemoryRequirements2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetBufferMemoryRequirements2* pPacket = (packet_vkGetBufferMemoryRequirements2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkBufferMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pMemoryRequirements = (VkMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetImageSparseMemoryRequirements2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageSparseMemoryRequirementsInfo2* pInfo;
    uint32_t* pSparseMemoryRequirementCount;
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements;
} packet_vkGetImageSparseMemoryRequirements2;

static packet_vkGetImageSparseMemoryRequirements2* interpret_body_as_vkGetImageSparseMemoryRequirements2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageSparseMemoryRequirements2* pPacket = (packet_vkGetImageSparseMemoryRequirements2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkImageSparseMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pSparseMemoryRequirementCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirementCount);
    pPacket->pSparseMemoryRequirements = (VkSparseImageMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFeatures2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures2* pFeatures;
} packet_vkGetPhysicalDeviceFeatures2;

static packet_vkGetPhysicalDeviceFeatures2* interpret_body_as_vkGetPhysicalDeviceFeatures2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFeatures2* pPacket = (packet_vkGetPhysicalDeviceFeatures2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFeatures = (VkPhysicalDeviceFeatures2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFeatures);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties2* pProperties;
} packet_vkGetPhysicalDeviceProperties2;

static packet_vkGetPhysicalDeviceProperties2* interpret_body_as_vkGetPhysicalDeviceProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceProperties2* pPacket = (packet_vkGetPhysicalDeviceProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pProperties = (VkPhysicalDeviceProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFormatProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkFormatProperties2* pFormatProperties;
} packet_vkGetPhysicalDeviceFormatProperties2;

static packet_vkGetPhysicalDeviceFormatProperties2* interpret_body_as_vkGetPhysicalDeviceFormatProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFormatProperties2* pPacket = (packet_vkGetPhysicalDeviceFormatProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFormatProperties = (VkFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceImageFormatProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo;
    VkImageFormatProperties2* pImageFormatProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceImageFormatProperties2;

static packet_vkGetPhysicalDeviceImageFormatProperties2* interpret_body_as_vkGetPhysicalDeviceImageFormatProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceImageFormatProperties2* pPacket = (packet_vkGetPhysicalDeviceImageFormatProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImageFormatInfo = (const VkPhysicalDeviceImageFormatInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageFormatInfo);
    pPacket->pImageFormatProperties = (VkImageFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceQueueFamilyProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pQueueFamilyPropertyCount;
    VkQueueFamilyProperties2* pQueueFamilyProperties;
} packet_vkGetPhysicalDeviceQueueFamilyProperties2;

static packet_vkGetPhysicalDeviceQueueFamilyProperties2* interpret_body_as_vkGetPhysicalDeviceQueueFamilyProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceQueueFamilyProperties2* pPacket = (packet_vkGetPhysicalDeviceQueueFamilyProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pQueueFamilyPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyPropertyCount);
    pPacket->pQueueFamilyProperties = (VkQueueFamilyProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceMemoryProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties;
} packet_vkGetPhysicalDeviceMemoryProperties2;

static packet_vkGetPhysicalDeviceMemoryProperties2* interpret_body_as_vkGetPhysicalDeviceMemoryProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceMemoryProperties2* pPacket = (packet_vkGetPhysicalDeviceMemoryProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryProperties = (VkPhysicalDeviceMemoryProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSparseImageFormatProperties2 {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo;
    uint32_t* pPropertyCount;
    VkSparseImageFormatProperties2* pProperties;
} packet_vkGetPhysicalDeviceSparseImageFormatProperties2;

static packet_vkGetPhysicalDeviceSparseImageFormatProperties2* interpret_body_as_vkGetPhysicalDeviceSparseImageFormatProperties2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSparseImageFormatProperties2* pPacket = (packet_vkGetPhysicalDeviceSparseImageFormatProperties2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFormatInfo = (const VkPhysicalDeviceSparseImageFormatInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFormatInfo);
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkSparseImageFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkTrimCommandPool {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandPoolTrimFlags flags;
} packet_vkTrimCommandPool;

static packet_vkTrimCommandPool* interpret_body_as_vkTrimCommandPool(vktrace_trace_packet_header* pHeader) {
    packet_vkTrimCommandPool* pPacket = (packet_vkTrimCommandPool*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetDeviceQueue2 {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDeviceQueueInfo2* pQueueInfo;
    VkQueue* pQueue;
} packet_vkGetDeviceQueue2;

static packet_vkGetDeviceQueue2* interpret_body_as_vkGetDeviceQueue2(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceQueue2* pPacket = (packet_vkGetDeviceQueue2*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pQueueInfo = (const VkDeviceQueueInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueInfo);
    pPacket->pQueue = (VkQueue*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueue);
    return pPacket;
}

typedef struct packet_vkCreateSamplerYcbcrConversion {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSamplerYcbcrConversion* pYcbcrConversion;
    VkResult result;
} packet_vkCreateSamplerYcbcrConversion;

static packet_vkCreateSamplerYcbcrConversion* interpret_body_as_vkCreateSamplerYcbcrConversion(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSamplerYcbcrConversion* pPacket = (packet_vkCreateSamplerYcbcrConversion*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkSamplerYcbcrConversionCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pYcbcrConversion = (VkSamplerYcbcrConversion*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pYcbcrConversion);
    return pPacket;
}

typedef struct packet_vkDestroySamplerYcbcrConversion {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSamplerYcbcrConversion ycbcrConversion;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySamplerYcbcrConversion;

static packet_vkDestroySamplerYcbcrConversion* interpret_body_as_vkDestroySamplerYcbcrConversion(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySamplerYcbcrConversion* pPacket = (packet_vkDestroySamplerYcbcrConversion*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateDescriptorUpdateTemplate {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate;
    VkResult result;
} packet_vkCreateDescriptorUpdateTemplate;

static packet_vkCreateDescriptorUpdateTemplate* interpret_body_as_vkCreateDescriptorUpdateTemplate(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDescriptorUpdateTemplate* pPacket = (packet_vkCreateDescriptorUpdateTemplate*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDescriptorUpdateTemplateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pDescriptorUpdateTemplate = (VkDescriptorUpdateTemplate*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorUpdateTemplate);
    return pPacket;
}

typedef struct packet_vkDestroyDescriptorUpdateTemplate {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDescriptorUpdateTemplate;

static packet_vkDestroyDescriptorUpdateTemplate* interpret_body_as_vkDestroyDescriptorUpdateTemplate(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDescriptorUpdateTemplate* pPacket = (packet_vkDestroyDescriptorUpdateTemplate*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkUpdateDescriptorSetWithTemplate {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorSet descriptorSet;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const void* pData;
} packet_vkUpdateDescriptorSetWithTemplate;

static packet_vkUpdateDescriptorSetWithTemplate* interpret_body_as_vkUpdateDescriptorSetWithTemplate(vktrace_trace_packet_header* pHeader) {
    packet_vkUpdateDescriptorSetWithTemplate* pPacket = (packet_vkUpdateDescriptorSetWithTemplate*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalBufferProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo;
    VkExternalBufferProperties* pExternalBufferProperties;
} packet_vkGetPhysicalDeviceExternalBufferProperties;

static packet_vkGetPhysicalDeviceExternalBufferProperties* interpret_body_as_vkGetPhysicalDeviceExternalBufferProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalBufferProperties* pPacket = (packet_vkGetPhysicalDeviceExternalBufferProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalBufferInfo = (const VkPhysicalDeviceExternalBufferInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalBufferInfo);
    if (pPacket->pExternalBufferInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalBufferInfo);
    }
    pPacket->pExternalBufferProperties = (VkExternalBufferProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalBufferProperties);
    if (pPacket->pExternalBufferProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalBufferProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalFenceProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo;
    VkExternalFenceProperties* pExternalFenceProperties;
} packet_vkGetPhysicalDeviceExternalFenceProperties;

static packet_vkGetPhysicalDeviceExternalFenceProperties* interpret_body_as_vkGetPhysicalDeviceExternalFenceProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalFenceProperties* pPacket = (packet_vkGetPhysicalDeviceExternalFenceProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalFenceInfo = (const VkPhysicalDeviceExternalFenceInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalFenceInfo);
    if (pPacket->pExternalFenceInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalFenceInfo);
    }
    pPacket->pExternalFenceProperties = (VkExternalFenceProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalFenceProperties);
    if (pPacket->pExternalFenceProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalFenceProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalSemaphoreProperties {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo;
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties;
} packet_vkGetPhysicalDeviceExternalSemaphoreProperties;

static packet_vkGetPhysicalDeviceExternalSemaphoreProperties* interpret_body_as_vkGetPhysicalDeviceExternalSemaphoreProperties(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalSemaphoreProperties* pPacket = (packet_vkGetPhysicalDeviceExternalSemaphoreProperties*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalSemaphoreInfo = (const VkPhysicalDeviceExternalSemaphoreInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalSemaphoreInfo);
    if (pPacket->pExternalSemaphoreInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalSemaphoreInfo);
    }
    pPacket->pExternalSemaphoreProperties = (VkExternalSemaphoreProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalSemaphoreProperties);
    if (pPacket->pExternalSemaphoreProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalSemaphoreProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetDescriptorSetLayoutSupport {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorSetLayoutCreateInfo* pCreateInfo;
    VkDescriptorSetLayoutSupport* pSupport;
} packet_vkGetDescriptorSetLayoutSupport;

static packet_vkGetDescriptorSetLayoutSupport* interpret_body_as_vkGetDescriptorSetLayoutSupport(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDescriptorSetLayoutSupport* pPacket = (packet_vkGetDescriptorSetLayoutSupport*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDescriptorSetLayoutCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pSupport = (VkDescriptorSetLayoutSupport*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSupport);
    return pPacket;
}

typedef struct packet_vkDestroySurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    VkSurfaceKHR surface;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySurfaceKHR;

static packet_vkDestroySurfaceKHR* interpret_body_as_vkDestroySurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySurfaceKHR* pPacket = (packet_vkDestroySurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceSupportKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t queueFamilyIndex;
    VkSurfaceKHR surface;
    VkBool32* pSupported;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceSupportKHR;

static packet_vkGetPhysicalDeviceSurfaceSupportKHR* interpret_body_as_vkGetPhysicalDeviceSurfaceSupportKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceSupportKHR* pPacket = (packet_vkGetPhysicalDeviceSurfaceSupportKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSupported = (VkBool32*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSupported);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    VkSurfaceCapabilitiesKHR* pSurfaceCapabilities;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR;

static packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR* interpret_body_as_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR* pPacket = (packet_vkGetPhysicalDeviceSurfaceCapabilitiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSurfaceCapabilities = (VkSurfaceCapabilitiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceCapabilities);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceFormatsKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    uint32_t* pSurfaceFormatCount;
    VkSurfaceFormatKHR* pSurfaceFormats;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceFormatsKHR;

static packet_vkGetPhysicalDeviceSurfaceFormatsKHR* interpret_body_as_vkGetPhysicalDeviceSurfaceFormatsKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceFormatsKHR* pPacket = (packet_vkGetPhysicalDeviceSurfaceFormatsKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSurfaceFormatCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceFormatCount);
    pPacket->pSurfaceFormats = (VkSurfaceFormatKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceFormats);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfacePresentModesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    uint32_t* pPresentModeCount;
    VkPresentModeKHR* pPresentModes;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfacePresentModesKHR;

static packet_vkGetPhysicalDeviceSurfacePresentModesKHR* interpret_body_as_vkGetPhysicalDeviceSurfacePresentModesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfacePresentModesKHR* pPacket = (packet_vkGetPhysicalDeviceSurfacePresentModesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPresentModeCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPresentModeCount);
    pPacket->pPresentModes = (VkPresentModeKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPresentModes);
    return pPacket;
}

typedef struct packet_vkCreateSwapchainKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSwapchainCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSwapchainKHR* pSwapchain;
    VkResult result;
} packet_vkCreateSwapchainKHR;

static packet_vkCreateSwapchainKHR* interpret_body_as_vkCreateSwapchainKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSwapchainKHR* pPacket = (packet_vkCreateSwapchainKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkSwapchainCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        uint32_t **ppQFI = (uint32_t**)&pPacket->pCreateInfo->pQueueFamilyIndices;
        (*ppQFI) = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pCreateInfo->pQueueFamilyIndices));
    }
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSwapchain = (VkSwapchainKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSwapchain);
    return pPacket;
}

typedef struct packet_vkDestroySwapchainKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySwapchainKHR;

static packet_vkDestroySwapchainKHR* interpret_body_as_vkDestroySwapchainKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySwapchainKHR* pPacket = (packet_vkDestroySwapchainKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkGetSwapchainImagesKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    uint32_t* pSwapchainImageCount;
    VkImage* pSwapchainImages;
    VkResult result;
} packet_vkGetSwapchainImagesKHR;

static packet_vkGetSwapchainImagesKHR* interpret_body_as_vkGetSwapchainImagesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetSwapchainImagesKHR* pPacket = (packet_vkGetSwapchainImagesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSwapchainImageCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSwapchainImageCount);
    pPacket->pSwapchainImages = (VkImage*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSwapchainImages);
    return pPacket;
}

typedef struct packet_vkAcquireNextImageKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    uint64_t timeout;
    VkSemaphore semaphore;
    VkFence fence;
    uint32_t* pImageIndex;
    VkResult result;
} packet_vkAcquireNextImageKHR;

static packet_vkAcquireNextImageKHR* interpret_body_as_vkAcquireNextImageKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkAcquireNextImageKHR* pPacket = (packet_vkAcquireNextImageKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImageIndex = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageIndex);
    return pPacket;
}

typedef struct packet_vkQueuePresentKHR {
    vktrace_trace_packet_header* header;
    VkQueue queue;
    const VkPresentInfoKHR* pPresentInfo;
    VkResult result;
} packet_vkQueuePresentKHR;

static packet_vkQueuePresentKHR* interpret_body_as_vkQueuePresentKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkQueuePresentKHR* pPacket = (packet_vkQueuePresentKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPresentInfo = (const VkPresentInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPresentInfo);
    if (pPacket->pPresentInfo != NULL) {
        VkSwapchainKHR **ppSC = (VkSwapchainKHR **)& pPacket->pPresentInfo->pSwapchains;
        *ppSC = (VkSwapchainKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pPresentInfo->pSwapchains));
        VkSemaphore **ppS = (VkSemaphore **) &pPacket->pPresentInfo->pWaitSemaphores;
        *ppS = (VkSemaphore *) vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pPresentInfo->pWaitSemaphores));
        uint32_t **ppII = (uint32_t **) &pPacket->pPresentInfo->pImageIndices;
        *ppII = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pPresentInfo->pImageIndices));
        if (pPacket->pPresentInfo->pResults != NULL) {
            VkResult **ppR = (VkResult **) &pPacket->pPresentInfo->pResults;
            *ppR = (VkResult*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)(pPacket->pPresentInfo->pResults));
        }
    }
    if (pPacket->pPresentInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pPresentInfo);
    }
    return pPacket;
}

typedef struct packet_vkGetDeviceGroupPresentCapabilitiesKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities;
    VkResult result;
} packet_vkGetDeviceGroupPresentCapabilitiesKHR;

static packet_vkGetDeviceGroupPresentCapabilitiesKHR* interpret_body_as_vkGetDeviceGroupPresentCapabilitiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceGroupPresentCapabilitiesKHR* pPacket = (packet_vkGetDeviceGroupPresentCapabilitiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDeviceGroupPresentCapabilities = (VkDeviceGroupPresentCapabilitiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDeviceGroupPresentCapabilities);
    if (pPacket->pDeviceGroupPresentCapabilities != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pDeviceGroupPresentCapabilities);
    }
    return pPacket;
}

typedef struct packet_vkGetDeviceGroupSurfacePresentModesKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSurfaceKHR surface;
    VkDeviceGroupPresentModeFlagsKHR* pModes;
    VkResult result;
} packet_vkGetDeviceGroupSurfacePresentModesKHR;

static packet_vkGetDeviceGroupSurfacePresentModesKHR* interpret_body_as_vkGetDeviceGroupSurfacePresentModesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDeviceGroupSurfacePresentModesKHR* pPacket = (packet_vkGetDeviceGroupSurfacePresentModesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pModes = (VkDeviceGroupPresentModeFlagsKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pModes);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDevicePresentRectanglesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    uint32_t* pRectCount;
    VkRect2D* pRects;
    VkResult result;
} packet_vkGetPhysicalDevicePresentRectanglesKHR;

static packet_vkGetPhysicalDevicePresentRectanglesKHR* interpret_body_as_vkGetPhysicalDevicePresentRectanglesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDevicePresentRectanglesKHR* pPacket = (packet_vkGetPhysicalDevicePresentRectanglesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pRectCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRectCount);
    pPacket->pRects = (VkRect2D*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pRects);
    return pPacket;
}

typedef struct packet_vkAcquireNextImage2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkAcquireNextImageInfoKHR* pAcquireInfo;
    uint32_t* pImageIndex;
    VkResult result;
} packet_vkAcquireNextImage2KHR;

static packet_vkAcquireNextImage2KHR* interpret_body_as_vkAcquireNextImage2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkAcquireNextImage2KHR* pPacket = (packet_vkAcquireNextImage2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAcquireInfo = (const VkAcquireNextImageInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAcquireInfo);
    if (pPacket->pAcquireInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pAcquireInfo);
    }
    pPacket->pImageIndex = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageIndex);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceDisplayPropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkDisplayPropertiesKHR* pProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceDisplayPropertiesKHR;

static packet_vkGetPhysicalDeviceDisplayPropertiesKHR* interpret_body_as_vkGetPhysicalDeviceDisplayPropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceDisplayPropertiesKHR* pPacket = (packet_vkGetPhysicalDeviceDisplayPropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayPropertiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkDisplayPlanePropertiesKHR* pProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR;

static packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR* interpret_body_as_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR* pPacket = (packet_vkGetPhysicalDeviceDisplayPlanePropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayPlanePropertiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetDisplayPlaneSupportedDisplaysKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t planeIndex;
    uint32_t* pDisplayCount;
    VkDisplayKHR* pDisplays;
    VkResult result;
} packet_vkGetDisplayPlaneSupportedDisplaysKHR;

static packet_vkGetDisplayPlaneSupportedDisplaysKHR* interpret_body_as_vkGetDisplayPlaneSupportedDisplaysKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDisplayPlaneSupportedDisplaysKHR* pPacket = (packet_vkGetDisplayPlaneSupportedDisplaysKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDisplayCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplayCount);
    pPacket->pDisplays = (VkDisplayKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplays);
    return pPacket;
}

typedef struct packet_vkGetDisplayModePropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDisplayKHR display;
    uint32_t* pPropertyCount;
    VkDisplayModePropertiesKHR* pProperties;
    VkResult result;
} packet_vkGetDisplayModePropertiesKHR;

static packet_vkGetDisplayModePropertiesKHR* interpret_body_as_vkGetDisplayModePropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDisplayModePropertiesKHR* pPacket = (packet_vkGetDisplayModePropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayModePropertiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkCreateDisplayModeKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDisplayKHR display;
    const VkDisplayModeCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDisplayModeKHR* pMode;
    VkResult result;
} packet_vkCreateDisplayModeKHR;

static packet_vkCreateDisplayModeKHR* interpret_body_as_vkCreateDisplayModeKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDisplayModeKHR* pPacket = (packet_vkCreateDisplayModeKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDisplayModeCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pMode = (VkDisplayModeKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMode);
    return pPacket;
}

typedef struct packet_vkGetDisplayPlaneCapabilitiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDisplayModeKHR mode;
    uint32_t planeIndex;
    VkDisplayPlaneCapabilitiesKHR* pCapabilities;
    VkResult result;
} packet_vkGetDisplayPlaneCapabilitiesKHR;

static packet_vkGetDisplayPlaneCapabilitiesKHR* interpret_body_as_vkGetDisplayPlaneCapabilitiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDisplayPlaneCapabilitiesKHR* pPacket = (packet_vkGetDisplayPlaneCapabilitiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCapabilities = (VkDisplayPlaneCapabilitiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCapabilities);
    return pPacket;
}

typedef struct packet_vkCreateDisplayPlaneSurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkDisplaySurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateDisplayPlaneSurfaceKHR;

static packet_vkCreateDisplayPlaneSurfaceKHR* interpret_body_as_vkCreateDisplayPlaneSurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDisplayPlaneSurfaceKHR* pPacket = (packet_vkCreateDisplayPlaneSurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDisplaySurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkCreateSharedSwapchainsKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t swapchainCount;
    const VkSwapchainCreateInfoKHR* pCreateInfos;
    const VkAllocationCallbacks* pAllocator;
    VkSwapchainKHR* pSwapchains;
    VkResult result;
} packet_vkCreateSharedSwapchainsKHR;

static packet_vkCreateSharedSwapchainsKHR* interpret_body_as_vkCreateSharedSwapchainsKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSharedSwapchainsKHR* pPacket = (packet_vkCreateSharedSwapchainsKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfos = (const VkSwapchainCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfos);
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSwapchains = (VkSwapchainKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSwapchains);
    return pPacket;
}

typedef struct packet_vkCreateXlibSurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkXlibSurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateXlibSurfaceKHR;

static packet_vkCreateXlibSurfaceKHR* interpret_body_as_vkCreateXlibSurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateXlibSurfaceKHR* pPacket = (packet_vkCreateXlibSurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkXlibSurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceXlibPresentationSupportKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t queueFamilyIndex;
    Display* dpy;
    VisualID visualID;
    VkBool32 result;
} packet_vkGetPhysicalDeviceXlibPresentationSupportKHR;

static packet_vkGetPhysicalDeviceXlibPresentationSupportKHR* interpret_body_as_vkGetPhysicalDeviceXlibPresentationSupportKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceXlibPresentationSupportKHR* pPacket = (packet_vkGetPhysicalDeviceXlibPresentationSupportKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->dpy = (Display*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->dpy);
    return pPacket;
}

typedef struct packet_vkCreateXcbSurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkXcbSurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateXcbSurfaceKHR;

static packet_vkCreateXcbSurfaceKHR* interpret_body_as_vkCreateXcbSurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateXcbSurfaceKHR* pPacket = (packet_vkCreateXcbSurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkXcbSurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceXcbPresentationSupportKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t queueFamilyIndex;
    xcb_connection_t* connection;
    xcb_visualid_t visual_id;
    VkBool32 result;
} packet_vkGetPhysicalDeviceXcbPresentationSupportKHR;

static packet_vkGetPhysicalDeviceXcbPresentationSupportKHR* interpret_body_as_vkGetPhysicalDeviceXcbPresentationSupportKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceXcbPresentationSupportKHR* pPacket = (packet_vkGetPhysicalDeviceXcbPresentationSupportKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->connection = (xcb_connection_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->connection);
    return pPacket;
}

typedef struct packet_vkCreateWaylandSurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkWaylandSurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateWaylandSurfaceKHR;

static packet_vkCreateWaylandSurfaceKHR* interpret_body_as_vkCreateWaylandSurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateWaylandSurfaceKHR* pPacket = (packet_vkCreateWaylandSurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkWaylandSurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t queueFamilyIndex;
    struct wl_display* display;
    VkBool32 result;
} packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR;

static packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR* interpret_body_as_vkGetPhysicalDeviceWaylandPresentationSupportKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR* pPacket = (packet_vkGetPhysicalDeviceWaylandPresentationSupportKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->display = (struct wl_display*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->display);
    return pPacket;
}

typedef struct packet_vkCreateAndroidSurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkAndroidSurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateAndroidSurfaceKHR;

static packet_vkCreateAndroidSurfaceKHR* interpret_body_as_vkCreateAndroidSurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateAndroidSurfaceKHR* pPacket = (packet_vkCreateAndroidSurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkAndroidSurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkCreateWin32SurfaceKHR {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkWin32SurfaceCreateInfoKHR* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSurfaceKHR* pSurface;
    VkResult result;
} packet_vkCreateWin32SurfaceKHR;

static packet_vkCreateWin32SurfaceKHR* interpret_body_as_vkCreateWin32SurfaceKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateWin32SurfaceKHR* pPacket = (packet_vkCreateWin32SurfaceKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkWin32SurfaceCreateInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pSurface = (VkSurfaceKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurface);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceWin32PresentationSupportKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t queueFamilyIndex;
    VkBool32 result;
} packet_vkGetPhysicalDeviceWin32PresentationSupportKHR;

static packet_vkGetPhysicalDeviceWin32PresentationSupportKHR* interpret_body_as_vkGetPhysicalDeviceWin32PresentationSupportKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceWin32PresentationSupportKHR* pPacket = (packet_vkGetPhysicalDeviceWin32PresentationSupportKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFeatures2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceFeatures2* pFeatures;
} packet_vkGetPhysicalDeviceFeatures2KHR;

static packet_vkGetPhysicalDeviceFeatures2KHR* interpret_body_as_vkGetPhysicalDeviceFeatures2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFeatures2KHR* pPacket = (packet_vkGetPhysicalDeviceFeatures2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFeatures = (VkPhysicalDeviceFeatures2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFeatures);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties2* pProperties;
} packet_vkGetPhysicalDeviceProperties2KHR;

static packet_vkGetPhysicalDeviceProperties2KHR* interpret_body_as_vkGetPhysicalDeviceProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pProperties = (VkPhysicalDeviceProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceFormatProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkFormatProperties2* pFormatProperties;
} packet_vkGetPhysicalDeviceFormatProperties2KHR;

static packet_vkGetPhysicalDeviceFormatProperties2KHR* interpret_body_as_vkGetPhysicalDeviceFormatProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceFormatProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceFormatProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFormatProperties = (VkFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceImageFormatProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo;
    VkImageFormatProperties2* pImageFormatProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceImageFormatProperties2KHR;

static packet_vkGetPhysicalDeviceImageFormatProperties2KHR* interpret_body_as_vkGetPhysicalDeviceImageFormatProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceImageFormatProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceImageFormatProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImageFormatInfo = (const VkPhysicalDeviceImageFormatInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageFormatInfo);
    pPacket->pImageFormatProperties = (VkImageFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImageFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pQueueFamilyPropertyCount;
    VkQueueFamilyProperties2* pQueueFamilyProperties;
} packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR;

static packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR* interpret_body_as_vkGetPhysicalDeviceQueueFamilyProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceQueueFamilyProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pQueueFamilyPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyPropertyCount);
    pPacket->pQueueFamilyProperties = (VkQueueFamilyProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pQueueFamilyProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceMemoryProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceMemoryProperties2* pMemoryProperties;
} packet_vkGetPhysicalDeviceMemoryProperties2KHR;

static packet_vkGetPhysicalDeviceMemoryProperties2KHR* interpret_body_as_vkGetPhysicalDeviceMemoryProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceMemoryProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceMemoryProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryProperties = (VkPhysicalDeviceMemoryProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryProperties);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo;
    uint32_t* pPropertyCount;
    VkSparseImageFormatProperties2* pProperties;
} packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR;

static packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR* interpret_body_as_vkGetPhysicalDeviceSparseImageFormatProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceSparseImageFormatProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFormatInfo = (const VkPhysicalDeviceSparseImageFormatInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFormatInfo);
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkSparseImageFormatProperties2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    return pPacket;
}

typedef struct packet_vkTrimCommandPoolKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandPoolTrimFlags flags;
} packet_vkTrimCommandPoolKHR;

static packet_vkTrimCommandPoolKHR* interpret_body_as_vkTrimCommandPoolKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkTrimCommandPoolKHR* pPacket = (packet_vkTrimCommandPoolKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo;
    VkExternalBufferProperties* pExternalBufferProperties;
} packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR;

static packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR* interpret_body_as_vkGetPhysicalDeviceExternalBufferPropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR* pPacket = (packet_vkGetPhysicalDeviceExternalBufferPropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalBufferInfo = (const VkPhysicalDeviceExternalBufferInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalBufferInfo);
    if (pPacket->pExternalBufferInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalBufferInfo);
    }
    pPacket->pExternalBufferProperties = (VkExternalBufferProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalBufferProperties);
    if (pPacket->pExternalBufferProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalBufferProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetMemoryWin32HandleKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo;
    HANDLE* pHandle;
    VkResult result;
} packet_vkGetMemoryWin32HandleKHR;

static packet_vkGetMemoryWin32HandleKHR* interpret_body_as_vkGetMemoryWin32HandleKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryWin32HandleKHR* pPacket = (packet_vkGetMemoryWin32HandleKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetWin32HandleInfo = (const VkMemoryGetWin32HandleInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetWin32HandleInfo);
    pPacket->pHandle = (HANDLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pHandle);
    return pPacket;
}

typedef struct packet_vkGetMemoryWin32HandlePropertiesKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkExternalMemoryHandleTypeFlagBits handleType;
    HANDLE handle;
    VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties;
    VkResult result;
} packet_vkGetMemoryWin32HandlePropertiesKHR;

static packet_vkGetMemoryWin32HandlePropertiesKHR* interpret_body_as_vkGetMemoryWin32HandlePropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryWin32HandlePropertiesKHR* pPacket = (packet_vkGetMemoryWin32HandlePropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryWin32HandleProperties = (VkMemoryWin32HandlePropertiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryWin32HandleProperties);
    return pPacket;
}

typedef struct packet_vkGetMemoryFdKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkMemoryGetFdInfoKHR* pGetFdInfo;
    int* pFd;
    VkResult result;
} packet_vkGetMemoryFdKHR;

static packet_vkGetMemoryFdKHR* interpret_body_as_vkGetMemoryFdKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryFdKHR* pPacket = (packet_vkGetMemoryFdKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetFdInfo = (const VkMemoryGetFdInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetFdInfo);
    if (pPacket->pGetFdInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pGetFdInfo);
    }
    pPacket->pFd = (int*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFd);
    return pPacket;
}

typedef struct packet_vkGetMemoryFdPropertiesKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkExternalMemoryHandleTypeFlagBits handleType;
    int fd;
    VkMemoryFdPropertiesKHR* pMemoryFdProperties;
    VkResult result;
} packet_vkGetMemoryFdPropertiesKHR;

static packet_vkGetMemoryFdPropertiesKHR* interpret_body_as_vkGetMemoryFdPropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryFdPropertiesKHR* pPacket = (packet_vkGetMemoryFdPropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMemoryFdProperties = (VkMemoryFdPropertiesKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryFdProperties);
    if (pPacket->pMemoryFdProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pMemoryFdProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo;
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties;
} packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;

static packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR* interpret_body_as_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR* pPacket = (packet_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalSemaphoreInfo = (const VkPhysicalDeviceExternalSemaphoreInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalSemaphoreInfo);
    if (pPacket->pExternalSemaphoreInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalSemaphoreInfo);
    }
    pPacket->pExternalSemaphoreProperties = (VkExternalSemaphoreProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalSemaphoreProperties);
    if (pPacket->pExternalSemaphoreProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalSemaphoreProperties);
    }
    return pPacket;
}

typedef struct packet_vkImportSemaphoreWin32HandleKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo;
    VkResult result;
} packet_vkImportSemaphoreWin32HandleKHR;

static packet_vkImportSemaphoreWin32HandleKHR* interpret_body_as_vkImportSemaphoreWin32HandleKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkImportSemaphoreWin32HandleKHR* pPacket = (packet_vkImportSemaphoreWin32HandleKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImportSemaphoreWin32HandleInfo = (const VkImportSemaphoreWin32HandleInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImportSemaphoreWin32HandleInfo);
    return pPacket;
}

typedef struct packet_vkGetSemaphoreWin32HandleKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo;
    HANDLE* pHandle;
    VkResult result;
} packet_vkGetSemaphoreWin32HandleKHR;

static packet_vkGetSemaphoreWin32HandleKHR* interpret_body_as_vkGetSemaphoreWin32HandleKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetSemaphoreWin32HandleKHR* pPacket = (packet_vkGetSemaphoreWin32HandleKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetWin32HandleInfo = (const VkSemaphoreGetWin32HandleInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetWin32HandleInfo);
    pPacket->pHandle = (HANDLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pHandle);
    return pPacket;
}

typedef struct packet_vkImportSemaphoreFdKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo;
    VkResult result;
} packet_vkImportSemaphoreFdKHR;

static packet_vkImportSemaphoreFdKHR* interpret_body_as_vkImportSemaphoreFdKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkImportSemaphoreFdKHR* pPacket = (packet_vkImportSemaphoreFdKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImportSemaphoreFdInfo = (const VkImportSemaphoreFdInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImportSemaphoreFdInfo);
    if (pPacket->pImportSemaphoreFdInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pImportSemaphoreFdInfo);
    }
    return pPacket;
}

typedef struct packet_vkGetSemaphoreFdKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSemaphoreGetFdInfoKHR* pGetFdInfo;
    int* pFd;
    VkResult result;
} packet_vkGetSemaphoreFdKHR;

static packet_vkGetSemaphoreFdKHR* interpret_body_as_vkGetSemaphoreFdKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetSemaphoreFdKHR* pPacket = (packet_vkGetSemaphoreFdKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetFdInfo = (const VkSemaphoreGetFdInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetFdInfo);
    if (pPacket->pGetFdInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pGetFdInfo);
    }
    pPacket->pFd = (int*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFd);
    return pPacket;
}

typedef struct packet_vkCmdPushDescriptorSetKHR {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkPipelineBindPoint pipelineBindPoint;
    VkPipelineLayout layout;
    uint32_t set;
    uint32_t descriptorWriteCount;
    const VkWriteDescriptorSet* pDescriptorWrites;
} packet_vkCmdPushDescriptorSetKHR;

static packet_vkCmdPushDescriptorSetKHR* interpret_body_as_vkCmdPushDescriptorSetKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdPushDescriptorSetKHR* pPacket = (packet_vkCmdPushDescriptorSetKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDescriptorWrites = (const VkWriteDescriptorSet*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites);
    if (pPacket->pDescriptorWrites != NULL) {
        uint32_t i;
        for (i = 0; i < pPacket->descriptorWriteCount; i++) {
            vktrace_interpret_pnext_pointers(pPacket->header, (void *)&pPacket->pDescriptorWrites[i]);
            switch (pPacket->pDescriptorWrites[i].descriptorType) {
            case VK_DESCRIPTOR_TYPE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            case VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT: {
                    VkDescriptorImageInfo** ppImageInfo = (VkDescriptorImageInfo**)&pPacket->pDescriptorWrites[i].pImageInfo;
                    *ppImageInfo = (VkDescriptorImageInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pImageInfo);
                }                break;            case VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER: {
                    VkBufferView** ppTexelBufferView = (VkBufferView**)&pPacket->pDescriptorWrites[i].pTexelBufferView;
                    *ppTexelBufferView = (VkBufferView*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pTexelBufferView);
                }                break;            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC: {
                    VkDescriptorBufferInfo** ppBufferInfo = (VkDescriptorBufferInfo**)&pPacket->pDescriptorWrites[i].pBufferInfo;
                    *ppBufferInfo = (VkDescriptorBufferInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorWrites[i].pBufferInfo);
                }
                break;
            default:
                break;
            }
        }
    }
    return pPacket;
}

typedef struct packet_vkCmdPushDescriptorSetWithTemplateKHR {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    VkPipelineLayout layout;
    uint32_t set;
    const void* pData;
} packet_vkCmdPushDescriptorSetWithTemplateKHR;

static packet_vkCmdPushDescriptorSetWithTemplateKHR* interpret_body_as_vkCmdPushDescriptorSetWithTemplateKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdPushDescriptorSetWithTemplateKHR* pPacket = (packet_vkCmdPushDescriptorSetWithTemplateKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkCreateDescriptorUpdateTemplateKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate;
    VkResult result;
} packet_vkCreateDescriptorUpdateTemplateKHR;

static packet_vkCreateDescriptorUpdateTemplateKHR* interpret_body_as_vkCreateDescriptorUpdateTemplateKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDescriptorUpdateTemplateKHR* pPacket = (packet_vkCreateDescriptorUpdateTemplateKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDescriptorUpdateTemplateCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pDescriptorUpdateTemplate = (VkDescriptorUpdateTemplate*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDescriptorUpdateTemplate);
    return pPacket;
}

typedef struct packet_vkDestroyDescriptorUpdateTemplateKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDescriptorUpdateTemplateKHR;

static packet_vkDestroyDescriptorUpdateTemplateKHR* interpret_body_as_vkDestroyDescriptorUpdateTemplateKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDescriptorUpdateTemplateKHR* pPacket = (packet_vkDestroyDescriptorUpdateTemplateKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkUpdateDescriptorSetWithTemplateKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDescriptorSet descriptorSet;
    VkDescriptorUpdateTemplate descriptorUpdateTemplate;
    const void* pData;
} packet_vkUpdateDescriptorSetWithTemplateKHR;

static packet_vkUpdateDescriptorSetWithTemplateKHR* interpret_body_as_vkUpdateDescriptorSetWithTemplateKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkUpdateDescriptorSetWithTemplateKHR* pPacket = (packet_vkUpdateDescriptorSetWithTemplateKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pData = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkGetSwapchainStatusKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    VkResult result;
} packet_vkGetSwapchainStatusKHR;

static packet_vkGetSwapchainStatusKHR* interpret_body_as_vkGetSwapchainStatusKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetSwapchainStatusKHR* pPacket = (packet_vkGetSwapchainStatusKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalFencePropertiesKHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo;
    VkExternalFenceProperties* pExternalFenceProperties;
} packet_vkGetPhysicalDeviceExternalFencePropertiesKHR;

static packet_vkGetPhysicalDeviceExternalFencePropertiesKHR* interpret_body_as_vkGetPhysicalDeviceExternalFencePropertiesKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalFencePropertiesKHR* pPacket = (packet_vkGetPhysicalDeviceExternalFencePropertiesKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalFenceInfo = (const VkPhysicalDeviceExternalFenceInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalFenceInfo);
    if (pPacket->pExternalFenceInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalFenceInfo);
    }
    pPacket->pExternalFenceProperties = (VkExternalFenceProperties*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalFenceProperties);
    if (pPacket->pExternalFenceProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pExternalFenceProperties);
    }
    return pPacket;
}

typedef struct packet_vkImportFenceWin32HandleKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo;
    VkResult result;
} packet_vkImportFenceWin32HandleKHR;

static packet_vkImportFenceWin32HandleKHR* interpret_body_as_vkImportFenceWin32HandleKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkImportFenceWin32HandleKHR* pPacket = (packet_vkImportFenceWin32HandleKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImportFenceWin32HandleInfo = (const VkImportFenceWin32HandleInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImportFenceWin32HandleInfo);
    return pPacket;
}

typedef struct packet_vkGetFenceWin32HandleKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo;
    HANDLE* pHandle;
    VkResult result;
} packet_vkGetFenceWin32HandleKHR;

static packet_vkGetFenceWin32HandleKHR* interpret_body_as_vkGetFenceWin32HandleKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetFenceWin32HandleKHR* pPacket = (packet_vkGetFenceWin32HandleKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetWin32HandleInfo = (const VkFenceGetWin32HandleInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetWin32HandleInfo);
    pPacket->pHandle = (HANDLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pHandle);
    return pPacket;
}

typedef struct packet_vkImportFenceFdKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImportFenceFdInfoKHR* pImportFenceFdInfo;
    VkResult result;
} packet_vkImportFenceFdKHR;

static packet_vkImportFenceFdKHR* interpret_body_as_vkImportFenceFdKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkImportFenceFdKHR* pPacket = (packet_vkImportFenceFdKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pImportFenceFdInfo = (const VkImportFenceFdInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pImportFenceFdInfo);
    return pPacket;
}

typedef struct packet_vkGetFenceFdKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkFenceGetFdInfoKHR* pGetFdInfo;
    int* pFd;
    VkResult result;
} packet_vkGetFenceFdKHR;

static packet_vkGetFenceFdKHR* interpret_body_as_vkGetFenceFdKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetFenceFdKHR* pPacket = (packet_vkGetFenceFdKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pGetFdInfo = (const VkFenceGetFdInfoKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pGetFdInfo);
    if (pPacket->pGetFdInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pGetFdInfo);
    }
    pPacket->pFd = (int*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFd);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo;
    VkSurfaceCapabilities2KHR* pSurfaceCapabilities;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR;

static packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR* interpret_body_as_vkGetPhysicalDeviceSurfaceCapabilities2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR* pPacket = (packet_vkGetPhysicalDeviceSurfaceCapabilities2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSurfaceInfo = (const VkPhysicalDeviceSurfaceInfo2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceInfo);
    if (pPacket->pSurfaceInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pSurfaceInfo);
    }
    pPacket->pSurfaceCapabilities = (VkSurfaceCapabilities2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceCapabilities);
    if (pPacket->pSurfaceCapabilities != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pSurfaceCapabilities);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceFormats2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo;
    uint32_t* pSurfaceFormatCount;
    VkSurfaceFormat2KHR* pSurfaceFormats;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceFormats2KHR;

static packet_vkGetPhysicalDeviceSurfaceFormats2KHR* interpret_body_as_vkGetPhysicalDeviceSurfaceFormats2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceFormats2KHR* pPacket = (packet_vkGetPhysicalDeviceSurfaceFormats2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSurfaceInfo = (const VkPhysicalDeviceSurfaceInfo2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceInfo);
    if (pPacket->pSurfaceInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pSurfaceInfo);
    }
    pPacket->pSurfaceFormatCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceFormatCount);
    pPacket->pSurfaceFormats = (VkSurfaceFormat2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceFormats);
    if (pPacket->pSurfaceFormats != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pSurfaceFormats);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceDisplayProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkDisplayProperties2KHR* pProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceDisplayProperties2KHR;

static packet_vkGetPhysicalDeviceDisplayProperties2KHR* interpret_body_as_vkGetPhysicalDeviceDisplayProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceDisplayProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceDisplayProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayProperties2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    if (pPacket->pProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    uint32_t* pPropertyCount;
    VkDisplayPlaneProperties2KHR* pProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR;

static packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR* interpret_body_as_vkGetPhysicalDeviceDisplayPlaneProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR* pPacket = (packet_vkGetPhysicalDeviceDisplayPlaneProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayPlaneProperties2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    if (pPacket->pProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetDisplayModeProperties2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDisplayKHR display;
    uint32_t* pPropertyCount;
    VkDisplayModeProperties2KHR* pProperties;
    VkResult result;
} packet_vkGetDisplayModeProperties2KHR;

static packet_vkGetDisplayModeProperties2KHR* interpret_body_as_vkGetDisplayModeProperties2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDisplayModeProperties2KHR* pPacket = (packet_vkGetDisplayModeProperties2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPropertyCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPropertyCount);
    pPacket->pProperties = (VkDisplayModeProperties2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProperties);
    if (pPacket->pProperties != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pProperties);
    }
    return pPacket;
}

typedef struct packet_vkGetDisplayPlaneCapabilities2KHR {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo;
    VkDisplayPlaneCapabilities2KHR* pCapabilities;
    VkResult result;
} packet_vkGetDisplayPlaneCapabilities2KHR;

static packet_vkGetDisplayPlaneCapabilities2KHR* interpret_body_as_vkGetDisplayPlaneCapabilities2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetDisplayPlaneCapabilities2KHR* pPacket = (packet_vkGetDisplayPlaneCapabilities2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDisplayPlaneInfo = (const VkDisplayPlaneInfo2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplayPlaneInfo);
    pPacket->pCapabilities = (VkDisplayPlaneCapabilities2KHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCapabilities);
    return pPacket;
}

typedef struct packet_vkGetImageMemoryRequirements2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
} packet_vkGetImageMemoryRequirements2KHR;

static packet_vkGetImageMemoryRequirements2KHR* interpret_body_as_vkGetImageMemoryRequirements2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageMemoryRequirements2KHR* pPacket = (packet_vkGetImageMemoryRequirements2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkImageMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pMemoryRequirements = (VkMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetBufferMemoryRequirements2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkBufferMemoryRequirementsInfo2* pInfo;
    VkMemoryRequirements2* pMemoryRequirements;
} packet_vkGetBufferMemoryRequirements2KHR;

static packet_vkGetBufferMemoryRequirements2KHR* interpret_body_as_vkGetBufferMemoryRequirements2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetBufferMemoryRequirements2KHR* pPacket = (packet_vkGetBufferMemoryRequirements2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkBufferMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pMemoryRequirements = (VkMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkGetImageSparseMemoryRequirements2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkImageSparseMemoryRequirementsInfo2* pInfo;
    uint32_t* pSparseMemoryRequirementCount;
    VkSparseImageMemoryRequirements2* pSparseMemoryRequirements;
} packet_vkGetImageSparseMemoryRequirements2KHR;

static packet_vkGetImageSparseMemoryRequirements2KHR* interpret_body_as_vkGetImageSparseMemoryRequirements2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkGetImageSparseMemoryRequirements2KHR* pPacket = (packet_vkGetImageSparseMemoryRequirements2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfo = (const VkImageSparseMemoryRequirementsInfo2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    pPacket->pSparseMemoryRequirementCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirementCount);
    pPacket->pSparseMemoryRequirements = (VkSparseImageMemoryRequirements2*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSparseMemoryRequirements);
    return pPacket;
}

typedef struct packet_vkCreateSamplerYcbcrConversionKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkSamplerYcbcrConversionCreateInfo* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkSamplerYcbcrConversion* pYcbcrConversion;
    VkResult result;
} packet_vkCreateSamplerYcbcrConversionKHR;

static packet_vkCreateSamplerYcbcrConversionKHR* interpret_body_as_vkCreateSamplerYcbcrConversionKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateSamplerYcbcrConversionKHR* pPacket = (packet_vkCreateSamplerYcbcrConversionKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkSamplerYcbcrConversionCreateInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pYcbcrConversion = (VkSamplerYcbcrConversion*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pYcbcrConversion);
    return pPacket;
}

typedef struct packet_vkDestroySamplerYcbcrConversionKHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSamplerYcbcrConversion ycbcrConversion;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroySamplerYcbcrConversionKHR;

static packet_vkDestroySamplerYcbcrConversionKHR* interpret_body_as_vkDestroySamplerYcbcrConversionKHR(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroySamplerYcbcrConversionKHR* pPacket = (packet_vkDestroySamplerYcbcrConversionKHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkBindBufferMemory2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindBufferMemoryInfo* pBindInfos;
    VkResult result;
} packet_vkBindBufferMemory2KHR;

static packet_vkBindBufferMemory2KHR* interpret_body_as_vkBindBufferMemory2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkBindBufferMemory2KHR* pPacket = (packet_vkBindBufferMemory2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBindInfos = (const VkBindBufferMemoryInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBindInfos);
    return pPacket;
}

typedef struct packet_vkBindImageMemory2KHR {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t bindInfoCount;
    const VkBindImageMemoryInfo* pBindInfos;
    VkResult result;
} packet_vkBindImageMemory2KHR;

static packet_vkBindImageMemory2KHR* interpret_body_as_vkBindImageMemory2KHR(vktrace_trace_packet_header* pHeader) {
    packet_vkBindImageMemory2KHR* pPacket = (packet_vkBindImageMemory2KHR*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pBindInfos = (const VkBindImageMemoryInfo*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pBindInfos);
    return pPacket;
}

typedef struct packet_vkCreateDebugReportCallbackEXT {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    const VkDebugReportCallbackCreateInfoEXT* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkDebugReportCallbackEXT* pCallback;
    VkResult result;
} packet_vkCreateDebugReportCallbackEXT;

static packet_vkCreateDebugReportCallbackEXT* interpret_body_as_vkCreateDebugReportCallbackEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateDebugReportCallbackEXT* pPacket = (packet_vkCreateDebugReportCallbackEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkDebugReportCallbackCreateInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pCallback = (VkDebugReportCallbackEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCallback);
    return pPacket;
}

typedef struct packet_vkDestroyDebugReportCallbackEXT {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    VkDebugReportCallbackEXT callback;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyDebugReportCallbackEXT;

static packet_vkDestroyDebugReportCallbackEXT* interpret_body_as_vkDestroyDebugReportCallbackEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyDebugReportCallbackEXT* pPacket = (packet_vkDestroyDebugReportCallbackEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkDebugReportMessageEXT {
    vktrace_trace_packet_header* header;
    VkInstance instance;
    VkDebugReportFlagsEXT flags;
    VkDebugReportObjectTypeEXT objectType;
    uint64_t object;
    size_t location;
    int32_t messageCode;
    const char* pLayerPrefix;
    const char* pMessage;
} packet_vkDebugReportMessageEXT;

static packet_vkDebugReportMessageEXT* interpret_body_as_vkDebugReportMessageEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDebugReportMessageEXT* pPacket = (packet_vkDebugReportMessageEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pLayerPrefix = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pLayerPrefix);
    pPacket->pMessage = (const char*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMessage);
    return pPacket;
}

typedef struct packet_vkDebugMarkerSetObjectTagEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDebugMarkerObjectTagInfoEXT* pTagInfo;
    VkResult result;
} packet_vkDebugMarkerSetObjectTagEXT;

static packet_vkDebugMarkerSetObjectTagEXT* interpret_body_as_vkDebugMarkerSetObjectTagEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDebugMarkerSetObjectTagEXT* pPacket = (packet_vkDebugMarkerSetObjectTagEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pTagInfo = (const VkDebugMarkerObjectTagInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pTagInfo);
    if (pPacket->pTagInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pTagInfo);
    }
    return pPacket;
}

typedef struct packet_vkDebugMarkerSetObjectNameEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDebugMarkerObjectNameInfoEXT* pNameInfo;
    VkResult result;
} packet_vkDebugMarkerSetObjectNameEXT;

static packet_vkDebugMarkerSetObjectNameEXT* interpret_body_as_vkDebugMarkerSetObjectNameEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDebugMarkerSetObjectNameEXT* pPacket = (packet_vkDebugMarkerSetObjectNameEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pNameInfo = (const VkDebugMarkerObjectNameInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pNameInfo);
    if (pPacket->pNameInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pNameInfo);
    }
    return pPacket;
}

typedef struct packet_vkCmdDebugMarkerBeginEXT {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo;
} packet_vkCmdDebugMarkerBeginEXT;

static packet_vkCmdDebugMarkerBeginEXT* interpret_body_as_vkCmdDebugMarkerBeginEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDebugMarkerBeginEXT* pPacket = (packet_vkCmdDebugMarkerBeginEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMarkerInfo = (const VkDebugMarkerMarkerInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMarkerInfo);
    if (pPacket->pMarkerInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pMarkerInfo);
    }
    return pPacket;
}

typedef struct packet_vkCmdDebugMarkerEndEXT {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
} packet_vkCmdDebugMarkerEndEXT;

static packet_vkCmdDebugMarkerEndEXT* interpret_body_as_vkCmdDebugMarkerEndEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDebugMarkerEndEXT* pPacket = (packet_vkCmdDebugMarkerEndEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDebugMarkerInsertEXT {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkDebugMarkerMarkerInfoEXT* pMarkerInfo;
} packet_vkCmdDebugMarkerInsertEXT;

static packet_vkCmdDebugMarkerInsertEXT* interpret_body_as_vkCmdDebugMarkerInsertEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDebugMarkerInsertEXT* pPacket = (packet_vkCmdDebugMarkerInsertEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMarkerInfo = (const VkDebugMarkerMarkerInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMarkerInfo);
    if (pPacket->pMarkerInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pMarkerInfo);
    }
    return pPacket;
}

typedef struct packet_vkCmdDrawIndirectCountAMD {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkBuffer countBuffer;
    VkDeviceSize countBufferOffset;
    uint32_t maxDrawCount;
    uint32_t stride;
} packet_vkCmdDrawIndirectCountAMD;

static packet_vkCmdDrawIndirectCountAMD* interpret_body_as_vkCmdDrawIndirectCountAMD(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDrawIndirectCountAMD* pPacket = (packet_vkCmdDrawIndirectCountAMD*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkCmdDrawIndexedIndirectCountAMD {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    VkBuffer buffer;
    VkDeviceSize offset;
    VkBuffer countBuffer;
    VkDeviceSize countBufferOffset;
    uint32_t maxDrawCount;
    uint32_t stride;
} packet_vkCmdDrawIndexedIndirectCountAMD;

static packet_vkCmdDrawIndexedIndirectCountAMD* interpret_body_as_vkCmdDrawIndexedIndirectCountAMD(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdDrawIndexedIndirectCountAMD* pPacket = (packet_vkCmdDrawIndexedIndirectCountAMD*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkGetShaderInfoAMD {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkPipeline pipeline;
    VkShaderStageFlagBits shaderStage;
    VkShaderInfoTypeAMD infoType;
    size_t* pInfoSize;
    void* pInfo;
    VkResult result;
} packet_vkGetShaderInfoAMD;

static packet_vkGetShaderInfoAMD* interpret_body_as_vkGetShaderInfoAMD(vktrace_trace_packet_header* pHeader) {
    packet_vkGetShaderInfoAMD* pPacket = (packet_vkGetShaderInfoAMD*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pInfoSize = (size_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfoSize);
    pPacket->pInfo = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pInfo);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkFormat format;
    VkImageType type;
    VkImageTiling tiling;
    VkImageUsageFlags usage;
    VkImageCreateFlags flags;
    VkExternalMemoryHandleTypeFlagsNV externalHandleType;
    VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties;
    VkResult result;
} packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV;

static packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV* interpret_body_as_vkGetPhysicalDeviceExternalImageFormatPropertiesNV(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV* pPacket = (packet_vkGetPhysicalDeviceExternalImageFormatPropertiesNV*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pExternalImageFormatProperties = (VkExternalImageFormatPropertiesNV*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pExternalImageFormatProperties);
    return pPacket;
}

typedef struct packet_vkGetMemoryWin32HandleNV {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDeviceMemory memory;
    VkExternalMemoryHandleTypeFlagsNV handleType;
    HANDLE* pHandle;
    VkResult result;
} packet_vkGetMemoryWin32HandleNV;

static packet_vkGetMemoryWin32HandleNV* interpret_body_as_vkGetMemoryWin32HandleNV(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryWin32HandleNV* pPacket = (packet_vkGetMemoryWin32HandleNV*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pHandle = (HANDLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pHandle);
    return pPacket;
}

typedef struct packet_vkCmdProcessCommandsNVX {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkCmdProcessCommandsInfoNVX* pProcessCommandsInfo;
} packet_vkCmdProcessCommandsNVX;

static packet_vkCmdProcessCommandsNVX* interpret_body_as_vkCmdProcessCommandsNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdProcessCommandsNVX* pPacket = (packet_vkCmdProcessCommandsNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pProcessCommandsInfo = (const VkCmdProcessCommandsInfoNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pProcessCommandsInfo);
    return pPacket;
}

typedef struct packet_vkCmdReserveSpaceForCommandsNVX {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkCmdReserveSpaceForCommandsInfoNVX* pReserveSpaceInfo;
} packet_vkCmdReserveSpaceForCommandsNVX;

static packet_vkCmdReserveSpaceForCommandsNVX* interpret_body_as_vkCmdReserveSpaceForCommandsNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdReserveSpaceForCommandsNVX* pPacket = (packet_vkCmdReserveSpaceForCommandsNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pReserveSpaceInfo = (const VkCmdReserveSpaceForCommandsInfoNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pReserveSpaceInfo);
    if (pPacket->pReserveSpaceInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pReserveSpaceInfo);
    }
    return pPacket;
}

typedef struct packet_vkCreateIndirectCommandsLayoutNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkIndirectCommandsLayoutCreateInfoNVX* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkIndirectCommandsLayoutNVX* pIndirectCommandsLayout;
    VkResult result;
} packet_vkCreateIndirectCommandsLayoutNVX;

static packet_vkCreateIndirectCommandsLayoutNVX* interpret_body_as_vkCreateIndirectCommandsLayoutNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateIndirectCommandsLayoutNVX* pPacket = (packet_vkCreateIndirectCommandsLayoutNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkIndirectCommandsLayoutCreateInfoNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pIndirectCommandsLayout = (VkIndirectCommandsLayoutNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pIndirectCommandsLayout);
    return pPacket;
}

typedef struct packet_vkDestroyIndirectCommandsLayoutNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkIndirectCommandsLayoutNVX indirectCommandsLayout;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyIndirectCommandsLayoutNVX;

static packet_vkDestroyIndirectCommandsLayoutNVX* interpret_body_as_vkDestroyIndirectCommandsLayoutNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyIndirectCommandsLayoutNVX* pPacket = (packet_vkDestroyIndirectCommandsLayoutNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkCreateObjectTableNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkObjectTableCreateInfoNVX* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkObjectTableNVX* pObjectTable;
    VkResult result;
} packet_vkCreateObjectTableNVX;

static packet_vkCreateObjectTableNVX* interpret_body_as_vkCreateObjectTableNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateObjectTableNVX* pPacket = (packet_vkCreateObjectTableNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkObjectTableCreateInfoNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pObjectTable = (VkObjectTableNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pObjectTable);
    return pPacket;
}

typedef struct packet_vkDestroyObjectTableNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkObjectTableNVX objectTable;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyObjectTableNVX;

static packet_vkDestroyObjectTableNVX* interpret_body_as_vkDestroyObjectTableNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyObjectTableNVX* pPacket = (packet_vkDestroyObjectTableNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkRegisterObjectsNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkObjectTableNVX objectTable;
    uint32_t objectCount;
    const VkObjectTableEntryNVX* const*    ppObjectTableEntries;
    const uint32_t* pObjectIndices;
    VkResult result;
} packet_vkRegisterObjectsNVX;

static packet_vkRegisterObjectsNVX* interpret_body_as_vkRegisterObjectsNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkRegisterObjectsNVX* pPacket = (packet_vkRegisterObjectsNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->ppObjectTableEntries = (const VkObjectTableEntryNVX* const*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->ppObjectTableEntries);
    pPacket->pObjectIndices = (const uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pObjectIndices);
    return pPacket;
}

typedef struct packet_vkUnregisterObjectsNVX {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkObjectTableNVX objectTable;
    uint32_t objectCount;
    const VkObjectEntryTypeNVX* pObjectEntryTypes;
    const uint32_t* pObjectIndices;
    VkResult result;
} packet_vkUnregisterObjectsNVX;

static packet_vkUnregisterObjectsNVX* interpret_body_as_vkUnregisterObjectsNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkUnregisterObjectsNVX* pPacket = (packet_vkUnregisterObjectsNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pObjectEntryTypes = (const VkObjectEntryTypeNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pObjectEntryTypes);
    pPacket->pObjectIndices = (const uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pObjectIndices);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDeviceGeneratedCommandsFeaturesNVX* pFeatures;
    VkDeviceGeneratedCommandsLimitsNVX* pLimits;
} packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX;

static packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX* interpret_body_as_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX* pPacket = (packet_vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pFeatures = (VkDeviceGeneratedCommandsFeaturesNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFeatures);
    if (pPacket->pFeatures != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pFeatures);
    }
    pPacket->pLimits = (VkDeviceGeneratedCommandsLimitsNVX*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pLimits);
    if (pPacket->pLimits != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pLimits);
    }
    return pPacket;
}

typedef struct packet_vkCmdSetViewportWScalingNV {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t firstViewport;
    uint32_t viewportCount;
    const VkViewportWScalingNV* pViewportWScalings;
} packet_vkCmdSetViewportWScalingNV;

static packet_vkCmdSetViewportWScalingNV* interpret_body_as_vkCmdSetViewportWScalingNV(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetViewportWScalingNV* pPacket = (packet_vkCmdSetViewportWScalingNV*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pViewportWScalings = (const VkViewportWScalingNV*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pViewportWScalings);
    return pPacket;
}

typedef struct packet_vkReleaseDisplayEXT {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkDisplayKHR display;
    VkResult result;
} packet_vkReleaseDisplayEXT;

static packet_vkReleaseDisplayEXT* interpret_body_as_vkReleaseDisplayEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkReleaseDisplayEXT* pPacket = (packet_vkReleaseDisplayEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    return pPacket;
}

typedef struct packet_vkAcquireXlibDisplayEXT {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    Display* dpy;
    VkDisplayKHR display;
    VkResult result;
} packet_vkAcquireXlibDisplayEXT;

static packet_vkAcquireXlibDisplayEXT* interpret_body_as_vkAcquireXlibDisplayEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkAcquireXlibDisplayEXT* pPacket = (packet_vkAcquireXlibDisplayEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->dpy = (Display*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->dpy);
    return pPacket;
}

typedef struct packet_vkGetRandROutputDisplayEXT {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    Display* dpy;
    RROutput rrOutput;
    VkDisplayKHR* pDisplay;
    VkResult result;
} packet_vkGetRandROutputDisplayEXT;

static packet_vkGetRandROutputDisplayEXT* interpret_body_as_vkGetRandROutputDisplayEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetRandROutputDisplayEXT* pPacket = (packet_vkGetRandROutputDisplayEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->dpy = (Display*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->dpy);
    pPacket->pDisplay = (VkDisplayKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplay);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    VkSurfaceCapabilities2EXT* pSurfaceCapabilities;
    VkResult result;
} packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT;

static packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT* interpret_body_as_vkGetPhysicalDeviceSurfaceCapabilities2EXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT* pPacket = (packet_vkGetPhysicalDeviceSurfaceCapabilities2EXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSurfaceCapabilities = (VkSurfaceCapabilities2EXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSurfaceCapabilities);
    if (pPacket->pSurfaceCapabilities != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pSurfaceCapabilities);
    }
    return pPacket;
}

typedef struct packet_vkDisplayPowerControlEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDisplayKHR display;
    const VkDisplayPowerInfoEXT* pDisplayPowerInfo;
    VkResult result;
} packet_vkDisplayPowerControlEXT;

static packet_vkDisplayPowerControlEXT* interpret_body_as_vkDisplayPowerControlEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDisplayPowerControlEXT* pPacket = (packet_vkDisplayPowerControlEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDisplayPowerInfo = (const VkDisplayPowerInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplayPowerInfo);
    if (pPacket->pDisplayPowerInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pDisplayPowerInfo);
    }
    return pPacket;
}

typedef struct packet_vkRegisterDeviceEventEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkDeviceEventInfoEXT* pDeviceEventInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFence* pFence;
    VkResult result;
} packet_vkRegisterDeviceEventEXT;

static packet_vkRegisterDeviceEventEXT* interpret_body_as_vkRegisterDeviceEventEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkRegisterDeviceEventEXT* pPacket = (packet_vkRegisterDeviceEventEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDeviceEventInfo = (const VkDeviceEventInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDeviceEventInfo);
    if (pPacket->pDeviceEventInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pDeviceEventInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pFence = (VkFence*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFence);
    return pPacket;
}

typedef struct packet_vkRegisterDisplayEventEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkDisplayKHR display;
    const VkDisplayEventInfoEXT* pDisplayEventInfo;
    const VkAllocationCallbacks* pAllocator;
    VkFence* pFence;
    VkResult result;
} packet_vkRegisterDisplayEventEXT;

static packet_vkRegisterDisplayEventEXT* interpret_body_as_vkRegisterDisplayEventEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkRegisterDisplayEventEXT* pPacket = (packet_vkRegisterDisplayEventEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDisplayEventInfo = (const VkDisplayEventInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplayEventInfo);
    if (pPacket->pDisplayEventInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pDisplayEventInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pFence = (VkFence*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pFence);
    return pPacket;
}

typedef struct packet_vkGetSwapchainCounterEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    VkSurfaceCounterFlagBitsEXT counter;
    uint64_t* pCounterValue;
    VkResult result;
} packet_vkGetSwapchainCounterEXT;

static packet_vkGetSwapchainCounterEXT* interpret_body_as_vkGetSwapchainCounterEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetSwapchainCounterEXT* pPacket = (packet_vkGetSwapchainCounterEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCounterValue = (uint64_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCounterValue);
    return pPacket;
}

typedef struct packet_vkGetRefreshCycleDurationGOOGLE {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties;
    VkResult result;
} packet_vkGetRefreshCycleDurationGOOGLE;

static packet_vkGetRefreshCycleDurationGOOGLE* interpret_body_as_vkGetRefreshCycleDurationGOOGLE(vktrace_trace_packet_header* pHeader) {
    packet_vkGetRefreshCycleDurationGOOGLE* pPacket = (packet_vkGetRefreshCycleDurationGOOGLE*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDisplayTimingProperties = (VkRefreshCycleDurationGOOGLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDisplayTimingProperties);
    return pPacket;
}

typedef struct packet_vkGetPastPresentationTimingGOOGLE {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkSwapchainKHR swapchain;
    uint32_t* pPresentationTimingCount;
    VkPastPresentationTimingGOOGLE* pPresentationTimings;
    VkResult result;
} packet_vkGetPastPresentationTimingGOOGLE;

static packet_vkGetPastPresentationTimingGOOGLE* interpret_body_as_vkGetPastPresentationTimingGOOGLE(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPastPresentationTimingGOOGLE* pPacket = (packet_vkGetPastPresentationTimingGOOGLE*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pPresentationTimingCount = (uint32_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPresentationTimingCount);
    pPacket->pPresentationTimings = (VkPastPresentationTimingGOOGLE*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pPresentationTimings);
    return pPacket;
}

typedef struct packet_vkCmdSetDiscardRectangleEXT {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    uint32_t firstDiscardRectangle;
    uint32_t discardRectangleCount;
    const VkRect2D* pDiscardRectangles;
} packet_vkCmdSetDiscardRectangleEXT;

static packet_vkCmdSetDiscardRectangleEXT* interpret_body_as_vkCmdSetDiscardRectangleEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetDiscardRectangleEXT* pPacket = (packet_vkCmdSetDiscardRectangleEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDiscardRectangles = (const VkRect2D*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDiscardRectangles);
    return pPacket;
}

typedef struct packet_vkSetHdrMetadataEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    uint32_t swapchainCount;
    const VkSwapchainKHR* pSwapchains;
    const VkHdrMetadataEXT* pMetadata;
} packet_vkSetHdrMetadataEXT;

static packet_vkSetHdrMetadataEXT* interpret_body_as_vkSetHdrMetadataEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkSetHdrMetadataEXT* pPacket = (packet_vkSetHdrMetadataEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSwapchains = (const VkSwapchainKHR*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSwapchains);
    pPacket->pMetadata = (const VkHdrMetadataEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMetadata);
    if (pPacket->pMetadata != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pMetadata);
    }
    return pPacket;
}

typedef struct packet_vkCmdSetSampleLocationsEXT {
    vktrace_trace_packet_header* header;
    VkCommandBuffer commandBuffer;
    const VkSampleLocationsInfoEXT* pSampleLocationsInfo;
} packet_vkCmdSetSampleLocationsEXT;

static packet_vkCmdSetSampleLocationsEXT* interpret_body_as_vkCmdSetSampleLocationsEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCmdSetSampleLocationsEXT* pPacket = (packet_vkCmdSetSampleLocationsEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSampleLocationsInfo = (const VkSampleLocationsInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSampleLocationsInfo);
    return pPacket;
}

typedef struct packet_vkGetPhysicalDeviceMultisamplePropertiesEXT {
    vktrace_trace_packet_header* header;
    VkPhysicalDevice physicalDevice;
    VkSampleCountFlagBits samples;
    VkMultisamplePropertiesEXT* pMultisampleProperties;
} packet_vkGetPhysicalDeviceMultisamplePropertiesEXT;

static packet_vkGetPhysicalDeviceMultisamplePropertiesEXT* interpret_body_as_vkGetPhysicalDeviceMultisamplePropertiesEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetPhysicalDeviceMultisamplePropertiesEXT* pPacket = (packet_vkGetPhysicalDeviceMultisamplePropertiesEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pMultisampleProperties = (VkMultisamplePropertiesEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMultisampleProperties);
    return pPacket;
}

typedef struct packet_vkCreateValidationCacheEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    const VkValidationCacheCreateInfoEXT* pCreateInfo;
    const VkAllocationCallbacks* pAllocator;
    VkValidationCacheEXT* pValidationCache;
    VkResult result;
} packet_vkCreateValidationCacheEXT;

static packet_vkCreateValidationCacheEXT* interpret_body_as_vkCreateValidationCacheEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkCreateValidationCacheEXT* pPacket = (packet_vkCreateValidationCacheEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pCreateInfo = (const VkValidationCacheCreateInfoEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pCreateInfo);
    if (pPacket->pCreateInfo != NULL) {
        vktrace_interpret_pnext_pointers(pHeader, (void *)pPacket->pCreateInfo);
    }
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    pPacket->pValidationCache = (VkValidationCacheEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pValidationCache);
    return pPacket;
}

typedef struct packet_vkDestroyValidationCacheEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkValidationCacheEXT validationCache;
    const VkAllocationCallbacks* pAllocator;
} packet_vkDestroyValidationCacheEXT;

static packet_vkDestroyValidationCacheEXT* interpret_body_as_vkDestroyValidationCacheEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkDestroyValidationCacheEXT* pPacket = (packet_vkDestroyValidationCacheEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pAllocator = (const VkAllocationCallbacks*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pAllocator);
    return pPacket;
}

typedef struct packet_vkMergeValidationCachesEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkValidationCacheEXT dstCache;
    uint32_t srcCacheCount;
    const VkValidationCacheEXT* pSrcCaches;
    VkResult result;
} packet_vkMergeValidationCachesEXT;

static packet_vkMergeValidationCachesEXT* interpret_body_as_vkMergeValidationCachesEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkMergeValidationCachesEXT* pPacket = (packet_vkMergeValidationCachesEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pSrcCaches = (const VkValidationCacheEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pSrcCaches);
    return pPacket;
}

typedef struct packet_vkGetValidationCacheDataEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkValidationCacheEXT validationCache;
    size_t* pDataSize;
    void* pData;
    VkResult result;
} packet_vkGetValidationCacheDataEXT;

static packet_vkGetValidationCacheDataEXT* interpret_body_as_vkGetValidationCacheDataEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetValidationCacheDataEXT* pPacket = (packet_vkGetValidationCacheDataEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pDataSize = (size_t*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pDataSize);
    pPacket->pData = (void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pData);
    return pPacket;
}

typedef struct packet_vkGetMemoryHostPointerPropertiesEXT {
    vktrace_trace_packet_header* header;
    VkDevice device;
    VkExternalMemoryHandleTypeFlagBits handleType;
    const void* pHostPointer;
    VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties;
    VkResult result;
} packet_vkGetMemoryHostPointerPropertiesEXT;

static packet_vkGetMemoryHostPointerPropertiesEXT* interpret_body_as_vkGetMemoryHostPointerPropertiesEXT(vktrace_trace_packet_header* pHeader) {
    packet_vkGetMemoryHostPointerPropertiesEXT* pPacket = (packet_vkGetMemoryHostPointerPropertiesEXT*)pHeader->pBody;
    pPacket->header = pHeader;
    pPacket->pHostPointer = (const void*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pHostPointer);
    pPacket->pMemoryHostPointerProperties = (VkMemoryHostPointerPropertiesEXT*)vktrace_trace_packet_interpret_buffer_pointer(pHeader, (intptr_t)pPacket->pMemoryHostPointerProperties);
    return pPacket;
}

