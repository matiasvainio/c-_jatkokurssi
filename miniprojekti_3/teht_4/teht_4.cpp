#include <iostream>

using namespace std;

class Big_Data {
   private:
    int* buffer;

   public:
    Big_Data(int i) : buffer((int*)malloc(i)) {}

    Big_Data(const Big_Data& big_data) {
        buffer = (int*)malloc(sizeof(big_data.buffer));
        *buffer = *big_data.buffer;
    }

    ~Big_Data() { free(buffer); }

    int* get_buffer() {
        return buffer;
    }

    void set_value(int i) {
        *buffer = i;
    }

    Big_Data& operator=(const Big_Data& other) {
        *buffer = *other.buffer;
        return *this;
    }

    Big_Data(Big_Data&& other) : buffer(move(other.buffer)) {}

    Big_Data& operator=(Big_Data&& other) {
        buffer = move(other.buffer);
        return *this;
    }
};

int main() {
    Big_Data a(Big_Data(1024));
    Big_Data b(1024);
    b = Big_Data(1024);
    Big_Data c(std::move(a));
    cout << c.get_buffer() << '\n';
    cout << a.get_buffer() << '\n';
    return 0;
}