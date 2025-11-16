#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include <hwangfu/generic.h>
#include <hwangfu/crayon.h>
#include <hwangfu/assertion.h>
#include <hwangfu/cstr.h>
#include <hwangfu/dequeue.h>
#include <hwangfu/hashmap.h>
#include <hwangfu/vector.h>

static void pass(u64 nr)
{
    fprintf(COUT, "Case " CRAYON_TO_BOLD(CRAYON_TO_GREEN("%lu")) " passed!\n", nr);
}

static void fail(u64 nr)
{
    fprintf(CERR, "Case " CRAYON_TO_BOLD(CRAYON_TO_RED("%lu")) " failed!\n", nr);
    exit(EXIT_FAILURE);
}

int main()
{
    fprintf(COUT, "=============== Testing Start ===============\n");
#include "./s/test.c"
#include "./dq/test.c"
#include "./hm/test.c"
#include "./vector/test.c"
    fprintf(COUT, "=============== Testing End ===============\n");
    return 0;
}
