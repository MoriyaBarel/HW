from myelevator import MyElevator


class MyBuilding:

    def __init__(self, num: int):
        self._numberOfElevators = num
        self._elevlist = []

    def getNumberOfElevators(self):
        return self._numberOfElevators

    def get_elevators_list(self):
        return self._elevlist

    def __add__(self, other: MyElevator):
        if isinstance(other, MyElevator):
            self._elevlist.append(other)

    def __str__(self):
        return self._elevlist.__str__()

    def __iter__(self):
        return iter(self._elevlist)
