#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "menu.hpp"

namespace node_actions{

void connect_parent(menu::menu_node* noda);
    
void show_level(menu::menu_node* noda);

void show_children(menu::menu_node* noda);

menu::menu_node* go_further(menu::menu_node* noda);

menu::menu_node* universal_action(menu::menu_node* noda);

}

#endif
