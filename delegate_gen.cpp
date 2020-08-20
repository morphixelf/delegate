//---------------------------------------------------------------------------
// Created by Morphixelf
// https://github.com/morphixelf/
// The MIT License
//---------------------------------------------------------------------------
/*
   Based on the article by Sergey Ryazanov:
   "The Impossibly Fast C++ Delegates", 18 Jul 2005
   https://www.codeproject.com/articles/11015/the-impossibly-fast-c-delegates
*/
//---------------------------------------------------------------------------
#include <string>       // std::string
#include <iostream>     // std::ostream
#include <sstream>      // std::ostringstream
#include <stdlib.h>     // strtol
#include <fstream>      // std::ofstream
//---------------------------------------------------------------------------
class CodeGen
{
protected:
    std::ostream &out;

    std::string List(const std::string &Item, int ItemsCount, const std::string &After = "")
    {
        std::ostringstream oss;
        for (int i = 1; i <= ItemsCount; ++i)
        {
            if (i > 1) oss << ", ";
            oss << Item << i << After;
        }
        return oss.str();
    }
    std::string List(const std::string &Item1, const std::string &Item2, int ItemsCount)
    {
        std::ostringstream oss;
        for (int i = 1; i <= ItemsCount; ++i)
        {
            if (i > 1) oss << ", ";
            oss << Item1 << i << " " << Item2 << i;
        }
        return oss.str();
    }
    std::string Join(std::string s1, std::string s2, std::string s3 = "", std::string s4 = "")
    {
        bool f = false;
        std::ostringstream oss;
        if (!s1.empty()) {f = true; oss << s1;}
        if (!s2.empty()) {if (f) oss << ", "; else f = true; oss << s2;}
        if (!s3.empty()) {if (f) oss << ", "; else f = true; oss << s3;}
        if (!s4.empty()) {if (f) oss << ", "; oss << s4;}
        return oss.str();
    }
    std::string Pack(std::string Left, std::string Value, std::string Right)
    {
        return Value.empty() ? Value : Left + Value + Right;
    }
public:
    CodeGen(std::ostream &os)
        : out(os)
    {
    }
    void AddLine(const char *s)
    {
        out << s << std::endl;
    }
    void AddLine(const std::string &s)
    {
        if (s.empty()) return;
        out << s << std::endl;
    }
    void AddSeparator()
    {
        AddLine("//---------------------------------------------------------------------------");
    }
    void AddDelegate(bool RetVal, int ArgsCount, bool Primary = false)
    {
        std::string class_name = "delegate";

        std::string ret_type   = RetVal ? "ret_type" : "void";
        std::string _ret_type  = RetVal ? "_ret_type" : "void";
        std::string return_cmd = RetVal ? "return " : "";

        std::string typename_list  = List("class type",ArgsCount,(Primary? " = void" : ""));
        std::string _typename_list = List("class _type",ArgsCount);
        std::string type_list      = List("type",ArgsCount);
        std::string _type_list     = List("_type",ArgsCount);
        std::string type_val_list  = List("type","v",ArgsCount);
        std::string _type_val_list = List("_type","v",ArgsCount);
        std::string val_list       = List("v",ArgsCount);

        std::string template_args          = Join((RetVal ? "class ret_type" : ""),typename_list);
        std::string template_params        = Join((RetVal ? "ret_type" : "void"),type_list);
        std::string wrap_type_args         = Join("const ptr_type &",type_list);
        std::string func_wrap_args         = Join("const ptr_type &ptr",type_val_list);
        std::string method_wrap_templ_args = Join((RetVal ? "class _ret_type" : ""),_typename_list,"class obj_type",_ret_type+" (obj_type::*method_type)("+_type_list+")");
        std::string method_wrap_args       = Join("const ptr_type &ptr",_type_val_list);
        std::string wrap_params            = Join("ptr",val_list);
        std::string wrap_templ_params      = Join((RetVal ? "ret_type" : ""),type_list,"obj_type","method_type");

        std::string class_templ_params = Pack("<",template_params,">");
        std::string class_templ_specs  = (Primary? std::string("") : class_templ_params);

        AddLine("template <"+template_args+">");
        AddLine("class "+class_name+class_templ_specs);
        AddLine("{");
        AddLine("private:");
        AddLine("    typedef "+class_name+class_templ_params+" delegate_type;");
        AddLine("    typedef "+ret_type+" (*func_type)("+type_list+");");
        AddLine("    typedef delegate_ptr<func_type> ptr_type;");
        AddLine("    typedef "+ret_type+" (*wrap_type)("+wrap_type_args+");");
        AddLine("");
        AddLine("    ptr_type ptr;");
        AddLine("    wrap_type wrap;");
        AddLine("");
        AddLine("    static "+ret_type+" func_wrap("+func_wrap_args+")");
        AddLine("    {");
        AddLine("        "+return_cmd+"ptr.func("+val_list+");");
        AddLine("    }");
        AddLine("");
        AddLine("    template <"+method_wrap_templ_args+">");
        AddLine("    static "+_ret_type+" method_wrap("+method_wrap_args+")");
        AddLine("    {");
        AddLine("        "+return_cmd+"(static_cast<obj_type *>(ptr.obj)->*method_type)("+val_list+");");
        AddLine("    }");
        AddLine("");
        AddLine("    template <"+method_wrap_templ_args+" const>");
        AddLine("    static "+_ret_type+" const_method_wrap("+method_wrap_args+")");
        AddLine("    {");
        AddLine("        "+return_cmd+"(static_cast<obj_type *>(ptr.obj)->*method_type)("+val_list+");");
        AddLine("    }");
        AddLine("");
        AddLine("    "+class_name+"(void *p, wrap_type s)");
        AddLine("        : ptr(p)");
        AddLine("        , wrap(s)");
        AddLine("    {}");
        AddLine("public:");
        AddLine("    "+class_name+"()");
        AddLine("        : wrap(0)");
        AddLine("    {}");
        AddLine("");
        AddLine("    "+class_name+"(func_type func_ptr)");
        AddLine("        : ptr(func_ptr)");
        AddLine("        , wrap(&func_wrap)");
        AddLine("    {}");
        AddLine("");
        AddLine("    operator bool() const");
        AddLine("    {");
        AddLine("        return wrap != 0;");
        AddLine("    }");
        AddLine("");
        AddLine("    "+ret_type+" operator()("+type_val_list+") const");
        AddLine("    {");
        AddLine("        "+return_cmd+"(*wrap)("+wrap_params+");");
        AddLine("    }");
        AddLine("");
        AddLine("    template <class obj_type, "+ret_type+" (obj_type::*method_type)("+type_list+")>");
        AddLine("    static delegate_type from_method(obj_type *obj_ptr)");
        AddLine("    {");
        AddLine("        return delegate_type(obj_ptr, &method_wrap<"+wrap_templ_params+">);");
        AddLine("    }");
        AddLine("");
        AddLine("    template <class obj_type, "+ret_type+" (obj_type::*method_type)("+type_list+") const>");
        AddLine("    static delegate_type from_const_method(const obj_type *obj_ptr)");
        AddLine("    {");
        AddLine("        return delegate_type(const_cast<obj_type *>(obj_ptr), &const_method_wrap<"+wrap_templ_params+">);");
        AddLine("    }");
        AddLine("};");
    }
    void Generate(int max_arg_count)
    {
        AddSeparator();
        AddLine("// Generated by delegate_gen.exe");
        AddLine("// https://github.com/morphixelf/delegate");
        AddLine("// The MIT License");
        AddSeparator();
        AddLine("#ifndef __delegate__");
        AddLine("#define __delegate__");
        AddSeparator();
        AddLine("template <class func_type>");
        AddLine("union delegate_ptr");
        AddLine("{");
        AddLine("    void *obj;");
        AddLine("    func_type func;");
        AddLine("    delegate_ptr() {}");
        AddLine("    delegate_ptr(void *ptr) : obj(ptr) {}");
        AddLine("    delegate_ptr(func_type ptr) : func(ptr) {}");
        AddLine("};");
        AddSeparator();

        for (int i=max_arg_count; i>=0; --i)
        {
            AddDelegate(true,i, i==max_arg_count);
            AddSeparator();
            AddDelegate(false,i);
            AddSeparator();
        }

        AddLine("#endif");
        AddSeparator();
    }
};
//---------------------------------------------------------------------------
int atoi(const char *str, int def_val)
{
    if (!*str) return def_val;
    char *p;
    int val = strtol(str,&p,10);
    return *p ? def_val : val;
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int max_args_count = argc > 1 ? atoi(argv[1],-1) : 4;
    if (max_args_count < 0) return 1;

    std::ofstream ofs("delegate.h");
    if (!ofs.good()) return 2;

    CodeGen cg(ofs);
    cg.Generate(max_args_count);

    ofs.close();
    return ofs.good() ? 0 : 3;
}
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
