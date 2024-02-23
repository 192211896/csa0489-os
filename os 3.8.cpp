#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main() 
{
    int fd = creat("example_file.txt", 0644);
    if (fd == -1) 
	{
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
	else
	{
        printf("File created successfully.\n");
    }
    const char *message = "Hello, UNIX system calls!\n";
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) 
	{
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }
	else 
	{
        printf("Data written to file successfully.\n");
    }
    close(fd);
    fd = open("example_file.txt", O_RDONLY);
    if (fd == -1) 
	{
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) 
	{
        perror("Error reading from file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';
    printf("Data read from file:\n%s", buffer);
    close(fd);
    if (unlink("example_file.txt") == -1) {
        perror("Error removing file");
        exit(EXIT_FAILURE);
    } 
	else
	{
        printf("File removed successfully.\n");
    }
    return 0;
}

