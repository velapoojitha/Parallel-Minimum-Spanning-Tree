# plot_mst_comparison.py
import matplotlib.pyplot as plt

# Example data (replace with your actual timings)
nodes = [100, 200, 300, 400, 500, 600, 700]
sequential_times = [0.5, 1.2, 2.4, 4.1, 6.8, 9.3, 13.5]
parallel_times = [0.3, 0.7, 1.1, 1.8, 2.9, 4.1, 6.0]

plt.figure(figsize=(10, 6))
plt.plot(nodes, sequential_times, marker='o', label='Sequential MST')
plt.plot(nodes, parallel_times, marker='s', label='Parallel MST')
plt.title('MST Execution Time Comparison')
plt.xlabel('Number of Nodes')
plt.ylabel('Time (seconds)')
plt.legend()
plt.grid(True)
plt.savefig('mst_performance_comparison.png')
plt.show()
