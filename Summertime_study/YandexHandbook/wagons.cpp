#include <fstream>

#include <deque>
#include <string>

void MakeTrain(){
    std::deque<int> train;

    std::ifstream in("input.txt");
    std::string operation;
    int wagon_number;

    while (in >> operation){
        in>>wagon_number;
        if (operation[0] == '+'){
            if (operation == "+right") train.push_back(wagon_number);
            if (operation == "+left") train.push_front(wagon_number);
        }else{
            wagon_number = std::min(wagon_number, (int)train.size());
            if (operation == "-left") train.erase(train.begin(), train.begin()+wagon_number);
            if (operation == "-right") train.erase(train.end() - wagon_number, train.end());
        }
    }

        std::ofstream out("output.txt");
        bool first = true;
        for (int wagon: train){
            if (first){
                out<<wagon;
                first = false;
            }else{
                out<<' '<<wagon;
            }
        }

        in.close(); out.close();
}
