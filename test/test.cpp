#include "acutest.hpp"
// https://www.youtube.com/watch?v=H6x53F5Do24
// https://github.com/mity/acutest


int add(int a, int b) {
	return (a + b);
}

void test_add(void) {
	int Expected = 2 + 3;
	int Produced = add(2,2);
	TEST_CHECK_(Expected == Produced, "test1 : %d", Produced);
	TEST_MSG("Expected: %d", Expected);
    TEST_MSG("Produced: %d", Produced);
}

void test_assert(void)
{
    void* mem;
    int a, b;

    mem = malloc(10);
    TEST_ASSERT(mem != NULL);
}

TEST_LIST = {
	{"int add(int,int) :: ", test_add},
	{"test_assert :: ", test_assert},
	{0}
};