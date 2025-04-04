/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_ERESULT_H_
#define ESKILIB_ERESULT_H_

#ifdef __cplusplus
extern "C" {
#endif

enum eresult {
    E_FAILURE_BAD_STRING = -8,
    E_FAILURE_NOT_FOUND = -7,
    E_FAILURE_ZERO_LENGTH = -6,
    E_FAILURE_UNDERFLOW_PROTECTION = -5,
    E_FAILURE_OVERFLOW_PROTECTION = -4,
    E_FAILURE_FILE_OP = -3,
    E_FAILURE_MALLOC = -2,
    E_FAILURE_NULL_REFERENCE = -1,
    E_FAILURE = 0,
    E_SUCCESS = 1,
    E_NO_OP = 2,
    E_NO_OP_MAX_LIMIT_REACHED = 3
};

#ifdef __cplusplus
}
#endif

#endif // !ESKILIB_ERESULT_H_
