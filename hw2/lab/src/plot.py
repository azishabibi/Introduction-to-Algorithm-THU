import matplotlib.pyplot as plt
x=[1,10,20,30,35,40,41,42,43,44,45]
y = [0,0.5,62,3859.1,48622.1,483902,794447,1.28069e+06,2.08149e+06,3.35353e+06,5.49404e+06]
plt.plot(x,y)
plt.xlabel("n")
plt.ylabel("time/μs")
plt.show()