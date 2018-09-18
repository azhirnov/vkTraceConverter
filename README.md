# vkTraceConverter
Work in progress.<br/>
<br/>
On input takes vktrace file.<br/>
On output can produce:
* C++ code with raw Vulkan API calls. (partialy done)
* trace for [Vulkan-EZ](https://github.com/GPUOpen-LibrariesAndSDKs/V-EZ) (somewhen)
* trace for OpenGL 4.6 API calls. (somewhen)
* trace for [FrameGraph API](https://github.com/azhirnov/FrameGraph) calls. (WIP)
* [graphviz](https://www.graphviz.org/) dot file. (WIP)

## Building
Generate project with CMake and build.<br/>
Required C++17 standard support.<br/>
All required dependencies will be downloaded at build time, as cmake external project.

Dependencies:<br/>
[Vulkan-Headers](https://github.com/KhronosGroup/Vulkan-Headers) - required for vktrace.<br/>
[Vulkan-Loader](https://github.com/KhronosGroup/Vulkan-Loader) - required for vktrace.<br/>
[glslang](https://github.com/KhronosGroup/glslang.git) - required for Vulkan-ValidationLayers.<br/>
[Vulkan-ValidationLayers](https://github.com/KhronosGroup/Vulkan-ValidationLayers) - required for vktrace.<br/>
[Vulkan-Tools](https://github.com/KhronosGroup/Vulkan-Tools) - required for vktrace.<br/>
[LunarG VulkanTools](https://github.com/LunarG/VulkanTools) - required, only for vktrace headers.<br/>
[FrameGraph](https://github.com/azhirnov/FrameGraph) - only VulkanLoader and Framework projects are required + their dependencies.<br/>
