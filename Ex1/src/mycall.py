class MyCall:

    def __init__(self, time: float, src_floor: int, dst_floor: int):
        self._time = float(time)
        self._src_floor = int(src_floor)
        self._dst_floor = int(dst_floor)
        self._elev_index = -1

    def get_time(self):
        return self._time

    def get_src_floor(self):
        return self._src_floor

    def get_dst_floor(self):
        return self._dst_floor

    def __str__(self):
        return f"Elevator call,{self._time},{self._src_floor},{self._dst_floor},0,{self._elev_index}"

    def __repr__(self):
        return f"Elevator call,{self._time},{self._src_floor},{self._dst_floor},0,{self._elev_index}"
