#include <string>
using std::string;
struct Person {
    string name;
    string address;
    int age;

  public:
    string const &getName() const { return name; }
    string const &getAddress() const { return address; }
    int const &getAge() const { return age; }
};