#include <iostream>

using namespace std;

class Big_Data {
   private:
    int* buffer;
    size_t size{0};

   public:
    Big_Data(int i) : buffer((int*)malloc(i)), size(i){}

    Big_Data(const Big_Data& other) {
        buffer = (int*)malloc(size);
        copy(other.buffer, other.buffer + sizeof(other.buffer), buffer);
    }

    ~Big_Data() { free(buffer); }

    Big_Data& operator=(const Big_Data& other) {
        free(buffer);
        buffer = (int*)malloc(size);
        copy(other.buffer, other.buffer + sizeof(other.buffer), buffer);
        return *this;
    }
};

int main() {
    Big_Data a(1024);
    Big_Data b(1025);
    a = a;
    a = b;
    Big_Data c(a);
    return 0;
}