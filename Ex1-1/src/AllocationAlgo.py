import json
import csv
from mybuilding import MyBuilding
from myelevator import MyElevator
from mycall import MyCall
from mycalls import MyCalls
import sys


def open_json_file(st: str) -> MyBuilding:
    with open(st, 'r') as f:
        data_dict = json.load(f)
    building = MyBuilding(len(data_dict["_elevators"]))
    elev_list = data_dict["_elevators"]
    for x in elev_list:
        elevator = MyElevator(x["_id"], x["_speed"], x["_minFloor"], x["_maxFloor"], x["_closeTime"], x["_openTime"],
                              x["_startTime"], x["_stopTime"])
        building + elevator
    return building


def open_csv_file(st: str) -> list:
    all_calls = []  # list of lists of calls as strings
    with open(st, 'r') as f:
        filereader = csv.reader(f)
        for row in filereader:
            all_calls.append(row)
    return all_calls


def write_to_csv(all_calls: list, my_calls: MyCalls, st3: str):
    i = 0
    for x in all_calls:
        x[5] = my_calls.get_calls_list()[i].allocated_to
        i += 1
    with open(st3, 'w', newline="") as f:
        for x in all_calls:
            writer = csv.writer(f)
            writer.writerow(x)


def calctime(src: int, dst: int, elevator: MyElevator):
    elevatortimes = elevator.get_opentime()+elevator.get_closetime()+elevator.get_starttime()+elevator.get_stoptime()
    return (abs(src-dst)/elevator.get_speed())+elevatortimes


def isinpath(call, nextcall, elevator):
    if nextcall.time_received-call.time_received < calctime(call.get_src(), nextcall.get_src(), elevator):
        return True
    return False


def timetocompletecall(elevator, current_pos, src, dst):
    if current_pos == src:
        t1 = elevator.get_closetime()
    else:
        t1 = abs(current_pos-src)/elevator.get_speed() + elevator.get_starttime() + elevator.get_opentime()\
             + elevator.get_stoptime() + elevator.get_closetime()
    t2 = abs(src-dst)/elevator.get_speed() + elevator.get_starttime() + elevator.get_opentime()\
        + elevator.get_stoptime() + elevator.get_closetime()
    return t1+t2


def get_best_elevator(call, building):
    t = 10000000000
    elv_id = -1
    for elevator in building:
        if len(elevator.get_calls()) == 0:
            time_for_call = calctime(call.get_src(), call.get_dst(), elevator)
        else:
            time_for_call = calctime(call.get_src(), call.get_dst(), elevator) * len(elevator.get_calls())
        if t > time_for_call:
            t = time_for_call
            elv_id = elevator.get_id()
    return elv_id


def allocate_extra_calls(call: MyCall, temp_call: MyCall, my_calls: MyCalls, elv: MyElevator):
    time = calctime(call.get_src(), call.get_dst(), elv)
    direction = call.get_dir()
    while temp_call is not None and temp_call.time_received < call.time_received + time:
        if direction == 1:
            if temp_call.get_dir() == 1 and temp_call.allocated_to == -1:
                if isinpath(call, temp_call, elv):
                    temp_call.allocated_to = elv.get_id()
                    elv + temp_call
        if direction == -1:
            if temp_call.get_dir() == -1 and temp_call.allocated_to == -1:
                if isinpath(call, temp_call, elv):
                    temp_call.allocated_to = elv.get_id()
                    elv + temp_call
        temp_call = my_calls.get_next_call(temp_call)


def allocate(st1, st2, st3):
    building = open_json_file(st1)
    all_calls = open_csv_file(st2)
    my_calls = MyCalls(all_calls)
    elv_list = building.get_elevators_list()
    # allocation start
    for call in my_calls:
        if call.allocated_to == -1:
            elv_id = get_best_elevator(call, building)
            call.allocated_to = elv_id
            curr_elev = elv_list[elv_id]
            curr_elev + call
            temp_call = my_calls.get_next_call(call)
            if temp_call is not None:
                allocate_extra_calls(call, temp_call, my_calls, curr_elev)
    write_to_csv(all_calls, my_calls, st3)


if __name__ == '__main__':
    allocate(sys.argv[2], sys.argv[3], sys.argv[4])
    # allocate("Assignments/Ex1/data/Ex1_Buildings/B5.json", "Ex1_Calls/Calls_d.csv", "output.csv")

