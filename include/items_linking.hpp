#pragma once
#include "actions.hpp"


menu::menu_node artist_1 = {"������ ������ ��� ������"};
menu::menu_node artist_2 = {"������� ���������� �������"}; 
menu::menu_node artist3 = {"���� �������������� �����������"};

menu::menu_node russian_artists = {"������� ���������", "������ ������� ������� ���������", nullptr, {&artist_1, &artist_2, &artist3}, *node_actions::universal_action};
menu::menu_node russian_musicians = {"������� ���������", "������ ������� ������� ���������", nullptr, {}, *node_actions::universal_action};

menu::menu_node russian_art =  {"��������� ������", "������ ������� ����: ", nullptr, {&russian_artists, &russian_musicians}, *node_actions::universal_action};

menu::menu_node zero_level = {"", "������� ����", nullptr, {&russian_art}, *node_actions::universal_action};
