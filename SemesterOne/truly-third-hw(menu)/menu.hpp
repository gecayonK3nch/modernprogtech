#pragma once

namespace Menu {
    struct MenuItem {
        const char* title;

        const MenuItem* (*func)(const MenuItem* curr_item);

        const MenuItem* parent;

        const MenuItem* const *children;
        const int child_cnt;
    };
}
