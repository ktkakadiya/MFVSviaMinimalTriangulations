import matplotlib.pyplot as plt
import matplotlib
import numpy as np

font = {'size' : 16 }
matplotlib.rc('font', **font)

plt.figure(figsize=[15, 10])
x = ["complete", "cycle", "path", "random", "random tree", "star"]

pos = np.arange(6)
ms = np.array([181, 1911, 241, 365, 362, 383]) # Minimal separator
fb = np.array([2, 2488, 397, 158, 534, 165]) # Full blocks
pmc = np.array([1656, 16457, 3511, 9495, 5682, 1437]) # Potential maximal cliques
gt = np.array([14, 4392, 886, 631, 919,1085]) # Good triples
  
# plot bars in stack manner
plt.bar(x, ms, color='r')
plt.bar(x, fb, bottom=ms, color='b')
plt.bar(x, pmc, bottom=ms+fb, color='y')
plt.bar(x, gt, bottom=ms+fb+pmc, color='g')
plt.xlabel("Graph types")
plt.ylabel("Running time (micro seconds)")
plt.legend(["Minimal Separators", "Full blocks", "PMC", "Good triple"])
plt.savefig('bar1.png')