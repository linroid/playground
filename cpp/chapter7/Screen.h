#include "Window_mgr.h"
#include <iostream>
#include <string>
class Screen {
    // friend class Window_mgr;
    friend void Window_mgr::clear(ScreenIndex);

  public:
    typedef std::string::size_type pos;
    // using pos = std::string::size_type;
    Screen() = default;
    Screen(pos h, pos w) : height(h), width(w), contents(h * w, ' '){};
    Screen(pos h, pos w, char c) : height(h), width(w), contents(h * w, c){};
    char get() const { return contents[cursor]; }
    inline char get(pos, pos) const;
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &move(pos, pos);
    void some_members() const;
    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }

  private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_str;
    void do_display(std::ostream &os) const { os << contents; }
};

inline Screen &Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char c) {
    contents[r * width + col] = c;
    return *this;
}

inline Screen &Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

void Screen::some_members() const { ++access_str; }