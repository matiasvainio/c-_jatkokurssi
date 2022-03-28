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
    T* data;

    // Write line to log file.
    void write_line(string s) {
        auto timestamp = get_timestamp();

        ofstream o;
        o.open("/home/matias/dev/c/cpp-jatkokurssi/miniprojekti_1/ptr_log.txt", std::ios_base::app);
        o << timestamp << " " << s << " " << data << "\n";
        o.close();
    }

    // Get current time.
    auto get_timestamp() {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto timestamp = std::ctime(&time);
        timestamp[sizeof(timestamp) * 3] = '\0';
        return timestamp;
    }

   public:
    log_ptr(T* value) {
        data = value;

        rc = new reference_counter();
        rc->add_ref();

        write_line("omistajuus siirretty");
    }

    ~log_ptr() {
        if (rc->release() == 0) {
            delete data;
            delete rc;
        }

        write_line("olio tuhottu");
    }

    T* operator->() {
        write_line("operator->");
        return data;
    }

    T& operator*() {
        write_line("operator*");
        return *data;
    }

    // Remove copy constructor and copy assignment operator.
    // log_ptr(const log_ptr&) = delete;
    // log_ptr& operator=(const log_ptr&) = delete;

    // Copy constructor.
    log_ptr(const log_ptr<T>& log_ptr) : data(log_ptr.data), rc(log_ptr.rc) {
        write_line("kopiokonstruktori");
        rc->add_ref();
    }

    // Assignment operator.
    log_ptr<T>& operator=(const log_ptr<T>& log_ptr) {
        if (this != &log_ptr) {
            if (rc->release() == 0) {
                delete data;
                delete rc;
                write_line("olio tuhottu sijoitusoperaatiosta");
            }

            data = log_ptr.data;
            rc = log_ptr.rc;
            rc->add_ref();
            write_line("sijoitusoperaatio");
        }

        return *this;
    }
};

class foobar {
   private:
    string s;

   public:
    foobar(string s) : s(s) {}
    string get_s() { return s; }
};

int main() {
    log_ptr<foobar> p(new foobar("foobar"));
    p->get_s();

    {
        log_ptr<foobar> q = p;
        *q;

        log_ptr<foobar> f(new foobar("bizbaz"));
        // The above object gets removed when new object gets assigned.
        f = q;
        cout << f->get_s() << endl;
    }
    
    cout << p->get_s() << endl;
}
