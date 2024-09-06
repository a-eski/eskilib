void eskilib_string_release_tests()
{
}

void eskilib_string_tests()
{
	#ifdef NDEBUG
		eskilib_string_release_tests();
	#endif /* ifdef NDEBUG */
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_string_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
