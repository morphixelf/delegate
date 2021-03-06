//---------------------------------------------------------------------------
// Generated by delegate_gen.exe
// https://github.com/morphixelf/delegate
// The MIT License
//---------------------------------------------------------------------------
#ifndef __delegate__
#define __delegate__
//---------------------------------------------------------------------------
template <class func_type>
union delegate_ptr
{
    void *obj;
    func_type func;
    delegate_ptr() {}
    delegate_ptr(void *ptr) : obj(ptr) {}
    delegate_ptr(func_type ptr) : func(ptr) {}
};
//---------------------------------------------------------------------------
template <class ret_type, class type1 = void, class type2 = void, class type3 = void, class type4 = void>
class delegate
{
private:
    typedef delegate<ret_type, type1, type2, type3, type4> delegate_type;
    typedef ret_type (*func_type)(type1, type2, type3, type4);
    typedef delegate_ptr<func_type> ptr_type;
    typedef ret_type (*wrap_type)(const ptr_type &, type1, type2, type3, type4);

    ptr_type ptr;
    wrap_type wrap;

    static ret_type func_wrap(const ptr_type &ptr, type1 v1, type2 v2, type3 v3, type4 v4)
    {
        return ptr.func(v1, v2, v3, v4);
    }

    template <class _ret_type, class _type1, class _type2, class _type3, class _type4, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2, _type3, _type4)>
    static _ret_type method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3, _type4 v4)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3, v4);
    }

    template <class _ret_type, class _type1, class _type2, class _type3, class _type4, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2, _type3, _type4) const>
    static _ret_type const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3, _type4 v4)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3, v4);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    ret_type operator()(type1 v1, type2 v2, type3 v3, type4 v4) const
    {
        return (*wrap)(ptr, v1, v2, v3, v4);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2, type3, type4)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<ret_type, type1, type2, type3, type4, obj_type, method_type>);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2, type3, type4) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<ret_type, type1, type2, type3, type4, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class type1, class type2, class type3, class type4>
class delegate<void, type1, type2, type3, type4>
{
private:
    typedef delegate<void, type1, type2, type3, type4> delegate_type;
    typedef void (*func_type)(type1, type2, type3, type4);
    typedef delegate_ptr<func_type> ptr_type;
    typedef void (*wrap_type)(const ptr_type &, type1, type2, type3, type4);

    ptr_type ptr;
    wrap_type wrap;

    static void func_wrap(const ptr_type &ptr, type1 v1, type2 v2, type3 v3, type4 v4)
    {
        ptr.func(v1, v2, v3, v4);
    }

    template <class _type1, class _type2, class _type3, class _type4, class obj_type, void (obj_type::*method_type)(_type1, _type2, _type3, _type4)>
    static void method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3, _type4 v4)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3, v4);
    }

    template <class _type1, class _type2, class _type3, class _type4, class obj_type, void (obj_type::*method_type)(_type1, _type2, _type3, _type4) const>
    static void const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3, _type4 v4)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3, v4);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    void operator()(type1 v1, type2 v2, type3 v3, type4 v4) const
    {
        (*wrap)(ptr, v1, v2, v3, v4);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2, type3, type4)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<type1, type2, type3, type4, obj_type, method_type>);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2, type3, type4) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<type1, type2, type3, type4, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class ret_type, class type1, class type2, class type3>
class delegate<ret_type, type1, type2, type3>
{
private:
    typedef delegate<ret_type, type1, type2, type3> delegate_type;
    typedef ret_type (*func_type)(type1, type2, type3);
    typedef delegate_ptr<func_type> ptr_type;
    typedef ret_type (*wrap_type)(const ptr_type &, type1, type2, type3);

    ptr_type ptr;
    wrap_type wrap;

    static ret_type func_wrap(const ptr_type &ptr, type1 v1, type2 v2, type3 v3)
    {
        return ptr.func(v1, v2, v3);
    }

    template <class _ret_type, class _type1, class _type2, class _type3, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2, _type3)>
    static _ret_type method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3);
    }

    template <class _ret_type, class _type1, class _type2, class _type3, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2, _type3) const>
    static _ret_type const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    ret_type operator()(type1 v1, type2 v2, type3 v3) const
    {
        return (*wrap)(ptr, v1, v2, v3);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2, type3)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<ret_type, type1, type2, type3, obj_type, method_type>);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2, type3) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<ret_type, type1, type2, type3, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class type1, class type2, class type3>
class delegate<void, type1, type2, type3>
{
private:
    typedef delegate<void, type1, type2, type3> delegate_type;
    typedef void (*func_type)(type1, type2, type3);
    typedef delegate_ptr<func_type> ptr_type;
    typedef void (*wrap_type)(const ptr_type &, type1, type2, type3);

    ptr_type ptr;
    wrap_type wrap;

    static void func_wrap(const ptr_type &ptr, type1 v1, type2 v2, type3 v3)
    {
        ptr.func(v1, v2, v3);
    }

    template <class _type1, class _type2, class _type3, class obj_type, void (obj_type::*method_type)(_type1, _type2, _type3)>
    static void method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3);
    }

    template <class _type1, class _type2, class _type3, class obj_type, void (obj_type::*method_type)(_type1, _type2, _type3) const>
    static void const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2, _type3 v3)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2, v3);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    void operator()(type1 v1, type2 v2, type3 v3) const
    {
        (*wrap)(ptr, v1, v2, v3);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2, type3)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<type1, type2, type3, obj_type, method_type>);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2, type3) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<type1, type2, type3, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class ret_type, class type1, class type2>
class delegate<ret_type, type1, type2>
{
private:
    typedef delegate<ret_type, type1, type2> delegate_type;
    typedef ret_type (*func_type)(type1, type2);
    typedef delegate_ptr<func_type> ptr_type;
    typedef ret_type (*wrap_type)(const ptr_type &, type1, type2);

    ptr_type ptr;
    wrap_type wrap;

    static ret_type func_wrap(const ptr_type &ptr, type1 v1, type2 v2)
    {
        return ptr.func(v1, v2);
    }

    template <class _ret_type, class _type1, class _type2, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2)>
    static _ret_type method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2);
    }

    template <class _ret_type, class _type1, class _type2, class obj_type, _ret_type (obj_type::*method_type)(_type1, _type2) const>
    static _ret_type const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    ret_type operator()(type1 v1, type2 v2) const
    {
        return (*wrap)(ptr, v1, v2);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<ret_type, type1, type2, obj_type, method_type>);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1, type2) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<ret_type, type1, type2, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class type1, class type2>
class delegate<void, type1, type2>
{
private:
    typedef delegate<void, type1, type2> delegate_type;
    typedef void (*func_type)(type1, type2);
    typedef delegate_ptr<func_type> ptr_type;
    typedef void (*wrap_type)(const ptr_type &, type1, type2);

    ptr_type ptr;
    wrap_type wrap;

    static void func_wrap(const ptr_type &ptr, type1 v1, type2 v2)
    {
        ptr.func(v1, v2);
    }

    template <class _type1, class _type2, class obj_type, void (obj_type::*method_type)(_type1, _type2)>
    static void method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2);
    }

    template <class _type1, class _type2, class obj_type, void (obj_type::*method_type)(_type1, _type2) const>
    static void const_method_wrap(const ptr_type &ptr, _type1 v1, _type2 v2)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1, v2);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    void operator()(type1 v1, type2 v2) const
    {
        (*wrap)(ptr, v1, v2);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<type1, type2, obj_type, method_type>);
    }

    template <class obj_type, void (obj_type::*method_type)(type1, type2) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<type1, type2, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class ret_type, class type1>
class delegate<ret_type, type1>
{
private:
    typedef delegate<ret_type, type1> delegate_type;
    typedef ret_type (*func_type)(type1);
    typedef delegate_ptr<func_type> ptr_type;
    typedef ret_type (*wrap_type)(const ptr_type &, type1);

    ptr_type ptr;
    wrap_type wrap;

    static ret_type func_wrap(const ptr_type &ptr, type1 v1)
    {
        return ptr.func(v1);
    }

    template <class _ret_type, class _type1, class obj_type, _ret_type (obj_type::*method_type)(_type1)>
    static _ret_type method_wrap(const ptr_type &ptr, _type1 v1)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1);
    }

    template <class _ret_type, class _type1, class obj_type, _ret_type (obj_type::*method_type)(_type1) const>
    static _ret_type const_method_wrap(const ptr_type &ptr, _type1 v1)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)(v1);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    ret_type operator()(type1 v1) const
    {
        return (*wrap)(ptr, v1);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<ret_type, type1, obj_type, method_type>);
    }

    template <class obj_type, ret_type (obj_type::*method_type)(type1) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<ret_type, type1, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class type1>
class delegate<void, type1>
{
private:
    typedef delegate<void, type1> delegate_type;
    typedef void (*func_type)(type1);
    typedef delegate_ptr<func_type> ptr_type;
    typedef void (*wrap_type)(const ptr_type &, type1);

    ptr_type ptr;
    wrap_type wrap;

    static void func_wrap(const ptr_type &ptr, type1 v1)
    {
        ptr.func(v1);
    }

    template <class _type1, class obj_type, void (obj_type::*method_type)(_type1)>
    static void method_wrap(const ptr_type &ptr, _type1 v1)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1);
    }

    template <class _type1, class obj_type, void (obj_type::*method_type)(_type1) const>
    static void const_method_wrap(const ptr_type &ptr, _type1 v1)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)(v1);
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    void operator()(type1 v1) const
    {
        (*wrap)(ptr, v1);
    }

    template <class obj_type, void (obj_type::*method_type)(type1)>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<type1, obj_type, method_type>);
    }

    template <class obj_type, void (obj_type::*method_type)(type1) const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<type1, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <class ret_type>
class delegate<ret_type>
{
private:
    typedef delegate<ret_type> delegate_type;
    typedef ret_type (*func_type)();
    typedef delegate_ptr<func_type> ptr_type;
    typedef ret_type (*wrap_type)(const ptr_type &);

    ptr_type ptr;
    wrap_type wrap;

    static ret_type func_wrap(const ptr_type &ptr)
    {
        return ptr.func();
    }

    template <class _ret_type, class obj_type, _ret_type (obj_type::*method_type)()>
    static _ret_type method_wrap(const ptr_type &ptr)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)();
    }

    template <class _ret_type, class obj_type, _ret_type (obj_type::*method_type)() const>
    static _ret_type const_method_wrap(const ptr_type &ptr)
    {
        return (static_cast<obj_type *>(ptr.obj)->*method_type)();
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    ret_type operator()() const
    {
        return (*wrap)(ptr);
    }

    template <class obj_type, ret_type (obj_type::*method_type)()>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<ret_type, obj_type, method_type>);
    }

    template <class obj_type, ret_type (obj_type::*method_type)() const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<ret_type, obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
template <>
class delegate<void>
{
private:
    typedef delegate<void> delegate_type;
    typedef void (*func_type)();
    typedef delegate_ptr<func_type> ptr_type;
    typedef void (*wrap_type)(const ptr_type &);

    ptr_type ptr;
    wrap_type wrap;

    static void func_wrap(const ptr_type &ptr)
    {
        ptr.func();
    }

    template <class obj_type, void (obj_type::*method_type)()>
    static void method_wrap(const ptr_type &ptr)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)();
    }

    template <class obj_type, void (obj_type::*method_type)() const>
    static void const_method_wrap(const ptr_type &ptr)
    {
        (static_cast<obj_type *>(ptr.obj)->*method_type)();
    }

    delegate(void *p, wrap_type s)
        : ptr(p)
        , wrap(s)
    {}
public:
    delegate()
        : wrap(0)
    {}

    delegate(func_type func_ptr)
        : ptr(func_ptr)
        , wrap(&func_wrap)
    {}

    operator bool() const
    {
        return wrap != 0;
    }

    void operator()() const
    {
        (*wrap)(ptr);
    }

    template <class obj_type, void (obj_type::*method_type)()>
    static delegate_type from_method(obj_type *obj_ptr)
    {
        return delegate_type(obj_ptr, &method_wrap<obj_type, method_type>);
    }

    template <class obj_type, void (obj_type::*method_type)() const>
    static delegate_type from_const_method(const obj_type *obj_ptr)
    {
        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<obj_type, method_type>);
    }
};
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
