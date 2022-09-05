# TinySTL

## ToDo

* [ ] 完善基本数据结构
* [ ] 补充一些算法
* [ ] 尝试配合自己的allocator

## algorithm

这个部分实现了一些算法，会借助原生的STL库容器

## containers

实现容器，是不会使用原生STL库的

## 动态库说明

mac上的动态库是以 `.dylib`结尾，linux上的动态库以 `so`结尾

### window

window 暂时还不熟悉这个平台，可以使用mingw去编译

或者安装WSL，切换到linux环境下，就非常简单了

### linux

linux上只需要

> epxort LD_LIBRARY_PATH=xxxx:${LD_LIBRARY}

或者干脆执行前 加上临时ldpath即可

### mac

mac上我们首先使用

```
otool -L [执行文件]
```

查看这个执行文件所需要的库路径

得到类似如下的结果

> @rpath/libalgo.dylib (compatibility version 0.0.0, current version 0.0.0)
> @rpath/libdata_struct.dylib (compatibility version 0.0.0, current version 0.0.0)
> /usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 1200.3.0)
> /usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1311.0.0)

需要注意的就是这里的 **@rpath**
而我们可以通过install_name_tool来对这些地址进行操作

```
install_name_tool -add_rpath [未被搜索到的需要的动态库路径] [执行文件]
```
