#ifndef eski_defines_h
#define eski_defines_h

// eski_nodiscard: an attribute qualifier wrapper for [[nodiscard]].
// If not using c2x/c23, does nothing, otherwise use [[nodiscard]] attribute.
// Useful to help with refactors and preventing bugs from not checking return values.

// IF YOU SEE AN ERROR BELOW:
// ignore the error function-like macro '__has_c_attribute' is not defined
// it only shows up in header files when using this attribute

#if __has_c_attribute(nodiscard)
#if __STDC_VERSION__ >= 202000
#define eski_nodiscard [[nodiscard]]
#else
#define eski_nodiscard
#endif
#else
#define eski_nodiscard
#endif

#endif // !eski_defines_h
