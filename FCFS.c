#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

int compareProcesses(const void *a, const void *b)
{
    struct Process *processA = (struct Process *)a;
    struct Process *processB = (struct Process *)b;
    if (processA->arrival_time != processB->arrival_time)
    {
        return processA->arrival_time - processB->arrival_time;
    }

    return processA->pid - processB->pid;
}

void main()
{
    int n, i;
    float total_wt = 0, total_tat = 0;

    printf("\n--- FCFS Scheduling Algorithm Implementation ---");
    printf("\n\nEnter the number of processes (N): ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("\n--- Enter Process Details ---\n");
    for (i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("Process P%d Arrival Time: ", processes[i].pid);
        scanf("%d", &processes[i].arrival_time);
        printf("Process P%d Burst Time: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    qsort(processes, n, sizeof(struct Process), compareProcesses);

    int current_time = 0;

    for (i = 0; i < n; i++)
    {

        if (processes[i].arrival_time > current_time)
        {
            processes[i].start_time = processes[i].arrival_time;
        }
        else
        {
            processes[i].start_time = current_time;
        }

        processes[i].completion_time = processes[i].start_time + processes[i].burst_time;

        current_time = processes[i].completion_time;

        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_wt += processes[i].waiting_time;
        total_tat += processes[i].turnaround_time;
    }

    printf("\n\n--- FCFS Scheduling Results ---\n");
    printf("+-------+-----+-----+-------+-----+-------+-------+\n");
    printf("| PID   | AT  | BT  | Start | CT  | TAT   | WT    |\n");
    printf("+-------+-----+-----+-------+-----+-------+-------+\n");

    for (i = 0; i < n; i++)
    {
        printf("| P%-5d | %-3d | %-3d | %-5d | %-3d | %-5d | %-5d |\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
    printf("+-------+-----+-----+-------+-----+-------+-------+\n");

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}
