#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

constexpr int MAP_WIDTH = 80;
constexpr int MAP_HEIGHT = 25;
constexpr int CELL_SIZE = 20;
constexpr float PADDING = 10.0f;
constexpr float GRAVITY = 0.05f;
constexpr float MARIO_JUMP_SPEED = -1.0f;
constexpr float DEFAULT_HORIZONTAL_SPEED = 0.35f;
constexpr int MAX_LEVEL = 3;

struct GameObject {
    float x, y;
    float width, height;
    float verticalSpeed;
    float horizontalSpeed;
    bool isAirborne;
    char type;
};

struct GameState {
    GameObject mario;
    std::vector<GameObject> bricks;
    std::vector<GameObject> movingObjects;
    int currentLevel;
    int score;
    int maxLevel;
};

void initializeLevel(GameState& state, int level);
bool checkCollision(const GameObject& o1, const GameObject& o2);

GameObject createObject(float x, float y, float w, float h, char type) {
    GameObject obj;
    obj.x = x;
    obj.y = y;
    obj.width = w;
    obj.height = h;
    obj.verticalSpeed = 0;
    obj.horizontalSpeed = DEFAULT_HORIZONTAL_SPEED;
    obj.isAirborne = false;
    obj.type = type;
    return obj;
}

void handlePlayerDeath(sf::RenderWindow& window, GameState& state) {
    window.clear(sf::Color::Red);
    window.display();
    sf::sleep(sf::milliseconds(500));
    initializeLevel(state, state.currentLevel);
}

void moveObjectVertically(GameObject& obj, GameState& state, sf::RenderWindow& window) {
    obj.isAirborne = true;
    obj.verticalSpeed += GRAVITY;
    obj.y += obj.verticalSpeed;

    for (auto& brick : state.bricks) {
        if (checkCollision(obj, brick)) {
            if (obj.verticalSpeed > 0) {
                obj.isAirborne = false;
            }

            if (brick.type == 'c' && obj.verticalSpeed < 0 && &obj == &state.mario) {
                brick.type = '-';
                GameObject coin = createObject(brick.x, brick.y - 3, 1, 1, 'o');
                coin.verticalSpeed = -0.7f;
                state.movingObjects.push_back(coin);
            }

            obj.y -= obj.verticalSpeed;
            obj.verticalSpeed = 0;

            if (brick.type == 'f' && &obj == &state.mario) {
                state.currentLevel++;
                if (state.currentLevel > state.maxLevel) state.currentLevel = 1;

                window.clear(sf::Color::Green);
                window.display();
                initializeLevel(state, state.currentLevel);
                return; 
            }
            break;
        }
    }
}

void handleMarioCollisions(GameState& state, sf::RenderWindow& window) {
    for (size_t i = 0; i < state.movingObjects.size(); ) {
        if (checkCollision(state.mario, state.movingObjects[i])) {
            if (state.movingObjects[i].type == 'a') {
                if (state.mario.isAirborne && state.mario.verticalSpeed > 0 && 
                    (state.mario.y + state.mario.height < state.movingObjects[i].y + state.movingObjects[i].height * 0.5)) {
                    state.score += 50;
                    state.movingObjects.erase(state.movingObjects.begin() + i);
                    continue;
                } else {
                    handlePlayerDeath(window, state);
                    return;
                }
            }
            if (state.movingObjects[i].type == 'o') {
                state.score += 100;
                state.movingObjects.erase(state.movingObjects.begin() + i);
                continue;
            }
        }
        ++i;
    }
}

void moveObjectHorizontally(GameObject& obj, GameState& state, sf::RenderWindow& window) {
    obj.x += obj.horizontalSpeed;

    for (const auto& brick : state.bricks) {
        if (checkCollision(obj, brick)) {
            obj.x -= obj.horizontalSpeed;
            obj.horizontalSpeed = -obj.horizontalSpeed;
            return;
        }
    }

    if (obj.type == 'a') {
        GameObject temp = obj;
        temp.isAirborne = true;
        temp.verticalSpeed += GRAVITY;
        temp.y += temp.verticalSpeed;
        
        bool wouldFall = true;
        for (const auto& brick : state.bricks) {
            if (checkCollision(temp, brick)) {
                wouldFall = false;
                break;
            }
        }
        
        if (wouldFall) {
            obj.x -= obj.horizontalSpeed;
            obj.horizontalSpeed = -obj.horizontalSpeed;
        }
    }
}

bool isPositionInMap(int x, int y) {
    return (x >= 0 && x < MAP_WIDTH * CELL_SIZE && y >= 0 && y < MAP_HEIGHT * CELL_SIZE);
}

void drawObject(sf::RenderWindow& window, const GameObject& obj, int level) {
    int ix = static_cast<int>(std::round(obj.x)) * CELL_SIZE;
    int iy = static_cast<int>(std::round(obj.y)) * CELL_SIZE;
    int iWidth = static_cast<int>(std::round(obj.width)) * CELL_SIZE;
    int iHeight = static_cast<int>(std::round(obj.height)) * CELL_SIZE;
    
    sf::VertexArray vertices(sf::PrimitiveType::Points);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (isPositionInMap(i, j)) {
                int localX = i - ix;
                int localY = j - iy;
                sf::Color color = sf::Color::Magenta;

                if (obj.type == 'b') {
                    float freq = 0.01f * level;
                    float threshold = 0.5f * level;
                    bool cond = (std::sin(localX * freq) + std::sin(localY * freq) < threshold);
                    color = cond ? sf::Color::Yellow : sf::Color::Red;
                } else if (obj.type == 'm') {
                    bool cond = ((i + j) % 2 == 0);
                    color = cond ? sf::Color::White : sf::Color::Cyan;
                } else if (obj.type == 'f') {
                    bool cond = ((i + j) % 2 == 0);
                    color = cond ? sf::Color::Green : sf::Color::Cyan;
                } else if (obj.type == 'a') {
                    bool cond = ((i + j) % 2 == 0);
                    color = cond ? sf::Color::Red : sf::Color::Magenta;
                } else if (obj.type == 'c') {
                    color = sf::Color::Blue;
                } else if (obj.type == '-') {
                    bool cond = ((i + j) % 2 == 0);
                    color = cond ? sf::Color::Red : sf::Color::Yellow;
                } else if (obj.type == 'o') {
                    color = sf::Color::Yellow;
                }
                
                vertices.append(sf::Vertex(sf::Vector2f((float)i, (float)j), color));
            }
        }
    }
    window.draw(vertices);
}

void scrollMap(float dx, GameState& state) {
    state.mario.x -= dx;
    for (const auto& brick : state.bricks) {
        if (checkCollision(state.mario, brick)) {
            state.mario.x += dx;
            return;
        }
    }
    state.mario.x += dx;

    for (auto& brick : state.bricks) brick.x += dx;
    for (auto& obj : state.movingObjects) obj.x += dx;
}

bool checkCollision(const GameObject& o1, const GameObject& o2) {
    return (o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) &&
           (o1.y + o1.height > o2.y) && (o1.y < o2.y + o2.height);
}

void drawScore(sf::RenderWindow& window, sf::Text& scoreText, int score) {
    scoreText.setString("Score: " + std::to_string(score));
    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setOrigin(bounds.left + bounds.width, bounds.top);
    scoreText.setPosition(bounds.width + PADDING, PADDING - bounds.top);
    window.draw(scoreText);
}

void initializeLevel(GameState& state, int level) {
    state.bricks.clear();
    state.movingObjects.clear();
    
    state.mario = createObject(39, 10, 3, 3, 'm');
    state.score = 0;
    state.currentLevel = level;
    state.maxLevel = MAX_LEVEL;

    if (level == 1) {
        state.bricks.push_back(createObject(20, 20, 40, 5, 'b'));
        state.bricks.push_back(createObject(30, 10, 5, 3, 'c'));
        state.bricks.push_back(createObject(50, 10, 5, 3, 'c'));
        state.bricks.push_back(createObject(60, 15, 40, 10, 'b'));
        state.bricks.push_back(createObject(60, 5, 10, 3, '-'));
        state.bricks.push_back(createObject(70, 5, 5, 3, 'c'));
        state.bricks.push_back(createObject(75, 5, 5, 3, '-'));
        state.bricks.push_back(createObject(80, 5, 5, 3, 'c'));
        state.bricks.push_back(createObject(85, 5, 10, 3, '-'));
        state.bricks.push_back(createObject(80, 20, 20, 5, 'b'));
        state.bricks.push_back(createObject(120, 15, 10, 10, 'b'));
        state.bricks.push_back(createObject(150, 20, 40, 5, 'b'));
        state.bricks.push_back(createObject(210, 15, 10, 10, 'f'));
    } else if (level == 2) {
        state.bricks.push_back(createObject(20, 20, 40, 5, 'b'));
        state.bricks.push_back(createObject(60, 15, 10, 10, 'b'));
        state.bricks.push_back(createObject(80, 20, 20, 5, 'b'));
        state.bricks.push_back(createObject(120, 15, 10, 10, 'b'));
        state.bricks.push_back(createObject(150, 20, 40, 5, 'b'));
        state.bricks.push_back(createObject(210, 15, 10, 10, 'f'));
        
        state.movingObjects.push_back(createObject(25, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(80, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(65, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(120, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(160, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(175, 10, 3, 2, 'a'));
    } else if (level == 3) {
        state.bricks.push_back(createObject(20, 20, 40, 5, 'b'));
        state.bricks.push_back(createObject(80, 20, 15, 5, 'b'));
        state.bricks.push_back(createObject(120, 15, 15, 10, 'b'));
        state.bricks.push_back(createObject(160, 10, 15, 15, 'f'));
        
        state.movingObjects.push_back(createObject(25, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(50, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(80, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(90, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(120, 10, 3, 2, 'a'));
        state.movingObjects.push_back(createObject(130, 10, 3, 2, 'a'));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE), "SuperMario");
    sf::Font font;
    if (!font.loadFromFile("Ubuntu-B.ttf")) {
        std::cerr << "Error loading font\n";
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    GameState state;
    initializeLevel(state, 1);

    bool left = false, right = false, up = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                sf::Keyboard::Key code = event.key.code;
                if (code == sf::Keyboard::W || code == sf::Keyboard::Space || code == sf::Keyboard::Up)
                    up = true;
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
                    left = true;
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
                    right = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                sf::Keyboard::Key code = event.key.code;
                if (code == sf::Keyboard::W || code == sf::Keyboard::Space || code == sf::Keyboard::Up)
                    up = false;
                if (code == sf::Keyboard::A || code == sf::Keyboard::Left)
                    left = false;
                if (code == sf::Keyboard::D || code == sf::Keyboard::Right)
                    right = false;
            }
        }

        if (!state.mario.isAirborne && up)
            state.mario.verticalSpeed = MARIO_JUMP_SPEED;
        
        if (left)
            scrollMap(1, state);
        if (right)
            scrollMap(-1, state);

        if (state.mario.y > MAP_HEIGHT) {
            handlePlayerDeath(window, state);
        }

        window.clear(sf::Color::Black);
        
        moveObjectVertically(state.mario, state, window);
        handleMarioCollisions(state, window);

        for (const auto& brick : state.bricks)
            drawObject(window, brick, state.currentLevel);
            
        for (size_t i = 0; i < state.movingObjects.size(); ) {
            moveObjectVertically(state.movingObjects[i], state, window);
            moveObjectHorizontally(state.movingObjects[i], state, window);
            
            if (state.movingObjects[i].y > MAP_HEIGHT) {
                state.movingObjects.erase(state.movingObjects.begin() + i);
            } else {
                drawObject(window, state.movingObjects[i], state.currentLevel);
                ++i;
            }
        }
        
        drawObject(window, state.mario, state.currentLevel);
        drawScore(window, scoreText, state.score);

        window.display();
        sf::sleep(sf::milliseconds(8));
    }

    return 0;
}
