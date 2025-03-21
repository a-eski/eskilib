#ifndef ESKILIB_ERROR_HANDLER_H_
#define ESKILIB_ERROR_HANDLER_H_

void eskilib_output_allocation_error_and_exit(char* errorMessage);

void eskilib_output_allocation_error_and_execute(char* errorMessage, void (*function)(void));

#endif /* !ESKILIB_ERROR_HANDLER_H_ */
