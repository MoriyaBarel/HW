

class MyCall:

    def __init__(self, time: str, src: str, dst: str):
        self.time_received = float(time)
        self.src = int(src)
        self.dst = int(dst)
        self.allocated_to = -1
        self.state = 0

    def get_time_received(self):
        return self.time_received

    def get_src(self):
        return self.src

    def get_dst(self):
        return self.dst

    def __str__(self):
        return f"Elevator Call,{self.time_received},{self.src},{self.dst},{self.allocated_to},-1"

    def __repr__(self):
        return f"Elevator Call,{self.time_received},{self.src},{self.dst},{self.allocated_to},-1"

    def get_dir(self):
        if self.src < self.dst:
            return 1
        else:
            return -1

    def __eq__(self, other):
        if self.time_received == other.time_received and self.src == other.src and self.dst == other.dst:
            return True
        return False
