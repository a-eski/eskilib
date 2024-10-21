#ifndef eskilib_types_h
#define eskilib_types_h

enum eskilib_Result {
	N_ZERO_LENGTH = -5,
	N_OVERFLOW_PROTECTION = -4,
	N_FAILURE_FILE_OP = -3,
	N_FAILURE_MALLOC = -2,
	N_FAILURE_NULL_REFERENCE = -1,
	N_FAILURE = 0,
	N_SUCCESS = 1,
	N_HISTORY_MAX_REACHED = 2
};

#endif // !eskilib_types_h

