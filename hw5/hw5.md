# <center> 作业5 

##### <center>刘喆骐     2020013163    探微化01


###8.4-4

使用bucket sort, 目标复杂度为 $Θ(n)$, 需将圆分为 n 份, 使得每个数出现在每一部分的概率均为$\frac 1n$。故bucket[i]中的点p应该满足$\sqrt \frac{i-1}n\leq \sqrt {p_x^2+p_y^2} \leq \sqrt \frac in$，也就是$\frac{i-1}n\leq  {p_x^2+p_y^2} \leq  \frac in$，对应的面积为$\frac 1n$的圆面积。
伪代码如下：
设a为待排数组。
$
n=a.length\\    
 for \quad i=1:n\\
\qquad    insert\quad a[i] \quad to \quad b[n\sqrt {a[i].x^{2}+a[i].y^2}]\\
for \quad i=0:n-1\\
\qquad    sort\quad b[i]\quad with\quad insertion\quad sort\\
concatenate\quad b[0], b[1], ... ,b[n-1]
$

### 9.3-6
所求的顺序统计量为$\frac nk, \frac{2n}k,...,\frac {(k-1)n}{k}$。算法设计如下:
(1)找到第$\frac {k-1}2$个统计量
(2)对于上述统计量分成的前后两个数组，执行上述操作(1)
伪代码如下，其中select(A[n],k)为linear selection，可在线性时间内找到A中第k大的元素。
```
function select_k(A[1~n],k)
    if k==0 return
    num_k=select(A[k],(k-1)n/2k)
    l=select_k(A[0~num_k-1],k/2)
    r=select_k(A[num_k+1~n],k/2)
```
时间复杂度为<center>
$T(k)=2T(k/2)+O(n)$</center>
故时间复杂度为$O(nlogk)$。