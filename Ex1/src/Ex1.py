from MyBuilding import MyBuilding
from MyElevator import MyElevator
from allcalls import AllCalls
from mycall import MyCall


import json
import csv


def cost(src: int, dst: int, elev: MyElevator):
    open_t = elev.get_open_time()
    close_t = elev.get_close_time()
    start_t = elev.get_start_time()
    stop_t = elev.get_stop_time()
    speed = elev.get_speed()
    # if pos == src:
    #     pos_to_src = 0
    # else:
    #     pos_to_src = (abs(src-pos))/speed + open_t + close_t + start_t + stop_t
    src_to_dst = ((abs(dst - src)) / speed) + open_t + close_t + start_t + stop_t
    return src_to_dst
    # return pos_to_src + src_to_dst

# def get_elev_pos(elev: MyElevator, call: MyCall, current_time: int):
#     if elev._elev_calls[0] == call :
#         elev_pos = 0
#     start_t = call.get_time()
#     elev_pos = call.get_src_floor() + top_value((current_time-start_t)/elev.get_speed())
#
#
# def top_value(x):
#     if isinstance(x, int):
#         return x
#     else:
#         return x+1



def allocate(building: str, calls: str, allocated_calls: str):
    with open(building, 'r') as building:
        building_dict = json.load(building)
    b = MyBuilding(len(building_dict["_elevators"]))
    elevators = building_dict.get("_elevators")
    for i in elevators:
        elev = MyElevator(i["_id"], i["_speed"], i["_minFloor"], i["_maxFloor"], i["_closeTime"], i["_openTime"], i["_startTime"], i["_stopTime"])
        b + elev
    with open(calls, 'r') as f:
        reader = csv.reader(f)
        all_calls = list(reader)
    my_calls = AllCalls()
    for c in all_calls:
        call_list = c
        call = MyCall(call_list[1], call_list[2], call_list[3])
        my_calls + call

    elev_list = b.get_elevators_list()
    for c in my_calls:
        t = 10000000
        elev_index = -1
        for e in b:
            if len(e.get_call_list()) == 0:
                time_for_call = cost(c.get_src_floor(), c.get_dst_floor(), e)
            else:
                time_for_call = cost(c.get_src_floor(), c.get_dst_floor(), e) * len(e.get_call_list())
            if time_for_call < t:
                t = time_for_call
                elev_index = e.get_id()
        c._elev_index = elev_list[elev_index].get_id()
        elev_list[elev_index] + c




    i = 0
    for x in all_calls:
        x[5] = my_calls.get_calls_list()[i]._elev_index
        i += 1
    with open(allocated_calls, 'w', newline="") as f:
        for x in all_calls:
            writer = csv.writer(f)
            writer.writerow(x)


if __name__ == '__main__':
    allocate("Ex1_Buildings/B5.json", "Ex1_Calls/Calls_d.csv", "output.csv")