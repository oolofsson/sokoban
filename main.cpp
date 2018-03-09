#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::vector<std::vector<std::pair<char, bool>>> map;
std::pair<int, int> start;
std::vector<std::pair<int, int>> goals;
std::pair<int, int> end;

void printMap();
void readFile(std::string mapString);
void findPath(std::pair<int, int> position, std::string path);
bool isValidPosition(int x, int y);
bool pathFound = false;

int main(int argc, char const *argv[]) {
  char c;
  std::string mapString = "";
  while ( (c = fgetc(stdin)) != EOF ){
    mapString += c;
  }
  readFile(mapString);
  std::string path = "";
  findPath(start, path);
  if(!pathFound) std::cout << "no path";

  std::cout << std::endl;
  return 0;
}
void readFile(std::string mapString){
    std::istringstream iss(mapString);

    std::string line;
    int y = 0;
    while(getline(iss, line)){
        std::vector<std::pair<char, bool>> mapLine;
        for(int x = 0; x < line.length(); x++){
            mapLine.push_back(std::make_pair(line.at(x), false));
            if(line.at(x) == '@' || line.at(x) == '+'){
              start = std::make_pair(y, x);
            }
            if(line.at(x) == '.' || line.at(x) == '+'){
              goals.push_back(std::make_pair(y, x));
            }
        }
        map.push_back(mapLine);
        y++;
    }
}
void findPath(std::pair<int, int> pos, std::string path){
  if(pathFound)return;
  map[pos.first][pos.second].second = true; // set as visited

  for(auto goal : goals){
    if(pos == goal){
      std::cout << path;
      pathFound = true;
    }
  }
  if(isValidPosition(pos.first + 1, pos.second)){
    findPath(std::make_pair(pos.first + 1, pos.second), path + "D");
  }
  if(isValidPosition(pos.first - 1, pos.second)){
    findPath(std::make_pair(pos.first - 1, pos.second), path + "U");
  }
  if(isValidPosition(pos.first, pos.second + 1)){
    findPath(std::make_pair(pos.first, pos.second + 1), path + "R");
  }
  if(isValidPosition(pos.first, pos.second - 1)){
    findPath(std::make_pair(pos.first, pos.second - 1), path + "L");
  }
}
bool isValidPosition(int y, int x){
  return !map[y][x].second &&
      map[y][x].first != '#' &&
      map[y][x].first != '$' &&
      map[y][x].first != '*';
}
