#include <iostream>
#include <fstream>
#include <vector>


bool isAccesible(std::vector<std::string> & rolls, int & x, int & y){
    uint cpt = 0;
    for(int i=x-1; i<=x+1; ++i){
        for(int j=y-1; j<=y+1; ++j){
            if(i>=0 and j>=0 and j<rolls.size() and i<rolls[0].length() and (i!=x or j!=y)){
                //std::cout<<i<<" "<<j<<std::endl;
                //std::cout<<rolls[j][i];
                if(rolls[j][i]=='@')
                    ++cpt;
                if(cpt>=4)
                    return false;
            }
        }
    }
    rolls[y][x]='.';
    return true;
}



long long accesibileRolls(std::vector<std::string> & rolls){
    long long n = 1;
    long long tot=0;
    while(n!=0){
        n=0;
        for(int y=0; y<rolls.size(); ++y){
            for(int x=0; x<rolls[y].length(); ++x){
                if(rolls[y][x]=='@'){
                    //std::cout<<rolls[y][x]<<"\n";
                    if(isAccesible(rolls, x, y))
                        ++n;
                }
            }
        }
        tot+=n;
    }
    return tot;
}

int main(){
    std::string file_name = "input.txt";
    std::ifstream fic;
    fic.open(file_name);
    if(fic.is_open()){
        std::vector<std::string> rolls;
        long long answer = 0;

        while(fic.good()){
            std::string ligne="";
            std::getline(fic, ligne);
            rolls.push_back(ligne);
        }
        //int x=0, y=1;
        //std::cout<<isAccesible(rolls, x, y)<<std::endl;
        answer = accesibileRolls(rolls);
        std::cout<<"The answer is : "<<answer<<"\n";

    }else
        std::cout<<"Fail to open \"input.txt\"\n";

    return 0;
}
