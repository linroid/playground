#include "Screen.h"
#include <string>
#include <vector>
class Window_mgr {
  public:
    using ScreenIndex std::vector<Screen>::size_type;
    void clear(ScreenIndex);

  private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex index) {
    Screen &s = screens[index];
    s.contents = string(s.height * s.width, ' ');
}