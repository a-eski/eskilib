#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../etrie.h"
#include "../etest.h"
#include "../estr.h"

void etrie_add_len_mismatch_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str = { .val = "and", .len = 3 };
	etrie_add(str.val, str.len, trie);

	//not crashing is a test pass here

	etrie_free(trie);
}

void etrie_add_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str = { .val = "and", .len = 4 };
	etrie_add(str.val, str.len, trie);

	// sanity check: unrelated letters are null
	eassert(trie->nodes[etrie_index_get('b')] == NULL);
	eassert(trie->nodes[etrie_index_get('c')] == NULL);
	eassert(trie->nodes[etrie_index_get('d')] == NULL);
	eassert(trie->nodes[etrie_index_get('e')] == NULL);

	etrie* first_node = trie->nodes[etrie_index_get('a')];
	eassert(first_node != NULL);
	eassert(first_node->is_end_of_a_word == false);
	eassert(first_node->letter == 'a')
	eassert(first_node->nodes[etrie_index_get('b')] == NULL); //sanity check
	etrie* second_node = first_node->nodes[etrie_index_get('n')];
	eassert(second_node != NULL);
	eassert(second_node->is_end_of_a_word == false);
	eassert(second_node->letter == 'n')
	eassert(second_node->nodes[etrie_index_get('b')] == NULL); //sanity check
	etrie* third_node = second_node->nodes[etrie_index_get('d')];
	eassert(third_node != NULL);
	eassert(third_node->is_end_of_a_word == true);
	eassert(third_node->letter == 'd');
	eassert(third_node->nodes[etrie_index_get('b')] == NULL); //sanity check

	etrie_free(trie);
}

void etrie_add_duplicate_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str = { .val = "and", .len = 4 };
	etrie_add(str.val, str.len, trie);
	etrie_add_str(str, trie);

	etrie* first_node = trie->nodes[etrie_index_get('a')];
	eassert(first_node != NULL);
	eassert(first_node->is_end_of_a_word == false);
	eassert(first_node->letter == 'a')

	etrie* second_node = first_node->nodes[etrie_index_get('n')];
	eassert(second_node != NULL);
	eassert(second_node->is_end_of_a_word == false);
	eassert(second_node->letter == 'n');

	etrie* third_node = second_node->nodes[etrie_index_get('d')];
	eassert(third_node != NULL);
	eassert(third_node->is_end_of_a_word == true);
	eassert(third_node->letter == 'd');

	etrie_free(trie);
}

void etrie_add_multiple_unrelated_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str_one = { .val = "ls", .len = 3 };
	etrie_add(str_one.val, str_one.len, trie);
	estr str_two = { .val = "echo", .len = 5 };
	etrie_add_str(str_two, trie);

	etrie* ls_first_node = trie->nodes[etrie_index_get('l')];
	eassert(ls_first_node != NULL);
	eassert(ls_first_node->is_end_of_a_word == false);
	eassert(ls_first_node->letter == 'l');
	etrie* ls_second_node = ls_first_node->nodes[etrie_index_get('s')];
	eassert(ls_second_node != NULL);
	eassert(ls_second_node->is_end_of_a_word == true);
	eassert(ls_second_node->letter == 's');

	etrie* first_node = trie->nodes[etrie_index_get('e')];
	eassert(first_node != NULL);
	eassert(first_node->is_end_of_a_word == false);
	eassert(first_node->letter == 'e');
	etrie* second_node = first_node->nodes[etrie_index_get('c')];
	eassert(second_node != NULL);
	eassert(second_node->is_end_of_a_word == false);
	eassert(second_node->letter == 'c');
	etrie* third_node = second_node->nodes[etrie_index_get('h')];
	eassert(third_node != NULL);
	eassert(third_node->is_end_of_a_word == false);
	eassert(third_node->letter == 'h');
	etrie* fourth_node = third_node->nodes[etrie_index_get('o')];
	eassert(fourth_node != NULL);
	eassert(fourth_node->is_end_of_a_word == true);
	eassert(fourth_node->letter == 'o');

	etrie_free(trie);
}

void etrie_add_multiple_related_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str_one = { .val = "gene", .len = 5 };
	etrie_add(str_one.val, str_one.len, trie);
	estr str_two = { .val = "genetic", .len = 8 };
	etrie_add_str(str_two, trie);
	estr str_three = { .val = "genius", .len = 7 };
	etrie_add_str(str_three, trie);

	// gene
	etrie* first_node = trie->nodes[etrie_index_get('g')];
	eassert(first_node != NULL);
	eassert(first_node->is_end_of_a_word == false);
	eassert(first_node->letter == 'g');
	etrie* second_node = first_node->nodes[etrie_index_get('e')];
	eassert(second_node != NULL);
	eassert(second_node->is_end_of_a_word == false);
	eassert(second_node->letter == 'e');
	etrie* third_node = second_node->nodes[etrie_index_get('n')];
	eassert(third_node != NULL);
	eassert(third_node->is_end_of_a_word == false);
	eassert(third_node->letter == 'n');
	etrie* fourth_node = third_node->nodes[etrie_index_get('e')];
	eassert(fourth_node != NULL);
	eassert(fourth_node->is_end_of_a_word == true);
	eassert(fourth_node->letter == 'e');

	// genetic
	etrie* genetic_fifth_node = fourth_node->nodes[etrie_index_get('t')];
	eassert(genetic_fifth_node  != NULL);
	eassert(genetic_fifth_node->is_end_of_a_word == false);
	eassert(genetic_fifth_node->letter == 't');
	etrie* genetic_sixth_node = genetic_fifth_node->nodes[etrie_index_get('i')];
	eassert(genetic_sixth_node != NULL);
	eassert(genetic_sixth_node->is_end_of_a_word == false);
	eassert(genetic_sixth_node->letter == 'i');
	etrie* genetic_seventh_node = genetic_sixth_node->nodes[etrie_index_get('c')];
	eassert(genetic_seventh_node != NULL);
	eassert(genetic_seventh_node->is_end_of_a_word == true);
	eassert(genetic_seventh_node->letter == 'c');

	// genius
	etrie* genius_fourth_node = third_node->nodes[etrie_index_get('i')];
	eassert(genius_fourth_node != NULL);
	eassert(genius_fourth_node->is_end_of_a_word == false);
	eassert(genius_fourth_node->letter == 'i');
	etrie* genius_fifth_node = genius_fourth_node->nodes[etrie_index_get('u')];
	eassert(genius_fifth_node != NULL);
	eassert(genius_fifth_node->is_end_of_a_word == false);
	eassert(genius_fifth_node->letter == 'u');
	etrie* genius_sixth_node = genius_fifth_node->nodes[etrie_index_get('s')];
	eassert(genius_sixth_node != NULL);
	eassert(genius_sixth_node->is_end_of_a_word == true);
	eassert(genius_sixth_node->letter == 's');

	etrie_free(trie);
}

void etrie_search_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str_one = { .val = "gene", .len = 5 };
	etrie_add(str_one.val, str_one.len, trie);
	estr str_two = { .val = "genetic", .len = 8 };
	etrie_add(str_two.val, str_two.len, trie);
	estr str_three = { .val = "genius", .len = 7 };
	etrie_add_str(str_three, trie);

	estr str_search = { .val = "gen", .len = 4 };
	etrie* result = etrie_search(str_search.val, str_search.len, trie);
	eassert(result != NULL);
	etrie* result_e = result->nodes[etrie_index_get('e')];
	eassert(result_e != NULL);
	eassert(result_e->is_end_of_a_word == true);
	eassert(result_e->letter == 'e');

	etrie_free(trie);
}

void etrie_search_commands_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	etrie_add_str((estr){ .val = "ls", .len = 3 }, trie);
	etrie_add_str((estr){ .val = "ls | sort", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "ls | sort | wc -c", .len = 18 }, trie);
	etrie_add_str((estr){ .val = "ls > t.txt", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "cat t.txt", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "rm t.txt", .len = 9 }, trie);
	etrie_add_str((estr){ .val = "ss", .len = 3 }, trie);

	etrie* result = trie->nodes[etrie_index_get('l')];
	eassert(result != NULL);
	eassert(result->is_end_of_a_word == false);
	eassert(result->letter == 'l');
	result = result->nodes[etrie_index_get('s')];
	eassert(result != NULL);
	eassert(result->is_end_of_a_word == true);
	eassert(result->letter == 's');
	result = result->nodes[etrie_index_get(' ')];
	eassert(result != NULL);
	eassert(result->is_end_of_a_word == false);
	eassert(result->letter == ' ');

	etrie* search_result = etrie_search_str((estr){ .val = "ls | ", .len = 6 }, trie);
	eassert(search_result != NULL);
	eassert(search_result->is_end_of_a_word == false);
	eassert(search_result->letter == ' ');
	search_result = search_result->nodes[etrie_index_get('s')];
	eassert(search_result != NULL);
	eassert(search_result->is_end_of_a_word == false);
	eassert(search_result->letter == 's');
	search_result = search_result->nodes[etrie_index_get('o')];
	eassert(search_result != NULL);
	eassert(search_result->is_end_of_a_word == false);
	eassert(search_result->letter == 'o');
	search_result = search_result->nodes[etrie_index_get('r')];
	eassert(search_result != NULL);
	eassert(search_result->is_end_of_a_word == false);
	eassert(search_result->letter == 'r');
	search_result = search_result->nodes[etrie_index_get('t')];
	eassert(search_result != NULL);
	eassert(search_result->is_end_of_a_word == true);
	eassert(search_result->letter == 't');

	etrie_free(trie);
}

void etrie_search_no_results_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	estr str_one = { .val = "gene", .len = 5 };
	etrie_add_str(str_one, trie);
	estr str_two = { .val = "genetic", .len = 8 };
	etrie_add_str(str_two, trie);
	estr str_three = { .val = "genius", .len = 7 };
	etrie_add_str(str_three, trie);

	estr str_search = { .val = "ls", .len = 3 };
	etrie* search_result = etrie_search_str(str_search, trie);
	eassert(search_result == NULL);

	etrie_free(trie);
}

void etrie_matches_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	etrie_add_str((estr){ .val = "ls", .len = 3 }, trie);
	etrie_add_str((estr){ .val = "ls | wc -c", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "ls | sort", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "ls | sort | wc -c", .len = 18 }, trie);
	etrie_add_str((estr){ .val = "ls > t.txt", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "cat t.txt", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "rm t.txt", .len = 9 }, trie);
	etrie_add_str((estr){ .val = "ss", .len = 3 }, trie);

	etrie* search_result = etrie_search_str((estr){ .val = "ls | ", .len = 6 }, trie);
	eassert(search_result != NULL);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = etrie_get("ls | ", 6, autocomplete, max_match_len, trie);

	eassert(match_count == 3);
	eassert(!memcmp(autocomplete[0], "sort", 5));
	eassert(!memcmp(autocomplete[1], "sort | wc -c", 13));
	eassert(!memcmp(autocomplete[2], "wc -c", 6));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}
	etrie_free(trie);
}

void etrie_matches_no_results_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	etrie_add_str((estr){ .val = "ls", .len = 3 }, trie);
	etrie_add_str((estr){ .val = "ls | wc -c", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "ls | sort", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "ls | sort | wc -c", .len = 18 }, trie);
	etrie_add_str((estr){ .val = "ls > t.txt", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "cat t.txt", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "rm t.txt", .len = 9 }, trie);
	etrie_add_str((estr){ .val = "ss", .len = 3 }, trie);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = etrie_get("n", 2, autocomplete, max_match_len, trie);

	eassert(match_count == 0);
	eassert(autocomplete[0] == NULL);

	etrie_free(trie);
}

void etrie_matches_multiple_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	etrie_add_str((estr){ .val = "ls", .len = 3 }, trie);
	etrie_add_str((estr){ .val = "ls | wc -c", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "ls | sort", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "ls | sort | wc -c", .len = 18 }, trie);
	etrie_add_str((estr){ .val = "ls > t.txt", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "cat t.txt", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "rm t.txt", .len = 9 }, trie);
	etrie_add_str((estr){ .val = "ss", .len = 3 }, trie);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = etrie_get("ls | ", 6, autocomplete, max_match_len, trie);

	eassert(match_count == 3);
	eassert(!memcmp(autocomplete[0], "sort", 5));
	eassert(!memcmp(autocomplete[1], "sort | wc -c", 13));
	eassert(!memcmp(autocomplete[2], "wc -c", 6));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_len] = {0};

	match_count = etrie_get("l", 2, autocomplete_two, max_match_len, trie);

	eassert(match_count == 5);
	eassert(!memcmp(autocomplete_two[0], "s", 2));
	eassert(!memcmp(autocomplete_two[1], "s > t.txt", 10));
	eassert(!memcmp(autocomplete_two[2], "s | sort", 9));
	eassert(!memcmp(autocomplete_two[3], "s | sort | wc -c", 17));
	eassert(!memcmp(autocomplete_two[4], "s | wc -c", 10));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	etrie_free(trie);
}

void etrie_matches_multiple_simulation_test(void)
{
	etrie* trie = etrie_malloc();
	eassert(trie);

	etrie_add_str((estr){ .val = "ls", .len = 3 }, trie);
	etrie_add_str((estr){ .val = "ls | wc -c", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "ls | sort", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "ls | sort | wc -c", .len = 18 }, trie);
	etrie_add_str((estr){ .val = "ls > t.txt", .len = 11 }, trie);
	etrie_add_str((estr){ .val = "cat t.txt", .len = 10 }, trie);
	etrie_add_str((estr){ .val = "rm t.txt", .len = 9 }, trie);
	etrie_add_str((estr){ .val = "ss", .len = 3 }, trie);
	etrie_add("nvim", 5, trie);
	etrie_add("nvim .", 7, trie);

	constexpr uint_fast32_t max_match_len = 256;
	char* autocomplete[max_match_len] = {0};

	size_t match_count = etrie_get("l", 2, autocomplete, max_match_len, trie);

	eassert(match_count == 5);
	eassert(!memcmp(autocomplete[0], "s", 2));
	eassert(!memcmp(autocomplete[1], "s > t.txt", 10));
	eassert(!memcmp(autocomplete[2], "s | sort", 9));
	eassert(!memcmp(autocomplete[3], "s | sort | wc -c", 17));
	eassert(!memcmp(autocomplete[4], "s | wc -c", 10));
	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete[i]);
			free(autocomplete[i]);
		}
	}

	char* autocomplete_two[max_match_len] = {0};

	match_count = etrie_get("ls", 3, autocomplete_two, max_match_len, trie);

	eassert(match_count == 4);
	eassert(!memcmp(autocomplete_two[0], " > t.txt", 9));
	eassert(!memcmp(autocomplete_two[1], " | sort", 8));
	eassert(!memcmp(autocomplete_two[2], " | sort | wc -c", 16));
	eassert(!memcmp(autocomplete_two[3], " | wc -c", 8));

	for (uint_fast32_t i = 0; i < max_match_len - 1; i++) {
		if (autocomplete_two[i] != NULL) {
			// printf("i:%lu %s\n", i, autocomplete_two[i]);
			free(autocomplete_two[i]);
		}
	}

	etrie_free(trie);
}

void etrie_tests(void)
{
	etest_start();

	etest_run(etrie_add_len_mismatch_test);
	etest_run(etrie_add_test);
	etest_run(etrie_add_duplicate_test);
	etest_run(etrie_add_multiple_unrelated_test);
	etest_run(etrie_add_multiple_related_test);
	etest_run(etrie_search_test);
	etest_run(etrie_search_no_results_test);
	etest_run(etrie_search_commands_test);
	etest_run(etrie_matches_test);
	etest_run(etrie_matches_no_results_test);
	etest_run(etrie_matches_multiple_test);
	etest_run(etrie_matches_multiple_simulation_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	etrie_tests();

	return EXIT_SUCCESS;
}
#endif /* ifndef etest_ALL */
