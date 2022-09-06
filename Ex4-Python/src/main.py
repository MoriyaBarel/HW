from types import SimpleNamespace

from DiGraph import DiGraph
from agent import Agent
from client import Client
import json
import pygame
from pygame import *
from gui import GUI
from pokemon import Pokemon

WIDTH, HEIGHT = 600, 600

# default port
PORT = 6666
# server host (default localhost 127.0.0.1)
HOST = '127.0.0.1'


def load_and_draw_pokemons(client: Client) -> None:
    pokemons = json.loads(client.get_pokemons(), object_hook=lambda d: SimpleNamespace(**d)).Pokemons
    pokemons = [p.Pokemon for p in pokemons]
    for p in pokemons:
        x_str, y_str, _ = p.pos.split(',')
        pos = (gui.my_scale(float(x_str), x=True), gui.my_scale(float(y_str), y=True))
        pokemon = Pokemon(p.value, p.type, pos)
        gui.draw_pokemons(pokemon)


def load_agents(client: Client) -> list:
    agents = json.loads(client.get_agents(), object_hook=lambda d: SimpleNamespace(**d)).Agents
    agents = [agent.Agent for agent in agents]
    agents_list = []
    for a in agents:
        x, y, _ = a.pos.split(',')
        pos = (gui.my_scale(float(x), x=True), gui.my_scale(float(y), y=True))
        agent = Agent(a.id, a.value, a.src, a.dest, a.speed, pos)
        agents_list.append(agent)

    return agents_list


def load_graph(client: Client) -> DiGraph:
    g = json.loads(client.get_graph(), object_hook=lambda json_dict: SimpleNamespace(**json_dict))
    di_graph = DiGraph()
    for n in g.Nodes:
        x, y, _ = n.pos.split(',')
        n.pos = SimpleNamespace(x=float(x), y=float(y))
        di_graph.add_node(n.id, (n.pos.x, n.pos.y))
    for e in g.Edges:
        di_graph.add_edge(e.src, e.dest, e.w)
    return di_graph


if __name__ == '__main__':
    client = Client()
    client.start_connection(HOST, PORT)

    graph = load_graph(client)

    gui = GUI(HEIGHT, WIDTH, graph.get_min_x(), graph.get_min_y(), graph.get_max_x(), graph.get_max_y())
    print(client.get_info())
    client.add_agent("{\"id\":0}")
    # client.add_agent("{\"id\":1}")
    # client.add_agent("{\"id\":2}")
    # client.add_agent("{\"id\":3}")

    agents_list = load_agents(client)

    # this commnad starts the server - the game is running now
    client.start()

    while client.is_running() == 'true':
        # check events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit(0)

        # refresh surface
        gui.screen.fill(Color(0, 0, 0))

        gui.draw_graph(graph)

        load_and_draw_pokemons(client)
        gui.draw_agents(agents_list)
        print(agents_list)
        # update screen changes
        display.update()

        # refresh rate
        gui.clock.tick(60)

        # choose next edge
        # for agent in agents:
        #     if agent.dest == -1:
        #         next_node = (agent.src - 1) % len(graph.get_all_v())
        #         client.choose_next_edge('{"agent_id":' + str(agent.id) + ', "next_node_id":' + str(next_node) + '}')
        #         ttl = client.time_to_end()
        #         print(ttl, client.get_info())

        client.move()
    # game over:

