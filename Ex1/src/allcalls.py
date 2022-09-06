from mycall import MyCall


class AllCalls:

    def __init__(self):
        self._calls_list = []

    def get_calls_list(self):
        return self._calls_list

    def __add__(self, other: MyCall):
        if isinstance(other, MyCall):
            return self._calls_list.append(other)

    def __str__(self):
        return self._calls_list.__str__()

    def __iter__(self):
        return iter(self._calls_list)
