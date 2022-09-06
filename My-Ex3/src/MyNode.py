class MyNode:

    def __init__(self, key: int, pos: tuple = None):
        self.key = key
        self.pos = pos
        self.in_edges = {}
        self.out_edges = {}
        self.distance = 0
        self.tag = 255
        self.prev = None

    def get_key(self) -> int:
        return self.key

    def get_prev(self):
        return self.prev

    def set_prev(self, prev) -> None:
        self.prev = prev

    def get_tag(self) -> int:
        return self.tag

    def set_tag(self, tag: int) -> None:
        self.tag = tag

    def get_distance(self) -> float:
        return self.distance

    def set_distance(self, dis: float) -> None:
        self.distance = dis

    def get_pos(self) -> tuple:
        return self.pos

    def get_in_edges(self) -> dict:
        return self.in_edges

    def get_out_edges(self) -> dict:
        return self.out_edges

    def reverse(self) -> None:
        temp = self.in_edges.copy()
        self.in_edges = self.out_edges
        self.out_edges = temp

    def __str__(self):
        return f"ID:{self.key},Pos: {self.pos}"

    def __repr__(self):
        return f"ID:{self.key},Pos: {self.pos}"
