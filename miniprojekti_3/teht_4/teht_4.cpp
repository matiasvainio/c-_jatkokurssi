#include <iostream>

using namespace std;

class Big_Data {
   private:
    int* buffer;
    size_t size{0};

   public:
    Big_Data(int i) : buffer((int*)malloc(i)), size(i) {}

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

    Big_Data(Big_Data&& other)
        : size(other.size), buffer(other.buffer) {
            other.buffer = nullptr;
            other.size = 0;
        }

    auto& operator=(Big_Data&& other) {
        buffer = other.buffer;
        size = other.size;
        other.buffer = nullptr;
        other.size = 0;
        return *this;
    }
};

int main() {
    Big_Data a(Big_Data(1024));
    Big_Data b(1024);
    b = Big_Data(1024);
    Big_Data c(std::move(a));
    return 0;
}