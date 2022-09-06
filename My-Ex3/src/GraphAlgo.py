import json
import random
import traceback
from math import sqrt
from typing import List

import pygame

import GraphInterface
from DiGraph import DiGraph
from GraphAlgoInterface import GraphAlgoInterface
from MyNode import MyNode

MAX_VALUE = 999999999
Grey = (120, 128, 144)
Black = (0, 0, 0)
White = (255, 255, 255)


class GraphAlgo(GraphAlgoInterface):

    def __init__(self, graph: GraphInterface = None):
        self.graph = graph

    def get_graph(self) -> GraphInterface:
        return self.graph

    def load_from_json(self, file_name: str) -> bool:
        try:
            with open(file_name, 'r') as graph_json:
                graph_dict = json.load(graph_json)
            graph = DiGraph()
            nodes_list = graph_dict.get("Nodes")
            edges_list = graph_dict.get("Edges")
            for n in nodes_list:
                if n.keys().__contains__("pos"):
                    pos = n["pos"]
                    pos_list = pos.split(",")
                    x = float(pos_list[0])
                    y = float(pos_list[1])
                    z = float(pos_list[2])
                    graph.add_node(n["id"], (x, y, z))
                else:
                    graph.add_node(n["id"])

            for e in edges_list:
                graph.add_edge(e["src"], e["dest"], e["w"])

            self.__init__(graph)
        except FileNotFoundError:
            traceback.print_exc()
            return False
        return True

    def save_to_json(self, file_name: str) -> bool:
        nodes_list = []
        edges_list = []
        for node_index in self.graph.get_all_v():
            node = self.graph.get_all_v()[node_index]
            if node.get_pos() is not None:
                nodes_list.append(
                    {"pos": f"{node.get_pos()[0]},{node.get_pos()[1]},{node.get_pos()[2]}", "id": node_index})
            else:
                nodes_list.append({"id": node_index})
            for dest in node.get_out_edges():
                edges_list.append({"src": node_index, "w": node.get_out_edges()[dest], "dest": dest})
        dict_graph = {"Edges": edges_list, "Nodes": nodes_list}
        try:
            with open(file_name, 'w') as f:
                json.dump(dict_graph, f, indent=2)
        except FileNotFoundError:
            traceback.print_exc()
            return False
        return True

    def shortest_path(self, id1: int, id2: int) -> (float, list):
        ans = []
        self.dijkstra(self.graph.get_all_v().get(id1))
        prev = self.graph.get_all_v().get(id2)
        shortest_dist = prev.get_distance()
        if prev.get_distance() == MAX_VALUE:
            return MAX_VALUE, []
        while prev is not None:
            ans.append(prev)
            prev = prev.get_prev()
        ans.reverse()
        return shortest_dist, ans

    def TSP(self, node_lst: List[int]) -> (List[int], float):
        for node in self.graph.get_all_v().values():
            node.set_tag(White)
        ans = []
        cities = node_lst.copy()
        shortest_dist = 0
        while len(cities) > 0:
            if len(cities) == 1:
                ans.append(cities[0])
                break
            for intersection_index in cities:
                intersection = self.graph.get_all_v().get(intersection_index)
                if intersection.get_tag() == Black:
                    cities.pop(intersection_index)
            n1 = self.graph.get_all_v().get(cities.pop(0))
            if len(cities) == 0:
                break
            n2 = self.graph.get_all_v().get(cities[0])
            temp_dist, path = self.shortest_path(n1.get_key(), n2.get_key())
            shortest_dist = shortest_dist + temp_dist
            for intersection in path:
                if ans.__contains__(intersection.get_key()) and intersection.get_key() != n2.get_key():
                    intersection.set_tag(Black)
                if intersection != n2:
                    ans.append(intersection.get_key())
        return ans, shortest_dist

    def centerPoint(self) -> (int, float):
        if not self.is_connected():
            return -1, MAX_VALUE

        shortest_dist = MAX_VALUE
        ans_node_index = -1

        for node in self.graph.get_all_v().values():
            self.dijkstra(node)
            max_dist = -1
            for v in self.graph.get_all_v().values():
                if v.get_distance() > max_dist:
                    max_dist = v.get_distance()
            if max_dist < shortest_dist:
                shortest_dist = max_dist
                ans_node_index = node.get_key()

        return ans_node_index, shortest_dist

    def plot_graph(self) -> None:
        width, height = 800, 600
        win = pygame.display.set_mode((width, height))
        win.fill(Grey)
        pygame.display.set_caption("Directed Weighted Graph")
        pygame.font.init()
        self.draw_graph(win)
        run = True
        while run:
            pygame.display.update()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
        pygame.quit()

    def dijkstra(self, src_node: MyNode) -> None:
        queue = {}
        for node in self.graph.get_all_v().values():
            node.set_prev(None)
            node.set_distance(MAX_VALUE)
            queue[node.get_key()] = node

        src_node.set_distance(0)
        while len(queue) != 0:
            key = self.get_min_dist_node_key(queue)
            if key == -1:
                break
            u = self.graph.get_all_v().get(key)
            queue.pop(key)
            for v_index in u.get_out_edges().keys():
                v = self.graph.get_all_v().get(v_index)
                dis_from_src = u.get_distance() + u.get_out_edges().get(v_index)
                if dis_from_src < v.get_distance():
                    v.set_distance(dis_from_src)
                    v.set_prev(u)

    def get_min_dist_node_key(self, queue: dict) -> int:
        ans = -1
        dist = MAX_VALUE
        for node in queue.values():
            if node.get_distance() < dist:
                dist = node.get_distance()
                ans = node.get_key()
        return ans

    def bfs(self, s: MyNode):
        for node in self.graph.get_all_v().values():
            node.set_distance(MAX_VALUE)
            node.set_tag(White)

        s.set_tag(Grey)
        s.set_distance(0)
        queue = [s]
        while len(queue) > 0:
            u = queue.pop(0)
            for v_index in u.get_out_edges().keys():
                v = self.graph.get_all_v().get(v_index)
                if v.get_tag() == White:
                    v.set_tag(Grey)
                    v.set_distance(u.get_distance() + 1)
                    queue.append(v)

            u.set_tag(Black)

    def is_connected(self) -> bool:
        n = None
        for node in self.graph.get_all_v().values():
            n = node
            break
        if n is None:
            return False
        self.bfs(n)
        for node in self.graph.get_all_v().values():
            if node.get_distance() == MAX_VALUE:
                return False
        self.graph.reverse_graph()
        self.bfs(n)
        self.graph.reverse_graph()
        for node in self.graph.get_all_v().values():
            if node.get_distance() == MAX_VALUE:
                return False
        return True

    def draw_graph(self, win: pygame.Surface):
        max_xy = self.get_max_xy()
        radius = 5
        if max_xy == (-1, -1):
            for node in self.graph.get_all_v().values():
                x = random.randrange(1, win.get_width())
                y = random.randrange(1, win.get_height())
                pygame.draw.circle(win, node.get_tag(), (x, y), 5)
                pos = str(node.get_key())
                font = pygame.font.SysFont('Ariel', 20)
                text = font.render(pos, True, (255, 0, 0))
                win.blit(text, (x - 15, y - 15, 100, 100))
        else:
            for node in self.graph.get_all_v().values():
                if node.get_pos() is not None:
                    xy = self.get_scaled_xy(win, node.get_pos())
                    x = xy[0]
                    y = xy[1]
                else:
                    x = random.randrange(0, max_xy[0])
                    y = random.randrange(0, max_xy[1])
                pygame.draw.circle(win, node.get_tag(), (x, y), radius)
                pos = str(node.get_key())
                font = pygame.font.SysFont('Ariel', 20)
                text = font.render(pos, True, (255, 0, 0))
                win.blit(text, (x - 15, y - 15, 100, 100))
                for dest_index in node.get_out_edges():
                    dest_node = self.graph.get_all_v()[dest_index]
                    if dest_node.get_pos() is not None:
                        dest_xy = self.get_scaled_xy(win, dest_node.get_pos())
                        dest_x = dest_xy[0]
                        dest_y = dest_xy[1]
                    else:
                        dest_x = random.randrange(0, max_xy[0])
                        dest_y = random.randrange(0, max_xy[1])
                    pygame.draw.line(win, (0, 0, 139), (x, y), (dest_x, dest_y))
                    self.draw_arrow_head(win, x, y, dest_x, dest_y)
        pygame.display.update()

    def draw_arrow_head(self, win: pygame.surface, x1: float, y1: float, x2: float, y2: float) -> None:
        arrow_width = 15
        arrow_height = 2
        diff_x = x2 - x1
        diff_y = y2 - y1
        D = sqrt(diff_x * diff_x + diff_y * diff_y)
        xm = D - arrow_width
        xn = xm
        ym = arrow_height
        yn = -arrow_height

        sin = diff_y / D
        cos = diff_x / D

        x = xm * cos - ym * sin + x1
        ym = xm * sin + ym * cos + y1
        xm = x

        x = xn * cos - yn * sin + x1
        yn = xn * sin + yn * cos + y1
        xn = x

        points = ((x2, y2), (xm, ym), (xn, yn))

        pygame.draw.line(win, (0, 0, 139), (x1, y1), (x2, y2))
        pygame.draw.polygon(win, (0, 0, 139), points)

    def get_max_xy(self) -> ():
        x = -1
        y = -1
        for node in self.graph.get_all_v().values():
            if node.get_pos() is None:
                continue
            else:
                if node.get_pos()[0] > x:
                    x = node.get_pos()[0]
                if node.get_pos()[1] > y:
                    y = node.get_pos()[1]
        return x, y

    def get_min_xy(self):
        x = MAX_VALUE
        y = MAX_VALUE
        for node in self.graph.get_all_v().values():
            if node.get_pos() is None:
                continue
            else:
                if node.get_pos()[0] < x:
                    x = node.get_pos()[0]
                if node.get_pos()[1] < y:
                    y = node.get_pos()[1]
        return x, y

    def get_scaled_xy(self, win: pygame.Surface, coordinates: ()) -> ():
        max_xy = self.get_max_xy()
        min_xy = self.get_min_xy()
        wide_factor_x = win.get_width() / (max_xy[0] - min_xy[0])
        wide_factor_y = win.get_height() / (max_xy[1] - min_xy[1])
        x = (((coordinates[0] - min_xy[0]) * wide_factor_x) * 0.65) + 150
        y = (((coordinates[1] - min_xy[1]) * wide_factor_y) * 0.65) + 100
        return x, y
