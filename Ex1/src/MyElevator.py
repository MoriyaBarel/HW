from mycall import MyCall


class MyElevator:

    def __init__(self, id: int, speed: float, min_floor: int, max_floor: int, close_time: float, open_time: float, start_time: float, stop_time: float):
        self._id = int(id)
        self._speed = float(speed)
        self._min_floor = int(min_floor)
        self._max_floor = int(max_floor)
        self._close_time = float(close_time)
        self._open_time = float(open_time)
        self._start_time = float(start_time)
        self._stop_time = float(stop_time)
        self._elev_calls = []

    def get_id(self):
        return self._id

    def get_speed(self):
        return self._speed

    def get_min_floor(self):
        return self._min_floor

    def get_max_floor(self):
        return self._max_floor

    def get_close_time(self):
        return self._close_time

    def get_open_time(self):
        return self._open_time

    def get_start_time(self):
        return self._start_time

    def get_stop_time(self):
        return self._stop_time

    def get_call_list(self):
        return self._elev_calls

    def __str__(self):
        return f"MyElevator: Id:{self._id}, speed:{self._speed}, minFloor:{self._min_floor}, maxFloor:{self._max_floor}, closeTime:{self._close_time}, openTime:{self._open_time}, startTime:{self._start_time}, stopTime:{self._stop_time}"

    def __repr__(self):
        return f"MyElevator: Id:{self._id}, speed:{self._speed}, minFloor:{self._min_floor}, maxFloor:{self._max_floor}, closeTime:{self._close_time}, openTime:{self._open_time}, startTime:{self._start_time}, stopTime:{self._stop_time}"

    def __add__(self, other: MyCall):
        if isinstance(other, MyCall):
            return self._elev_calls.append(other)

    def calctime(self, src, dest):
        elevatortimes = self.get_open_time() + self.get_close_time() + self.get_start_time() + self.get_start_time()
        return abs(src - dest) / self.get_speed() + elevatortimes

    def remove_completed_calls(self, call):
        t = call.get_time()
        for x in self._elev_calls:
            if x.get_time() + self.calctime(call.get_src_floor(), call.get_dst_floor()) < t:
                self._elev_calls.remove(x)