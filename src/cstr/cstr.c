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
    if (EQ(s1, s2))
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

bool strncmp_safe_ignorecase(BORROWED const char * s1, BORROWED const char * s2, u64 length)
{
    /// 1. if length is @const {0}, no need to compare.
    if (EQ(length, 0))
    {
        return True;
    }

    /// 2. if points to the same memory / both @const {NIL}, definitely same.
    if (EQ(s1, s2))
    {
        return True;
    }

    /// 3. if only one string is @const {NIL}, definitely not same.
    if (!s1 || !s2)
    {
        return False;
    }

    while (--length && *s1 && *s2 && EQ(cto_english_lowerletter(*s1), cto_english_lowerletter(*s2)))
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
    if (EQ(s1, s2))
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

bool strncmp_safe(BORROWED const char * s1, BORROWED const char * s2, u64 length)
{
#ifdef CSTR_IGNORE_CASE
    return strncmp_safe_ignorecase(s1, s2);
#else
    /// 1. if length is @const {0}, no need to compare.
    if (EQ(length, 0))
    {
        return True;
    }

    /// 2. if points to the same memory / both @const {NIL}, definitely same.
    if (EQ(s1, s2))
    {
        return True;
    }

    /// 3. if only one string is @const {NIL}, definitely not same.
    if (!s1 || !s2)
    {
        return False;
    }

    return EQ(0, strncmp(s1, s2, length));
#endif // CSTR_IGNORE_CASE
}

OWNED char * strdup_safe(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        s = "";
    }
    OWNED char * duplicated = strdup(s);
    if (!duplicated)
    {
        PANIC("Error @%s(): failed to duplicate string \"%s\"", __func__, s);
    }
    return duplicated;
}

bool cstr_starts_with_owned(BORROWED const char * s, OWNED char * prefix)
{
    bool result = cstr_starts_with(s, prefix);
    XFREE(prefix);
    return result;
}

bool cstr_starts_with_ignorecase(BORROWED const char * s, BORROWED const char * prefix)
{
    if (EQ(s, prefix))
    {
        return True;
    }
}

bool cstr_starts_with(BORROWED const char * s, BORROWED const char * prefix)
{
    if (EQ(s, prefix))
    {
        return True;
    }

    if (!s || !prefix)
    {
        return False;
    }

    u64 len1 = strlen_safe(s);
    u64 len2 = strlen_safe(prefix);

    if (len1 < len2)
    {
        return False;
    }

    // @const {""} is the prefix for any string.
    if (prefix && EQ(len2, 0))
    {
        return True;
    }

    return EQ(0, memcmp(s, prefix, len2));
}

bool cstr_ends_with_owned(BORROWED const char * s, OWNED char * suffix)
{
    bool result = cstr_ends_with(s, suffix);
    XFREE(suffix);
    return result;
}

bool cstr_ends_with_ignorecase(BORROWED const char * s, BORROWED const char * suffix)
{
    if (EQ(s, suffix))
    {
        return True;
    }
}

bool cstr_ends_with(BORROWED const char * s, BORROWED const char * suffix)
{
    if (EQ(s, suffix))
    {
        return True;
    }

    if (!s || !suffix)
    {
        return False;
    }

    u64 len1 = strlen_safe(s);
    u64 len2 = strlen_safe(suffix);

    if (len1 < len2)
    {
        return False;
    }

    // @const {""} is the suffix for any string.
    if (suffix && EQ(len2, 0))
    {
        return True;
    }

    return EQ(0, memcmp(s, suffix, len2));
}

char cstr_at(BORROWED const char * s, u64 idx)
{
    if (strlen_safe(s) <= idx)
    {
        PANIC("%s(): index %lu out of range for \"%s\".",
                __func__,
                idx,
                s);
    }
    return s[idx];
}
