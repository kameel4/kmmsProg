#include "items_linking.hpp"

int main(){
    node_actions::connect_parent(&zero_level);

    menu::menu_node* current_node = &zero_level;
    while(true){
        current_node = current_node->action(current_node);
    }
    return 0;
}