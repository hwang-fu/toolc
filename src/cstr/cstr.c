#include "cstr.h"

u64 strlen_safe(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return 0;
    }

    return (u64) strlen(s);
}

