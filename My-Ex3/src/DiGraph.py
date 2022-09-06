from GraphInterface import GraphInterface
from MyNode import MyNode


class DiGraph(GraphInterface):

    def __init__(self):
        self.nodes_dict = {}
        self.MC = 0
        self.edges_size = 0

    def v_size(self) -> int:
        return len(self.nodes_dict)

    def e_size(self) -> int:
        return self.edges_size

    def get_all_v(self) -> dict:
        return self.nodes_dict

    def all_in_edges_of_node(self, id1: int) -> dict:
        return self.nodes_dict.get(id1).get_in_edges()

    def all_out_edges_of_node(self, id1: int) -> dict:
        return self.nodes_dict.get(id1).get_out_edges()

    def get_mc(self) -> int:
        return self.MC

    def add_edge(self, id1: int, id2: int, weight: float) -> bool:
        if id1 in self.nodes_dict.keys() and id2 in self.nodes_dict.keys():
            if id2 in self.nodes_dict.get(id1).get_out_edges().keys() or id1 in self.nodes_dict.get(id2).get_in_edges().keys():
                return False
            else:
                self.nodes_dict.get(id1).get_out_edges()[id2] = weight
                self.nodes_dict.get(id2).get_in_edges()[id1] = weight
                self.MC += 1
                self.edges_size += 1
                return True
        return False

    def add_node(self, node_id: int, pos: tuple = None) -> bool:
        n = MyNode(node_id, pos)
        if node_id in self.nodes_dict.keys():
            return False
        else:
            self.nodes_dict[node_id] = n
            self.MC += 1
            return True

    def reverse_graph(self) -> None:
        for node in self.nodes_dict.values():
            node.reverse()

    def remove_node(self, node_id: int) -> bool:
        if self.nodes_dict.get(node_id) is not None:
            self.nodes_dict.pop(node_id)
            self.MC += 1
            return True
        return False

    def remove_edge(self, node_id1: int, node_id2: int) -> bool:
        if node_id1 in self.nodes_dict.keys() and node_id2 in self.nodes_dict.keys():
            if node_id2 in self.nodes_dict.get(node_id1).get_out_edges().keys() or\
                    node_id1 in self.nodes_dict.get(node_id2).get_in_edges().keys():
                self.nodes_dict.get(node_id1).get_out_edges().pop(node_id2)
                self.nodes_dict.get(node_id2).get_in_edges().pop(node_id1)
                self.MC += 1
                self.edges_size -= 1
                return True
            else:
                return False
        return False

    def __str__(self):
        return f"Graph: |V|={self.v_size()} , |E|={self.e_size()}"
