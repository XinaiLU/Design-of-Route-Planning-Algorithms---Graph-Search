## Lab 6: Design and Implementation of a Flight Route Planning System
---

## Experiment Objective

Utilize basic knowledge of graph structures, adjacency matrices, and adjacency lists to construct a flight route graph for XM Airlines based on existing route data. On this foundation, design a simple flight route planning system. This system can provide different flight route solutions according to user needs.

![image](https://github.com/user-attachments/assets/f0bd71b1-a5ab-4bba-90aa-5e54eec428a7)

### System Features

1. Perform a depth-first traversal from any airport, outputting all reachable airport IDs and paths. No airport should be repeated in any main route.
2. Perform a breadth-first traversal from any airport, outputting all reachable airport IDs and paths. No airport should be repeated in any main route.
3. Determine the connectivity between any two airports (direct or with one stopover) and output the sequence of Flight IDs.
4. Calculate the shortest flight time (including layover) between any two airports, and output Flight ID, total flight time, total layover time, departure time, and arrival time.
5. Given a specified departure or arrival time window, provide multiple alternative routes between two airports, either direct or with one stopover.
6. Given a specified departure or arrival time window, find the lowest fare between two airports and the corresponding flight route.

---

## Overall Approach

The program consists of seven main header files and a primary function:

<img width="233" alt="image" src="https://github.com/user-attachments/assets/0a33786e-dcf2-485a-a325-ee26fd0b353e">

- **flight_reader**: Reads CSV data and structures it into corresponding structs, modifying the time format.
- **dfs_and_bfs**: Implements depth-first search (DFS) using stack operations and breadth-first search (BFS) using queue operations.
- **find_all_flight**: Uses DFS to find all possible routes from the starting point to the destination, outputs direct or one-stop flights to `result.txt`, and stores the paths in arrays.
- **count_fares** and **count_time**: Use stored route information from `all_route` to calculate time and cost, selecting the optimal route accordingly.

---

## Detailed Design and Key Code

### Feature 1 & 2: DFS/BFS

After reading the flight data, each flight detail is stored in a struct, with each struct acting as a data block. **DFS** is implemented using stack operations. Since the task is to determine connectivity rather than finding the shortest time or lowest cost, the algorithm selects the earliest available flight when multiple paths satisfy the departure and arrival times, simplifying the data to one optimal path.

```cpp
// Depth-First Search function using stack
void dfs(int startAirport) {
    // Implementation using stack operations
}
```

DFS ensures that each path satisfies the time sequence requirement. A two-dimensional array `time_char[ROUTE_NO][CHAR_LEN]` stores arrival time strings, enabling easy retrieval of time information when backtracking from an empty stack node.

The logic for both DFS and BFS revolves around similar connectivity checks, with **DFS** using stacks and **BFS** using queues as auxiliary structures.

<img width="362" alt="Function to Determine Connectivity Between Two Airports" src="https://github.com/user-attachments/assets/6e4d36a1-79e9-4b67-b716-fca8a0860ea9">


<img width="353" alt="DFS Function Using Stack Operations" src="https://github.com/user-attachments/assets/a761b87c-ec6d-45ef-8aad-ccae83636ec8">


---

### Feature 3: All Routes with One Stop

To accommodate features that require time constraints, the DFS function incorporates parameters for start and end times. When calling this feature, default parameters `"000000000000"` and `"999999999999"` are passed to ensure all flight times are considered, effectively removing time constraints.

Beyond this point, features require precise flight IDs. While Features 1 and 2 focus on airport connectivity, Feature 3 emphasizes flight connectivity, incorporating both airports and connecting routes. The DFS process uses two stacks: `faf_stack` for airport nodes and `help_stack` for flight route IDs. When descending deeper in the search, all paths are explored, and if connected, airport IDs are pushed onto the left stack and route IDs onto the right stack.

<img width="256" alt="image" src="https://github.com/user-attachments/assets/5d802655-d1be-4f8b-b8e9-7f06578cf7aa">

```cpp
// Checking if the route has been visited
if (!faf_visited[DEP_ID][ARR_ID][BRANCH_NO]) {
    // Code to mark the route as visited
}
```

The program uses a three-dimensional array `faf_visited[DEP_ID][ARR_ID][BRANCH_NO]` to track visited paths, ensuring precise route ID management. To prevent repeated airport nodes in a single path, a temporary `save` array is used, which also aids in printing paths.

<img width="170" alt="image" src="https://github.com/user-attachments/assets/5f6e1e35-c24f-4276-b799-5d600cf1c9e4">

**Diagram**: *Function to Check for Repeated Airports*  

<img width="201" alt="Path Representation Example" src="https://github.com/user-attachments/assets/af2d3c31-c313-4719-88f2-5f33fdf5eff0">

**Diagram**: *Path Representation Example*  

Upon backtracking (when no valid paths remain at the top of the stack), the program removes all marks between the popped node and connected nodes to explore alternate paths. This is crucial for cases like multiple paths between two airports, e.g., `B->D->E` and `B->C->D->E`, ensuring the second path is not skipped due to premature marking.

```cpp
// Code to remove marks when backtracking
void unmarkPath(int node) {
    // Logic to unmark routes
}
```
<img width="368" alt="image" src="https://github.com/user-attachments/assets/8c3c4618-ed32-4e88-b305-57507b44893f">

**Diagram**: *Function to Unmark Routes During Backtracking*

Stack size is limited to three (start, stopover, destination) to meet the requirement of direct or one-stop routes.

---

### Feature 4: Shortest Flight Time

All paths from Feature 3 are stored and analyzed for total flight and layover times using helper arrays.

```cpp
// Code snippet for time calculation
int totalTime = calculateTime(path);
```
<img width="406" alt="image" src="https://github.com/user-attachments/assets/4d1892a6-6665-4a0e-a87a-3a0fa9c3b5c1">

### Feature 5: Time-Constrained Routes

Time constraints are passed into the DFS function, filtering paths that don't meet the departure time requirement.

```cpp
// Code to check if departure time is within limits
if (departure >= minTime && departure <= maxTime) {
    // Include the path in results
}
```
<img width="411" alt="image" src="https://github.com/user-attachments/assets/a025bb53-3b8e-46e7-90ef-9bc12a5dc7dd">

**Diagram**: *Condition to Enforce Departure Time Limits*

---

### Feature 6: Minimum Fare Calculation

Building on Feature 5, all paths are analyzed to find the one with the lowest fare.

```cpp
// Code to calculate minimum fare
int minFare = findLowestFare(routes);
```

---
<img width="410" alt="image" src="https://github.com/user-attachments/assets/3414ce19-4af0-4c1b-82d8-e1802e84cd24">

## Main Function

The main function presents a user interface for selecting features and executing the appropriate functions.

```cpp
int main() {
    // User menu and feature selection
    displayMenu();
    // Execute chosen option
}
```

---

## Results

### Feature 1: DFS Traversal

**Input**: `3`  
**Output**: All paths from Airport 3 using DFS

```
Airport Sequence: 3 -> 4 -> 5
```
<img width="364" alt="image" src="https://github.com/user-attachments/assets/41f3d4b2-7c44-4cac-a032-7046656c4522">


<img width="415" alt="image" src="https://github.com/user-attachments/assets/1fc10b8a-09b7-4657-b05f-ab90811a211c">

<img width="416" alt="image" src="https://github.com/user-attachments/assets/f3d6e56f-7650-46d1-8445-51b08e5b44d9">

<img width="415" alt="image" src="https://github.com/user-attachments/assets/ac68e7eb-123f-4c78-b0bd-765c298a4219">


### Feature 2: BFS Traversal

**Input**: `3`  
**Output**: BFS traversal order

```
Airport Sequence: 3 -> 5 -> 4
```
<img width="416" alt="image" src="https://github.com/user-attachments/assets/9d76d21b-6e84-475d-bb9f-571c6a924410">

### Feature 3: Direct/One-Stop Routes

**Input**: `48 49`  
**Output**: All routes from Airport 48 to 49 saved in `result.txt`.
<img width="272" alt="image" src="https://github.com/user-attachments/assets/83448a42-7c7f-4c35-a2a8-84c214d13a00">
<img width="307" alt="image" src="https://github.com/user-attachments/assets/adb9b96b-3baa-413e-a8b3-7d85af2fc3dc">

### Feature 4: Shortest Flight Time

**Input**: `49 50`  
**Output**: Flight details including ID, departure, and arrival times.
<img width="335" alt="image" src="https://github.com/user-attachments/assets/a8f708ee-8f54-4277-bcad-540bb1b04819">

- **Validation**: Verified 200-minute total time matches expected results.
<img width="346" alt="image" src="https://github.com/user-attachments/assets/d7ed7a24-3729-470f-afc2-25228aaf9589">

### Feature 5: Time-Constrained Routes

**Input**: `49 50 201705070000 201705091000`  
**Output**: All valid routes within the specified time window, saved to a file.
<img width="226" alt="image" src="https://github.com/user-attachments/assets/92995498-f678-4e59-ae4f-fdff93574e46">
<img width="322" alt="image" src="https://github.com/user-attachments/assets/1d61885f-7a09-4b9d-bbe2-56a98de151fe">

### Feature 6: Minimum Fare

**Input**: `50 25 201705051200 201705051400`  
**Output**: Minimum fare route between Airport 50 and 25 within the given time range.
<img width="323" alt="image" src="https://github.com/user-attachments/assets/8674a067-168b-4cc9-828b-c442dda8a1aa">
