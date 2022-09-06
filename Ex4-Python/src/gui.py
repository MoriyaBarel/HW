import json
from types import SimpleNamespace

import pygame
from pygame import *
from pygame import gfxdraw

from agent import Agent
from DiGraph import DiGraph
from pokemon import Pokemon

radius = 15


class GUI:

    def __init__(self, WIDTH: int, HEIGHT: int,  min_x, min_y, max_x, max_y):
        pygame.init()
        self.screen = display.set_mode((WIDTH, HEIGHT), depth=32, flags=RESIZABLE)
        self.clock = pygame.time.Clock()
        pygame.font.init()
        self.FONT = pygame.font.SysFont('Arial', 20, bold=True)
        self.min_x = min_x
        self.min_y = min_y
        self.max_x = max_x
        self.max_y = max_y

    def draw_graph(self, graph: DiGraph) -> None:
        for n in graph.get_all_v().values():
            x = self.my_scale(n.get_pos()[0], x=True)
            y = self.my_scale(n.get_pos()[1], y=True)

            # its just to get a nice antialiased circle
            gfxdraw.filled_circle(self.screen, int(x), int(y), radius, Color(64, 80, 174))
            gfxdraw.aacircle(self.screen, int(x), int(y), radius, Color(255, 255, 255))

            # draw the node id
            id_srf = self.FONT.render(str(n.get_id()), True, Color(255, 255, 255))
            rect = id_srf.get_rect(center=(x, y))
            self.screen.blit(id_srf, rect)

            for dest_index in n.get_out_edges():
                dest_node = graph.get_all_v()[dest_index]
                dest_x = self.my_scale(dest_node.get_pos()[0], x=True)
                dest_y = self.my_scale(dest_node.get_pos()[1], y=True)

                # draw the line
                pygame.draw.line(self.screen, Color(61, 72, 126), (x, y), (dest_x, dest_y))

    def draw_pokemons(self, pokemon: Pokemon) -> None:
        pygame.draw.circle(self.screen, Color(0, 255, 255), (pokemon.get_pos()[0], pokemon.get_pos()[1]), 10)

    def draw_agents(self, agents_list: list) -> None:
        for agent in agents_list:
            pygame.draw.circle(self.screen, Color(122, 61, 23), (agent.get_pos()[0], agent.get_pos()[1]), 10)

    def scale(self, data, min_screen, max_screen, min_data, max_data):
        """
        get the scaled data with proportions min_data, max_data
        relative to min and max screen dimentions
        """
        return ((data - min_data) / (max_data - min_data)) * (max_screen - min_screen) + min_screen

    def my_scale(self, data, x=False, y=False):
        if x:
            return self.scale(data, 50, self.screen.get_width() - 50, self.min_x, self.max_x)
        if y:
            return self.scale(data, 50, self.screen.get_height() - 50, self.min_y, self.max_y)


