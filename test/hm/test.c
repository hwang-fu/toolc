{
    printf("Testing module " CRAYON_TO_BOLD(CRAYON_TO_YELLOW("hm")) "...\n");

    u64 cases = 1;

    {
        OWNED Hashmap * hm = mk_hm(0);
        hm_dispose(hm);
        pass(cases++);
    }

    {
        OWNED Hashmap * hm = mk_hm(0);

        ASSERT_EXPR(EQ(hm_get_capacity(hm), HASHMAP_DEFAULT_CAPACITY));

        hm_ins(hm, "one", -1);
        hm_ins(hm, "two", -2);
        hm_ins(hm, "three", -3);
        hm_ins(hm, "four", -4);
        hm_ins(hm, "five", -5);

        ASSERT_EXPR(EQ(hm_get_size(hm), 5));

        ASSERT_EQ((i64)hm_get(hm, "one"), -1);
        ASSERT_EQ((i64)hm_get(hm, "two"), -2);
        ASSERT_EQ((i64)hm_get(hm, "three"), -3);
        ASSERT_EQ((i64)hm_get(hm, "four"), -4);
        ASSERT_EQ((i64)hm_get(hm, "five"), -5);

        ASSERT_EXPR(hm_has(hm, "one"));
        ASSERT_EXPR(hm_has(hm, "two"));
        ASSERT_EXPR(hm_has(hm, "three"));
        ASSERT_EXPR(hm_has(hm, "four"));
        ASSERT_EXPR(hm_has(hm, "five"));

        hm_del(hm, "one");
        hm_del(hm, "two");
        hm_del(hm, "three");
        hm_del(hm, "four");
        hm_del(hm, "five");

        ASSERT_EXPR(!hm_has(hm, "one"));
        ASSERT_EXPR(!hm_has(hm, "two"));
        ASSERT_EXPR(!hm_has(hm, "three"));
        ASSERT_EXPR(!hm_has(hm, "four"));
        ASSERT_EXPR(!hm_has(hm, "five"));

        hm_dispose(hm);
        pass(cases++);
    }

    {
        OWNED Hashmap * hm = mk_hm(3, 100, dispose);

        hm_ins(hm, "one", strdup_safe("A"));
        hm_ins(hm, "two", strdup_safe("B"));
        hm_ins(hm, "three", strdup_safe("C"));
        hm_ins(hm, "four", strdup_safe("D"));
        hm_ins(hm, "five", strdup_safe("E"));

        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "five"), "E"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "four"), "D"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "three"), "C"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "two"), "B"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "one"), "A"));

        hm_dispose(hm);
        pass(cases++);
    }

    {
        OWNED Hashmap * hm = mk_hm(3, 100, dispose);
        OWNED char * s = NIL;

        hm_ins(hm, "one", strdup_safe("A"));

        s = (char*) hm_set(hm, "one", strdup_safe("ONE"));
        ASSERT_EXPR(strcmp_safe(s, "A"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "one"), "ONE"));
        s = dispose(s);

        s = (char*) hm_set(hm, "one", strdup_safe("1"));
        ASSERT_EXPR(strcmp_safe(s, "ONE"));
        ASSERT_EXPR(strcmp_safe((char*) hm_get(hm, "one"), "1"));
        s = dispose(s);

        hm_dispose(hm);
        pass(cases++);
    }
}
