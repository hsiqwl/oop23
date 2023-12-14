#include "../include/dynamic_array.h"
#include "../include/matrix.h"

static_assert(std::contiguous_iterator<array_iterator<int, false>>);
static_assert(std::contiguous_iterator<array_iterator<int, true>>);


