#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include "eski_trie.h"

struct eski_Trie* eski_trie_malloc() {
	struct eski_Trie* tree = calloc(1, sizeof(struct eski_Trie));
	if (tree == NULL)
		return NULL;

	tree->is_end_of_a_word = false;
	return tree;
}

void eski_trie_free(struct eski_Trie* tree) {
	assert(tree != NULL);

	for (size_t i = 0; i < ESKI_TRIE_LETTERS; i++) {
		if (tree->nodes[i] != NULL)
			eski_trie_free(tree->nodes[i]);
		else
			continue;
	}
	free(tree);
}

void eski_trie_add(char* string, size_t length, struct eski_Trie* tree) {
	assert(string != NULL);
	assert(length > 0);
	assert(tree != NULL);

	int index = 0;

	for (size_t i = 0; i < length - 1; i++) { //string.length - 1 because it includes null terminator
		index = (int)string[i] - ' ';
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eski_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = string[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eski_trie_add_string(struct eski_String string, struct eski_Trie* tree) {
	assert(string.value != NULL);
	assert(string.length > 0);
	assert(tree != NULL);

	int index = 0;

	for (size_t i = 0; i < string.length - 1; i++) { //string.length - 1 because it includes null terminator
		index = (int)string.value[i] - ' ';
		if (tree->nodes[index] == NULL) {
			tree->nodes[index] = calloc(1, sizeof(struct eski_Trie));
			tree->nodes[index]->is_end_of_a_word = false;
			tree->nodes[index]->letter = string.value[i];
		}

		tree = tree->nodes[index];
	}

	tree->is_end_of_a_word = true;
}

void eski_trie_add_multiple(struct eski_String* strings, int count, struct eski_Trie* tree) {
	for (int i = 0; i < count; i++) {
		eski_trie_add_string(strings[i], tree);
	}
}

struct eski_Trie* eski_trie_search(char* string, size_t length, struct eski_Trie* tree) {
	assert(string != NULL);
	assert(length > 0);
	assert(tree != NULL);

	int index = 0;

	for (size_t i = 0; i < length - 1; i++) {
		index = (int)string[i] - ' ';
		if (tree->nodes[index] == NULL)
			return NULL;

		tree = tree->nodes[index];
	}

	if (tree != NULL)
		return tree;

	return NULL;
}

struct eski_Trie* eski_trie_search_string(struct eski_String string, struct eski_Trie* tree) {
	assert(string.value != NULL);
	assert(string.length > 0);
	assert(tree != NULL);

	int index = 0;

	for (size_t i = 0; i < string.length - 1; i++) {
		index = (int)string.value[i] - ' ';
		if (tree->nodes[index] == NULL)
			return NULL;

		tree = tree->nodes[index];
	}

	if (tree != NULL)
		return tree;

	return NULL;
}

void eski_trie_match(char* matches[],
				size_t* string_position,
				size_t* matches_position,
				const uint_fast32_t max_match_length,
				struct eski_Trie* tree) {
	for (uint_fast32_t i = 0; i < ESKI_TRIE_LETTERS; i++) {
		if (tree->nodes[i] != NULL) {
			if (matches[*matches_position] == NULL) {
				matches[*matches_position] = malloc(sizeof(char) * max_match_length);
				if (matches[*matches_position] == NULL)
					return;

				if (*string_position > 0 && *matches_position > 0)
					eski_string_copy(matches[*matches_position], matches[*matches_position - 1], *string_position);
			}

			matches[*matches_position][*string_position] = tree->nodes[i]->letter;
			++*string_position;
			matches[*matches_position][*string_position] = '\0';

			if (tree->nodes[i]->is_end_of_a_word == true && *matches_position + 1 < max_match_length)
				++*matches_position;

			eski_trie_match(matches, string_position, matches_position, max_match_length, tree->nodes[i]);

			if (matches[*matches_position] != NULL)
				++*matches_position;

			*string_position = *string_position - 1;
		}
	}
}

size_t eski_trie_matches(char* matches[], const uint_fast32_t max_match_length, struct eski_Trie* tree) {
	size_t string_position = 0;
	size_t matches_position = 0;

	eski_trie_match(matches, &string_position, &matches_position, max_match_length, tree);

	return matches_position;
}

size_t eski_trie_get(char* search,
				       size_t search_length,
				       char* matches[],
				       const uint_fast32_t max_match_length,
				       struct eski_Trie* tree) {
	struct eski_Trie *search_result = eski_trie_search(search, search_length, tree);
	if (search_result == NULL)
		return 0;

	return eski_trie_matches(matches, max_match_length, search_result);
}

int eski_trie_map_char(char character) {
	return (int)character - ' ';
}

char eski_trie_map_position(int position) {
	return (char)position + ' ';
}

