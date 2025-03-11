#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

int main(int argc, char *argv[]){
	dbge(); 
    int pipe_fd[2];  // Array to hold the pipe's file descriptors
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork(); // Create a child process
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipe_fd[0]); // Close the read end of the pipe
// #define __test__ 
#ifdef __test__
        int tmpfd=
#endif
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to the pipe's write end
        close(pipe_fd[1]); // Close the original write end

        // Run the command (e.g., ls -l)
#ifdef __test__
		char buf[16]; 
		sprintf(buf, "tmpfd(%d)", tmpfd); 
        execlp("echo", "echo", buf, NULL);
#else
        execlp("ls", "ls", "-l", NULL);
#endif
        perror("execlp"); // If execlp fails
        exit(1);
    } else { // Parent process
        close(pipe_fd[1]); // Close the write end of the pipe

        // Open a file for writing
        int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file_fd < 0) {
            perror("open");
            return 1;
        }

        // Read from the pipe and write to the file
        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            write(file_fd, buffer, bytes_read);
        }

        close(pipe_fd[0]); // Close the read end of the pipe
        close(file_fd);    // Close the file
    }

    exit(EXIT_SUCCESS);
}

