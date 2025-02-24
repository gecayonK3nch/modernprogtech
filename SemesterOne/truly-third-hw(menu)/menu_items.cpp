#include "menu_items.hpp"
#include "menu_func.hpp"

const Menu::MenuItem Items::STUDY_BACK = {
    "Выйти в главное меню",
    Func::display_and_use,
    &Items::STUDY,
    nullptr,
    0
};

const Menu::MenuItem Items::STUDY_LANGS = {
    "Изучать языки программирования",
    Func::display_and_use,
    &Items::STUDY,
    nullptr,
    0
};

const Menu::MenuItem Items::STUDY_ALGORITHMS = {
    "Алгоритмы и структуры",
    Func::display_and_use,
    &Items::STUDY,
    nullptr,
    0
};

const Menu::MenuItem Items::TECH_BACK = {
    "Выйти в предыдущее меню",
    Func::display_and_use,
    &Items::STUDY_TECHNOLOGIES,
    nullptr,
    0
};

const Menu::MenuItem Items::TECH_DB = {
    "Базы данных",
    Func::display_and_use,
    &Items::STUDY_TECHNOLOGIES,
    nullptr,
    0
};

const Menu::MenuItem Items::TECH_PROG = {
    "Многопоточное программирование",
    Func::display_and_use,
    &Items::STUDY_TECHNOLOGIES,
    nullptr,
    0
};

const Menu::MenuItem Items::TECH_NET = {
    "Сетевые технологии",
    Func::display_and_use,
    &Items::STUDY_TECHNOLOGIES,
    nullptr,
    0
};

namespace {
    const Menu::MenuItem* const tech_children[] = {
        &Items::TECH_BACK,
        &Items::TECH_DB,
        &Items::TECH_PROG,
        &Items::TECH_NET
    };
    const int tech_size = sizeof(tech_children) / sizeof(tech_children[0]);
}

const Menu::MenuItem Items::STUDY_TECHNOLOGIES = {
    "Другие технологии",
    Func::display_and_use,
    &Items::STUDY,
    tech_children,
    tech_size
};

namespace {
    const Menu::MenuItem* const study_children[] = {
        &Items::STUDY_BACK,
        &Items::STUDY_LANGS,
        &Items::STUDY_ALGORITHMS,
        &Items::STUDY_TECHNOLOGIES,
    };
    const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}

const Menu::MenuItem Items::STUDY = {
    "Изучать программирование",
    Func::display_and_use,
    &Items::MAIN,
    study_children,
    study_size
};

const Menu::MenuItem Items::EXIT = {
    "Пойти играть в футбол",
    Func::display_and_use,
    nullptr,
    nullptr,
    0
};

namespace {
    const Menu::MenuItem* const main_children[] = {
        &Items::EXIT,
        &Items::STUDY
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const Menu::MenuItem Items::MAIN = {
    "Программирка приветствует вас!",
    Func::display_and_use,
    nullptr,
    main_children,
    main_size
};
