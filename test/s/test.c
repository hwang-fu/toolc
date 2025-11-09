{
    printf("Testing module " CRAYON_TO_BOLD(CRAYON_TO_YELLOW("s")) "...\n");

    u64 cases = 1;

    {
        OWNED char * s = strdup_safe("abcdef");
        ASSERT_EXPR(strcmp_safe(s, "abcdef"));
        ASSERT_EXPR(strncmp_safe(s, "a", 1));
        ASSERT_EXPR(strncmp_safe(s, "ab", 2));
        ASSERT_EXPR(strncmp_safe(s, "abc", 3));
        ASSERT_EXPR(strncmp_safe(s, "abcd", 4));
        ASSERT_EXPR(strncmp_safe(s, "abcde", 5));
        ASSERT_EXPR(strncmp_safe(s, "abcdef", 6));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe("i have a dream");
        ASSERT_EXPR(cstr_starts_with(s, "i"));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe("i have dream");
        ASSERT_EXPR(cstr_ends_with(s, "dream"));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe("xxx yyy zzz");
        ASSERT_EXPR(EQ(strlen_safe(s), 11));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe(NIL);
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe("");
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = strdup_safe("once upon a time...");
        ASSERT_EXPR(EQ(strlen_safe(s), 19));
        dispose(s);
        pass(cases++);
    }

    {
        ASSERT_EXPR(!strcmp_safe("ABC", "abc"));
        pass(cases++);
    }

    {
        ASSERT_EXPR(strcmp_safe_ignorecase("ABC", "abc"));
        pass(cases++);
    }

    {
        ASSERT_EXPR(cstr_starts_with("good morning", "good"));
        ASSERT_EXPR(cstr_starts_with_ignorecase("good morning", "GoOD"));
        pass(cases++);
    }

    {
        ASSERT_EXPR(cstr_ends_with("good morning", "morning"));
        ASSERT_EXPR(cstr_ends_with_ignorecase("good morning", "MornInG"));
        pass(cases++);
    }

    {
        OWNED char * s = mk_cstr("xxx", "yyy");
        ASSERT_EXPR(EQ(strlen_safe(s), 6));
        ASSERT_EXPR(strcmp_safe(s, "xxxyyy"));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = mk_cstr("", "");
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        ASSERT_EXPR(strcmp_safe(s, ""));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = mk_cstr("", NIL);
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        ASSERT_EXPR(strcmp_safe(s, ""));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = mk_cstr(NIL, "");
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        ASSERT_EXPR(strcmp_safe(s, ""));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s = mk_cstr(NIL, NIL);
        ASSERT_EXPR(EQ(strlen_safe(s), 0));
        ASSERT_EXPR(strcmp_safe(s, ""));
        dispose(s);
        pass(cases++);
    }

    {
        OWNED char * s1 = mk_cstr_toupper("good");
        ASSERT_EXPR(strcmp_safe(s1, "GOOD"));

        OWNED char * s2 = mk_cstr_tolower("Hello Hey");
        ASSERT_EXPR(strcmp_safe(s2, "hello hey"));

        dispose(s1);
        dispose(s2);
        pass(cases++);
    }

}
