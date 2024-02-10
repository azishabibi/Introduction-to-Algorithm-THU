Homework_3.exe为可执行文件，Homework_3_boxed.exe是使用enigma virtual box打包形成的可执行文件，不依赖dll文件，两者效果相同。如果Homework_3.exe无法执行，请将mingw加入环境变量，并把QT下的\5.9.9\mingw53_32\bin,\Tools\mingw530_32\bin加入环境变量。

打开exe文件，点击左边的框加入点，然后点击ExeMouse运行，会显示最短距离的点和两点连线，右边则会输出时间，距离和坐标。

输入点的数量，然后点击execute，在右下方就会生成两种方法的耗时和最短距离和两个点的坐标。

当n>10000后则不会显示暴力法的时间。

点击remove清除平面上的点。

鼠标点击和随机生成的点是独立的，不会一起计算。