#pragma once

#include <string.h>

#include "hwangfu/generic.h"
#include "hwangfu/assertion.h"
#include "hwangfu/result.h"


/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       Returns @const {0} if @param {s} is @const {NIL}
 */
u64 strlen_safe(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 * @brief       Safely compares two C strings.
 *
 * Performs a {NIL}-safe comparison between @param s1 and @param {s2}.
 * - Returns @const {True} if both strings have the length @const {0}.
 * - Otherwise, compares the string contents using strcmp().
 *
 * Optionally supports case-insensitive comparison if `CSTR_IGNORE_CASE` macro is defined at compile time.
 *
 * @param s1 Borrowed pointer to the first C string (may be @const {NIL}).
 * @param s2 Borrowed pointer to the second C string (may be @const {NIL}).
 *
 * @return @const {True}  if both strings are @const {NIL} or have identical contents.
 * @return @const {False} if only one is @const {NIL} or the strings differ.
 */
bool strcmp_safe(BORROWED const char * s1, BORROWED const char * s2);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 * @brief       If @param {length} is @const {0}, the function always returns @const {True}.
 */
bool strncmp_safe(BORROWED const char * s1, BORROWED const char * s2, u64 length);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 * @brief       Compares two C strings ignoring case. Other from that, similar to @func {strcmp_safe}.
 */
bool strcmp_safe_ignorecase(BORROWED const char * s1, BORROWED const char * s2);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 * @brief       If @param {length} is @const {0}, the function always returns @const {True}.
 */
bool strncmp_safe_ignorecase(BORROWED const char * s1, BORROWED const char * s2, u64 length);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 * @brief       Safely duplicates a C string.
 *
 * Creates a dynamically allocated duplicate of @param {s}.
 * - If @param s is @const {NIL}, returns a newly allocated empty string @const {""}.
 * - The result is always heap-allocated and never @const {NIL}.
 * - The caller MUST release the returned string with @func {free}.
 *
 * @param s Borrowed pointer to the source C string (may be @const {NIL}).
 * @return OWNED pointer to a heap-allocated copy of the string.
 *         Guaranteed non-{NIL} and safe to pass to @func {free}.
 */
OWNED char * strdup_safe(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_starts_with_ignorecase(BORROWED const char * s, BORROWED const char * prefix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_ends_with_ignorecase(BORROWED const char * s, BORROWED const char * suffix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_starts_with(BORROWED const char * s, BORROWED const char * prefix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_ends_with(BORROWED const char * s, BORROWED const char * suffix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_starts_with_owned(BORROWED const char * s, OWNED char * prefix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If both inputs are of length @const {0}, it also returns @const {True}.
 */
bool cstr_ends_with_owned(BORROWED const char * s, OWNED char * suffix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
char cstr_at(BORROWED const char * s, u64 idx);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
OWNED char * mk_cstr(BORROWED const char * s1, BORROWED const char * s2);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
OWNED char * mk_cstr_owned(OWNED char * s1, OWNED char * s2);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
OWNED char * mk_cstr_with_owned_suffix(BORROWED const char * s, OWNED char * suffix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    04.11.2025
 *
 */
OWNED char * mk_cstr_with_owned_prefix(BORROWED const char * s, OWNED char * prefix);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_toupper(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_toupper_owned(OWNED char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_tolower(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_tolower_owned(OWNED char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_from_char(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_from_buffer(BORROWED const u8 * buffer, const u64 size);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * mk_cstr_from_owned_buffer(OWNED u8 * buffer, const u64 size);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_digit(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_bdigit(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_odigit(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_xdigit(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_english_upperletter(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_english_lowerletter(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool cis_english_letter(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If the @param {c} is not a valid english letter, it will returned as it was.
 */
char cto_english_upperletter(const char c);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If the @param {c} is not a valid english letter, it will returned as it was.
 */
char cto_english_lowerletter(const char c);

/**
 * @since       05.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED Result * sto_integer(BORROWED const char * s);

/**
 * @since       05.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED Result * sto_integer_owned(OWNED char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       If if @param {s} is a valid integer string (either decimal or other types),
 *              returns @const {True}. Otherwise, returns @const {False}.
 */
bool sis_integer(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       This function does not care whether a "0b" or "0B" prefix is present or not.
 */
bool sis_binary_integer(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       This function does not care whether a "0o" or "0O" prefix is present or not.
 */
bool sis_octal_integer(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
bool sis_decimal_integer(BORROWED const char * s);

/**
 * @since       04.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 * @brief       This function does not care whether a "0x" or "0X" prefix is present or not.
 */
bool sis_hexadecimal_integer(BORROWED const char * s);

/**
 * @since       05.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * strrev_safe(BORROWED const char * s);

/**
 * @since       05.11.2025
 * @author      Junzhe
 * @modified    05.11.2025
 *
 */
OWNED char * strrev_safe_owned(OWNED char * s);
