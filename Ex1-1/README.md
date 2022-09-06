# Ex1

In this project we were required to design an optimal elevator algorithm which allocates each elevator to certain calls in order to bring the overall waiting time of all calls to the minimum. more precisely, given a building (set of elevators with stats such as floor per second, time to open/close doors etc) and a set of calls (time received, source floor, destination floor), determine the best allocation in terms of minimal waiting time.

## Literature Survey:
https://www.geeksforgeeks.org/smart-elevator-pro-geek-cup/

https://www.diva-portal.org/smash/get/diva2:668654/FULLTEXT01.pdf

https://www.npr.org/templates/story/story.php?storyId=6799860

## Our Algorithm:

After extracting the data from the files, we loop over the calls and for each call we loop over all the elevators, while looping over the elevators calculate the cost of the call, multiple the cost by the amount of active calls the elevator has at that time and choose the elevator with the lowest cost. In addition, after choosing the elevator for a certain call, we loop over the calls again in order to allocate additional calls that would work well with the original call (calls that are contained within the original call and such).

## flowchart:
![image](https://user-images.githubusercontent.com/92747945/142666483-0a5d7156-01cf-470e-aa58-37be3fd63ac2.png)



## Our Classes

| Class | Description |
| ------ | ------ |
| MyCall | insert every call from the csv file and create a MyCall to have easier access to data such as time received, source floor and such |
| MyCalls | every MyCall we create we add to our MyCalls object which holds a list of all calls with few basic functions such as get_next_call() |
| MyElevator | insert every Elevator from the json file and create an Elevator to have easier access to elevator's data such as speed, opentime, starttime and such |
| MyBuilding | every Elevator we create we add to our Building object which holds a list of elevators with very basic functions |
| AllocationAlgo | the main class of our algorithm which is connected to all the other classes, contains the function "Allocate" which runs our algorithm and all the other classes that are included |

## Results:


| Calls | Building | Uncompleted | AverageWaitTime |
| ------ | ------ | ------------ | ------------- |
| a | B1 | 0 | 112.92 |
| a | B2 | 0 | 53.64 |
| b | B3 | 233 | 542.88 |
| c | B3 | 96 | 527.94 |
| d | B3 | 90 | 548.74 |
| b | B4 | 14 | 203.85 |
| c | B4 | 8 | 198.26 |
| d | B4 | 4 | 201.15 |
| b | B5 | 0 | 65.408 |
| c | B5 | 0 | 67.023 |
| d | B5 | 0 | 64.257 |



## How to Run:
running our function from terminal/cmd which prints the csv file with the allocated elevators:

```sh
python AllocationAlgo.py 206284960,207304353 <json_file_name.json> <csv_file(calls).csv> <output_file_name.csv>
```
running the tester in terminal/cmd:

```sh
java -jar Ex1_checker_V1.2_obf.jar 206284960,207304353 <json_file(building).csv> <output_file_name(allocated calls).csv> <log_file_name.log>
```


