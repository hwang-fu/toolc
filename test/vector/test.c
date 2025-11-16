{
    printf("Testing module " CRAYON_TO_BOLD(CRAYON_TO_YELLOW("vector")) "...\n");
    u64 cases = 1;

    {
        OWNED Vector * vector = mk_vector(0);
        ASSERT_EXPR(NEQ(vector, NIL));
        vector_dispose(vector);
        pass(cases++);
    }

    {
        OWNED Vector * vector = mk_vector(0);
        vector_pushback(vector, 1, NIL);
        vector_pushback(vector, 2, NIL);
        vector_pushback(vector, 3, NIL);
        vector_pushback(vector, 4, NIL);
        vector_pushback(vector, 5, NIL);

        ASSERT_EXPR(EQ(
                    vector_popback(vector),
                    5
        ));
        ASSERT_EXPR(EQ(
                    vector_popback(vector),
                    4
        ));
        ASSERT_EXPR(EQ(
                    vector_popback(vector),
                    3
        ));
        ASSERT_EXPR(EQ(
                    vector_popback(vector),
                    2
        ));
        ASSERT_EXPR(EQ(
                    vector_popback(vector),
                    1
        ));

        vector_dispose(vector);
        pass(cases++);
    }

    {
        OWNED Vector * vector = mk_vector(0);
        vector_pushback(vector, 1, NIL);
        vector_pushback(vector, 2, NIL);
        vector_pushback(vector, 3, NIL);
        vector_pushback(vector, 4, NIL);
        vector_pushback(vector, 5, NIL);

        ASSERT_EXPR(EQ(
                    vector_popfront(vector),
                    1
        ));
        ASSERT_EXPR(EQ(
                    vector_popfront(vector),
                    2
        ));
        ASSERT_EXPR(EQ(
                    vector_popfront(vector),
                    3
        ));
        ASSERT_EXPR(EQ(
                    vector_popfront(vector),
                    4
        ));
        ASSERT_EXPR(EQ(
                    vector_popfront(vector),
                    5
        ));

        vector_dispose(vector);
        pass(cases++);
    }

    {
        OWNED Vector * vector = mk_vector(0);
        vector_pushback(vector, strdup_safe("A"), dispose);
        vector_pushback(vector, strdup_safe("B"), dispose);
        vector_pushback(vector, strdup_safe("C"), dispose);
        vector_pushback(vector, strdup_safe("D"), dispose);
        vector_dispose(vector);
        pass(cases++);
    }

    {
        OWNED Vector * vector = mk_vector(0);

        vector_pushback(vector, strdup_safe("A"), dispose);
        vector_pushback(vector, strdup_safe("B"), dispose);
        vector_pushback(vector, strdup_safe("C"), dispose);
        vector_pushback(vector, strdup_safe("D"), dispose);
        vector_pushback(vector, strdup_safe("a"), dispose);
        vector_pushback(vector, strdup_safe("b"), dispose);
        vector_pushback(vector, strdup_safe("c"), dispose);
        vector_pushback(vector, strdup_safe("d"), dispose);

        ASSERT_EXPR(EQ(vector_get_size(vector), 8));
        ASSERT_EXPR(vector_get_capacity(vector) > 2);

        char * s = NIL;

        s = (char *) vector_popback(vector);
        ASSERT_EXPR(
                strcmp_safe("d", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 7));

        s = (char *) vector_popback(vector);
        ASSERT_EXPR(
                strcmp_safe("c", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 6));

        s = (char *) vector_popback(vector);
        ASSERT_EXPR(
                strcmp_safe("b", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 5));

        s = (char *) vector_popback(vector);
        ASSERT_EXPR(
                strcmp_safe("a", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 4));

        s = (char *) vector_popfront(vector);
        ASSERT_EXPR(
                strcmp_safe("A", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 3));

        s = (char *) vector_popfront(vector);
        ASSERT_EXPR(
                strcmp_safe("B", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 2));

        s = (char *) vector_popfront(vector);
        ASSERT_EXPR(
                strcmp_safe("C", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 1));

        s = (char *) vector_popfront(vector);
        ASSERT_EXPR(
                strcmp_safe("D", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(vector_get_size(vector), 0));

        vector_dispose(vector);
        pass(cases++);
    }

    {
        OWNED Vector * nested = mk_vector(0);

        OWNED Vector * vector1 = mk_vector(0);
        OWNED Vector * vector2 = mk_vector(0);
        OWNED Vector * vector3 = mk_vector(0);

        vector_pushback(nested, vector1, vector_dispose);
        vector_pushback(nested, vector2, vector_dispose);
        vector_pushback(nested, vector3, vector_dispose);

        ASSERT_EXPR(EQ(vector_get_size(nested), 3));

        vector_pushback(vector3, strdup_safe("lorem"), dispose);
        vector_pushback(vector3, strdup_safe("ipsum"), dispose);

        ASSERT_EXPR(EQ(vector_get_size((OWNED Vector*) vector_at(nested, 2)), 2));

        vector_dispose(nested);
        pass(cases++);
    }

}
