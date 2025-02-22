#ifndef MENU_HPP
#define MENU_HPP


#include <vector>
#include <iostream>

namespace menu{
    struct menu_node{
        std::string name;
        std::string level_name;
        menu_node* parent;
        std::vector<menu_node*> children;
        menu_node* (*action)(menu_node* node);
    };
}
#endif