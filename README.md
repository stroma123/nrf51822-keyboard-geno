# nrf51822-keyboard

## 概述

这是一个基于nrf51822蓝牙键盘的固件，使用了nRF SDK 10.0作为底层硬件驱动，并使用TMK键盘库作为键盘功能的上部实现。

## 软件

目录说明：

- bootloader：用于DFU更新固件的Bootloader
- main：键盘主程序
- sdk：nRF SDK 10.0 里用到的源码文件
- tmk：TMK源码
- usb：双模的USB部分固件
- KeymapDownloader：配列下载器源码
- hex：预编译的固件hex文件

## 硬件

最初这个固件是[Jim](https://www.lotlab.org/)为BLE4100设计的，关于BLE4100可以参见[这个页面](https://wiki.lotlab.org/page/ble4100/advanced/)

后续Jim加入了tmk的支持，并首先加入了基于GH60的60%键盘：Lot60-BLE

后面个人采用E73-2G4M04S1D与RF-BM-ND01这个蓝牙模块重新设计了个人的60%键盘：GT-BLE60 (注：此分支不再适合Lot60-BLE)

硬件部分采用NRF51822作为键盘主控、蓝牙模块。CH552T（或CH554T）通过UART和NRF51822通讯，实现USB模块。整个BOM清单详见[表格](https://github.com/genokolar/GT_BLE60_Keyboard_PCB/blob/master/rev.d/keyboard_BOM.csv)(以60%键盘为例，部分元件需要根据轴的个数确定数量） 

<img alt="Keyboard图片" src="https://notes.glab.online/img/keyboard.jpg" width="60%" />

## 编译

1. 键盘固件编译  

   安装keil，并打开`main/project/arm5_no_packs/`目录下的keil工程，编译键盘固件；

   安装keil，并打开`bootloader/project/arm5_no_packs/`目录下的keil工程，编译DFU升级Bootloader固件；
   
2. USB模块固件编译  

   安装Code Blocks，SDCC，并打开`usb/project/CH554.cbp`工程文件，编译USB模块固件
   
## 烧录

1. 键盘固件需要Jlink通过SWD接口（PCB有预留）烧入，后续烧录可通过烧入的Bootloader程序DFU升级

2. USB模块固件可用PC程序WCHISPTool直接通过USB连接烧入

## 键盘使用说明  

-  **休眠按键：Fn2+ESC** - 15分钟不按键自动休眠，自动休眠后可按任意键唤醒；按Fn2+ESC键可以手动进入休眠模式，手动休眠后只能按ESC键（_第一个按钮_）才可以唤醒。
- *注:GT-BLE60默认将APP/MENU键设定为Fn2键,可通过配例自由设定更改*

-  **关机按钮：Fn2+Backspace** - 按Fn2+Backspace键可以手动进入关机模式，关机后需要按背部的Bootloader按钮才可重新开机。
  
-  **清空蓝牙绑定信息按键：SPACE+E** - 每次唤醒或开机同时立即按SPACE+E可以清空蓝牙绑定信息。
  
-  **切换连接模式按键：Fn2+TAB** - 在通过USB和蓝牙同时连接一台设备（也可通过USB连接一台设备、蓝牙连接另一台设备）的情况下，按Fn2+TAB可以切换连接模式。如未同时使用USB模式和蓝牙模式，此按键无效。

-  **清空Keymap自定义配例：SPACE+BACKSPACE** -  每次唤醒或开机同时按SPACE+BACKSPACE可以清空自定义配例信息。如果出现按键错乱，也可以采用此键恢复初始配例。其余BOOTMAGIC键参考TMK，是基本一样的。

- **切换默认层** - 每次唤醒或开机通过同时按住SPACE+0、SPACE+1，切换第0层或第1层为默认层。默认配列中第0层启用了二合一按键作为方向键，第1层中未启用二合一方向键，启用了二合一按键作为Menu键。详细参看源码配例文件。此默认层设定将存储，重启或者休眠后唤醒都会恢复你设置的默认层。

- **切换临时默认层** - 通过同时按住Lshift+Rshift不放，按0、1，切第0层或第1层为默认层。此临时默认层不做记录，重启或者休眠后唤醒都会恢复第0层为默认层。   
  
-  **关于耗电** - 由于硬件上采用的低功耗蓝牙芯片，功耗控制的相当的好。官方数据来看，使用时耗电每小时为10ma左右，休眠时耗电为5ua。从自己使用感受看，1000mah的锂电池，每天2小时使用时间，大体使用时间80天以上。如果自己调整源码的相关省电参数，功耗还可以继续降低。 

-  **关于蓝牙通讯** - 蓝牙通讯上，延迟基本不存在，通过KeyboardTest测试出来的延迟，蓝牙模式下单按大约是120ms，双按键大概是2ms，USB模式下单按键大约是135ms，双按键大约是2ms（个人认为这个测试数据仅供参考，并不一定科学，因为居然比AKKO 3108的数据还好 ））。由于是低功耗，实测有效使用距离是5米内。耗电也和蓝牙信号有关，信号越好，耗电越低。
  
-  **相关参数的设定** - 考虑到耗电问题，正常键盘扫描按键输入为4ms一次，回报率为250Mhz;如果两分钟不按键转入慢速扫描，100ms一次，当有按键按下，又自动转入正常扫描速度4ms一次；如果15分钟无按键行为将自动转入休眠模式，此时要重新启用键盘，只需要按任意键就可唤醒，唤醒动作后约1-2s可以正常输入。

- **默认按键设定**
- 默认按键共有4层，1、2层是不同的全局按键设定，3、4层是功能按键设定。[查看默认按键设定](https://notes.glab.online/#/posts/9)。

- **自定义按键**

- 自定义按键采用Tkg网页+配例下载工具的方式实现：通过网站（因为tkg.io官网没支持，我自己建立了一个：[kb.glab.online](http://kb.glab.online)）配置好按键，然后下载keymap.eep文件，通过专门的刷配例软件[KeymapDownloader.exe](https://github.com/genokolar/nrf51822-keyboard/releases/download/20190416/KeymapDownloader.exe)刷入蓝牙芯片。如下图

<img alt="TKG图片" src="/img/TKG.png" width="60%" style="vertical-align:middle;display:table; text-align:center"/>

<img alt="配例下载" src="/img/keymapdownload.png" width="60%" style="vertical-align:middle;display:table; text-align:center"/>

- **DFU空中升级**

- 除了初次烧录固件需要jlink外，后续升级固件可以通过手机蓝牙连接键盘，通过DFU模式更新固件。 [点击查看详细升级方法](https://notes.glab.online/#/posts/7)

## PCB电路

- [https://github.com/genokolar/GT_BLE60_Keyboard_PCB](https://github.com/genokolar/GT_BLE60_Keyboard_PCB)  注:可以直接打板使用。

更多内容可以参看[这里](https://notes.glab.online)
