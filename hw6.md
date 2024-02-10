# <center>Homework6

##### <center>刘喆骐     2020013163    探微化01

## 15.1-3
```
BOTTOM-UP-CUT(p,n)
let r[0,...,n] be a new array
r[0]=0
for j=1 to n:
    q=-inf
    for i=1 to j
        q=max(q,p[i]-c+r[j-i])
    r[j]=q
return r[n]
```
##15.3-4
例如对于矩阵链$A_1A_2A_3$,矩阵规模为4×3，3×2，2×1。对于此种贪心算法，其会寻找$p_{i-1}p_kp_j$最小的k，此例中会取k=2，需要的运算次数为4×3×2+4×2×1=32次。而最优的算法是k取1，所需的运算次数为3×2×1+4×3×1=18。故贪心可能会得到次优解。
