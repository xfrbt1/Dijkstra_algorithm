from read_data import read_weight_matrix, print_weight_matrix
from config import path_to_file_with_matrix

import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
import pylab

wm = read_weight_matrix(path_to_file_with_matrix)
graph = nx.Graph(np.matrix(wm))


for i in range(len(wm)):
    for j in range(len(wm)):
        if wm[i][j] != 0:
            graph.add_edge(i, j, weight=wm[i][j])

pos = nx.spring_layout(graph, seed=5)

pylab.figure(2)
nx.draw(graph, pos, with_labels=False, node_size=600)
nx.draw_networkx_labels(graph, pos, font_size=22, font_family="sans-serif")

edge_labels = dict([((u, v,), d['weight']) for u, v, d in graph.edges(data=True)])
nx.draw_networkx_edges(
    graph, pos,  alpha=1, edge_color="b", style="dashed"
)
nx.draw_networkx_edge_labels(graph, pos, edge_labels=edge_labels)

plt.show()
