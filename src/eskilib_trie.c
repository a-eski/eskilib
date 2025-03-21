/* Copyright (c) eskilib by Alex Eski 2024 */

#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "eskilib_trie.h"

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

void eskilib_trie_add(char* string, size_t length, struct eskilib_Trie* tree) {
	assert(string);
	assert(length > 0);
	assert(tree);

	int index = 0;

	for (size_t i = 0; i < length - 1; i++) { //string.length - 1 because it includes null terminator
		index = (int)string[i] - ' ';
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eskilib_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = string[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eskilib_trie_add_string(struct eskilib_String string, struct eskilib_Trie* tree) {
	assert(tree);
	assert(string.value);
	assert(string.length > 0);

	int index = 0;

	for (size_t i = 0; i < string.length - 1; i++) { //string.length - 1 because it includes null terminator
		index = eskilib_trie_index_get(string.value[i]);
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eskilib_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = string.value[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eskilib_trie_add_multiple(struct eskilib_String* strings, int count, struct eskilib_Trie* tree) {
	assert(tree && strings);

	for (int i = 0; i < count; i++) {
		eskilib_trie_add_string(strings[i], tree);
	}
}

struct eskilib_Trie* eskilib_trie_search(char* string, size_t length, struct eskilib_Trie* tree) {
	assert(tree);
	assert(string);
	assert(length > 0);

	int index = 0;

	for (size_t i = 0; i < length - 1; i++) {
		index = eskilib_trie_index_get(string[i]);
		if (tree->nodes[index] == NULL) {
			return NULL;
		}

		tree = tree->nodes[index];
	}

	return tree;
}

struct eskilib_Trie* eskilib_trie_search_string(struct eskilib_String string, struct eskilib_Trie* tree) {
	assert(tree);
	assert(string.value);
	assert(string.length > 0);

	int index = 0;

	for (size_t i = 0; i < string.length - 1; i++) {
		index = eskilib_trie_index_get(string.value[i]);
		if (tree->nodes[index] == NULL) {
			return NULL;
		}

		tree = tree->nodes[index];
	}

	return tree;
}

void eskilib_trie_match(char* matches[],
				size_t* string_position,
				size_t* matches_position,
				const uint_fast32_t max_match_length,
				struct eskilib_Trie* tree) {
	for (uint_fast32_t i = 0; i < ESKILIB_TRIE_LETTERS; i++) {
		if (tree->nodes[i] != NULL) {
			if (matches[*matches_position] == NULL) {
				matches[*matches_position] = malloc(sizeof(char) * max_match_length);
				if (matches[*matches_position] == NULL) {
					return;
				}

				if (*string_position > 0 && *matches_position > 0) {
					strcpy(matches[*matches_position], matches[*matches_position - 1]);
				}
			}

			matches[*matches_position][*string_position] = tree->nodes[i]->letter;
			++*string_position;
			matches[*matches_position][*string_position] = '\0';

			if (tree->nodes[i]->is_end_of_a_word == true && *matches_position + 1 < max_match_length) {
				++*matches_position;
			}

			eskilib_trie_match(matches, string_position, matches_position, max_match_length, tree->nodes[i]);

			if (matches[*matches_position] != NULL) {
				++*matches_position;
			}

			*string_position = *string_position - 1;
		}
	}
}

size_t eskilib_trie_matches(char* matches[], const uint_fast32_t max_match_length, struct eskilib_Trie* tree) {
	size_t string_position = 0;
	size_t matches_position = 0;

	eskilib_trie_match(matches, &string_position, &matches_position, max_match_length, tree);

	return matches_position;
}

size_t eskilib_trie_get(char* search,
				       size_t search_length,
				       char* matches[],
				       const uint_fast32_t max_match_length,
				       struct eskilib_Trie* tree) {
	struct eskilib_Trie *search_result = eskilib_trie_search(search, search_length, tree);
	if (search_result == NULL) {
		return 0;
	}

	return eskilib_trie_matches(matches, max_match_length, search_result);
}
