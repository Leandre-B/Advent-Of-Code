#include <iostream>
#include <fstream>


void part2(uint & password, const std::string & mouvement, int & cur){
    int dpl = std::stoi(mouvement.substr(1));
    for(int i=0; i<dpl; ++i){
        if(mouvement[0]=='L')
            cur=((cur - 1) %100 + 100)%100;
        else
            cur=((cur + 1) %100 + 100)%100;
        if(cur== 0)
            ++password;
    }
}


void part1(uint & password, const std::string & mouvement, int & cur){
    int dpl = std::stoi(mouvement.substr(1));
    if(mouvement[0]=='L')
        cur=((cur - dpl) %100 + 100)%100; //get positive mod
    else
        cur=((cur + dpl) %100 + 100)%100; //get positive mod
    
    if(cur== 0)
        ++password;
}

int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        
        uint password = 0;
        int cur = 50;
        std::string mouvement;
        while(fic.good()){
            std::getline(fic, mouvement);
            
            //part1(password, mouvement, cur);
            part2(password, mouvement, cur);
        }

        std::cout<<"The password is : "<<password<<"\n";



    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}