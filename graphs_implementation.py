class Graph:
    def __init__(self, nodes):
        self.nodes = nodes
        self.VE_list = {}

        for node in self.nodes:
            self.VE_list[node] = list()

    def create_links(self, node, link_list):
        if node in self.VE_list:
            self.VE_list[node].append(link_list)
            for i in link_list:
                if i[0] in self.VE_list:
                    self.VE_list[i[0]].append([node, i[1]])

    def print_all_nodes(self):
        for k, v in self.VE_list.items():
            print(k, v)


nodes = ['a', 'b', 'c', 'd']
a_link = [['b', 5], ['d', 3]]
graph = Graph(nodes)
graph.create_links('a', a_link)
graph.print_all_nodes()



