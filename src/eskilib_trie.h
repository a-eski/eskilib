/* Copyright (c) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_TRIE_H_
#define ESKILIB_TRIE_H_

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "estr.h"

#define ESKILIB_TRIE_LETTERS 96 // ascii printable characters 32-127

// prefix tree for storing autocomplete posibilities
struct eskilib_Trie;

struct eskilib_Trie {
	bool is_end_of_a_word;
	char letter;
	struct eskilib_Trie* nodes[ESKILIB_TRIE_LETTERS];
};

struct eskilib_Trie_Matches {
	uint_fast32_t count;
	struct estr* entries;
};

static inline int eskilib_trie_index_get(char character) {
	return (int)character - ' ';
}

static inline char eskilib_trie_char_get(int position) {
	return (char)position + ' ';
}

struct eskilib_Trie* eskilib_trie_malloc();

void eskilib_trie_free(struct eskilib_Trie* tree);

void eskilib_trie_add(char* str, size_t len, struct eskilib_Trie* tree);
void eskilib_trie_add_str(struct estr str, struct eskilib_Trie* tree);
void eskilib_trie_add_multiple(struct estr* strs, int count, struct eskilib_Trie* tree);

struct eskilib_Trie* eskilib_trie_search(char* str, size_t len, struct eskilib_Trie* tree);
struct eskilib_Trie* eskilib_trie_search_str(struct estr str, struct eskilib_Trie* tree);

// gets all matches based on a search into matches. returns matches_len;
size_t eskilib_trie_get(char* search,
			size_t search_len,
			char* matches[],
			const uint_fast32_t max_match_len,
			struct eskilib_Trie* tree);

int eskilib_trie_index_get(char character);
char eskilib_trie_char_get(int position);

#endif // !ESKILIB_TRIE_H_
