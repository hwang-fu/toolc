{
    u64 cases = 1;

    {
        Dequeue * dq = mk_dq(0);
        if (EQ(dq, NIL))
        {
            fail(cases);
        }
        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(0);
        dq_pushback(dq, 1);
        dq_pushback(dq, 2);
        dq_pushback(dq, 3);
        dq_pushback(dq, 4);
        dq_pushback(dq, 5);

        ASSERT_EXPR(EQ(
                    dq_popback(dq),
                    5
        ));
        ASSERT_EXPR(EQ(
                    dq_popback(dq),
                    4
        ));
        ASSERT_EXPR(EQ(
                    dq_popback(dq),
                    3
        ));
        ASSERT_EXPR(EQ(
                    dq_popback(dq),
                    2
        ));
        ASSERT_EXPR(EQ(
                    dq_popback(dq),
                    1
        ));

        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(0);
        dq_pushback(dq, 1);
        dq_pushback(dq, 2);
        dq_pushback(dq, 3);
        dq_pushback(dq, 4);
        dq_pushback(dq, 5);

        ASSERT_EXPR(EQ(
                    dq_popfront(dq),
                    1
        ));
        ASSERT_EXPR(EQ(
                    dq_popfront(dq),
                    2
        ));
        ASSERT_EXPR(EQ(
                    dq_popfront(dq),
                    3
        ));
        ASSERT_EXPR(EQ(
                    dq_popfront(dq),
                    4
        ));
        ASSERT_EXPR(EQ(
                    dq_popfront(dq),
                    5
        ));

        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(2, dispose);
        dq_pushback(dq, strdup_safe("A"));
        dq_pushback(dq, strdup_safe("B"));
        dq_pushback(dq, strdup_safe("C"));
        dq_pushback(dq, strdup_safe("D"));
        dq_dispose(dq);

        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(3, 0, dispose);
        dq_pushback(dq, strdup_safe("A"));
        dq_pushback(dq, strdup_safe("B"));
        dq_pushback(dq, strdup_safe("C"));
        dq_pushback(dq, strdup_safe("D"));

        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(3, 2, dispose);
        dq_pushback(dq, strdup_safe("A"));
        dq_pushback(dq, strdup_safe("B"));
        dq_pushback(dq, strdup_safe("C"));
        dq_pushback(dq, strdup_safe("D"));
        dq_pushback(dq, strdup_safe("a"));
        dq_pushback(dq, strdup_safe("b"));
        dq_pushback(dq, strdup_safe("c"));
        dq_pushback(dq, strdup_safe("d"));

        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * dq = mk_dq(3, 2, dispose);

        dq_pushback(dq, strdup_safe("A"));
        dq_pushback(dq, strdup_safe("B"));
        dq_pushback(dq, strdup_safe("C"));
        dq_pushback(dq, strdup_safe("D"));
        dq_pushback(dq, strdup_safe("a"));
        dq_pushback(dq, strdup_safe("b"));
        dq_pushback(dq, strdup_safe("c"));
        dq_pushback(dq, strdup_safe("d"));

        ASSERT_EXPR(EQ(dq_get_size(dq), 8));
        ASSERT_EXPR(dq_get_capacity(dq) > 2);

        char * s = NIL;

        s = (char *) dq_popback(dq);
        ASSERT_EXPR(
                strcmp_safe("d", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 7));

        s = (char *) dq_popback(dq);
        ASSERT_EXPR(
                strcmp_safe("c", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 6));

        s = (char *) dq_popback(dq);
        ASSERT_EXPR(
                strcmp_safe("b", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 5));

        s = (char *) dq_popback(dq);
        ASSERT_EXPR(
                strcmp_safe("a", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 4));

        s = (char *) dq_popfront(dq);
        ASSERT_EXPR(
                strcmp_safe("A", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 3));

        s = (char *) dq_popfront(dq);
        ASSERT_EXPR(
                strcmp_safe("B", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 2));

        s = (char *) dq_popfront(dq);
        ASSERT_EXPR(
                strcmp_safe("C", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 1));

        s = (char *) dq_popfront(dq);
        ASSERT_EXPR(
                strcmp_safe("D", s)
        );
        dispose(s);
        ASSERT_EXPR(EQ(dq_get_size(dq), 0));

        dq_dispose(dq);
        pass(cases++);
    }

    {
        Dequeue * nested = mk_dq(2, dq_dispose);

        Dequeue * dq1 = mk_dq(0);
        Dequeue * dq2 = mk_dq(0);
        Dequeue * dq3 = mk_dq(2, dispose);

        dq_pushback(nested, dq1);
        dq_pushback(nested, dq2);
        dq_pushback(nested, dq3);

        ASSERT_EXPR(EQ(dq_get_size(nested), 3));

        dq_pushback(dq3, strdup_safe("lorem"));
        dq_pushback(dq3, strdup_safe("ipsum"));

        ASSERT_EXPR(EQ(dq_get_size((Dequeue*) dq_at(nested, 2)), 2));

        dq_dispose(nested);
        pass(cases++);
    }
}
