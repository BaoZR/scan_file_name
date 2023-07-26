适用环境windows GBK编码格式。
这个软件用来扫描当前目录下的所有文件，打印到屏幕上，并写入到CSV中,核心是c++17的std::filesystem
1. 实现了UTF8 EVERYWHERE
2. 实现了iconv的导入，文件名写入到CSV时还应该是GBK格式的。
3. 实现了颜色打印 
