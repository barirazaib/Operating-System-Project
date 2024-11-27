# OS Banking System

A simulated banking system designed to demonstrate key concepts of Operating Systems, such as process synchronization, mutual exclusion, deadlock prevention, and fairness. The system manages multiple processes (representing banking operations) interacting with shared memory using semaphores.

## Features

- **Process Synchronization**: Handles concurrent access to shared resources.
- **Deadlock-Free Design**: Implements mechanisms to prevent deadlocks.
- **Fairness**: Ensures no process is starved and all processes are executed in the correct order.
- **Banking Operations**:
  - **Process A**: Reads or stores customer data.
  - **Process B**: Writes or modifies customer data.
  - **Process C**: Executes after both A and B are completed.

## Project Overview

This project simulates three types of banking operations using shared memory and semaphores:

1. **Process A**: Responsible for reading or storing customer data.
2. **Process B**: Handles writing or modifying customer data.
3. **Process C**: Depends on the completion of Process A and Process B.

### Synchronization Constraints

- **Mutual Exclusion**: Only one process can access shared memory at a time.
- **Execution Order**: Process C executes only after A and B complete.
- **Deadlock Prevention**: Ensures smooth execution without deadlock.
- **Fairness**: All processes get equal opportunity to access shared memory.

---

## Technologies Used

- **Programming Language**: C/C++ (or your preferred language)
- **Synchronization Tool**: Semaphores
- **OS Concepts**: Process scheduling, resource allocation, synchronization

---

## How to Run the Project

### Prerequisites

1. A C/C++ compiler (e.g., GCC)
2. Basic understanding of semaphores and process synchronization

### Steps to Run

1. Clone this repository:
   ```bash
   git clone https://github.com/your-repo/os-banking-system.git
   cd os-banking-system
   gcc -o banking_system banking_system.c -pthread
   ./banking_system
