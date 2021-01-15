# macos-alert

一个用于在shell脚本中显示alert弹窗的工具，支持MacOS。

# 用法

```shell
./macos-alert <<EOF
title = Test
message = Hello world!
subMessage = Have fun playing with macos-alert
icon = icon.png
buttons = Yes, No
needRet = true
EOF
```

更多细节，参考help文档 `./macos-alert --help`

# 构建

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

# 二进制文件

点击 [bin/macos-alert](bin/macos-alert) 下载
