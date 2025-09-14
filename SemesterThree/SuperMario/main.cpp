#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#define mapWidth 80
#define mapHeight 25
#define cellSize 20

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
} TObject;

char map[mapHeight][mapWidth + 1];
sf::RenderWindow window(sf::VideoMode(mapWidth * cellSize, mapHeight * cellSize), "SuperMario SFML");
TObject mario;
TObject brick[1];

void ClearMap()
{
    window.clear(sf::Color::Black);
}

void ShowMap()
{
    window.display();
}

void SetObjectPos(TObject *obj, float xPos, float yPos)
{
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight)
{
    SetObjectPos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
}

bool IsCollision(TObject o1, TObject o2);

void VertMoveObject(TObject *obj)
{
    obj->IsFly = true;
    obj->vertSpeed += 0.05;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);
    if (IsCollision(*obj, brick[0]))
    {
        obj->y -= obj->vertSpeed;
        obj->vertSpeed = 0;
        obj->IsFly = false;
    }
}

bool IsPosInMap(int x, int y)
{
    return ((x >= 0) && (x < mapWidth * cellSize) && (y >= 0) && (y < mapHeight * cellSize));
}

void PutObjectOnMap(TObject obj)
{
    int ix = (int)round(obj.x) * cellSize;
    int iy = (int)round(obj.y) * cellSize;
    int iWidth = (int)round(obj.width) * cellSize;
    int iHeight = (int)round(obj.height) * cellSize;
    sf::VertexArray vertices(sf::PrimitiveType::Points);

    for (int i = ix; i < (ix + iWidth); i++)
        for (int j = iy; j < (iy + iHeight); j++)
            if (IsPosInMap(i, j))
                vertices.append({{(float)i, (float)j}, sf::Color::White, {(float)i, (float)j}});

    window.draw(vertices);
}

void HorizonMoveMap(float dx)
{
    brick[0].x += dx;
}

bool IsCollision(TObject o1, TObject o2)
{
    return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)));
}


int main()
{

    InitObject(&mario, 39, 10, 3, 3);
    InitObject(brick, 20, 20, 40, 5);
    bool left = false, right = false, up = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                sf::Keyboard::Key code = event.key.code;
                if (code == sf::Keyboard::W || code == sf::Keyboard::Space || code == sf::Keyboard::Up)
                    up = true;
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
                    left = true;
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
                    right = true;
            }
            if (event.type == sf::Event::KeyReleased){
                sf::Keyboard::Key code = event.key.code;
                if (code == sf::Keyboard::W || code == sf::Keyboard::Space || code == sf::Keyboard::Up)
                    up = false;
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
                    left = false;
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
                    right = false;
            } 
        }
        if (mario.IsFly == false && up)
            mario.vertSpeed = -1;
        if (left)
            HorizonMoveMap(1);
        if (right)
            HorizonMoveMap(-1);

        ClearMap();
        VertMoveObject(&mario);
        PutObjectOnMap(brick[0]);
        PutObjectOnMap(mario);

        ShowMap();
    }

    return 0;
}
