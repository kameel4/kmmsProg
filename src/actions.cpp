#include "actions.hpp"


void node_actions::show_level(menu::menu_node* noda){
    std::cout<<noda->level_name<<std::endl;
}

void node_actions::show_children(menu::menu_node* noda){
    std::vector<menu::menu_node*> children = noda->children;

    int i =1;
    for (menu::menu_node* child: children){
        std::cout<<i++<<". "<<child->name<<std::endl;
    }
    std::cout<<"0. Назад"<<std::endl;
}

menu::menu_node* node_actions::go_further(menu::menu_node* noda){
    int answer;
    std::cin>>answer;

    if (answer==0) return noda->parent;
    else return noda->children[answer-1];
}

menu::menu_node* node_actions::universal_action(menu::menu_node* noda){
    show_level(noda);
    show_children(noda);
    return go_further(noda);
}

void node_actions::connect_parent(menu::menu_node* parent){
    for (menu::menu_node* child: parent->children){
        child->parent = parent;
    }
    if (parent->children.size() != 0){
        for(menu::menu_node* child: parent->children){
            connect_parent(child);
        }
    }
}
