#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class reference_counter {
   private:
    int count;

   public:
    void add_ref() {
        count++;
    }

    int release() {
        return --count;
    }
};

template <typename T>
class log_ptr {
   private:
    reference_counter* rc;
    T* ptr;

    void write_line(string s) {
        auto timestamp = get_timestamp();

        ofstream o;
        o.open("/home/matias/dev/c/c++_jatkokurssi/miniprojekti_1/temp.txt", std::ios_base::app);
        o << timestamp << " " << s << " " << ptr << "\n";
        o.close();
    }

    auto get_timestamp() {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto timestamp = std::ctime(&time);
        timestamp[sizeof(timestamp) * 3] = '\0';
        return timestamp;
    }

   public:
    log_ptr(T* value) {
        ptr = value;

        rc = new reference_counter();
        rc->add_ref();

        write_line("omistajuus siirretty");
    }

    ~log_ptr() {
        if (rc->release() == 0) {
            delete ptr;
            delete rc;
        }

        write_line("olio tuhottu");
    }

    T* operator->() {
        write_line("operator->");
        return ptr;
    }

    T& operator*() {
        write_line("operator*");
        return *ptr;
    }

    // Remove copy constructor and copy assignment operator.
    // log_ptr(const log_ptr&) = delete;
    // log_ptr& operator=(const log_ptr&) = delete;

    log_ptr(const log_ptr<T>& log_ptr) : ptr(log_ptr.ptr), rc(log_ptr.rc) {
        rc->add_ref();
    }


};

class foobar {
   public:
    string i = "foobar";
};

int main() {
    log_ptr<foobar> ptr(new foobar);
    *ptr;
}
