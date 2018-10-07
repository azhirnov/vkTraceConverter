# Console commands examples

## Convert without modifications
```
--convert    vk-trace
--open       parallaxmapping.vktrace
--output-dir converted
```
In the "converted/vk-trace" folder there are 2 files: 'main.cpp' and 'CMakeLists.txt'.
To run player you need VTPlayer shared library (.dll or .so) and original vktrace file, becouse large data is not copied to new trace.
Warning: you can not run this trace on other GPU then used for vktrace recording, you can not resize the window.


## Convert with memory remapping and indirect swapchain
```
--convert       vk-trace
--cfg-vk-trace  indirect-swapchain=true  remap-mem=true
--open          parallaxmapping.vktrace
--output-dir    converted
```
Now you can resize window, becouse frame rendered to intermediate image and then blitted to swapchain image.
Also you can run player on any GPU, becouse memory allocation overrided.
(queue remapping for full portability is in progress, but for both application there is not needed)


## Convert to C++ source code
```
--convert       vk-cpp
--cfg-vk-cpp    begin=0  end=10
--open          parallaxmapping.vktrace
--output-dir    converted
```
You can inpect some frames or convert full trace (by removing 'begin' and 'end' commands) and get fully editable application source code, but usualy there is a megabytes of code and compilation may take a lot of time.


## Convert to C++ source code with dividing by threads
```
--convert       vk-cpp
--cfg-vk-cpp    begin=0  end=10  divide-by-threads
--open          parallaxmapping.vktrace
--output-dir    converted
```
Same as above, but vulkan api calls grouped by thread.
Warning: threre is incorrect execution order, so application may not work correctly.


## Convert to synchronization graph and visualize
```
--convert       graphviz
--cfg-graphviz  begin=0  end=3  show-sync=true
--open          parallaxmapping.vktrace
--output-dir    converted
```

