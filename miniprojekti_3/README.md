
# Teema 3 tehtävät

# 1.

## a.

`nullptr`-avainsana tarkoittaa null pointer vakiota. Vakiolla saadaan tehtyä ero kokonaisluvun 0 ja null pointer arvon välille käytettäessä ylikuormitettuja funktioita. Vakioita `0` ja `NULL` kohdellaan kokonaisluku tyyppisinä ylikuormitetuissa funktioissa.

```cpp
#include <cstddef>
#include <iostream>
 
template<class T>
constexpr T clone(const T& t)
{
    return t;
}
 
void g(int*)
{
    std::cout << "Function g called\n";
}
 
int main()
{
    g(nullptr);        // Fine
    g(NULL);           // Fine
    g(0);              // Fine
 
    g(clone(nullptr)); // Fine
//  g(clone(NULL));    // ERROR: non-literal zero cannot be a null pointer constant
//  g(clone(0));       // ERROR: non-literal zero cannot be a null pointer constant
}
```

## b.

`auto`-avainsanalla voidaan muuttujan arvo tai funktion paluuarvo päätellä vasta käännösvaiheessa.

```cpp
struct Foo {
	auto val() const {
		return m_;
 }
 auto& cref() const {
	 return m_;
 }
 auto& mref() {
	 return m_;
 }
 int m_{};
};
```

```cpp
auto val_wrapper() { return val(); }
```

## c.

Range based for loop.

```cpp
for ( range_declaration : range_expression )
{
    loop_statement
}
```

## d.

`final`-avainsanalla määritetään virtuaalifunktio, jota ei voida kuormittaa aliluokassa tai luokka, josta ei voida periytyä.

```cpp
struct Base
{
    virtual void foo();
};
 
struct A : Base
{
    void foo() final; // Base::foo is overridden and A::foo is the final override
    void bar() final; // Error: bar cannot be final as it is non-virtual
};
 
struct B final : A // struct B is final
{
    void foo() override; // Error: foo cannot be overridden as it is final in A
};
 
struct C : B // Error: B is final
{
};
```

`override`-avainsanala määritetään, että virtuaalifunktio kuormittaa toisen virtuaalifunktion.

```cpp
#include <iostream>
 
struct A
{
    virtual void foo();
    void bar();
    virtual ~A();
};
 
// member functions definitions of struct A:
void A::foo() { std::cout << "A::foo();\n"; }
A::~A() { std::cout << "A::~A();\n"; }
 
struct B : A
{
//  void foo() const override; // Error: B::foo does not override A::foo
                               // (signature mismatch)
    void foo() override; // OK: B::foo overrides A::foo
//  void bar() override; // Error: A::bar is not virtual
    ~B() override; // OK: `override` can also be applied to virtual
                   // special member functions, e.g. destructors
    void override(); // OK, member function name, not a reserved keyword
};
 
// member functions definitions of struct B:
void B::foo() { std::cout << "B::foo();\n"; }
B::~B() { std::cout << "B::~B();\n"; }
void B::override() { std::cout << "B::override();\n"; }
 
int main() {
    B b;
    b.foo();
    b.override(); // OK, invokes the member function `override()`
    int override{42}; // OK, defines an integer variable
    std::cout << "override: " << override << '\n';
}
```

## e.

`=delete` käskyllä voidaan poistaa funktio.

```cpp
class X 
{
    // ...
    X& operator=(const X&) = delete;  // Disallow copying
    X(const X&) = delete;
};
```

## f.

`long long int` tietotyyppi varaa muistista enemmän tilaa verrattuna long int:iin tai int:iin. Long long int tyypillä on tilaa vähintään 64 bittiä.

```cpp
// C++ program to implement
// the above approach
#include <iostream>
using namespace std;
  
// Driver code
int main()
{
    // Value of p 10^5
    int p = 100000;
  
    // Value of q 10^5
    int q = 100000;
  
    long long int result = (long long int)p * q;
    cout << result << endl;
    return 0;
}

// output: 10000000000
```

## g.

`std::unordered_map` on hajautustaulu, jossa on avain-arvo pareja. Elementtien etsimisellä, poistamisella ja lisäämisellä on keskiarvoinen aikavaatimus.

```cpp
#include <iostream>
#include <string>
#include <unordered_map>
 
int main()
{
    // Create an unordered_map of three strings (that map to strings)
    std::unordered_map<std::string, std::string> u = {
        {"RED","#FF0000"},
        {"GREEN","#00FF00"},
        {"BLUE","#0000FF"}
    };
 
    // Helper lambda function to print key:value pairs
    auto print_key_value = [](std::string const& key, std::string const& value) {
        std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
    };
 
    std::cout << "Iterate and print keys and values of unordered_map, being\n"
                 "explicit with the type of the iterator, n:\n";
    for( const std::pair<const std::string, std::string>& n : u ) {
        print_key_value(n.first, n.second);
    }
    std::cout << "\n";
 
    std::cout << "Iterate and print keys and values of unordered_map,\n"
                 "using auto:\n";
    for( const auto& n : u ) {
        print_key_value(n.first, n.second);
    }
    std::cout << "\n";
 
    std::cout << "Iterate and print keys and values using structured binding\n"
                 "(since C++17):\n";
    for( const auto& [key, value] : u ) {
        print_key_value(key, value);
    }
    std::cout << "\n";
 
    // Add two new entries to the unordered_map
    u["BLACK"] = "#000000";
    u["WHITE"] = "#FFFFFF";
 
    std::cout << "Output values by key:\n";
    std::cout << "The HEX of color RED is:[" << u["RED"] << "]\n";
    std::cout << "The HEX of color BLACK is:[" << u["BLACK"] << "]\n\n";
 
    // Use of operator[] with non-existent key inserts a new value
    print_key_value("new_key", u["new_key"]);
    std::cout << "Iterating over the unordered_map shows `new_key` is now one\n"
                 "of the keys in the map:\n";
    for( const std::pair<const std::string, std::string>& n : u ) {
        print_key_value(n.first, n.second);
    }
}

// output
Iterate and print keys and values of unordered_map, being
explicit with the type of the iterator, n:
Key:[BLUE] Value:[#0000FF]
Key:[GREEN] Value:[#00FF00]
Key:[RED] Value:[#FF0000]

Iterate and print keys and values of unordered_map,
using auto:
Key:[BLUE] Value:[#0000FF]
Key:[GREEN] Value:[#00FF00]
Key:[RED] Value:[#FF0000]

Iterate and print keys and values using structured binding
(since C++17):
Key:[BLUE] Value:[#0000FF]
Key:[GREEN] Value:[#00FF00]
Key:[RED] Value:[#FF0000]

Output values by key:
The HEX of color RED is:[#FF0000]
The HEX of color BLACK is:[#000000]

Key:[new_key] Value:[]
Iterating over the unordered_map shows `new_key` is now one
of the keys in the map:
Key:[new_key] Value:[]
Key:[WHITE] Value:[#FFFFFF]
Key:[BLACK] Value:[#000000]
Key:[BLUE] Value:[#0000FF]
Key:[GREEN] Value:[#00FF00]
Key:[RED] Value:[#FF0000]
```

## h.

`std::regex` kirjasto tarjoaa luokan, joka kuvaa säännöllisiä lausekkeita. Säännöllinen lauseke on yksinkertainen merkkijonokieli, joka voi joko vastata tai olla vastaamatta jotain toista merkkijonoa.

```cpp
#include <iostream>
#include <iterator>
#include <string>
#include <regex>
 
int main()
{
    std::string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";
 
    std::regex self_regex("REGULAR EXPRESSIONS",
            std::regex_constants::ECMAScript | std::regex_constants::icase);
    if (std::regex_search(s, self_regex)) {
        std::cout << "Text contains the phrase 'regular expressions'\n";
    }
 
    std::regex word_regex("(\\w+)");
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), word_regex);
    auto words_end = std::sregex_iterator();
 
    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words\n";
 
    const int N = 6;
    std::cout << "Words longer than " << N << " characters:\n";
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {
            std::cout << "  " << match_str << '\n';
        }
    }
 
    std::regex long_word_regex("(\\w{7,})");
    std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    std::cout << new_s << '\n';
}

// output
Text contains the phrase 'regular expressions'
Found 20 words
Words longer than 6 characters:
  confronted
  problem
  regular
  expressions
  problems
Some people, when [confronted] with a [problem], think 
"I know, I'll use [regular] [expressions]." Now they have two [problems].
```