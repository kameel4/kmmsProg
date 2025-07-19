#include <iostream>
#include <fstream>

#include <string>
#include <deque>

int main(){
    std::deque<std::string> stopka;

    std::ifstream in("input.txt");
    int num_of_works;
    in >> num_of_works;

    for (int i = 0; i<num_of_works; ++i){
        std::string last_name, deque_end;
        in>> last_name >> deque_end;

        if (deque_end == "top"){
            stopka.push_back(last_name);
        }else{
            stopka.push_front(last_name);
        }

    }

    int num_of_requests;
    in >> num_of_requests;

    std::ofstream out("output.txt");

    for (int i = 0; i<num_of_requests; ++i){
        int work_index;
        in>>work_index;
        
        out<<stopka[num_of_works - work_index]<<std::endl;
    }

    in.close(); out.close();
}