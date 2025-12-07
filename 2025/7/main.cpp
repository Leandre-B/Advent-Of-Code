#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using Input = std::vector<std::string>;

void printInput(const Input & input){
    for(int i=0; i<input.size(); ++i)
        std::cout<<input[i]<<"\n";
    std::cout<<"\n";
}

/* test
 * 291817675 -> to low
*/

long timeline(Input & input, uint x, uint y, std::map<std::pair<uint, uint>, long> & map){
    if(y==input.size()-1)
        return 1;
    else{
        if(!(map.contains({x,y}))){
            long t;
            if(input[y+1][x]=='.'){
                t = timeline(input, x, y+1, map);
                //printInput(input);
                input[y+1][x]='.';
            }else{ //forcement un '^'
                t = timeline(input,x-1, y+1, map);
                //printInput(input);


                t+= timeline(input, x+1, y+1, map);
                //printInput(input);
            }
            map[{x,y}]=t;
        }
        return map[{x,y}];
    }
}

int main(){
    std::ifstream fic {"input.txt"};
    Input input;

    std::string ligne;
    while (std::getline(fic, ligne))
    {
        input.push_back((ligne));
    }

    /*
    for(int i=0; i<input[0].length(); ++i){
        if(input[0][i]=='S'){
            input[1][i]='|';
            i=input[0].length();
        }
    }
    //printInput(input);
    uint split = -2;
    for(int i=1; i<input.size()-1; ++i){
        for(int j=0; j<input[i].length(); ++j){
            if(input[i][j]=='|'){
                if(input[i+1][j]=='.')
                    input[i+1][j]='|';
                else if(input[i+1][j]=='^'){
                    input[i+1][j+1]='|';
                    input[i+1][j-1]='|';
                    ++split;
                }

            }
        }
    }
    printInput(input);
    std::cout<<"split = "<<split<<"\n";
    */

    std::map<std::pair<uint, uint>, long> map;
    int pos_S=0;
    while(input[0][pos_S]!='S')
        ++pos_S;
    long sol = timeline(input, pos_S, 1, map);
    std::cout<<sol<<"\n";

    return 0;
}