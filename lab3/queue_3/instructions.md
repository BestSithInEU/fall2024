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

1. `processEmergencyRoom`: Simulate an emergency room processing patients with different severity levels
2. `processCustomerService`: Handle customer service requests matching them with appropriate representatives

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

### 1. processEmergencyRoom

- **Purpose**: Simulate an emergency room processing patients with different severity levels and room requirements
- **Parameters**: Vector of `Patient` objects and vector of available `Room` objects
- **Return**: Vector of `Result` containing `{patient_id, treatment_start_time, room_id}`
- **Example**:

  ```cpp
  Input:
  patients = {
    {1, 0, 120, 0, "ICU"},       // {severity, arrival, treatment_time, id, room_type}
    {2, 1, 60, 1, "Emergency"},
    {1, 2, 90, 2, "ICU"},
    {3, 3, 45, 3, "General"},
    {4, 4, 30, 4, "General"}
  }
  rooms = {
    {"ICU", 1},
    {"ICU", 2},
    {"Emergency", 3},
    {"General", 4}
  }

  Output:
  Patient 0 assigned to Room 1 starting at time 0
  Patient 2 assigned to Room 2 starting at time 2
  Patient 1 assigned to Room 3 starting at time 1
  Patient 3 assigned to Room 4 starting at time 3
  Patient 4 assigned to Room 4 starting at time 48
  ```

### 2. processCustomerService

- **Purpose**: Handle customer service requests matching them with appropriate representatives
- **Parameters**: Vector of `ServiceRequest` objects and vector of available `Representative` objects
- **Return**: Vector of `Result` containing `{request_id, handling_start_time, representative_id}`
- **Example**:

  ```cpp
  	Input:
  requests = {
    {1, "Technical", 30, 0, 0},   // {priority, expertise, estimated_time, arrival_time, id}
    {2, "Billing", 20, 1, 1},
    {1, "Technical", 25, 2, 2},
    {3, "General", 15, 3, 3}
  }
  representatives = {
    {{"Technical", "General"}, 1},
    {{"Billing", "General"}, 2},
    {{"Technical", "Billing", "General"}, 3}
  }

  Output:
  Request 0 assigned to Representative 1 starting at time 0
  Request 2 assigned to Representative 3 starting at time 2
  Request 1 assigned to Representative 2 starting at time 1
  Request 3 assigned to Representative 2 starting at time 21
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
