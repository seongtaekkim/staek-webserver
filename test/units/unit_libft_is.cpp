#include "../test_unit.hpp"

CASE("libft", "islower")
{
	ASSERT(std::islower('a'));
	ASSERT(std::islower('z'));

	ASSERT(!std::islower('A'));
	ASSERT(!std::islower('Z'));

	return (0);
}

CASE("libft", "isupper")
{
	ASSERT(std::isupper('A'));
	ASSERT(std::isupper('Z'));

	ASSERT(!std::isupper('a'));
	ASSERT(!std::isupper('z'));

	return (0);
}
