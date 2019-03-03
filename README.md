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

最初这个固件是Jim为BLE4100设计的，关于BLE4100可以参见[这个页面](https://wiki.lotlab.org/page/ble4100/advanced/)

后续Jim加入了tmk的支持，并首先加入了基于GH60的60%键盘：Lot60-BLE

后面个人采用E73-2G4M04S1D这个蓝牙模块重新设计了个人的60%键盘：GT-BLE60 (注：此分支不再适合Lot60-BLE)

硬件部分采用NRF51822作为键盘主控、蓝牙模块。CH552T（或CH554T）通过UART和NRF51822通讯，实现USB模块。详细硬件列表可以参看BOM清单

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

-  **开机按键：SPACE+U** - 每次自动休眠或手动休眠后按任意键唤醒键盘，同时按下SPACE+U方可开机；开启Debug不需要按此按键，可按任意键唤醒键盘并直接开机。
  
-  **清空蓝牙绑定信息按键：SPACE+E** - 每次休眠后唤醒同时按SPACE+E可以清空蓝牙绑定信息。
  
-  **切换连接模式按键：Fn2+TAB** - 在通过USB和蓝牙同时连接一台设备（也可通过USB连接一台设备、蓝牙连接另一台设备）的情况下，按Fn2+TAB可以切换连接模式。如未同时使用USB模式和蓝牙模式，此按键无效。*注:GT-BLE60默认将APP/MENU键设定为Fn2键,可通过配例自由设定更改*
  
-  **休眠按键：Fn2+ESC** - 按Fn2+ESC键可以直接进入休眠模式，按任意键可以唤醒。开启Debug无法通过此按键进行休眠，只能自动休眠。Seclink版本唤醒键盘必须同时按下Space+U方可开机。

-  **清空Keymap自定义配例：SPACE+BACKSPACE** -  每次休眠后唤醒同时按SPACE+BACKSPACE可以清空自定义配例信息。如果出现按键错乱，也可以采用此键恢复初识配例。其余BOOTMAGIC键参考TMK，是基本一样的。
  
-  **关于耗电** - 由于硬件上采用的低功耗蓝牙芯片，功耗控制的相当的好。以200mah的小容量锂电池计算，每天2小时使用时间，其余时间自动休眠，保守估计使用时间长达一个月以上（个人暂时没有长时间实测，但是应该只会更好）。 
  
-  **相关参数的设定** - 考虑到耗电问题，正常键盘扫描按键输入为10ms一次，回报率为100Mhz;如果两分钟不按键转入慢速扫描，100ms一次，当有按键按下，又自动转入正常扫描速度10ms一次；如果30分钟无按键行为将自动转入休眠模式，此时要重新启用键盘，Debug版本只需要按任意键就可唤醒（唤醒动作后约1-2s可以正常输入），Seclink版本需要按Space+U方可唤醒。
  

更多内容可以参看[这个页面](http://genokolar.github.io/blog/201903)