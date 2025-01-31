#ifndef eski_error_handler_h
#define eski_error_handler_h

void eski_output_allocation_error_and_exit(char* errorMessage);

void eski_output_allocation_error_and_execute(char* errorMessage, void (*function)(void));

#endif /* !eski_error_handler_h */
