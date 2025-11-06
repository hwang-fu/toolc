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
}
