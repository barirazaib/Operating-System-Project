#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_ACCOUNTS 100
#define MAX_PROCESSES 50
#define MEMORY_SIZE 16
#define PAGE_SIZE 4
#define NUM_PAGES (MEMORY_SIZE / PAGE_SIZE)
#define TIME_QUANTUM 2

// IPC Message Structure
struct message {
    long msg_type;
    char content[100];
};

// Process Table Entry
typedef struct {
    int transaction_id;
    char operation[10];  // "Deposit" or "Withdraw"
    int account_id;
    int amount;
    int burst_time;      // Time required for execution
    int remaining_time;  // Time left for execution
    int waiting_time;    // Time spent waiting in the queue
    int turnaround_time; // Time from creation to termination
    char status[20];     // "Running", "Waiting", "Terminated"
} ProcessTableEntry;

// Global Variables
int accounts[MAX_ACCOUNTS] = {0};       // Array to store account balances
sem_t account_mutex[MAX_ACCOUNTS];     // Semaphore for account synchronization
ProcessTableEntry process_table[MAX_PROCESSES]; // Process table
int process_count = 0;                 // Number of active processes

// Message Queue ID
int msg_queue_id;

// Function Prototypes
void create_transaction_process(const char *operation, int account_id, int amount, int burst_time);
void round_robin_scheduling();
void display_process_table();
void execute_transaction(ProcessTableEntry *process);
void send_message(const char *message_content);
void receive_message();
void create_account(int customer_id, int initial_balance);
void deposit(int account_id, int amount);
void withdraw(int account_id, int amount);
void check_balance(int account_id);