#pragma once
#include "actions.hpp"


menu::menu_node artist_1 = {"Андрей Иванов сын Рублев"};
menu::menu_node artist_2 = {"Василий Дмитриевич Поленов"}; 
menu::menu_node artist3 = {"Иван Константинович Айвазовский"};

menu::menu_node russian_artists = {"Русские художники", "Третий уровень Русские художники", nullptr, {&artist_1, &artist_2, &artist3}, *node_actions::universal_action};
menu::menu_node russian_musicians = {"Русские музыканты", "Третий уровень Русские музыканты", nullptr, {}, *node_actions::universal_action};

menu::menu_node russian_art =  {"Искусство России", "Второй уровень меню: ", nullptr, {&russian_artists, &russian_musicians}, *node_actions::universal_action};

menu::menu_node zero_level = {"", "Главное меню", nullptr, {&russian_art}, *node_actions::universal_action};
