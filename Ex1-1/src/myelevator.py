from mycall import MyCall


class MyElevator:

    def __init__(self, id: int, speed: int, minfloor: int, maxfloor: int,
                 closetime: int, opentime: int, starttime: int, stoptime: int):
        self._id = id
        self._speed = speed
        self._minfloor = minfloor
        self._maxfloor = maxfloor
        self._closetime = closetime
        self._opentime = opentime
        self._starttime = starttime
        self._stoptime = stoptime
        self._calls = []

    def get_id(self):
        return self._id

    def get_speed(self):
        return self._speed

    def get_minfloor(self):
        return self._minfloor

    def get_maxfloor(self):
        return self._maxfloor

    def get_closetime(self):
        return self._closetime

    def get_opentime(self):
        return self._opentime

    def get_starttime(self):
        return self._starttime

    def get_stoptime(self):
        return self._stoptime

    def __str__(self):
        return f"elevator id: {self._id} speed: +{self._speed}"

    def __repr__(self):
        return f"elevator id: {self._id} speed: +{self._speed}"

    def __add__(self, other):
        if isinstance(other, MyCall):
            self._calls.append(other)

    def get_calls(self):
        return self._calls

    def remove_completed_calls(self):
        for x in self._calls:
            if x.state == 3:
                self._calls.remove(x)

    def simulate(self):
        current_pos = 0
        if len(self._calls) == 1:
            return 0
        counter = 1
        while counter < len(self._calls):
            current_call = self._calls[counter-1]
            next_call = self._calls[counter]
            delta_time = next_call.time_received - current_call.time_received
            if self.timetocompletecall(current_pos, current_call.get_src(), current_call.get_dst()) < delta_time:
                current_pos = current_call.get_dst()
                current_call.state = 3
            elif self.timetosrc(current_pos, current_call.get_src()) < delta_time:
                current_call.state = 2
                if current_pos < current_call.get_src():
                    current_pos = current_pos + self.calcpos(delta_time)
                else:
                    current_pos = current_pos - self.calcpos(delta_time)
            else:
                current_call.state = 1
                if current_pos < current_call.get_src():
                    current_pos = current_pos + self.calcpos(delta_time)
                else:
                    current_pos = current_pos - self.calcpos(delta_time)
            counter += 1
        return current_pos

    def timetocompletecall(self, current_pos, src, dst):
        if current_pos == src:
            t1 = self._closetime
        else:
            t1 = abs(current_pos-src)/self._speed + self._starttime + self._opentime + self._stoptime + self._closetime
        t2 = abs(src-dst)/self._speed + self._starttime + self._opentime + self._stoptime + self._closetime
        return t1+t2

    def timetosrc(self, current_pos, src):
        return abs(current_pos-src)/self._speed + self._starttime + self._opentime + self._stoptime + self._closetime

    def calcpos(self, timeframe):
        return self._speed*int(timeframe) + self._starttime + self._opentime + self._stoptime + self._closetime

