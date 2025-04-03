/* Copyright (C) eskilib by Alex Eski 2024 */
/* This is free software under GPLv3 or higher. See LICENSE.md for more information */
/* etrie.h: a prefix tree/trie implementation useful for autocomplete implementations */

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "etrie.h"
#include "edefs.h"

enodiscard
etrie* etrie_malloc() {
	etrie* trie = calloc(1, sizeof(etrie));
	if (!trie)
		return NULL;

	trie->is_end_of_a_word = false;
	return trie;
}

void etrie_free(etrie* trie)
{
	assert(trie);
	if (!trie) {
		return;
	}

	for (size_t i = 0; i < ETRIE_LETTERS; i++) {
		if (trie->nodes[i]) {
			etrie_free(trie->nodes[i]);
		}
	}
	free(trie);
}

void etrie_add(char* str, size_t len, etrie* trie)
{
	assert(str);
	assert(len > 0);
	assert(trie);

	int index = 0;

	for (size_t i = 0; i < len - 1; i++) { //str.len - 1 because it includes null terminator
		index = (int)str[i] - ' ';
		if (trie->nodes[index] == NULL) {
			trie->nodes[index] = calloc(1, sizeof(etrie));
			trie->nodes[index]->is_end_of_a_word = false;
			trie->nodes[index]->letter = str[i];
		}

		trie = trie->nodes[index];
	}

	trie->is_end_of_a_word = true;
}

void etrie_add_str(estr str, etrie* trie)
{
	assert(trie && str.val && str.len);

	int index = 0;
	for (size_t i = 0; i < str.len - 1; i++) { //str.len - 1 because it includes null terminator
		index = etrie_index_get(str.val[i]);
		if (trie->nodes[index] == NULL) {
			trie->nodes[index] = calloc(1, sizeof(etrie));
			trie->nodes[index]->is_end_of_a_word = false;
			trie->nodes[index]->letter = str.val[i];
		}

		trie = trie->nodes[index];
	}

	trie->is_end_of_a_word = true;
}

void etrie_add_multiple(estr* strs, int count, etrie* trie)
{
	assert(trie && strs && (*strs).val);

        for (int i = 0; i < count; i++) {
		etrie_add_str(strs[i], trie);
	}
}

enodiscard
etrie* etrie_search(char* str, size_t len, etrie* trie)
{
	assert(trie && str && len);

	int index = 0;
	for (size_t i = 0; i < len - 1; i++) {
		index = etrie_index_get(str[i]);
		if (trie->nodes[index] == NULL) {
			return NULL;
		}

		trie = trie->nodes[index];
	}

	return trie;
}

enodiscard
etrie* etrie_search_str(estr str, etrie* trie)
{
	assert(trie && str.val && str.len);

	int index = 0;
	for (size_t i = 0; i < str.len - 1; i++) {
		index = etrie_index_get(str.val[i]);
		if (trie->nodes[index] == NULL) {
			return NULL;
		}

		trie = trie->nodes[index];
	}

	return trie;
}

void etrie_match(char* matches[],
		 size_t* str_pos,
		 size_t* matches_position,
		 const uint_fast32_t max_match_len,
		 etrie* trie)
{
	for (uint_fast32_t i = 0; i < ETRIE_LETTERS; i++) {
		if (trie->nodes[i] != NULL) {
			if (matches[*matches_position] == NULL) {
				matches[*matches_position] = malloc(sizeof(char) * max_match_len);
				if (matches[*matches_position] == NULL) {
					return;
				}

				if (*str_pos > 0 && *matches_position > 0) {
					strcpy(matches[*matches_position], matches[*matches_position - 1]);
				}
			}

			matches[*matches_position][*str_pos] = trie->nodes[i]->letter;
			++*str_pos;
			matches[*matches_position][*str_pos] = '\0';

			if (trie->nodes[i]->is_end_of_a_word == true && *matches_position + 1 < max_match_len) {
				++*matches_position;
			}

			etrie_match(matches, str_pos, matches_position, max_match_len, trie->nodes[i]);

			if (matches[*matches_position] != NULL) {
				++*matches_position;
			}

			*str_pos = *str_pos - 1;
		}
	}
}

enodiscard
size_t etrie_matches(char* matches[], const uint_fast32_t max_match_len, etrie* trie)
{
	size_t str_pos = 0;
	size_t matches_position = 0;

	etrie_match(matches, &str_pos, &matches_position, max_match_len, trie);

	return matches_position;
}

enodiscard
size_t etrie_get(char* search,
		 size_t search_len,
		 char* matches[],
		 const uint_fast32_t max_match_len,
		 etrie* trie)
{
	etrie *search_result = etrie_search(search, search_len, trie);
	if (search_result == NULL) {
		return 0;
	}

	return etrie_matches(matches, max_match_len, search_result);
}
