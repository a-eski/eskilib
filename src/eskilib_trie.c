/* Copyright (c) eskilib by Alex Eski 2024 */

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "eskilib_trie.h"
#include "eskilib_defines.h"

eskilib_nodiscard
struct eskilib_Trie* eskilib_trie_malloc() {
	struct eskilib_Trie* tree = calloc(1, sizeof(struct eskilib_Trie));
	if (!tree)
		return NULL;

	tree->is_end_of_a_word = false;
	return tree;
}

void eskilib_trie_free(struct eskilib_Trie* tree) {
	assert(tree);
	if (!tree) {
		return;
	}

	for (size_t i = 0; i < ESKILIB_TRIE_LETTERS; i++) {
		if (tree->nodes[i]) {
			eskilib_trie_free(tree->nodes[i]);
		}
	}
	free(tree);
}

void eskilib_trie_add(char* str, size_t len, struct eskilib_Trie* tree) {
	assert(str);
	assert(len > 0);
	assert(tree);

	int index = 0;

	for (size_t i = 0; i < len - 1; i++) { //str.len - 1 because it includes null terminator
		index = (int)str[i] - ' ';
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eskilib_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = str[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eskilib_trie_add_str(struct estr str, struct eskilib_Trie* tree) {
	assert(tree);
	assert(str.val);
	assert(str.len > 0);

	int index = 0;

	for (size_t i = 0; i < str.len - 1; i++) { //str.len - 1 because it includes null terminator
		index = eskilib_trie_index_get(str.val[i]);
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eskilib_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = str.val[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eskilib_trie_add_multiple(struct estr* strs, int count, struct eskilib_Trie* tree) {
	assert(tree && strs);

	for (int i = 0; i < count; i++) {
		eskilib_trie_add_str(strs[i], tree);
	}
}

eskilib_nodiscard
struct eskilib_Trie* eskilib_trie_search(char* str, size_t len, struct eskilib_Trie* tree) {
	assert(tree);
	assert(str);
	assert(len > 0);

	int index = 0;

	for (size_t i = 0; i < len - 1; i++) {
		index = eskilib_trie_index_get(str[i]);
		if (tree->nodes[index] == NULL) {
			return NULL;
		}

		tree = tree->nodes[index];
	}

	return tree;
}

eskilib_nodiscard
struct eskilib_Trie* eskilib_trie_search_str(struct estr str, struct eskilib_Trie* tree) {
	assert(tree);
	assert(str.val);
	assert(str.len > 0);

	int index = 0;

	for (size_t i = 0; i < str.len - 1; i++) {
		index = eskilib_trie_index_get(str.val[i]);
		if (tree->nodes[index] == NULL) {
			return NULL;
		}

		tree = tree->nodes[index];
	}

	return tree;
}

void eskilib_trie_match(char* matches[],
			size_t* str_pos,
			size_t* matches_position,
			const uint_fast32_t max_match_len,
			struct eskilib_Trie* tree) {
	for (uint_fast32_t i = 0; i < ESKILIB_TRIE_LETTERS; i++) {
		if (tree->nodes[i] != NULL) {
			if (matches[*matches_position] == NULL) {
				matches[*matches_position] = malloc(sizeof(char) * max_match_len);
				if (matches[*matches_position] == NULL) {
					return;
				}

				if (*str_pos > 0 && *matches_position > 0) {
					strcpy(matches[*matches_position], matches[*matches_position - 1]);
				}
			}

			matches[*matches_position][*str_pos] = tree->nodes[i]->letter;
			++*str_pos;
			matches[*matches_position][*str_pos] = '\0';

			if (tree->nodes[i]->is_end_of_a_word == true && *matches_position + 1 < max_match_len) {
				++*matches_position;
			}

			eskilib_trie_match(matches, str_pos, matches_position, max_match_len, tree->nodes[i]);

			if (matches[*matches_position] != NULL) {
				++*matches_position;
			}

			*str_pos = *str_pos - 1;
		}
	}
}

eskilib_nodiscard
size_t eskilib_trie_matches(char* matches[], const uint_fast32_t max_match_len, struct eskilib_Trie* tree) {
	size_t str_pos = 0;
	size_t matches_position = 0;

	eskilib_trie_match(matches, &str_pos, &matches_position, max_match_len, tree);

	return matches_position;
}

eskilib_nodiscard
size_t eskilib_trie_get(char* search,
			size_t search_len,
			char* matches[],
			const uint_fast32_t max_match_len,
			struct eskilib_Trie* tree) {
	struct eskilib_Trie *search_result = eskilib_trie_search(search, search_len, tree);
	if (search_result == NULL) {
		return 0;
	}

	return eskilib_trie_matches(matches, max_match_len, search_result);
}
