#include "main.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(void){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	dbge(); 
    // Open a file to write to
    int file_fd = open("build/output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("open");
        return 1;
    }

    // Duplicate file_fd to stdout (file descriptor 1)
    if (dup2(file_fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(file_fd);
        return 1;
    }
	// close(STDOUT_FILENO); 

    // Now stdout is redirected to the file
    printf("This will be written to the file 'build/output.txt'.\n");

    // Close the file descriptor
    close(file_fd);

	return 0; 
}
