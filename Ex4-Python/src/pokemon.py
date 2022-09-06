class Pokemon:

    def __init__(self, value: float, type: int, pos: tuple):
        self.value = value
        self.type = type
        self.pos = pos

    def get_value(self) -> float:
        return self.value

    def get_type(self) -> int:
        return self.get_type()

    def get_pos(self) -> tuple:
        return self.pos

    def set_pos(self, pos: tuple) -> None:
        self.pos = pos

    def __str__(self):
        return f"value: {self.value}, type: {self.type}, pos: {self.pos}"

    def __repr__(self):
        return f"value: {self.value}, type: {self.type}, pos: {self.pos}"

