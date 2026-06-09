#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
struct Boxe{
    int x;
    int y;
    int z;
    int circuit_id = -1;
    int circuit_size = 0;
};
struct Connexion{
    Boxe* A;
    Boxe* B;
    uint distance;
};


using Connexions = std::vector<Connexion>;
using Input = std::vector<Boxe>;

uint distance(Boxe b1, Boxe b2){
    return (std::sqrt(
        std::pow(b2.x-b1.x, 2) +
        std::pow(b2.y-b1.y, 2) +
        std::pow(b2.z-b1.z, 2)
    ));
}

Connexion build(Connexion c){
    return c;
}

Connexions makeConnections(Input & input){
    Connexions cs;
    for(int i=0; i<input.size()-1;++i){
        Connexion c;
        c.A = &input[i];
        for(int j=i+1; j<input.size(); ++j){
            c.B = &input[j];
            c.distance = distance(input[i], input[j]);
            cs.push_back(c);
        }

    }
    return cs;
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
        //std::cout<<b.x<<" "<<b.y<<" "<<b.z<<"\n";
    }
    std::cout<<"\n\n";

    Connexions c =  makeConnections(boxes);
    std::sort(c.begin(), c.end(), [](const Connexion& a, const Connexion& b) {
        return a.distance < b.distance and b.distance!=0 and a.distance!=0;
    });

    //test  : 10 shortest connections
    //c.erase(c.begin()+24, c.end());
    // for(int i=0; i<c.size(); ++i){
    //     std::cout<<i<<" : "<<distance(*c[i].A, *c[i].B)<<" : ("<<c[i].A->x<<", "<<c[i].A->y<<", "<<c[i].A->z<<") - ("
    //              <<c[i].B->x<<", "<<c[i].B->y<<", "<<c[i].B->z<<")\n";
    // }

    int id=1;
    int cluster = 0;
    int last = 0;
    Connexion lastConnection;
    for(int i=0; i<c.size(); ++i){
        // std::cout<<i<<" : "<<distance(*c[i].A, *c[i].B)<<" : ("<<c[i].A->x<<", "<<c[i].A->y<<", "<<c[i].A->z<<") - ("
        //          <<c[i].B->x<<", "<<c[i].B->y<<", "<<c[i].B->z<<")\n";

        if(c[i].A->circuit_id == -1 and c[i].B->circuit_id == -1){
            ++cluster;
            c[i].A->circuit_id = id;
            c[i].B->circuit_id = id;
            ++id;
        }else if(c[i].A->circuit_id != -1 and c[i].B->circuit_id == -1){
            if(cluster==1)
                lastConnection = c[i];
            c[i].B->circuit_id = c[i].A->circuit_id;
        }
        else if(c[i].A->circuit_id == -1 and c[i].B->circuit_id != -1){
            if(cluster==1)
                lastConnection = c[i];
            c[i].A->circuit_id = c[i].B->circuit_id;
        }else if(c[i].A->circuit_id != c[i].B->circuit_id){
            --cluster;
            std::cout<<"cluster : "<<cluster<<"\n";
            if(cluster==1){
                lastConnection = c[i];
                last = i;
            }
            int aux_id = c[i].B->circuit_id;
            //c[i].B->circuit_id = c[i].A->circuit_id;
            for(int j=0; j<boxes.size(); ++j){
                if(boxes[j].circuit_id == aux_id){
                    //std::cout<<"Hey ! : "<<boxes[j].x<<"\n";
                    boxes[j].circuit_id = c[i].A->circuit_id;
                }
            }

        }
    }

    // std::sort(boxes.begin(), boxes.end(), [](const Boxe& a, const Boxe& b) {
    //     return a.circuit_id < b.circuit_id;
    // });

    for(int i=0; i<boxes.size(); ++i){
        std::cout<<boxes[i].circuit_id<<" : "<<boxes[i].x<<" "<<boxes[i].y<<" "<<boxes[i].z<<" ("<<boxes[i].circuit_size<<")\n";
    }

    std::cout<<"\n\n";
    int tot=0;
    int m1=0, m2=0, m3=0;
    int cur_id = boxes[0].circuit_id;
    std::vector<int> tots;
    for(int i=1; i<boxes.size(); ++i){
        if(boxes[i].circuit_id == cur_id && cur_id!=-1){
            ++tot;
        }else{
            std::cout<<tot<<"\n";
            tots.push_back(tot);
            cur_id = boxes[i].circuit_id;
            tot=1;
        }
    }
    std::sort(tots.begin(), tots.end(), [](const int& a, const int& b){
        return a>b;
    });
    //std::cout<<tots[0]<<" "<<tots[1]<<" "<<tots[2]<<"\n"<<tots[0]*tots[1]*tots[2]<<"\n";
    std::cout<<"\n\n"<<cluster<<"\n";
    std::cout<<"["<<last<<"] ("
             <<lastConnection.A->x<<", "
             <<lastConnection.A->y<<", "
             <<lastConnection.A->z<<") - ("
             <<lastConnection.B->x<<", "
             <<lastConnection.B->y<<", "
             <<lastConnection.B->z<<")\n";
    
    std::cout<<(long)lastConnection.A->x * (long)lastConnection.B->x<<"\n";


    return 0;
}