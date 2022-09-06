from MyElevator import MyElevator


class MyBuilding:

    def __init__(self, num: int):
        self._elevators_list = []
        self.num = num

    def get_numofelev(self):
        return self.num

    def get_elevators_list(self):
        return self._elevators_list

    def __add__(self, other: MyElevator):
        if isinstance(other, MyElevator):
            return self._elevators_list.append(other)

    def __str__(self):
        return self._elevators_list.__str__()

    def __iter__(self):
        return iter(self._elevators_list)




