#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../eskilib_trie.h"
#include "../eskilib_test.h"
#include "../estr.h"

void eskilib_trie_add_len_mismatch_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str = { .val = "and", .len = 3 };
	eskilib_trie_add(str.val, str.len, tree);

	//not crashing is a test pass here

	eskilib_trie_free(tree);
}

void eskilib_trie_add_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str = { .val = "and", .len = 4 };
	eskilib_trie_add(str.val, str.len, tree);

	// sanity check: unrelated letters are null
	eskilib_assert(tree->nodes[eskilib_trie_index_get('b')] == NULL);
	eskilib_assert(tree->nodes[eskilib_trie_index_get('c')] == NULL);
	eskilib_assert(tree->nodes[eskilib_trie_index_get('d')] == NULL);
	eskilib_assert(tree->nodes[eskilib_trie_index_get('e')] == NULL);

	struct eskilib_Trie* first_node = tree->nodes[eskilib_trie_index_get('a')];
	eskilib_assert(first_node != NULL);
	eskilib_assert(first_node->is_end_of_a_word == false);
	eskilib_assert(first_node->letter == 'a')
	eskilib_assert(first_node->nodes[eskilib_trie_index_get('b')] == NULL); //sanity check
	struct eskilib_Trie* second_node = first_node->nodes[eskilib_trie_index_get('n')];
	eskilib_assert(second_node != NULL);
	eskilib_assert(second_node->is_end_of_a_word == false);
	eskilib_assert(second_node->letter == 'n')
	eskilib_assert(second_node->nodes[eskilib_trie_index_get('b')] == NULL); //sanity check
	struct eskilib_Trie* third_node = second_node->nodes[eskilib_trie_index_get('d')];
	eskilib_assert(third_node != NULL);
	eskilib_assert(third_node->is_end_of_a_word == true);
	eskilib_assert(third_node->letter == 'd');
	eskilib_assert(third_node->nodes[eskilib_trie_index_get('b')] == NULL); //sanity check

	eskilib_trie_free(tree);
}

void eskilib_trie_add_duplicate_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str = { .val = "and", .len = 4 };
	eskilib_trie_add(str.val, str.len, tree);
	eskilib_trie_add_str(str, tree);

	struct eskilib_Trie* first_node = tree->nodes[eskilib_trie_index_get('a')];
	eskilib_assert(first_node != NULL);
	eskilib_assert(first_node->is_end_of_a_word == false);
	eskilib_assert(first_node->letter == 'a')

	struct eskilib_Trie* second_node = first_node->nodes[eskilib_trie_index_get('n')];
	eskilib_assert(second_node != NULL);
	eskilib_assert(second_node->is_end_of_a_word == false);
	eskilib_assert(second_node->letter == 'n');

	struct eskilib_Trie* third_node = second_node->nodes[eskilib_trie_index_get('d')];
	eskilib_assert(third_node != NULL);
	eskilib_assert(third_node->is_end_of_a_word == true);
	eskilib_assert(third_node->letter == 'd');

	eskilib_trie_free(tree);
}

void eskilib_trie_add_multiple_unrelated_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str_one = { .val = "ls", .len = 3 };
	eskilib_trie_add(str_one.val, str_one.len, tree);
	struct estr str_two = { .val = "echo", .len = 5 };
	eskilib_trie_add_str(str_two, tree);

	struct eskilib_Trie* ls_first_node = tree->nodes[eskilib_trie_index_get('l')];
	eskilib_assert(ls_first_node != NULL);
	eskilib_assert(ls_first_node->is_end_of_a_word == false);
	eskilib_assert(ls_first_node->letter == 'l');
	struct eskilib_Trie* ls_second_node = ls_first_node->nodes[eskilib_trie_index_get('s')];
	eskilib_assert(ls_second_node != NULL);
	eskilib_assert(ls_second_node->is_end_of_a_word == true);
	eskilib_assert(ls_second_node->letter == 's');

	struct eskilib_Trie* first_node = tree->nodes[eskilib_trie_index_get('e')];
	eskilib_assert(first_node != NULL);
	eskilib_assert(first_node->is_end_of_a_word == false);
	eskilib_assert(first_node->letter == 'e');
	struct eskilib_Trie* second_node = first_node->nodes[eskilib_trie_index_get('c')];
	eskilib_assert(second_node != NULL);
	eskilib_assert(second_node->is_end_of_a_word == false);
	eskilib_assert(second_node->letter == 'c');
	struct eskilib_Trie* third_node = second_node->nodes[eskilib_trie_index_get('h')];
	eskilib_assert(third_node != NULL);
	eskilib_assert(third_node->is_end_of_a_word == false);
	eskilib_assert(third_node->letter == 'h');
	struct eskilib_Trie* fourth_node = third_node->nodes[eskilib_trie_index_get('o')];
	eskilib_assert(fourth_node != NULL);
	eskilib_assert(fourth_node->is_end_of_a_word == true);
	eskilib_assert(fourth_node->letter == 'o');

	eskilib_trie_free(tree);
}

void eskilib_trie_add_multiple_related_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str_one = { .val = "gene", .len = 5 };
	eskilib_trie_add(str_one.val, str_one.len, tree);
	struct estr str_two = { .val = "genetic", .len = 8 };
	eskilib_trie_add_str(str_two, tree);
	struct estr str_three = { .val = "genius", .len = 7 };
	eskilib_trie_add_str(str_three, tree);

	// gene
	struct eskilib_Trie* first_node = tree->nodes[eskilib_trie_index_get('g')];
	eskilib_assert(first_node != NULL);
	eskilib_assert(first_node->is_end_of_a_word == false);
	eskilib_assert(first_node->letter == 'g');
	struct eskilib_Trie* second_node = first_node->nodes[eskilib_trie_index_get('e')];
	eskilib_assert(second_node != NULL);
	eskilib_assert(second_node->is_end_of_a_word == false);
	eskilib_assert(second_node->letter == 'e');
	struct eskilib_Trie* third_node = second_node->nodes[eskilib_trie_index_get('n')];
	eskilib_assert(third_node != NULL);
	eskilib_assert(third_node->is_end_of_a_word == false);
	eskilib_assert(third_node->letter == 'n');
	struct eskilib_Trie* fourth_node = third_node->nodes[eskilib_trie_index_get('e')];
	eskilib_assert(fourth_node != NULL);
	eskilib_assert(fourth_node->is_end_of_a_word == true);
	eskilib_assert(fourth_node->letter == 'e');

	// genetic
	struct eskilib_Trie* genetic_fifth_node = fourth_node->nodes[eskilib_trie_index_get('t')];
	eskilib_assert(genetic_fifth_node  != NULL);
	eskilib_assert(genetic_fifth_node->is_end_of_a_word == false);
	eskilib_assert(genetic_fifth_node->letter == 't');
	struct eskilib_Trie* genetic_sixth_node = genetic_fifth_node->nodes[eskilib_trie_index_get('i')];
	eskilib_assert(genetic_sixth_node != NULL);
	eskilib_assert(genetic_sixth_node->is_end_of_a_word == false);
	eskilib_assert(genetic_sixth_node->letter == 'i');
	struct eskilib_Trie* genetic_seventh_node = genetic_sixth_node->nodes[eskilib_trie_index_get('c')];
	eskilib_assert(genetic_seventh_node != NULL);
	eskilib_assert(genetic_seventh_node->is_end_of_a_word == true);
	eskilib_assert(genetic_seventh_node->letter == 'c');

	// genius
	struct eskilib_Trie* genius_fourth_node = third_node->nodes[eskilib_trie_index_get('i')];
	eskilib_assert(genius_fourth_node != NULL);
	eskilib_assert(genius_fourth_node->is_end_of_a_word == false);
	eskilib_assert(genius_fourth_node->letter == 'i');
	struct eskilib_Trie* genius_fifth_node = genius_fourth_node->nodes[eskilib_trie_index_get('u')];
	eskilib_assert(genius_fifth_node != NULL);
	eskilib_assert(genius_fifth_node->is_end_of_a_word == false);
	eskilib_assert(genius_fifth_node->letter == 'u');
	struct eskilib_Trie* genius_sixth_node = genius_fifth_node->nodes[eskilib_trie_index_get('s')];
	eskilib_assert(genius_sixth_node != NULL);
	eskilib_assert(genius_sixth_node->is_end_of_a_word == true);
	eskilib_assert(genius_sixth_node->letter == 's');

	eskilib_trie_free(tree);
}

void eskilib_trie_search_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str_one = { .val = "gene", .len = 5 };
	eskilib_trie_add(str_one.val, str_one.len, tree);
	struct estr str_two = { .val = "genetic", .len = 8 };
	eskilib_trie_add(str_two.val, str_two.len, tree);
	struct estr str_three = { .val = "genius", .len = 7 };
	eskilib_trie_add_str(str_three, tree);

	struct estr str_search = { .val = "gen", .len = 4 };
	struct eskilib_Trie* result = eskilib_trie_search(str_search.val, str_search.len, tree);
	eskilib_assert(result != NULL);
	struct eskilib_Trie* result_e = result->nodes[eskilib_trie_index_get('e')];
	eskilib_assert(result_e != NULL);
	eskilib_assert(result_e->is_end_of_a_word == true);
	eskilib_assert(result_e->letter == 'e');

	eskilib_trie_free(tree);
}

void eskilib_trie_search_commands_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	eskilib_trie_add_str((struct estr){ .val = "ls", .len = 3 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort | wc -c", .len = 18 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls > t.txt", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "cat t.txt", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "rm t.txt", .len = 9 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ss", .len = 3 }, tree);

	struct eskilib_Trie* result = tree->nodes[eskilib_trie_index_get('l')];
	eskilib_assert(result != NULL);
	eskilib_assert(result->is_end_of_a_word == false);
	eskilib_assert(result->letter == 'l');
	result = result->nodes[eskilib_trie_index_get('s')];
	eskilib_assert(result != NULL);
	eskilib_assert(result->is_end_of_a_word == true);
	eskilib_assert(result->letter == 's');
	result = result->nodes[eskilib_trie_index_get(' ')];
	eskilib_assert(result != NULL);
	eskilib_assert(result->is_end_of_a_word == false);
	eskilib_assert(result->letter == ' ');

	struct eskilib_Trie* search_result = eskilib_trie_search_str((struct estr){ .val = "ls | ", .len = 6 }, tree);
	eskilib_assert(search_result != NULL);
	eskilib_assert(search_result->is_end_of_a_word == false);
	eskilib_assert(search_result->letter == ' ');
	search_result = search_result->nodes[eskilib_trie_index_get('s')];
	eskilib_assert(search_result != NULL);
	eskilib_assert(search_result->is_end_of_a_word == false);
	eskilib_assert(search_result->letter == 's');
	search_result = search_result->nodes[eskilib_trie_index_get('o')];
	eskilib_assert(search_result != NULL);
	eskilib_assert(search_result->is_end_of_a_word == false);
	eskilib_assert(search_result->letter == 'o');
	search_result = search_result->nodes[eskilib_trie_index_get('r')];
	eskilib_assert(search_result != NULL);
	eskilib_assert(search_result->is_end_of_a_word == false);
	eskilib_assert(search_result->letter == 'r');
	search_result = search_result->nodes[eskilib_trie_index_get('t')];
	eskilib_assert(search_result != NULL);
	eskilib_assert(search_result->is_end_of_a_word == true);
	eskilib_assert(search_result->letter == 't');

	eskilib_trie_free(tree);
}

void eskilib_trie_search_no_results_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	struct estr str_one = { .val = "gene", .len = 5 };
	eskilib_trie_add_str(str_one, tree);
	struct estr str_two = { .val = "genetic", .len = 8 };
	eskilib_trie_add_str(str_two, tree);
	struct estr str_three = { .val = "genius", .len = 7 };
	eskilib_trie_add_str(str_three, tree);

	struct estr str_search = { .val = "ls", .len = 3 };
	struct eskilib_Trie* search_result = eskilib_trie_search_str(str_search, tree);
	eskilib_assert(search_result == NULL);

	eskilib_trie_free(tree);
}

void eskilib_trie_matches_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	eskilib_trie_add_str((struct estr){ .val = "ls", .len = 3 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | wc -c", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort | wc -c", .len = 18 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls > t.txt", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "cat t.txt", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "rm t.txt", .len = 9 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ss", .len = 3 }, tree);

	struct eskilib_Trie* search_result = eskilib_trie_search_str((struct estr){ .val = "ls | ", .len = 6 }, tree);
	eskilib_assert(search_result != NULL);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = eskilib_trie_get("ls | ", 6, autocomplete, max_match_len, tree);

	eskilib_assert(match_count == 3);
	eskilib_assert(!memcmp(autocomplete[0], "sort", 5));
	eskilib_assert(!memcmp(autocomplete[1], "sort | wc -c", 13));
	eskilib_assert(!memcmp(autocomplete[2], "wc -c", 6));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}
	eskilib_trie_free(tree);
}

void eskilib_trie_matches_no_results_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	eskilib_trie_add_str((struct estr){ .val = "ls", .len = 3 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | wc -c", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort | wc -c", .len = 18 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls > t.txt", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "cat t.txt", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "rm t.txt", .len = 9 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ss", .len = 3 }, tree);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = eskilib_trie_get("n", 2, autocomplete, max_match_len, tree);

	eskilib_assert(match_count == 0);
	eskilib_assert(autocomplete[0] == NULL);

	eskilib_trie_free(tree);
}

void eskilib_trie_matches_multiple_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	eskilib_trie_add_str((struct estr){ .val = "ls", .len = 3 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | wc -c", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort | wc -c", .len = 18 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls > t.txt", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "cat t.txt", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "rm t.txt", .len = 9 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ss", .len = 3 }, tree);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = eskilib_trie_get("ls | ", 6, autocomplete, max_match_len, tree);

	eskilib_assert(match_count == 3);
	eskilib_assert(!memcmp(autocomplete[0], "sort", 5));
	eskilib_assert(!memcmp(autocomplete[1], "sort | wc -c", 13));
	eskilib_assert(!memcmp(autocomplete[2], "wc -c", 6));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_len] = {0};

	match_count = eskilib_trie_get("l", 2, autocomplete_two, max_match_len, tree);

	eskilib_assert(match_count == 5);
	eskilib_assert(!memcmp(autocomplete_two[0], "s", 2));
	eskilib_assert(!memcmp(autocomplete_two[1], "s > t.txt", 10));
	eskilib_assert(!memcmp(autocomplete_two[2], "s | sort", 9));
	eskilib_assert(!memcmp(autocomplete_two[3], "s | sort | wc -c", 17));
	eskilib_assert(!memcmp(autocomplete_two[4], "s | wc -c", 10));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	eskilib_trie_free(tree);
}

void eskilib_trie_matches_multiple_simulation_test(void) {
	struct eskilib_Trie* tree = eskilib_trie_malloc();
	eskilib_assert(tree);

	eskilib_trie_add_str((struct estr){ .val = "ls", .len = 3 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | wc -c", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls | sort | wc -c", .len = 18 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ls > t.txt", .len = 11 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "cat t.txt", .len = 10 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "rm t.txt", .len = 9 }, tree);
	eskilib_trie_add_str((struct estr){ .val = "ss", .len = 3 }, tree);
	eskilib_trie_add("nvim", 5, tree);
	eskilib_trie_add("nvim .", 7, tree);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = eskilib_trie_get("l", 2, autocomplete, max_match_len, tree);

	eskilib_assert(match_count == 5);
	eskilib_assert(!memcmp(autocomplete[0], "s", 2));
	eskilib_assert(!memcmp(autocomplete[1], "s > t.txt", 10));
	eskilib_assert(!memcmp(autocomplete[2], "s | sort", 9));
	eskilib_assert(!memcmp(autocomplete[3], "s | sort | wc -c", 17));
	eskilib_assert(!memcmp(autocomplete[4], "s | wc -c", 10));
	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_len] = {0};

	match_count = eskilib_trie_get("ls", 3, autocomplete_two, max_match_len, tree);

	eskilib_assert(match_count == 4);
	eskilib_assert(!memcmp(autocomplete_two[0], " > t.txt", 9));
	eskilib_assert(!memcmp(autocomplete_two[1], " | sort", 8));
	eskilib_assert(!memcmp(autocomplete_two[2], " | sort | wc -c", 16));
	eskilib_assert(!memcmp(autocomplete_two[3], " | wc -c", 8));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	eskilib_trie_free(tree);
}

void eskilib_trie_tests(void) {
	eskilib_test_start();

	eskilib_test_run(eskilib_trie_add_len_mismatch_test);
	eskilib_test_run(eskilib_trie_add_test);
	eskilib_test_run(eskilib_trie_add_duplicate_test);
	eskilib_test_run(eskilib_trie_add_multiple_unrelated_test);
	eskilib_test_run(eskilib_trie_add_multiple_related_test);
	eskilib_test_run(eskilib_trie_search_test);
	eskilib_test_run(eskilib_trie_search_no_results_test);
	eskilib_test_run(eskilib_trie_search_commands_test);
	eskilib_test_run(eskilib_trie_matches_test);
	eskilib_test_run(eskilib_trie_matches_no_results_test);
	eskilib_test_run(eskilib_trie_matches_multiple_test);
	eskilib_test_run(eskilib_trie_matches_multiple_simulation_test);

	eskilib_test_finish();
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_trie_tests();

	return EXIT_SUCCESS;
}
#endif /* ifndef ESKILIB_TEST_ALL */
