#include "menu_items.hpp"
#include "menu_func.hpp"

int main() {
    const Menu::MenuItem* curr_item = &Items::MAIN;
    while (true) {
        curr_item = Func::display_and_use(curr_item);
    }
    return 0;
}
