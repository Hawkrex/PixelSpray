#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 400), "SFML lol!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.move(0.f, 200.f);

    sf::Font font;
    sf::Text text("Connexion en cours", font);
    text.setColor(sf::Color::Red);
    try
    {
        if(!font.loadFromFile("data/arial.ttf"))
            throw string("Error loading arial font");
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }


    window.draw(text);
    window.display();

    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 8080);//("www.pixelspray.fr");
    try
    {
        if(status != sf::Socket::Done)
            throw string("Error network");
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }

    text.setString("En attente");




    char data[100];
    std::size_t received;

    // TCP socket:

    try
    {
        if(socket.receive(data, 100, received) != sf::Socket::Done)
            throw string("Error network");
    }
    catch(string const& chaine)
    {
        cerr << chaine << endl;
    }


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Space)
                {
                    shape.setFillColor(sf::Color::Yellow);
                    text.setString("Go !!!");
                    text.setColor(sf::Color::Green);
                }
        }

        window.clear();
        window.draw(shape);
        window.draw(text);
        window.display();
    }

    return 0;
}
