#include <iostream>
#include "menu_func.hpp"

const Menu::MenuItem* Func::display_and_use(const Menu::MenuItem* curr_item){
    std::cout << curr_item->title << std::endl;

    if (curr_item->child_cnt == 0) {
        std::cout << std::endl;
        return curr_item->parent;
    }

    for (int i = 1; i <= curr_item->child_cnt - 1; ++i) {
        std::cout << i << " - " << curr_item->children[i]->title << std::endl;
    }
    std::cout << "0 - " << curr_item->children[0]->title << std::endl << std::endl;
    std::cout << "Программирка > ";

    int user_input;
    std::cin >> user_input;
    std::cout << std::endl;

    if (user_input == 0) {
        if (curr_item->parent == nullptr) {
            exit(0);
        }
        return curr_item->parent;
    }
    if (user_input < 0 || user_input > curr_item->child_cnt) {
        std::cout << "Неверный ввод" << std::endl;
        return curr_item;
    }
    return curr_item->children[user_input];
}
