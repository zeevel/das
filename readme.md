
# Module DAS(Dynamic Adaptive Streaming)

libdash是ISO/IEC MPEG-DASH标准的官方参考软件，是一个开源库，提供了一个面向对象(OO)接口的MPEG-DASH标准，由bitmovin开发。

# Installing Procedure

## Pre-Requesits

```
sudo apt-get install build-essential gccxml
sudo apt-get install git-core build-essential cmake libxml2-dev libcurl4-openssl-dev
sudo apt-get install cmake libxml2-dev libcurl4-openssl-dev
sudo apt-get install libxml2-dev libxslt-dev python-dev lib32z1-dev
```

其中，`libdash`的代码直接依赖2个library，分别是

- `libcurl`
- `libxml2`

## `libcurl`的安装部署

1. `sudo apt-get install libcurl4-openssl-dev`
2. 检查头文件
   ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/include/x86_64-linux-gnu/ | grep curl
    curl
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/include/x86_64-linux-gnu/curl/ 
    curl.h  curlver.h  easy.h  mprintf.h  multi.h  stdcheaders.h  system.h  typecheck-gcc.h
   ```
3. 检查库文件
   ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/lib/x86_64-linux-gnu/ | grep curl
    libcurl.a
    libcurl-gnutls.so.3
    libcurl-gnutls.so.4
    libcurl-gnutls.so.4.5.0
    libcurl.la
    libcurl.so
    libcurl.so.4
    libcurl.so.4.5.0
    zeevel@zeevel-virtual-machine:~/tkj/multi$
   ```
4. 检查库文件(该文件指明了该library的名称和include路径等)
   ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/lib/x86_64-linux-gnu/pkgconfig/ | grep curl
    libcurl.pc
    zeevel@zeevel-virtual-machine:~/tkj/multi$
   ```

对libcurl的安装执行以上的检查步骤，一般不需要额外配置就能顺利装上，libdash的代码也能顺利依赖curl

## `libxml2`的安装部署

1. `sudo apt-get install libxml2`
2. `sudo apt-get install libxml2-dev`
3. 检查头文件
   ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/include/ | grep xml
    libxml2
    zeevel@zeevel-virtual-machine:~/tkj/multi$
   ```
4. 检查库文件
   ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/lib/x86_64-linux-gnu/ | grep xml
    libxml2.a
    libxml2.so
    libxml2.so.2
    libxml2.so.2.9.4
    libxmlb.so.1
    libxmlb.so.1.0.0
    libxmlsec1-nss.so.1
    libxmlsec1-nss.so.1.2.25
    libxmlsec1.so.1
    libxmlsec1.so.1.2.25
    xml2Conf.sh
   ```
5. 检查库文件(该文件指明了该library的名称和include路径等)
   ```
    ls /usr/lib/x86_64-linux-gnu/pkgconfig/ | grep xml
    libxml-2.0.pc
   ```

以上是apt安装libxml2后的相关默认配置，为了让libdash的代码能顺利依赖到libxml2,需做以下额外配置

- 将libxml2的配置文件重命名并复制到另一个位置
  ```
    cp /usr/lib/x86_64-linux-gnu/pkgconfig/libxml-2.0.pc /usr/lib/pkgconfig/
    mv /usr/lib/pkgconfig/libxml-2.0.pc /usr/lib/pkgconfig/libXML.pc
  ```
  做以下检查
  ```
    zeevel@zeevel-virtual-machine:~/tkj/multi$ ls /usr/lib/pkgconfig/ | grep XML
    libXML.pc
  ```

- 将libxml2的头文件目录移至上一层
  ```
    sudo cp -r /usr/include/libxml2/libxml/ /usr/include/
  ```
  做以下检查
  ```
    ls /usr/include/ | grep xml
    libxml
    libxml2
  ```

  ## Install `das` module in ns3
  
  经过以上步骤，即可正常安装`das` module
  ```
    cp -r das ?/ns-3/src
    sudo chmod -R 777 ?/ns-3
    cd ?/ns-3
    ./waf configure --enable-examples --python=/usr/bin/python3.6
    ./waf
  ```

需注意的是，以上示例步骤中的路径可能会根据不同ubuntu版本发生改变
