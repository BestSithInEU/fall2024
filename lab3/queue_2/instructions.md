<h1 align="center">CSE211 DATA STRUCTURES</h1>
<h2 align="center">LAB 3 FALL 2024</h2>
<h3 align="center">QUEUE OPERATIONS</h3>

<h2 align="center">Prerequisites</h2>

Open the terminal and execute the following commands after downloading the `tarball` file:

```sh
cd /mnt/c/Users/user/Downloads && tar -xvf lab3_2.tar.gz --one-top-level=lab3_2
cd /mnt/c/Users/user/Downloads/lab3_2 && make all
code .
```

<h2 align="center">Introduction</h2>

In this lab, you will implement advanced operations on a Queue data structure using C++. The Queue is implemented as a template class that can store elements of any type T. Your task is to implement the following challenging operations:

1. `processParallel`: Schedule tasks across multiple processors
2. `processOrders`: Process restaurant orders across cooking stations

<h2 align="center">Project Structure</h2>

```text
.
├── bin/
│   └── queue
├── include/
│   ├── Queue.hpp
│   └── Color.hpp
├── obj/
│   ├── Queue.o
│   ├── Color.o
│   └── main.o
├── src/
│   ├── Queue.cpp
│   ├── Color.cpp
│   └── main.cpp
├── instructions.md
└── Makefile
```

<h2 align="center">Implementation Details</h2>

### 1. processParallel

- **Purpose**: Schedule tasks across multiple processors considering priorities
- **Parameters**: Vector of {duration, priority} pairs and number of processors
- **Return**: Vector of Results containing {task_id, start_time, processor_id}
- **Example**:

  ```cpp
  Input: tasks = {{4,1}, {2,2}, {3,1}, {1,3}}, processors = 2
  Output:
  Task 0 starts at 0 on processor 1  // Priority 1
  Task 2 starts at 0 on processor 2  // Priority 1
  Task 1 starts at 3 on processor 2  // Priority 2
  Task 3 starts at 4 on processor 1  // Priority 3
  ```

### 2. processOrders

- **Purpose**: Process restaurant orders across multiple cooking stations
- **Parameters**: Vector of OrderRequest (table_id, items, priority, order_time) and number of stations
- **Return**: Vector of Results containing {order_id, completion_time, station_id}
- **Example**:

  ```cpp
  Input: orders = {
    {1, {"steak", "salad"}, 2, 0},     // 30 units total
    {2, {"pasta"}, 1, 1},              // 15 units
    {3, {"soup", "dessert"}, 3, 2}     // 20 units
  }, stations = 2

  Output:
  Order 0 completed at 30 on station 1
  Order 1 completed at 16 on station 2
  Order 2 completed at 36 on station 2
  ```

<h2 align="center">Testing</h2>

1. Build and run:

```sh
make clean  # Clean previous builds
make all    # Compile all files
make run    # Execute the program
```

<h2 align="center">Restrictions</h2>

❌ Do not modify:

- Queue.hpp interface
- main.cpp test cases
- Project structure
- Build system

❌ Do not use:

- External libraries
- Global variables
- Additional data structures (except where specified)

<h2 align="center">Academic Integrity</h2>

- Individual work only
- No code sharing
- No plagiarism
- Violations result in zero grade

<h2 align="center">Submission</h2>

1. Test thoroughly
2. Clean build files: `make clean`
3. Send only the `Queue.cpp` file to the course portal

Good luck with your implementation!
