#include <iostream>

#include <stack>
#include <fstream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>

using namespace std;

class World{
public:
    using Cell = pair<int,int>;
    int rows, cols;
    vector<string> data;

    vector<vector<int>> m_distance;
    vector<vector<Cell>> m_parent;
    const Cell unvisited_block = {-1,-1};
    Cell start, goal;

    World(istream &in){
        string line;
        // Read rows and cols
        in >> rows >> cols;
        // Throw away remaining \n
        getline(in, line);

        for(int r = 0; r < rows; r++){
            // Read the line
            getline(in, line);
            data.push_back(line);

            m_parent.emplace_back(cols, unvisited_block);
            m_distance.emplace_back(cols, numeric_limits<int>::max());

            // Check for the start
            auto tmp = line.find('1');
            if(tmp != line.npos){
                start.first  = r;
                start.second = tmp;
            }
            // Check for the goal
            tmp = line.find('0');
            if(tmp != line.npos){
                goal.first  = r;
                goal.second = tmp;
            }
        }
    }

    void print(){
        for(const string &line : data){
            cout << line << endl;
        }
    }

    int& distance(Cell &coord){
        return m_distance[coord.first][coord.second];
    }

    Cell& parent(Cell &coord){
        return m_parent[coord.first][coord.second];
    }

    bool unvisited(Cell &coord) {
        return parent(coord) == unvisited_block;
    }

    bool valid(Cell &coord){
        if(coord.first >= 0 && coord.first < rows
                && coord.second >= 0 && coord.second < cols){
            return data[coord.first][coord.second] == ' '
                    || data[coord.first][coord.second] == '.'
                    || data[coord.first][coord.second] == '0';
        }else{
            return false;
        }
    }

    void bfs(){


    }
};

int main()
{
    fstream f("maze3.txt");
    World w(f);
    w.bfs();
    return 0;
}

