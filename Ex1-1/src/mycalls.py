from mycall import MyCall


class MyCalls:

    def __init__(self, list: list):
        self.list_of_calls = []
        for x in list:
            temp_call = MyCall(x[1], x[2], x[3])
            self.list_of_calls.append(temp_call)

    def __add__(self, other):
        if isinstance(other, MyCall):
            self.list_of_calls.append(other)

    def __str__(self):
        return self.list_of_calls.__str__()

    def get_calls_list(self):
        return self.list_of_calls

    def get_next_index(self, call):
        counter = 0
        for i in self.list_of_calls:
            if i.__eq__(call):
                return counter+1
            else:
                counter += 1
        return 0

    def __iter__(self):
        return iter(self.list_of_calls)

    def get_next_call(self, call):
        i = self.get_next_index(call)
        if i >= len(self.list_of_calls) or i < 1:
            return None
        return self.list_of_calls[i]