// Create a Transaction Process
void create_transaction_process(const char *operation, int account_id, int amount, int burst_time) {
    if (process_count >= MAX_PROCESSES) {
        printf("Error: Maximum number of processes reached.\n");
        return;
    }

    // Add process to the process table
    process_table[process_count].transaction_id = process_count + 1;
    strcpy(process_table[process_count].operation, operation);
    process_table[process_count].account_id = account_id;
    process_table[process_count].amount = amount;
    process_table[process_count].burst_time = burst_time;
    process_table[process_count].remaining_time = burst_time;
    process_table[process_count].waiting_time = 0;
    process_table[process_count].turnaround_time = 0;
    strcpy(process_table[process_count].status, "Waiting");

    printf("Transaction Process %d created: %s %d on Account %d\n",
           process_table[process_count].transaction_id,
           operation, amount, account_id);

    process_count++;
}

// Execute a Transaction (Simulates Deposits/Withdrawals)
void execute_transaction(ProcessTableEntry *process) {
    sem_wait(&account_mutex[process->account_id]); // Lock the account for transaction
    if (strcmp(process->operation, "Deposit") == 0) {
        accounts[process->account_id] += process->amount;
        printf("Deposited %d to account %d. New balance: %d\n",
               process->amount, process->account_id, accounts[process->account_id]);
    } else if (strcmp(process->operation, "Withdraw") == 0) {
        if (accounts[process->account_id] < process->amount) {
            printf("Error: Insufficient funds in account %d.\n", process->account_id);
        } else {
            accounts[process->account_id] -= process->amount;
            printf("Withdrawn %d from account %d. New balance: %d\n",
                   process->amount, process->account_id, accounts[process->account_id]);
        }
    }
    sem_post(&account_mutex[process->account_id]); // Unlock the account
}

// Round Robin Scheduling
void round_robin_scheduling() {
    int time = 0, completed = 0;
    printf("\nGantt Chart:\n|");
    while (completed < process_count) {
        for (int i = 0; i < process_count; i++) {
            if (process_table[i].remaining_time > 0) {
                printf(" P%d (%d-%d) |", process_table[i].transaction_id, time,
                       time + (process_table[i].remaining_time > TIME_QUANTUM ? TIME_QUANTUM : process_table[i].remaining_time));

                int execution_time = process_table[i].remaining_time > TIME_QUANTUM ? TIME_QUANTUM : process_table[i].remaining_time;
                process_table[i].remaining_time -= execution_time;
                time += execution_time;

                if (process_table[i].remaining_time == 0) {
                    process_table[i].turnaround_time = time;
                    strcpy(process_table[i].status, "Terminated");
                    completed++;
                }
            }
        }
    }
    printf("\n");

    // Calculate metrics
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < process_count; i++) {
        process_table[i].waiting_time = process_table[i].turnaround_time - process_table[i].burst_time;
        total_waiting_time += process_table[i].waiting_time;
        total_turnaround_time += process_table[i].turnaround_time;
    }

    printf("\nProcess Metrics:\n");
    printf("ID\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < process_count; i++) {
        printf("%d\t%d\t%d\t%d\n", process_table[i].transaction_id, process_table[i].burst_time,
               process_table[i].waiting_time, process_table[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / process_count);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / process_count);
    printf("CPU Utilization: %.2f%%\n", (total_turnaround_time / time) * 100);
}
