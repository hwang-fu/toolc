{
    u64 cases = 1;

    {
        Dequeue * dq = mk_dq(0);
        ASSERT_EXPR(NEQ(dq, NIL));
        dq_dispose(dq);
        pass(cases++);
    }

    {
    }
}
