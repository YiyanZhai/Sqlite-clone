#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** define InputBuffer as a small wrapper around the 
    state we need to store to interact with getline(). **/
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

/** print_prompt() prints a prompt to the user.
    We do this before reading each line of input. **/
void print_prompt() { printf("db > "); }

void read_input(InputBuffer* input_buffer) {
    
    // We tell getline to store the read line in input_buffer->buffer 
    // and the size of the allocated buffer in input_buffer->buffer_length.
    // buffer starts as null, so getline allocates enough memory to hold the 
    // line of input and makes buffer point to it.
    ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
       
    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // We store the return value in input_buffer->input_length.
    // Ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();

    // the infinite loop in main function
    while(true) {
        // print the prompt
        print_prompt();

        // get a line of input
        read_input(input_buffer);

        // processes the line of input
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            // exit
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }

    }
}