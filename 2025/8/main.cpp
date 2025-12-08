#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

struct Boxe{
    int x;
    int y;
    int z;
    uint id_circuit=0;
};

using Input = std::vector<Boxe>;

uint distance(Boxe b1, Boxe b2){
    return (std::sqrt(
        std::pow(b2.x-b1.x, 2) +
        std::pow(b2.y-b1.y, 2) +
        std::pow(b2.z-b1.z, 2)
    ));
}

int main(){
    std::ifstream fic {"input.txt"};
    Input boxes;

    std::string ligne;
    while (std::getline(fic, ligne, ',')){
        Boxe b;
        b.x = std::stoi(ligne);
        std::getline(fic, ligne, ',');
        b.y = std::stoi(ligne);
        std::getline(fic, ligne);
        b.z = std::stoi(ligne);
        boxes.push_back(b);
    }

    std::cout<<distance(boxes[0], boxes[1])<<"\n";




    return 0;
}