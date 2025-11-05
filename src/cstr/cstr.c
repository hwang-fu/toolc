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

    return strncmp_safe_ignorecase(s, prefix, len2);
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

    TODO;
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

OWNED char * mk_cstr(BORROWED const char * s1, BORROWED const char * s2)
{
    const u64 len1 = strlen_safe(s1);
    const u64 len2 = strlen_safe(s2);
    const u64 total = len1 + len2;

    if (EQ(total, 0))
    {
        return strdup_safe("");
    }

    if (EQ(len1, 0))
    {
        return strdup_safe(s2);
    }

    if (EQ(len2, 0))
    {
        return strdup_safe(s1);
    }

    OWNED char * s = NEW((total + 1) * sizeof(char));
    memcpy(s,        s1, len1);
    memcpy(s + len1, s2, len2);
    s[total] = '\0';

    return s;
}

OWNED char * mk_cstr_owned(OWNED char * s1, OWNED char * s2)
{
    OWNED char * theString = mk_cstr(s1, s2);
    XFREE(s1);
    XFREE(s2);
    return theString;
}

OWNED char * mk_cstr_with_owned_prefix(BORROWED const char * s, OWNED char * prefix)
{
    OWNED char * theString = mk_cstr(s, prefix);
    XFREE(prefix);
    return theString;
}

OWNED char * mk_cstr_with_owned_suffix(BORROWED const char * s, OWNED char * suffix)
{
    OWNED char * theString = mk_cstr(s, suffix);
    XFREE(suffix);
    return theString;
}

OWNED char * mk_cstr_tolower_owned(OWNED char * s)
{
    OWNED char * theString = mk_cstr_tolower(s);
    XFREE(s);
    return theString;
}

OWNED char * mk_cstr_tolower(BORROWED const char * s)
{
    u64 len = strlen_safe(s);
    if (EQ(len, 0))
    {
        return strdup_safe(s);
    }

    OWNED char * theString = NEW((len + 1) * sizeof(char));
    for (u64 i = 0; i < len; i++)
    {
        theString[i] = cto_english_lowerletter(s[i]);
    }
    theString[len] = '\0';
    return theString;
}

OWNED char * mk_cstr_toupper_owned(OWNED char * s)
{
    OWNED char * theString = mk_cstr_toupper(s);
    XFREE(s);
    return theString;
}

OWNED char * mk_cstr_toupper(BORROWED const char * s)
{
    u64 len = strlen_safe(s);
    if (EQ(len, 0))
    {
        return strdup_safe(s);
    }

    OWNED char * theString = NEW((len + 1) * sizeof(char));
    for (u64 i = 0; i < len; i++)
    {
        theString[i] = cto_english_upperletter(s[i]);
    }
    theString[len] = '\0';
    return theString;
}

OWNED char * mk_cstr_from_char(const char c)
{
    char buffer[2] = { 0 };
    buffer[0] = c;
    return strdup_safe(buffer);
}

OWNED char * mk_cstr_from_buffer(BORROWED const u8 * buffer, const u64 size)
{
    OWNED char * theString = NEW((size + 1)* sizeof(char));
    memcpy(theString, buffer, size);
    theString[size] = '\0';
    return theString;
}

OWNED char * mk_cstr_from_owned_buffer(OWNED u8 * buffer, const u64 size)
{
    OWNED char * theString = mk_cstr_from_buffer(buffer, size);
    XFREE(buffer);
    return theString;
}

bool cis_digit(const char c)
{
    return ('0' <= c) && (c <= '9');
}

bool cis_bdigit(const char c)
{
    return EQ(c, '0') || EQ(c, '1');
}

bool cis_odigit(const char c)
{
    return ('0' <= c) && (c <= '7');
}

bool cis_xdigit(const char c)
{
    return cis_digit(c)
        || (('a' <= c) && (c <= 'f'))
        || (('A' <= c) && (c <= 'F'));
}

bool cis_english_upperletter(const char c)
{
    return ('A' <= c) && (c <= 'Z');
}

bool cis_english_lowerletter(const char c)
{
    return ('a' <= c) && (c <= 'z');
}

bool cis_english_letter(const char c)
{
    return cis_english_upperletter(c) || cis_english_lowerletter(c);
}

char cto_english_upperletter(const char c)
{
    if (cis_english_lowerletter(c))
    {
        return c - 'a' + 'A';
    }
    return c;
}

char cto_english_lowerletter(const char c)
{
    if (cis_english_upperletter(c))
    {
        return c - 'A' + 'a';
    }
    return c;
}

OWNED Result * mk_u64_from_cstring(BORROWED const char * s)
{
}

OWNED Result * mk_u64_from_owned_cstring(OWNED char * s)
{
}

bool sis_integer(BORROWED const char * s)
{
    return sis_binary_integer(s) || sis_octal_integer(s) || sis_decimal_integer(s) || sis_hexadecimal_integer(s);
}

bool sis_binary_integer(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return False;
    }

    if (cstr_starts_with(s, "0b") || cstr_starts_with(s, "0B"))
    {
        INC(s);
        INC(s);
    }

    if (EQ(*s, '\0'))
    {
        return False;
    }

    while (cis_bdigit(*s))
    {
        INC(s);
    }

    return EQ(*s, '\0');
}

bool sis_octal_integer(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return False;
    }

    if (cstr_starts_with(s, "0o") || cstr_starts_with(s, "0O"))
    {
        INC(s);
        INC(s);
    }

    if (EQ(*s, '\0'))
    {
        return False;
    }

    while (cis_odigit(*s))
    {
        INC(s);
    }

    return EQ(*s, '\0');
}

bool sis_decimal_integer(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return False;
    }

    if (EQ(*s, '\0'))
    {
        return False;
    }

    while (cis_digit(*s))
    {
        INC(s);
    }

    return EQ(*s, '\0');
}

bool sis_hexadecimal_integer(BORROWED const char * s)
{
    if (EQ(s, NIL))
    {
        return False;
    }

    if (cstr_starts_with(s, "0x") || cstr_starts_with(s, "0X"))
    {
        INC(s);
        INC(s);
    }

    if (EQ(*s, '\0'))
    {
        return False;
    }

    while (cis_xdigit(*s))
    {
        INC(s);
    }

    return EQ(*s, '\0');
}
