#include <stdio.h>
#include <stdlib.h>
struct MemoryBlock 
{
    int id;          
    int size;        
    int allocated;   
};
void initializeMemory(struct MemoryBlock memory[], int numBlocks);
void bestFit(struct MemoryBlock memory[], int numBlocks, int requestSize);
void displayMemory(struct MemoryBlock memory[], int numBlocks);
int main() 
{
   int numBlocks = 5;
   int memorySize = 100;
   struct MemoryBlock memory[numBlocks];
    initializeMemory(memory, numBlocks);
    printf("Initial Memory State:\n");
    displayMemory(memory, numBlocks);
    bestFit(memory, numBlocks, 30);
    printf("\nFinal Memory State:\n");
    displayMemory(memory, numBlocks);
    return 0;
}
void initializeMemory(struct MemoryBlock memory[], int numBlocks) 
{
    for (int i = 0; i < numBlocks; i++) 
	{
        memory[i].id = i + 1;
        memory[i].size = rand() % 20 + 1;  
        memory[i].allocated = 0;           
    }
}
void bestFit(struct MemoryBlock memory[], int numBlocks, int requestSize) 
{
    int bestFitIndex = -1;
    int bestFitSize = -1;
    for (int i = 0; i < numBlocks; i++) 
	{
        if (!memory[i].allocated && memory[i].size >= requestSize) 
		{
            if (bestFitSize == -1 || memory[i].size < bestFitSize) 
			{
                bestFitIndex = i;
                bestFitSize = memory[i].size;
            }
        }
    }
    if (bestFitIndex != -1) 
	{
        memory[bestFitIndex].allocated = 1;
        printf("Allocated %d units of memory to Process %d using Best Fit.\n", requestSize, memory[bestFitIndex].id);
    } 
	else
	{
        printf("Memory allocation failed for Process. No suitable block found using Best Fit.\n");
    }
}
void displayMemory(struct MemoryBlock memory[], int numBlocks) 
{
    printf("Block\tSize\tAllocated\n");
    for (int i = 0; i < numBlocks; i++) 
	{
        printf("%d\t%d\t%s\n", memory[i].id, memory[i].size, (memory[i].allocated ? "Yes" : "No"));
    }
}

