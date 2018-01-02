#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


void render();
void update(sf::Time delta);
void init();
bool processEvents();
int makeMove(int player);
std::vector<int> piles;
std::vector<int> primes = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23};
int n=3;
int player = 1;

sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
sf::RectangleShape rectangle(sf::Vector2f(50, 10));
sf::RectangleShape button(sf::Vector2f(70,40));

int main(int argc, char const** argv)
{
    init();
    sf::Clock clock;
    render();
    // Start the game loop
    while (window.isOpen())
    {
        if(!processEvents()) break;
        update(clock.restart());
        render();
    }
    return EXIT_SUCCESS;
}

void init(){
    //setup game
    player = 1;
    srand(time(NULL));
    std::cout << "Game Started!";
    for (int i = 0; i<n; i++){
        piles.push_back(rand()%28);
        std::cout << "Number Added" << std::endl;
    }
}

void update(sf::Time delta){
    std::cout << "Pile 1: " << piles.at(0) << std::endl << "Pile 2: " << piles.at(1) << std::endl << "Pile 3: " << piles.at(2) << std::endl<< std::endl;
    if(makeMove(player) !=0)
    {
        std::cout << "Player " << player <<" Wins!" << std::endl;
        exit(0);
    }
    if(player == 1){
        player = 2;
    } else if(player ==2){
        player = 1;
    }
}

bool processEvents() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window.close();
            break;
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) return false;
    return true;
}


int makeMove(int player){
    std::cout << "Player " << player << " choose pile 1, 2 or 3"<< std::endl;
    int pile=0;
    int prime=0;
    std::cin >> pile;
    std::cout << "Player " << player << " choose a prime"<< std::endl;
    std::cin >> prime;
    if(pile == 1){
        piles.at(0) -= prime;
    }
    if(pile == 2){
        piles.at(1) -= prime;
    }
    if(pile == 3){
        piles.at(2) -= prime;
    }
    if(piles.at(0)&& piles.at(1)&&piles.at(2) !=0)
        return 0;
    return player;
}

void render(){
    std::ostringstream oss;
    
    // Clear screen
    window.clear();
    
    
    //draw text
    //set up text to be drawn
    sf::Text text;
    sf::Font font;
    
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(35);
    if (!font.loadFromFile("/Users/SeanK/Documents/ConsoleGameDevelopment/YANFWWFML/YANFWWFML/sansation.ttf"))
    {
        std::cout << "Font not found";
    }
    text.setFont(font);
    window.draw(text);
    //draw coins
    int k = 15;
    rectangle.setFillColor(sf::Color(255,255,0));
    for(int i = 0; i < piles.at(0); i++)
    {
        rectangle.setPosition(200, k * i);
        window.draw(rectangle);
    }
    for(int i = 0; i < piles.at(1); i++)
    {
        rectangle.setPosition(400, k * i);
        window.draw(rectangle);
    }
    for(int i = 0; i < piles.at(2); i++)
    {
        rectangle.setPosition(600, k * i);
        window.draw(rectangle);
    }
    
    //draw three blocks to select a pile.
    int w = 190;
    for(int i = 0; i < 3; i++){
        button.setPosition(w, 450);
        window.draw(button);
        oss << i+1;
        text.setPosition(w+25, 450);
        text.setString(oss.str());
        window.draw(text);
        w += 200;
        oss.str("");
    }
    
    
    //draw buttons for pile 1
    int widthBetweenBlocks = 10;
    for(int i = 0; i < primes.size(); i++){
        if(primes.at(i) < piles.at(0)){
            button.setPosition(widthBetweenBlocks, 550);
            window.draw(button);
            oss << primes.at(i);
            text.setPosition(widthBetweenBlocks+25, 550);
            text.setString(oss.str());
            window.draw(text);
            widthBetweenBlocks += 80;
            oss.str("");
        }
    }
    
    //display the amount of coins beside each pile
    text.setPosition(130, 20);
    text.setFillColor(sf::Color::White);
    oss << piles.at(0);
    text.setString(oss.str());
    window.draw(text);
    oss.str("");
    text.setPosition(340, 20);
    oss << piles.at(1);
    text.setString(oss.str());
    window.draw(text);
    oss.str("");
    text.setPosition(540, 20);
    oss << piles.at(2);
    text.setString(oss.str());
    window.draw(text);
    oss.str("");
    
    
    // Update the window
    window.display();
}


