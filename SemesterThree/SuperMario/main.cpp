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

    GameObject(float xPos, float yPos, float w, float h, char t)
        : x(xPos), y(yPos), width(w), height(h), verticalSpeed(0), horizontalSpeed(DEFAULT_HORIZONTAL_SPEED), isAirborne(false), type(t) {}
};

class Game {
public:
    Game() : window(sf::VideoMode(MAP_WIDTH * CELL_SIZE, MAP_HEIGHT * CELL_SIZE), "SuperMario"), 
             mario(39, 10, 3, 3, 'm'), currentLevel(1), score(0) {
        if (!font.loadFromFile("Ubuntu-B.ttf")) {
            std::cerr << "Error loading font\n";
        }
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        initializeLevel(currentLevel);
    }

    void run() {
        bool left = false, right = false, up = false;

        while (window.isOpen()) {
            processEvents(left, right, up);
            update(left, right, up);
            render();
            sf::sleep(sf::milliseconds(8));
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;

    GameObject mario;
    std::vector<GameObject> bricks;
    std::vector<GameObject> movingObjects;

    int currentLevel;
    int score;

    void processEvents(bool& left, bool& right, bool& up) {
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
    }

    void update(bool left, bool right, bool up) {
        if (!mario.isAirborne && up) {
            mario.verticalSpeed = MARIO_JUMP_SPEED;
        }
        
        if (left) scrollMap(1);
        if (right) scrollMap(-1);

        if (mario.y > MAP_HEIGHT) {
            resetLevel();
            return;
        }

        moveObjectVertically(mario);
        handleMarioCollisions();

        for (size_t i = 0; i < movingObjects.size(); ) {
            moveObjectVertically(movingObjects[i]);
            moveObjectHorizontally(movingObjects[i]);

            if (movingObjects[i].y > MAP_HEIGHT) {
                movingObjects.erase(movingObjects.begin() + i);
            } else {
                ++i;
            }
        }
    }

    void render() {
        window.clear(sf::Color::Black);

        for (const auto& brick : bricks) {
            drawObject(brick);
        }
        for (const auto& obj : movingObjects) {
            drawObject(obj);
        }
        drawObject(mario);
        
        updateScoreDisplay();
        window.display();
    }

    void initializeLevel(int lvl) {
        bricks.clear();
        movingObjects.clear();
        
        mario = GameObject(39, 10, 3, 3, 'm');
        score = 0;

        if (lvl == 1) {
            bricks.emplace_back(20, 20, 40, 5, 'b');
            bricks.emplace_back(30, 10, 5, 3, 'c');
            bricks.emplace_back(50, 10, 5, 3, 'c');
            bricks.emplace_back(60, 15, 40, 10, 'b');
            bricks.emplace_back(60, 5, 10, 3, '-');
            bricks.emplace_back(70, 5, 5, 3, 'c');
            bricks.emplace_back(75, 5, 5, 3, '-');
            bricks.emplace_back(80, 5, 5, 3, 'c');
            bricks.emplace_back(85, 5, 10, 3, '-');
            bricks.emplace_back(80, 20, 20, 5, 'b');
            bricks.emplace_back(120, 15, 10, 10, 'b');
            bricks.emplace_back(150, 20, 40, 5, 'b');
            bricks.emplace_back(210, 15, 10, 10, 'f');
        } else if (lvl == 2) {
            bricks.emplace_back(20, 20, 40, 5, 'b');
            bricks.emplace_back(60, 15, 10, 10, 'b');
            bricks.emplace_back(80, 20, 20, 5, 'b');
            bricks.emplace_back(120, 15, 10, 10, 'b');
            bricks.emplace_back(150, 20, 40, 5, 'b');
            bricks.emplace_back(210, 15, 10, 10, 'f');
            
            movingObjects.emplace_back(25, 10, 3, 2, 'a');
            movingObjects.emplace_back(80, 10, 3, 2, 'a');
            movingObjects.emplace_back(65, 10, 3, 2, 'a');
            movingObjects.emplace_back(120, 10, 3, 2, 'a');
            movingObjects.emplace_back(160, 10, 3, 2, 'a');
            movingObjects.emplace_back(175, 10, 3, 2, 'a');
        } else if (lvl == 3) {
            bricks.emplace_back(20, 20, 40, 5, 'b');
            bricks.emplace_back(80, 20, 15, 5, 'b');
            bricks.emplace_back(120, 15, 15, 10, 'b');
            bricks.emplace_back(160, 10, 15, 15, 'f');
            
            movingObjects.emplace_back(25, 10, 3, 2, 'a');
            movingObjects.emplace_back(50, 10, 3, 2, 'a');
            movingObjects.emplace_back(80, 10, 3, 2, 'a');
            movingObjects.emplace_back(90, 10, 3, 2, 'a');
            movingObjects.emplace_back(120, 10, 3, 2, 'a');
            movingObjects.emplace_back(130, 10, 3, 2, 'a');
        }
    }

    void resetLevel() {
        window.clear(sf::Color::Red);
        window.display();
        sf::sleep(sf::milliseconds(500));
        initializeLevel(currentLevel);
    }

    void moveObjectVertically(GameObject& obj) {
        obj.isAirborne = true;
        obj.verticalSpeed += GRAVITY;
        obj.y += obj.verticalSpeed;

        for (auto& brick : bricks) {
            if (checkCollision(obj, brick)) {
                if (obj.verticalSpeed > 0) {
                    obj.isAirborne = false;
                }

                if (brick.type == 'c' && obj.verticalSpeed < 0 && &obj == &mario) {
                    brick.type = '-';
                    GameObject coin(brick.x, brick.y - 3, 1, 1, 'o');
                    coin.verticalSpeed = -0.7f;
                    movingObjects.emplace_back(coin);
                }

                obj.y -= obj.verticalSpeed;
                obj.verticalSpeed = 0;

                if (brick.type == 'f' && &obj == &mario) {
                    currentLevel++;
                    if (currentLevel > MAX_LEVEL) currentLevel = 1;
                    
                    window.clear(sf::Color::Green);
                    window.display();
                    initializeLevel(currentLevel);
                    return; 
                }
                break;
            }
        }
    }

    void moveObjectHorizontally(GameObject& obj) {
        obj.x += obj.horizontalSpeed;

        for (const auto& brick : bricks) {
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
            for (const auto& brick : bricks) {
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

    void handleMarioCollisions() {
        for (size_t i = 0; i < movingObjects.size(); ) {
            if (checkCollision(mario, movingObjects[i])) {
                if (movingObjects[i].type == 'a') {
                    if (mario.isAirborne && mario.verticalSpeed > 0 && 
                        (mario.y + mario.height < movingObjects[i].y + movingObjects[i].height * 0.5)) {
                        score += 50;
                        movingObjects.erase(movingObjects.begin() + i);
                        continue;
                    } else {
                        resetLevel();
                        return;
                    }
                } else if (movingObjects[i].type == 'o') {
                    score += 100;
                    movingObjects.erase(movingObjects.begin() + i);
                    continue;
                }
            }
            ++i;
        }
    }

    void scrollMap(float dx) {
        mario.x -= dx;
        for (const auto& brick : bricks) {
            if (checkCollision(mario, brick)) {
                mario.x += dx;
                return;
            }
        }
        mario.x += dx;

        for (auto& brick : bricks) brick.x += dx;
        for (auto& obj : movingObjects) obj.x += dx;
    }

    bool checkCollision(const GameObject& o1, const GameObject& o2) const {
        return (o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) &&
               (o1.y + o1.height > o2.y) && (o1.y < o2.y + o2.height);
    }

    bool isPositionInMap(int x, int y) const {
        return (x >= 0 && x < MAP_WIDTH * CELL_SIZE && y >= 0 && y < MAP_HEIGHT * CELL_SIZE);
    }

    void drawObject(const GameObject& obj) {
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
                        float freq = 0.01f * currentLevel;
                        float threshold = 0.5f * currentLevel;
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

    void updateScoreDisplay() {
        scoreText.setString("Score: " + std::to_string(score));
        sf::FloatRect bounds = scoreText.getLocalBounds();
        scoreText.setOrigin(bounds.left + bounds.width, bounds.top);
        scoreText.setPosition(bounds.width + PADDING, PADDING - bounds.top);
        window.draw(scoreText);
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
