#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../eski_trie.h"
#include "../eski_test.h"
#include "../eski_string.h"

void eski_trie_add_length_mismatch_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string = { .value = "and", .length = 3 };
	eski_trie_add(string.value, string.length, tree);

	//not crashing is a test pass here

	eski_trie_free(tree);
}

void eski_trie_add_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string = { .value = "and", .length = 4 };
	eski_trie_add(string.value, string.length, tree);

	// sanity check: unrelated letters are null
	eski_assert(tree->nodes[eski_trie_map_char('b')] == NULL);
	eski_assert(tree->nodes[eski_trie_map_char('c')] == NULL);
	eski_assert(tree->nodes[eski_trie_map_char('d')] == NULL);
	eski_assert(tree->nodes[eski_trie_map_char('e')] == NULL);

	struct eski_Trie* first_node = tree->nodes[eski_trie_map_char('a')];
	eski_assert(first_node != NULL);
	eski_assert(first_node->is_end_of_a_word == false);
	eski_assert(first_node->letter == 'a')
	eski_assert(first_node->nodes[eski_trie_map_char('b')] == NULL); //sanity check
	struct eski_Trie* second_node = first_node->nodes[eski_trie_map_char('n')];
	eski_assert(second_node != NULL);
	eski_assert(second_node->is_end_of_a_word == false);
	eski_assert(second_node->letter == 'n')
	eski_assert(second_node->nodes[eski_trie_map_char('b')] == NULL); //sanity check
	struct eski_Trie* third_node = second_node->nodes[eski_trie_map_char('d')];
	eski_assert(third_node != NULL);
	eski_assert(third_node->is_end_of_a_word == true);
	eski_assert(third_node->letter == 'd');
	eski_assert(third_node->nodes[eski_trie_map_char('b')] == NULL); //sanity check

	eski_trie_free(tree);
}

void eski_trie_add_duplicate_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string = { .value = "and", .length = 4 };
	eski_trie_add(string.value, string.length, tree);
	eski_trie_add_string(string, tree);

	struct eski_Trie* first_node = tree->nodes[eski_trie_map_char('a')];
	eski_assert(first_node != NULL);
	eski_assert(first_node->is_end_of_a_word == false);
	eski_assert(first_node->letter == 'a')

	struct eski_Trie* second_node = first_node->nodes[eski_trie_map_char('n')];
	eski_assert(second_node != NULL);
	eski_assert(second_node->is_end_of_a_word == false);
	eski_assert(second_node->letter == 'n');

	struct eski_Trie* third_node = second_node->nodes[eski_trie_map_char('d')];
	eski_assert(third_node != NULL);
	eski_assert(third_node->is_end_of_a_word == true);
	eski_assert(third_node->letter == 'd');

	eski_trie_free(tree);
}

void eski_trie_add_multiple_unrelated_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string_one = { .value = "ls", .length = 3 };
	eski_trie_add(string_one.value, string_one.length, tree);
	struct eski_String string_two = { .value = "echo", .length = 5 };
	eski_trie_add_string(string_two, tree);

	struct eski_Trie* ls_first_node = tree->nodes[eski_trie_map_char('l')];
	eski_assert(ls_first_node != NULL);
	eski_assert(ls_first_node->is_end_of_a_word == false);
	eski_assert(ls_first_node->letter == 'l');
	struct eski_Trie* ls_second_node = ls_first_node->nodes[eski_trie_map_char('s')];
	eski_assert(ls_second_node != NULL);
	eski_assert(ls_second_node->is_end_of_a_word == true);
	eski_assert(ls_second_node->letter == 's');

	struct eski_Trie* first_node = tree->nodes[eski_trie_map_char('e')];
	eski_assert(first_node != NULL);
	eski_assert(first_node->is_end_of_a_word == false);
	eski_assert(first_node->letter == 'e');
	struct eski_Trie* second_node = first_node->nodes[eski_trie_map_char('c')];
	eski_assert(second_node != NULL);
	eski_assert(second_node->is_end_of_a_word == false);
	eski_assert(second_node->letter == 'c');
	struct eski_Trie* third_node = second_node->nodes[eski_trie_map_char('h')];
	eski_assert(third_node != NULL);
	eski_assert(third_node->is_end_of_a_word == false);
	eski_assert(third_node->letter == 'h');
	struct eski_Trie* fourth_node = third_node->nodes[eski_trie_map_char('o')];
	eski_assert(fourth_node != NULL);
	eski_assert(fourth_node->is_end_of_a_word == true);
	eski_assert(fourth_node->letter == 'o');

	eski_trie_free(tree);
}

void eski_trie_add_multiple_related_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string_one = { .value = "gene", .length = 5 };
	eski_trie_add(string_one.value, string_one.length, tree);
	struct eski_String string_two = { .value = "genetic", .length = 8 };
	eski_trie_add_string(string_two, tree);
	struct eski_String string_three = { .value = "genius", .length = 7 };
	eski_trie_add_string(string_three, tree);

	// gene
	struct eski_Trie* first_node = tree->nodes[eski_trie_map_char('g')];
	eski_assert(first_node != NULL);
	eski_assert(first_node->is_end_of_a_word == false);
	eski_assert(first_node->letter == 'g');
	struct eski_Trie* second_node = first_node->nodes[eski_trie_map_char('e')];
	eski_assert(second_node != NULL);
	eski_assert(second_node->is_end_of_a_word == false);
	eski_assert(second_node->letter == 'e');
	struct eski_Trie* third_node = second_node->nodes[eski_trie_map_char('n')];
	eski_assert(third_node != NULL);
	eski_assert(third_node->is_end_of_a_word == false);
	eski_assert(third_node->letter == 'n');
	struct eski_Trie* fourth_node = third_node->nodes[eski_trie_map_char('e')];
	eski_assert(fourth_node != NULL);
	eski_assert(fourth_node->is_end_of_a_word == true);
	eski_assert(fourth_node->letter == 'e');

	// genetic
	struct eski_Trie* genetic_fifth_node = fourth_node->nodes[eski_trie_map_char('t')];
	eski_assert(genetic_fifth_node  != NULL);
	eski_assert(genetic_fifth_node->is_end_of_a_word == false);
	eski_assert(genetic_fifth_node->letter == 't');
	struct eski_Trie* genetic_sixth_node = genetic_fifth_node->nodes[eski_trie_map_char('i')];
	eski_assert(genetic_sixth_node != NULL);
	eski_assert(genetic_sixth_node->is_end_of_a_word == false);
	eski_assert(genetic_sixth_node->letter == 'i');
	struct eski_Trie* genetic_seventh_node = genetic_sixth_node->nodes[eski_trie_map_char('c')];
	eski_assert(genetic_seventh_node != NULL);
	eski_assert(genetic_seventh_node->is_end_of_a_word == true);
	eski_assert(genetic_seventh_node->letter == 'c');

	// genius
	struct eski_Trie* genius_fourth_node = third_node->nodes[eski_trie_map_char('i')];
	eski_assert(genius_fourth_node != NULL);
	eski_assert(genius_fourth_node->is_end_of_a_word == false);
	eski_assert(genius_fourth_node->letter == 'i');
	struct eski_Trie* genius_fifth_node = genius_fourth_node->nodes[eski_trie_map_char('u')];
	eski_assert(genius_fifth_node != NULL);
	eski_assert(genius_fifth_node->is_end_of_a_word == false);
	eski_assert(genius_fifth_node->letter == 'u');
	struct eski_Trie* genius_sixth_node = genius_fifth_node->nodes[eski_trie_map_char('s')];
	eski_assert(genius_sixth_node != NULL);
	eski_assert(genius_sixth_node->is_end_of_a_word == true);
	eski_assert(genius_sixth_node->letter == 's');

	eski_trie_free(tree);
}

void eski_trie_search_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string_one = { .value = "gene", .length = 5 };
	eski_trie_add(string_one.value, string_one.length, tree);
	struct eski_String string_two = { .value = "genetic", .length = 8 };
	eski_trie_add(string_two.value, string_two.length, tree);
	struct eski_String string_three = { .value = "genius", .length = 7 };
	eski_trie_add_string(string_three, tree);

	struct eski_String string_search = { .value = "gen", .length = 4 };
	struct eski_Trie* result = eski_trie_search(string_search.value, string_search.length, tree);
	eski_assert(result != NULL);
	struct eski_Trie* result_e = result->nodes[eski_trie_map_char('e')];
	eski_assert(result_e != NULL);
	eski_assert(result_e->is_end_of_a_word == true);
	eski_assert(result_e->letter == 'e');

	eski_trie_free(tree);
}

void eski_trie_search_commands_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	eski_trie_add_string((struct eski_String){ .value = "ls", .length = 3 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort | wc -c", .length = 18 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls > t.txt", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "cat t.txt", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "rm t.txt", .length = 9 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ss", .length = 3 }, tree);

	struct eski_Trie* result = tree->nodes[eski_trie_map_char('l')];
	eski_assert(result != NULL);
	eski_assert(result->is_end_of_a_word == false);
	eski_assert(result->letter == 'l');
	result = result->nodes[eski_trie_map_char('s')];
	eski_assert(result != NULL);
	eski_assert(result->is_end_of_a_word == true);
	eski_assert(result->letter == 's');
	result = result->nodes[eski_trie_map_char(' ')];
	eski_assert(result != NULL);
	eski_assert(result->is_end_of_a_word == false);
	eski_assert(result->letter == ' ');

	struct eski_Trie* search_result = eski_trie_search_string((struct eski_String){ .value = "ls | ", .length = 6 }, tree);
	eski_assert(search_result != NULL);
	eski_assert(search_result->is_end_of_a_word == false);
	eski_assert(search_result->letter == ' ');
	search_result = search_result->nodes[eski_trie_map_char('s')];
	eski_assert(search_result != NULL);
	eski_assert(search_result->is_end_of_a_word == false);
	eski_assert(search_result->letter == 's');
	search_result = search_result->nodes[eski_trie_map_char('o')];
	eski_assert(search_result != NULL);
	eski_assert(search_result->is_end_of_a_word == false);
	eski_assert(search_result->letter == 'o');
	search_result = search_result->nodes[eski_trie_map_char('r')];
	eski_assert(search_result != NULL);
	eski_assert(search_result->is_end_of_a_word == false);
	eski_assert(search_result->letter == 'r');
	search_result = search_result->nodes[eski_trie_map_char('t')];
	eski_assert(search_result != NULL);
	eski_assert(search_result->is_end_of_a_word == true);
	eski_assert(search_result->letter == 't');

	eski_trie_free(tree);
}

void eski_trie_search_no_results_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	struct eski_String string_one = { .value = "gene", .length = 5 };
	eski_trie_add_string(string_one, tree);
	struct eski_String string_two = { .value = "genetic", .length = 8 };
	eski_trie_add_string(string_two, tree);
	struct eski_String string_three = { .value = "genius", .length = 7 };
	eski_trie_add_string(string_three, tree);

	struct eski_String string_search = { .value = "ls", .length = 3 };
	struct eski_Trie* search_result = eski_trie_search_string(string_search, tree);
	eski_assert(search_result == NULL);

	eski_trie_free(tree);
}

void eski_trie_matches_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	eski_trie_add_string((struct eski_String){ .value = "ls", .length = 3 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | wc -c", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort | wc -c", .length = 18 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls > t.txt", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "cat t.txt", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "rm t.txt", .length = 9 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ss", .length = 3 }, tree);

	struct eski_Trie* search_result = eski_trie_search_string((struct eski_String){ .value = "ls | ", .length = 6 }, tree);
	eski_assert(search_result != NULL);

	constexpr uint_fast32_t max_match_length = 256;
	char* autocomplete[max_match_length] = {0};

	size_t match_count = eski_trie_get("ls | ", 6, autocomplete, max_match_length, tree);

	eski_assert(match_count == 3);
	eski_assert(eski_string_equals(autocomplete[0], "sort", 5) == true);
	eski_assert(eski_string_equals(autocomplete[1], "sort | wc -c", 13) == true);
	eski_assert(eski_string_equals(autocomplete[2], "wc -c", 6) == true);

	for (uint_fast32_t i = 0; i < max_match_length - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}
	eski_trie_free(tree);
}

void eski_trie_matches_no_results_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	eski_trie_add_string((struct eski_String){ .value = "ls", .length = 3 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | wc -c", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort | wc -c", .length = 18 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls > t.txt", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "cat t.txt", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "rm t.txt", .length = 9 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ss", .length = 3 }, tree);

	constexpr uint_fast32_t max_match_length = 256;
	char* autocomplete[max_match_length] = {0};

	size_t match_count = eski_trie_get("n", 2, autocomplete, max_match_length, tree);

	eski_assert(match_count == 0);
	eski_assert(autocomplete[0] == NULL);

	eski_trie_free(tree);
}

void eski_trie_matches_multiple_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	eski_trie_add_string((struct eski_String){ .value = "ls", .length = 3 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | wc -c", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort | wc -c", .length = 18 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls > t.txt", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "cat t.txt", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "rm t.txt", .length = 9 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ss", .length = 3 }, tree);

	constexpr uint_fast32_t max_match_length = 256;
	char* autocomplete[max_match_length] = {0};

	size_t match_count = eski_trie_get("ls | ", 6, autocomplete, max_match_length, tree);

	eski_assert(match_count == 3);
	eski_assert(eski_string_equals(autocomplete[0], "sort", 5) == true);
	eski_assert(eski_string_equals(autocomplete[1], "sort | wc -c", 13) == true);
	eski_assert(eski_string_equals(autocomplete[2], "wc -c", 6) == true);

	for (uint_fast32_t i = 0; i < max_match_length - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_length] = {0};

	match_count = eski_trie_get("l", 2, autocomplete_two, max_match_length, tree);

	eski_assert(match_count == 5);
	eski_assert(eski_string_equals(autocomplete_two[0], "s", 2) == true);
	eski_assert(eski_string_equals(autocomplete_two[1], "s > t.txt", 10) == true);
	eski_assert(eski_string_equals(autocomplete_two[2], "s | sort", 9) == true);
	eski_assert(eski_string_equals(autocomplete_two[3], "s | sort | wc -c", 17) == true);
	eski_assert(eski_string_equals(autocomplete_two[4], "s | wc -c", 10) == true);

	for (uint_fast32_t i = 0; i < max_match_length - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	eski_trie_free(tree);
}

void eski_trie_matches_multiple_simulation_test(void) {
	struct eski_Trie* tree = eski_trie_malloc();
	eski_assert(tree);

	eski_trie_add_string((struct eski_String){ .value = "ls", .length = 3 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | wc -c", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls | sort | wc -c", .length = 18 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ls > t.txt", .length = 11 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "cat t.txt", .length = 10 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "rm t.txt", .length = 9 }, tree);
	eski_trie_add_string((struct eski_String){ .value = "ss", .length = 3 }, tree);
	eski_trie_add("nvim", 5, tree);
	eski_trie_add("nvim .", 7, tree);

	constexpr uint_fast32_t max_match_length = 256;
	char* autocomplete[max_match_length] = {0};

	size_t match_count = eski_trie_get("l", 2, autocomplete, max_match_length, tree);

	eski_assert(match_count == 5);
	eski_assert(eski_string_equals(autocomplete[0], "s", 2) == true);
	eski_assert(eski_string_equals(autocomplete[1], "s > t.txt", 10) == true);
	eski_assert(eski_string_equals(autocomplete[2], "s | sort", 9) == true);
	eski_assert(eski_string_equals(autocomplete[3], "s | sort | wc -c", 17) == true);
	eski_assert(eski_string_equals(autocomplete[4], "s | wc -c", 10) == true);
	for (uint_fast32_t i = 0; i < max_match_length - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_length] = {0};

	match_count = eski_trie_get("ls", 3, autocomplete_two, max_match_length, tree);

	eski_assert(match_count == 4);
	eski_assert(eski_string_equals(autocomplete_two[0], " > t.txt", 9) == true);
	eski_assert(eski_string_equals(autocomplete_two[1], " | sort", 8) == true);
	eski_assert(eski_string_equals(autocomplete_two[2], " | sort | wc -c", 16) == true);
	eski_assert(eski_string_equals(autocomplete_two[3], " | wc -c", 8) == true);

	for (uint_fast32_t i = 0; i < max_match_length - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	eski_trie_free(tree);
}

void eski_trie_tests(void) {
	eski_test_start();
	eski_test_run("eski_trie_add_length_mismatch_test", eski_trie_add_length_mismatch_test);
	eski_test_run("eski_trie_add_test", eski_trie_add_test);
	eski_test_run("eski_trie_add_duplicate_test", eski_trie_add_duplicate_test);
	eski_test_run("eski_trie_add_multiple_unrelated_test", eski_trie_add_multiple_unrelated_test);
	eski_test_run("eski_trie_add_multiple_related_test", eski_trie_add_multiple_related_test);
	eski_test_run("eski_trie_search_test", eski_trie_search_test);
	eski_test_run("eski_trie_search_no_results_test", eski_trie_search_no_results_test);
	eski_test_run("eski_trie_search_commands_test", eski_trie_search_commands_test);
	eski_test_run("eski_trie_matches_test", eski_trie_matches_test);
	eski_test_run("eski_trie_matches_no_results_test", eski_trie_matches_no_results_test);
	eski_test_run("eski_trie_matches_multiple_test", eski_trie_matches_multiple_test);
	eski_test_run("eski_trie_matches_multiple_simulation_test", eski_trie_matches_multiple_simulation_test);
	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void) {
	eski_trie_tests();

	return EXIT_SUCCESS;
}
#endif /* ifndef ncsh_TEST_ALL */
