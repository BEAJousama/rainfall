#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
    public:
        char padding[104];   // Filler or internal data
        int32_t annotation;   // Stored at offset 0x68

        N(int value) 
        {
            *(int**)this = (int*)&vtable; // Set vtable pointer
            annotation = value;
        }

        void setAnnotation(const char* input) 
        {
            // Writes the input into this->padding (starts at offset 4)
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

    static int vtable; // Fake vtable placeholder
};

int N::vtable = 0x8048848; // Dummy vtable pointer (from binary)

/// Main function
int main(int argc, char** argv, char** envp) 
{
    if (argc <= 1) 
    {
        exit(1); // Exit if no arguments
    }

    // Create two instances of N
    N* obj1 = new N(5);
    N* obj2 = new N(6);

    // Use argv[1] to set annotation on obj1
    obj1->setAnnotation(argv[1]);

    // Call obj2's virtual function (function pointer call)
    // Likely: obj2->someFunction(obj1);
    return ((int (*)(N*, N*))(*(int**)obj2))(obj2, obj1);
}