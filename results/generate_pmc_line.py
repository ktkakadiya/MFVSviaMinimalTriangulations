import matplotlib.pyplot as plt
import numpy as np

# create data
x = [5,10,15,20,25,30,35,40,45,50]
new = [283,1946,4241,9215,13970,20173,46023,60962,71820,104387]
old = [314,3205,19057,43187,81503,161482,232301,402377,612172,1218107]

# plot lines
plt.plot(x, np.log(new)/np.log(1.734601), label = "New method")
plt.plot(x, np.log(old)/np.log(1.734601), label = "Old method")
plt.xlabel("Nodes")
plt.ylabel("Running time (log(time in μs) base 1.734601)")
plt.legend()
plt.title("Cardinality vs. Time for generating PMC in random tree")
plt.savefig('line_pmc_1.png')