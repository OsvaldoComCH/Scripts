#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#define SEED 12345

using int64 = long long;

std::mt19937 Rng(std::chrono::system_clock::now().time_since_epoch().count());

struct Pos
{
    int x, y;
};

enum class TileType
{
    Void = 0,
    BasicFloor = 1,
    BasicWall = 2,
    Entrance = 3
};

class RoomGrid
{
    public:
    std::vector<std::vector<TileType>> Grid;
    std::vector<Pos> Entrances;
    
    int Width, Height;

    RoomGrid(int w, int h)
    {
        Width = w;
        Height = h;
        Grid = std::vector(w, std::vector(h, TileType::Void));
    }

    void Print()
    {
        for(int i = 0; i < Grid.size(); ++i)
        {
            for(int j = 0; j < Grid[i].size(); ++j)
            {
                std::cout << '[';

                switch(Grid[i][j])
                {
                    case TileType::Void:
                    std::cout << '%';
                    break;
                    case TileType::BasicFloor:
                    std::cout << ' ';
                    break;
                    case TileType::BasicWall:
                    std::cout << '#';
                    break;
                    case TileType::Entrance:
                    std::cout << 'o';
                    break;
                }

                std::cout << ']';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void AddEntrance(const Pos& pos)
    {
        Entrances.push_back(pos);
        Grid[pos.x][pos.y] = TileType::Entrance;
    }

    bool IsTileValid(const Pos& pos, const std::vector<std::vector<char>>& walked)
    {
        return !(pos.x <= 0 || pos.y <= 0 || pos.x >= Width - 1 || pos.y >= Height - 1 || walked[pos.x][pos.y] || Grid[pos.x][pos.y] == TileType::Entrance);
    }

    void GetNeighborTiles(const Pos& pos, std::vector<Pos>& tiles, const std::vector<std::vector<char>>& walked)
    {
        Pos tile = {pos.x + 1, pos.y};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x - 1, pos.y};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x, pos.y + 1};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
        tile = {pos.x, pos.y - 1};
        if(IsTileValid(tile, walked) && std::none_of(tiles.begin(), tiles.end(), [tile](Pos p){return *(int64*)&p == *(int64*)&tile;}))
        {
            tiles.push_back(tile);
        }
    }

    void Generate(TileType firstTile, const std::vector<TileType>& walkableTiles)
    {
        using namespace std;

        for(int i = 0; i < Grid.size(); ++i)
        {
            for(int j = 0; j < Grid[i].size(); ++j)
            {
                if(Grid[i][j] != TileType::Entrance && (i == 0 || j == 0 || i == Width - 1 || j == Height - 1))
                {
                    Grid[i][j] = TileType::BasicWall;
                }
            }
        }

        for(int i = 0; i < Entrances.size(); ++i)
        {
            Pos start = Entrances[i];

            vector<Pos> possibleTiles;

            vector<vector<char>> walkedGrid(Width, vector<char>(Height, 0));

            GetNeighborTiles(start, possibleTiles, walkedGrid);

            int startBias = 6;

            while(1)
            {
                std::vector<Pos> newTiles;

                for_each(possibleTiles.begin(), possibleTiles.end(),
                [this, &startBias, &newTiles, &walkedGrid](Pos p)
                {
                    walkedGrid[p.x][p.y] = 1;
                    if(Rng() % (4 + startBias))
                    {
                        Grid[p.x][p.y] = TileType::BasicFloor;
                        GetNeighborTiles(p, newTiles, walkedGrid);
                    }
                });

                possibleTiles = std::move(newTiles);

                Print();

                if(possibleTiles.size() == 0){break;}
                if(startBias > 0){startBias -= 2;}

                if(startBias == 0 && any_of(possibleTiles.begin(), possibleTiles.end(),
                [this](Pos p){return Grid[p.x][p.y] == TileType::BasicFloor;}))
                {
                    break;
                }
            }
        }
    }
};

int main()
{
    RoomGrid room(15, 21);

    room.AddEntrance({0, 10});
    room.AddEntrance({7, 0});
    room.AddEntrance({7, 20});
    room.AddEntrance({14, 10});

    room.Generate(TileType::BasicFloor, std::vector<TileType>({TileType::BasicFloor}));
}
