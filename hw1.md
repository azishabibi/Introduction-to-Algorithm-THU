# <center>Homework1
##### <center>刘喆骐     2020013163    探微化01
## T1
###### a.
即证明$2n=O(n^2)$。由于存在$n_0=1,c=4$,使得对于任意$n>n_0$，有$2n<4n^2$,故$2n=O(n^2)$，原式得证。
###### b.
取$f(n)=\Theta(g(n))$，由定义有存在$n_0,c$，使得对于任意$n>n_0,f(n)\geq cg(n)$,这和$f(n)=o(g(n))$矛盾，故原命题得证。
###### c.
只需要寻找到一个例子即可。
例如取$f(n)=cos(x)+1,g(n)=1$，则有$f(n)\leq 2×1=2g(n)$,故$g(n)=O(f(n))$。
显然，对于f(n)而言，无法找到正数$n_0,c$，使得$f(n)\geq c×g(n)=c$，因为 $f(n)$ 值域为[-1,1]，故g(n)不属于$\Theta(f(n))$。
又由于对于任意的c>0,无法找到$n_0$使得对于任意$n>n_0$，有$f(n)<c×g(n)$，故g(n)不属于$o(g(n))$。
故存在g(n)属于$O(g(n))$，而不属于$\Theta(f(n))$和$o(g(n))$。得证。
###### d.
不妨假设当$n>n_0$时，有$f(n)>g(n)$.那么当$n>n_0$时，$max(f(n),g(n))>0.1(f(n)+g(n))$
显然也有$max(f(n),g(n))<2(f(n)+g(n))$
故存在$c_1=0.1,c_2=2,n_0$，使得对任意$n>n_0,c_1×(f(n)+g(n))<max(f(n),g(n))<c_2×(f(n)+g(n))$
故$max(f(n),g(n))=\Theta(f(n)+g(n))$

## T3-2

$$
\begin{array}
{cll}
\hline
A& B & O & o &\Omega &\omega &\Theta\\
\hline
 lg^kn & n^\epsilon &T&T&F&F&F \\
 n^k & c^n  &T&T&F&F&F \\
 \sqrt n & n^{sinn} &F&F&F&F&F  \\
 2^n & 2^{n\over 2} &F&F&T&T&F  \\
 n^{lgc}&c^{lgn}&T&F&T&F&T\\
 lg(n!)&lg(n^n)&T&F&T&F&T\\
\hline
\end{array}
$$
## T3-3
1. 顺序：从小到大
1，$n^\frac1{lg(n)}$
$lg(lg^*(n))$
$lg^*(lg(n))$
$lg^*(n)$
$2^{lg^*n}$
$ln(ln(n))$
$\sqrt{lg(n)}$
$ln(n)$
$(lgn)^2$
$2^{\sqrt{2lgn}}$
${\sqrt2}^{lgn}$
$n,2^{lgn}$
$nlgn,log(n!)$
$n^2,4^{lgn}$
$n^3$
$n^{lglgn},lg(n)！$
$lgn^{lgn}$
$1.5^n$
$2^n$
$e^n$
$n*2^n$
$n!$
$(n+1)!$
$2^{2^n}$
$2^{2^{n+1}}$

2. $f(n)=4^{4^n}+cos(n\pi/2)4^{4^n}$，n为正整数。
