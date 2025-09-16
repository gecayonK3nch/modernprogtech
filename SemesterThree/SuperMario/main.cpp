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
    char cType;
    float horizSpeed;
} TObject;

sf::RenderWindow window(sf::VideoMode(mapWidth * cellSize, mapHeight * cellSize), "SuperMario");
TObject mario;

TObject *brick = nullptr;
int bricklength;

TObject *moving = nullptr;
int movinglength;

int lvl = 1;

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

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType)
{
    SetObjectPos(obj, xPos, yPos);
    obj->width = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
    obj->cType = inType;
    obj->horizSpeed = 0.35;
}

bool IsCollision(TObject o1, TObject o2);
void CreateLevel(int lvl);
TObject *GetNewMoving();

void VertMoveObject(TObject *obj)
{
    obj->IsFly = true;
    obj->vertSpeed += 0.05;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < bricklength; i++)
        if (IsCollision(*obj, brick[i]))
        {
            if (obj[0].vertSpeed > 0)
                obj[0].IsFly = false;

            if ((brick[i].cType == 'c') && (obj[0].vertSpeed < 0) && (obj == &mario))
            {
                brick[i].cType = '-';
                InitObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 1, 1, 'o');
            }
            
            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            if (brick[i].cType == 'f')
            {
                lvl++;
                if (lvl > 3) lvl = 1;
                CreateLevel(lvl);
                sf::sleep(sf::milliseconds(1000));
            }
            break;
        }
}

void DeleteMoving(int i)
{
    movinglength--;
    moving[i] = moving[movinglength];
    moving = (TObject*)realloc(moving, sizeof(*moving) * movinglength);
}

void MarioCollisison()
{
    for (int i = 0; i < movinglength; i++)
        if (IsCollision(mario, moving[i]))
        {
            if (moving[i].cType == 'a')
            {
                if ((mario.IsFly == true) && (mario.vertSpeed > 0) && (mario.y + mario.height < moving[i].y + moving[i].height * 0.5))
                {
                    DeleteMoving(i);
                    i--;
                    continue;
                } else CreateLevel(lvl);
            }
            if (moving[i].cType == 'o')
            {
                DeleteMoving(i);
                i--;
                continue;
            }
        }
}

void HorizonMoveObject(TObject *obj)
{
    obj[0].x += obj[0].horizSpeed;

    for (int i = 0; i < bricklength; i++)
        if (IsCollision(obj[0], brick[i]))
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
            return;
        }
    if (obj[0].cType == 'a')
    {
        TObject tmp = *obj;
        VertMoveObject(&tmp);
        if (tmp.IsFly == true)
        {
            obj[0].x -= obj[0].horizSpeed;
            obj[0].horizSpeed = -obj[0].horizSpeed;
        }
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
            if (IsPosInMap(i, j)){
                int localX = i - ix; 
                int localY = j - iy; 
                if (obj.cType == 'b')
                {
                    float freq = 0.01f * lvl;      // частота волн
                    float threshold = 0.5f * lvl;

                    bool cond = (std::sin(localX * freq) + std::sin(localY * freq) < threshold);

                    vertices.append({{(float)i, (float)j}, cond ? sf::Color::Yellow : sf::Color::Red, {(float)i, (float)j}});
                }
                else if (obj.cType == 'm') {
                    bool cond = ((i + j) % 2 == 0);

                    vertices.append({{(float)i, (float)j}, cond ? sf::Color::White : sf::Color::Cyan, {(float)i, (float)j}});
                } else if (obj.cType == 'f') {
                    bool cond = ((i + j) % 2 == 0);

                    vertices.append({{(float)i, (float)j}, cond ? sf::Color::Green : sf::Color::Cyan, {(float)i, (float)j}});
                } else if (obj.cType == 'a') {
                    bool cond = ((i + j) % 2 == 0);

                    vertices.append({{(float)i, (float)j}, cond ? sf::Color::Red : sf::Color::Magenta, {(float)i, (float)j}});
                } else if (obj.cType == 'c') {
                    vertices.append({{(float)i, (float)j}, sf::Color::Blue, {(float)i, (float)j}});
                } else if (obj.cType == '-') {
                    bool cond = ((i + j) % 2 == 0);

                    vertices.append({{(float)i, (float)j}, cond ? sf::Color::Red : sf::Color::Yellow, {(float)i, (float)j}});
                } else if (obj.cType == 'o') {
                    vertices.append({{(float)i, (float)j}, sf::Color::Yellow, {(float)i, (float)j}});
                }
            }
    
    window.draw(vertices);
}

void HorizonMoveMap(float dx)
{
    mario.x -= dx;
    for (int i = 0; i < bricklength; i++)
        if (IsCollision(mario, brick[i]))
        {
            mario.x += dx;
            return;
        }
    mario.x += dx;

    for (int i = 0; i < bricklength; i++)
        brick[i].x += dx;
    for (int i = 0; i < movinglength; i++)
        moving[i].x += dx;
}

bool IsCollision(TObject o1, TObject o2)
{
    return (((o1.x + o1.width) > o2.x) && (o1.x < (o2.x + o2.width)) && ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height)));
}

TObject *GetNewBrick()
{
    bricklength++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * bricklength);
    return brick + bricklength - 1;
}

TObject *GetNewMoving()
{
    movinglength++;
    moving = (TObject*)realloc(moving, sizeof(*moving) * movinglength);
    return moving + movinglength - 1;
}

void CreateLevel(int lvl)
{
    bricklength = 0;
    brick = (TObject*)realloc(brick, 0);
    movinglength = 0;
    moving = (TObject*)realloc(moving, 0);
    InitObject(&mario, 39, 10, 3, 3, 'm');

    if (lvl == 1)
    {
        InitObject(GetNewBrick(), 20, 20, 40, 5, 'b');
            InitObject(GetNewBrick(), 30, 10, 5, 3, 'c');
            InitObject(GetNewBrick(), 50, 10, 5, 3, 'c');
        InitObject(GetNewBrick(), 60, 15, 40, 10, 'b');
            InitObject(GetNewBrick(), 60, 5, 10, 3, '-');
            InitObject(GetNewBrick(), 70, 5, 5, 3, 'c');
            InitObject(GetNewBrick(), 75, 5, 5, 3, '-');
            InitObject(GetNewBrick(), 80, 5, 5, 3, 'c');
            InitObject(GetNewBrick(), 85, 5, 10, 3, '-');
        InitObject(GetNewBrick(), 80, 20, 20, 5, 'b');
        InitObject(GetNewBrick(), 120, 15, 10, 10, 'b');
        InitObject(GetNewBrick(), 150, 20, 40, 5, 'b');
        InitObject(GetNewBrick(), 210, 15, 10, 10, 'f');
    }
    if (lvl == 2)
    {
        InitObject(GetNewBrick(), 20, 20, 40, 5, 'b');
        InitObject(GetNewBrick(), 60, 15, 10, 10, 'b');
        InitObject(GetNewBrick(), 80, 20, 20, 5, 'b');
        InitObject(GetNewBrick(), 120, 15, 10, 10, 'b');
        InitObject(GetNewBrick(), 150, 20, 40, 5, 'b');
        InitObject(GetNewBrick(), 210, 15, 10, 10, 'f');
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 65, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 160, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 175, 10, 3, 2, 'a');
    } else if (lvl == 3) {
        InitObject(GetNewBrick(), 20, 20, 40, 5, 'b');
        InitObject(GetNewBrick(), 80, 20, 15, 5, 'b');
        InitObject(GetNewBrick(), 120, 15, 15, 10, 'b');
        InitObject(GetNewBrick(), 160, 10, 15, 15, 'f');
        InitObject(GetNewMoving(), 25, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 50, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 80, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 90, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'a');
        InitObject(GetNewMoving(), 130, 10, 3, 2, 'a');
    }
}


int main()
{

    CreateLevel(lvl);
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

        if (mario.y > mapHeight) CreateLevel(lvl);

        ClearMap();
        VertMoveObject(&mario);
        MarioCollisison();

        for (int i = 0; i < bricklength; i++)
            PutObjectOnMap(brick[i]);
        for (int i = 0; i < movinglength; i++)
        {
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);
            if (moving[i].y > mapHeight)
            {
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOnMap(moving[i]);
        }
        PutObjectOnMap(mario);

        ShowMap();
        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}
