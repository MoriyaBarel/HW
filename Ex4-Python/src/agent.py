class Agent:

    def __init__(self, id: int, value: float, src: int, dest: int, speed: float, pos: tuple):
        self.id = id
        self.value = value
        self.src = src
        self.dest = dest
        self.speed = speed
        self.pos = pos

    def get_id(self) -> int:
        return self.id

    def get_value(self) -> float:
        return self.value

    def get_src(self) -> int:
        return self.src

    def get_dest(self) -> int:
        return self.dest

    def get_speed(self) -> float:
        return self.speed

    def get_pos(self) -> tuple:
        return self.pos

    def set_pos(self, pos: tuple) -> None:
        self.pos = pos

    def __str__(self):
        return f"id: {self.id}, value: {self.value}, src: {self.src}, dest: {self.dest}," \
               f" speed: {self.speed}, pos: {self.pos}"

    def __repr__(self):
        return f"id: {self.id}, value: {self.value}, src: {self.src}, dest: {self.dest}," \
               f" speed: {self.speed}, pos: {self.pos}"
