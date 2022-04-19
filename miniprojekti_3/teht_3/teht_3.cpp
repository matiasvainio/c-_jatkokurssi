#include <iostream>

using namespace std;

class Big_Data {
   private:
    int* buffer;

   public:
    Big_Data(int i) {
        buffer = (int*)malloc(i);
    }

    Big_Data(const Big_Data& big_data) {
        buffer = (int*)malloc(sizeof(big_data.buffer));
        *buffer = *big_data.buffer;
    }

    ~Big_Data() { free(buffer); }

    Big_Data& operator=(const Big_Data& other) {
        *buffer = *other.buffer;
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