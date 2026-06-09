#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

struct Boxe{
    int x;
    int y;
    int z;
};

struct Connexion{
    int A;
    int B;
    uint distance;
};


using Connexions = std::vector<Connexion>;
using Boxes = std::vector<Boxe>;

long long distance(Boxe b1, Boxe b2){
    return (
        std::pow(b2.x-b1.x, 2) +
        std::pow(b2.y-b1.y, 2) +
        std::pow(b2.z-b1.z, 2)
    );
}

Connexions makeConnections(Boxes & boxes){
    Connexions cs;
    for(int i=0; i<boxes.size()-1;++i){
        Connexion c;
        c.A = i;
        for(int j=i+1; j<boxes.size(); ++j){
            c.B = j;
            c.distance = distance(boxes[i], boxes[j]);
            cs.push_back(c);
        }

    }
    return cs;
}

class DSU {
    private:
        std::vector<int> parent;
        std::vector<int> size;

    public:
        DSU(int n) : parent(n), size(n, 1)
        {
            for(int i = 0; i < n; ++i)
                parent[i] = i;
        }

        int find(int x)
        {
            if(parent[x] == x)
                return x;

            return parent[x] = find(parent[x]); // path compression
        }

        bool unite(int a, int b)
        {
            a = find(a);
            b = find(b);

            if(a == b)
                return false;

            // union by size
            if(size[a] < size[b])
                std::swap(a, b);

            parent[b] = a;
            size[a] += size[b];

            return true;
        }

        int component_size(int x)
        {
            return size[find(x)];
        }
};

int main(){
    std::ifstream fic {"input.txt"};
    Boxes boxes;

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

    Connexions connexions = makeConnections(boxes);

    std::sort(connexions.begin(), connexions.end(),
        [](const Connexion  & c1, const Connexion & c2){
            return c1.distance<c2.distance;
        }
    );
    //connexions.erase(connexions.begin()+10, connexions.end());

    // for(Connexion c : connexions){
    //     std::cout<<c.distance<<" : ("<<c.A->x<<", "<<c.A->y<<", "<<c.A->z<<") - ("
    //               <<c.B->x<<", "<<c.B->y<<", "<<c.B->z<<")\n";
    // }

    int used = 0;
    DSU dsu(boxes.size());

    for(const Connexion& c : connexions)
    {
        used++;
        dsu.unite(c.A, c.B);
        if(used == 1000)
            break;
    }
    
    std::unordered_map<int, int> comp_size;

    for(int i = 0; i < boxes.size(); ++i)
    {
        int root = dsu.find(i);
        comp_size[root]++;
    }

    std::vector<int> sizes;
    for(auto& [root, sz] : comp_size)
        sizes.push_back(sz);

    std::sort(sizes.rbegin(), sizes.rend());

    int result = sizes[0] * sizes[1] * sizes[2];
    std::cout<<result<<" "<<sizes[0]<<" "<<sizes[1]<<" "<<sizes[2]<<" "<<"\n";



}