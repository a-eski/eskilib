#ifndef ESKILIB_DEFINES_H_
#define ESKILIB_DEFINES_H_

// eskilib_nodiscard: an attribute qualifier wrapper for [[nodiscard]].
// If not using c2x/c23, does nothing, otherwise use [[nodiscard]] attribute.
// Useful to help with refactors and preventing bugs from not checking return values.

// IF YOU SEE AN ERROR BELOW:
// ignore the error function-like macro '__has_c_attribute' is not defined.
// it only shows up in header files when using this attribute with clangd when c2x/c23 not specified.

#if __has_c_attribute(nodiscard)
#if __STDC_VERSION__ >= 202000
#define eskilib_nodiscard [[nodiscard]]
#else
#define eskilib_nodiscard
#endif
#else
#define eskilib_nodiscard
#endif

#endif // !ESKILIB_DEFINES_H_
