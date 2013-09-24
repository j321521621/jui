#pragma once
namespace thread
{
class task
{
public:
    virtual void run()=0;
};

template<class Tobj, class Tpfunc>
class class_task_0:public task
{
public:
    class_task_0(Tobj obj,Tpfunc pfunc):
    m_obj(obj),
    m_pfunc(pfunc)
    {}

    void run()
    {
        (m_obj->*m_pfunc)();
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
};

template<class Tobj, class Tpfunc,class Targ1>
class class_task_1:public task
{
public:
    class_task_1(Tobj obj,Tpfunc pfunc,Targ1 arg1):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2>
class class_task_2:public task
{
public:
    class_task_2(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3>
class class_task_3:public task
{
public:
    class_task_3(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4>
class class_task_4:public task
{
public:
    class_task_4(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5>
class class_task_5:public task
{
public:
    class_task_5(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6>
class class_task_6:public task
{
public:
    class_task_6(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7>
class class_task_7:public task
{
public:
    class_task_7(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8>
class class_task_8:public task
{
public:
    class_task_8(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7),
    m_arg8(arg8)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7,m_arg8);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
    Targ8 m_arg8;
};

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8,class Targ9>
class class_task_9:public task
{
public:
    class_task_9(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8,Targ9 arg9):
    m_obj(obj),
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7),
    m_arg8(arg8),
    m_arg9(arg9)
    {}

    void run()
    {
        (m_obj->*m_pfunc)(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7,m_arg8,m_arg9);
    }

private:
    Tobj m_obj;
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
    Targ8 m_arg8;
    Targ9 m_arg9;
};

template<class Tobj, class Tpfunc>
task* cctask(Tobj obj,Tpfunc pfunc)
{
    return new class_task_0<Tobj,Tpfunc>(obj,pfunc);
}

template<class Tobj, class Tpfunc,class Targ1>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1)
{
    return new class_task_1<Tobj,Tpfunc,Targ1>(obj,pfunc,arg1);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2)
{
    return new class_task_2<Tobj,Tpfunc,Targ1,Targ2>(obj,pfunc,arg1,arg2);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3)
{
    return new class_task_3<Tobj,Tpfunc,Targ1,Targ2,Targ3>(obj,pfunc,arg1,arg2,arg3);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4)
{
    return new class_task_4<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4>(obj,pfunc,arg1,arg2,arg3,arg4);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5)
{
    return new class_task_5<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5>(obj,pfunc,arg1,arg2,arg3,arg4,arg5);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6)
{
    return new class_task_6<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6>(obj,pfunc,arg1,arg2,arg3,arg4,arg5,arg6);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7)
{
    return new class_task_7<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7>(obj,pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8)
{
    return new class_task_8<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7,Targ8>(obj,pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);
}

template<class Tobj, class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8,class Targ9>
task* cctask(Tobj obj,Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8,Targ9 arg9)
{
    return new class_task_9<Tobj,Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7,Targ8,Targ9>(obj,pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
}

template<class Tpfunc>
class function_task_0:public task
{
public:
    function_task_0(Tpfunc pfunc):
    m_pfunc(pfunc)
    {}

    void run()
    {
        m_pfunc();
    }

private:
    Tpfunc m_pfunc;
};

template<class Tpfunc,class Targ1>
class function_task_1:public task
{
public:
    function_task_1(Tpfunc pfunc,Targ1 arg1):
    m_pfunc(pfunc),
    m_arg1(arg1)
    {}

    void run()
    {
        m_pfunc(m_arg1);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
};

template<class Tpfunc,class Targ1,class Targ2>
class function_task_2:public task
{
public:
    function_task_2(Tpfunc pfunc,Targ1 arg1,Targ2 arg2):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3>
class function_task_3:public task
{
public:
    function_task_3(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4>
class function_task_4:public task
{
public:
    function_task_4(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5>
class function_task_5:public task
{
public:
    function_task_5(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6>
class function_task_6:public task
{
public:
    function_task_6(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7>
class function_task_7:public task
{
public:
    function_task_7(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8>
class function_task_8:public task
{
public:
    function_task_8(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7),
    m_arg8(arg8)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7,m_arg8);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
    Targ8 m_arg8;
};

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8,class Targ9>
class function_task_9:public task
{
public:
    function_task_9(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8,Targ9 arg9):
    m_pfunc(pfunc),
    m_arg1(arg1),
    m_arg2(arg2),
    m_arg3(arg3),
    m_arg4(arg4),
    m_arg5(arg5),
    m_arg6(arg6),
    m_arg7(arg7),
    m_arg8(arg8),
    m_arg9(arg9)
    {}

    void run()
    {
        m_pfunc(m_arg1,m_arg2,m_arg3,m_arg4,m_arg5,m_arg6,m_arg7,m_arg8,m_arg9);
    }

private:
    Tpfunc m_pfunc;
    Targ1 m_arg1;
    Targ2 m_arg2;
    Targ3 m_arg3;
    Targ4 m_arg4;
    Targ5 m_arg5;
    Targ6 m_arg6;
    Targ7 m_arg7;
    Targ8 m_arg8;
    Targ9 m_arg9;
};

template<class Tpfunc>
task* cftask(Tpfunc pfunc)
{
    return new function_task_0<Tpfunc>(pfunc);
}

template<class Tpfunc,class Targ1>
task* cftask(Tpfunc pfunc,Targ1 arg1)
{
    return new function_task_1<Tpfunc,Targ1>(pfunc,arg1);
}

template<class Tpfunc,class Targ1,class Targ2>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2)
{
    return new function_task_2<Tpfunc,Targ1,Targ2>(pfunc,arg1,arg2);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3)
{
    return new function_task_3<Tpfunc,Targ1,Targ2,Targ3>(pfunc,arg1,arg2,arg3);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4)
{
    return new function_task_4<Tpfunc,Targ1,Targ2,Targ3,Targ4>(pfunc,arg1,arg2,arg3,arg4);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5)
{
    return new function_task_5<Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5>(pfunc,arg1,arg2,arg3,arg4,arg5);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6)
{
    return new function_task_6<Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6>(pfunc,arg1,arg2,arg3,arg4,arg5,arg6);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7)
{
    return new function_task_7<Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7>(pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8)
{
    return new function_task_8<Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7,Targ8>(pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8);
}

template<class Tpfunc,class Targ1,class Targ2,class Targ3,class Targ4,class Targ5,class Targ6,class Targ7,class Targ8,class Targ9>
task* cftask(Tpfunc pfunc,Targ1 arg1,Targ2 arg2,Targ3 arg3,Targ4 arg4,Targ5 arg5,Targ6 arg6,Targ7 arg7,Targ8 arg8,Targ9 arg9)
{
    return new function_task_9<Tpfunc,Targ1,Targ2,Targ3,Targ4,Targ5,Targ6,Targ7,Targ8,Targ9>(pfunc,arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9);
}


};
