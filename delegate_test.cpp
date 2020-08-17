//---------------------------------------------------------------------------
// Created by Morphixelf
// https://github.com/morphixelf/
// The MIT License
//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------
#include "delegate.h"
typedef delegate<const char *, int, int> func_a;
typedef delegate<bool, const func_a &> func_b;
typedef delegate<void, bool> func_c;
//---------------------------------------------------------------------------
class Test
{
public:
    const char *a(int x, int y)
    {
        printf("Test::a(%d,%d);\r\n",x,y);
        return "abcdef";
    }
    bool b(const func_a &func) const
    {
        const char *s = func(123,456);
        printf("Test::b(\"%s\");\r\n",s);
        return true;
    }
    static void c(bool f)
    {
        printf("Test::c(%s);\r\n",(f?"true":"false"));
    }
};
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    Test obj;
    func_a a = func_a::from_method<Test,&Test::a>(&obj);
    func_b b = func_b::from_const_method<Test,&Test::b>(&obj);
    func_c c = Test::c;

    c( b( a ) );

    system("pause");
    return 0;
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
