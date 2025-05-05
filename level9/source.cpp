#include <iostream>
#include <cstring>
#include <cstdlib>

class N {
public:
    N(int value) : id(value) {}

    virtual void doSomething(N* target) {
        std::cout << "Base class called with: " << id << " and target: " << target->id << std::endl;
    }

    void setAnnotation(const char* s) {
        // In binary: memcpy(this + 4, s, strlen(s));
        std::strncpy(buffer, s, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';
    }

    int operator+(const N& other) const {
        return this->id + other.id;
    }

    int operator-(const N& other) const {
        return this->id - other.id;
    }

protected:
    char buffer[100]; // guess based on `this + 4` offset
    int id;
};

// main reconstructed
int main(int argc, char** argv) {
    if (argc < 2)
        exit(1); // used in decompiled binary

    N* a = new N(5);
    N* b = new N(6);

    a->setAnnotation(argv[1]);
    b->doSomething(a); // virtual call from vtable

    return 0;
}
