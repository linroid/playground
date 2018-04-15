#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::string;
struct Sales_data {
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);

  public:
    Sales_data &combine(const Sales_data &);
    inline double avg_price() const;
    string isbn() const { return bookNo; };

  private:
    string bookNo;
    unsigned int units_sold = 0;
    double revenue;
};

Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, const Sales_data &);

inline double Sales_data::avg_price() const {
    if (units_sold) {
        return revenue / units_sold;
    }
    return 0;
}

Sales_data &Sales_data::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
std::ostream &print(std::ostream &output, const Sales_data &item) {
    output << item.isbn() << " " << item.units_sold << " " << item.revenue
           << " " << item.avg_price();
}
std::istream &read(std::istream &input, Sales_data &item) {
    double price = 0;
    input >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return input;
}
Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}