#include <stdio.h>
#include <stdlib.h>
struct Process 
{
    int id;
    int priority;
    int burst_time;
};
void priorityScheduling(struct Process processes[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
	{
        for (int j = 0; j < n - i - 1; j++) 
		{
            if (processes[j].priority < processes[j + 1].priority) 
			{
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    printf("Execution Order:\n");
    for (int i = 0; i < n; i++) {
    printf("Process %d (Priority %d, Burst Time %d)\n", processes[i].id, processes[i].priority, processes[i].burst_time);
    }
}
int main() 
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));
   for (int i = 0; i < n; i++)
	 {
        processes[i].id = i + 1;
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }
    priorityScheduling(processes, n);
    free(processes);
    return 0;
}

