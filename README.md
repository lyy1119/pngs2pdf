# pngs2pdf

***
将以页码顺序命名的png文件转换为一个pdf  
## 使用

将二进制可执行文件与**以页码顺序数字命名的png文件**放在同一目录下，然后直接执行这个二进制文件即可。  

### 下载release的二进制文件

从最新的release下载二进制文件即可，目前只提供64位Windows平台。  

### 从源码编译

先安装libharu库、g++和make，可参见我的[Wiki](https://lyy1119.github.io/%E7%BC%96%E7%A8%8B/C%2B%2B/libharu%E5%BA%93%E7%9A%84%E7%BC%96%E8%AF%91/)或者自行搜索编译教程。我使用的编译平台是Windows下的mingw64。  

安装好编译环境后，运行以下命令  
```bash
make
```
