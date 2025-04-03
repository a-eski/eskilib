/* Copyright (C) eskilib by Alex Eski 2024 */
/* This is free software under GPLv3 or higher. See LICENSE.md for more information */
/* etrie.h: a prefix tree/trie implementation useful for autocomplete implementations */

#ifndef ESKILIB_ETRIE_H_
#define ESKILIB_ETRIE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "estr.h"

#define ETRIE_LETTERS 96 // ascii printable characters 32-127

struct etrie;
typedef struct etrie etrie;

struct etrie {
	bool is_end_of_a_word;
	char letter;
	etrie* nodes[ETRIE_LETTERS];
};

struct etrie_Matches {
	uint_fast32_t count;
	estr* entries;
};
typedef struct etrie_Matches etrie_Matches;

static inline int etrie_index_get(char character) {
	return (int)character - ' ';
}

static inline char etrie_char_get(int position) {
	return (char)position + ' ';
}

etrie* etrie_malloc();

void etrie_free(etrie* tree);

void etrie_add(char* str, size_t len, etrie* tree);
void etrie_add_str(estr str, etrie* tree);
void etrie_add_multiple(estr* strs, int count, etrie* tree);

etrie* etrie_search(char* str, size_t len, etrie* tree);
etrie* etrie_search_str(estr str, etrie* tree);

// gets all matches based on a search into matches. returns matches_len;
size_t etrie_get(char* search,
		 size_t search_len,
		 char* matches[],
		 const uint_fast32_t max_match_len,
		 etrie* tree);

#ifdef __cplusplus
}
#endif

#endif // !ESKILIB_ETRIE_H_
