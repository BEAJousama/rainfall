#include <iostream>
#include <cstring>
#include <cstdlib>

class N
{
    public:
        char padding[104];
        int annotation;

    N(int value) 
    {
        *(int**)this = (int*)&vtable;
        annotation = value;
    }

    void setAnnotation(const char* input) 
    {
        memcpy(((char*)this) + 4, input, strlen(input));
    }

    int operator+(const N& other) const 
    {
        return this->annotation + other.annotation;
    }

    int operator-(const N& other) const 
    {
        return this->annotation - other.annotation;
    }

    static int vtable;
};

int N::vtable = 0x8048848;

int main(int argc, char** argv, char** envp) 
{
    if (argc <= 1) 
    {
        exit(1);
    }

    N* obj1 = new N(5);
    N* obj2 = new N(6);

    obj1->setAnnotation(argv[1]);

    return ((int (*)(N*, N*))(*(int**)obj2))(obj2, obj1);
}