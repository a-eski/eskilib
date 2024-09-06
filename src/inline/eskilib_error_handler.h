#ifndef eskilib_error_handler_h
#define eskilib_error_handler_h

void eskilib_output_allocation_error_and_exit(char* errorMessage);

void eskilib_output_allocation_error_and_execute(char* errorMessage, void (*function)());

#endif /* !eskilib_error_handler_h */

