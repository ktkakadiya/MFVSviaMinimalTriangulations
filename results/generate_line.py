import matplotlib.pyplot as plt
import numpy as np
import math

# create data
x = [5,10,15,20,25,30,35,40,45,50]
com = [214,676,1869,3993,7195,13090,23276,33723,71797,76477]
cyc = [569,6388,31347,76005,155168,329775,521410,922833,1789904,2182895]
pat = [495,1947,4895,13056,17444,26199,39771,61667,85321,103338]
int = [182,2797,13395,48731,135784,218096,221631,1037499,2578165,2345008]
tre = [471,2436,5528,11551,17198,23586,50136,67209,83592,114446]
str = [422,690,1193,1869,3466,3605,4875,6270,7466,8998]
  
# plot lines
plt.plot(x, np.log(com)/np.log(1.734601), label = "Complete")
plt.plot(x, np.log(cyc)/np.log(1.734601), label = "Cycle")
plt.plot(x, np.log(pat)/np.log(1.734601), label = "Path")
plt.plot(x, np.log(int)/np.log(1.734601), label = "Random internet")
plt.plot(x, np.log(tre)/np.log(1.734601), label = "Random tree")
plt.plot(x, np.log(str)/np.log(1.734601), label = "Star")
plt.xlabel("Nodes")
plt.ylabel("Running time (log(time in μs) base 1.734601)")
plt.legend()
plt.title("Cardinality vs. Time")
plt.savefig('line1.png')
