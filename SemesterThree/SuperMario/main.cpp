#include <SFML/Graphics.hpp>
#include <cmath>

#define mapWidth 80
#define mapHeight 25
#define cellSize 20

typedef struct SObject {
    float x, y;
    float width, height;
} TObject;

char map[mapHeight][mapWidth + 1];
sf::RenderWindow window(sf::VideoMode(mapWidth * cellSize, mapHeight * cellSize), "SuperMario SFML");
TObject mario;

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
            vertices.append({{(float)i, (float)j}, sf::Color::White, {(float)i, (float)j}});

    window.draw(vertices);
}


int main()
{

    InitObject(&mario, 39, 10, 3, 3);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed)
                window.close();
        }

        ClearMap();
        PutObjectOnMap(mario);
        ShowMap();
    }

    return 0;
}
