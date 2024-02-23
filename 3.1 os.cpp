#include <stdio.h>
#define P 5
#define R 3
int isSafe(int processes[], int available[], int max[][R], int allocation[][R]) 
{
    int need[P][R];
    for (int i = 0; i < P; i++)
    for (int j = 0; j < R; j++)
    need[i][j] = max[i][j] - allocation[i][j];
    int finish[P];
    for (int i = 0; i < P; i++)
    finish[i] = 0;
    int work[R];
    for (int i = 0; i < R; i++)
    work[i] = available[i];
    for (int i = 0; i < P; i++)
	{
        if (finish[i] == 0) 
		{
            int j;
            for (j = 0; j < R; j++) 
			{
                if (need[i][j] > work[j])
                    break;
            }
            if (j == R)
			{
                for (int k = 0; k < R; k++)
                work[k] += allocation[i][k];
                finish[i] = 1;
                i = -1;
            }
        }
    }
    for (int i = 0; i < P; i++)
	{
        if (finish[i] == 0)
            return 0; 
    }
    return 1; 
}
void allocateResources(int processes[], int available[], int max[][R], int allocation[][R], int request[][R], int pid) 
{
    for (int i = 0; i < R; i++) 
	{
        if (request[pid][i] > available[i]) 
		{
            printf("Process %d's request exceeds available resources. Request denied.\n", pid);
            return;
        }
    }
    for (int i = 0; i < R; i++) 
	{
        if (request[pid][i] > max[pid][i]) 
		{
            printf("Process %d's request exceeds maximum claim. Request denied.\n", pid);
            return;
        }
    }    for (int i = 0; i < R; i++) {
        available[i] -= request[pid][i];
        allocation[pid][i] += request[pid][i];
    }
    if (isSafe(processes, available, max, allocation))
	{
        printf("Request for resources by Process %d granted.\n", pid);
    }
	else 
	{
        for (int i = 0; i < R; i++) 
		{
            available[i] += request[pid][i];
            allocation[pid][i] -= request[pid][i];
        }
        printf("Request for resources by Process %d denied to avoid deadlock.\n", pid);
    }
}
int main() 
{
    int processes[P] = {0, 1, 2, 3, 4};
    int available[R] = {3, 3, 2};
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[P][R] = 
	{
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int request[P][R] = 
	{
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    };
    int pid = 1;
    allocateResources(processes, available, max, allocation, request, pid);
    return 0;
}

