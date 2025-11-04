#include "cstr.h"

u64 strlen_safe(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return 0;
    }

    return (u64) strlen(s);
}

bool strcmp_safe_ignorecase(BORROWED const char * s1, BORROWED const char * s2)
{
    /// 1. if points to the same memory / both @const {NIL}, definitely same.
    if (s1 == s2)
    {
        return True;
    }

    /// 2. if only one string is @const {NIL}, definitely not same.
    if (!s1 || !s2)
    {
        return False;
    }

    while (*s1 && *s2 && EQ(cto_english_lowerletter(*s1), cto_english_lowerletter(*s2)))
    {
        INC(s1);
        INC(s2);
    }
    return EQ(cto_english_lowerletter(*s1), cto_english_lowerletter(*s2));
}

bool strcmp_safe(BORROWED const char * s1, BORROWED const char * s2)
{
#ifdef CSTR_IGNORE_CASE
    return strcmp_safe_ignorecase(s1, s2);
#else
    /// 1. if points to the same memory / both @const {NIL}, definitely same.
    if (s1 == s2)
    {
        return True;
    }

    /// 2. if only one string is @const {NIL}, definitely not same.
    if (!s1 || !s2)
    {
        return False;
    }

    return EQ(0, strcmp(s1, s2));
#endif // CSTR_IGNORE_CASE
}
