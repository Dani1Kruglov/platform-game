#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "view.h"
#include "Map.hpp"
#include "Player.hpp"
#include "villian.hpp"
#include "menu.hpp"


using namespace sf;

int main()
{
    int ox,oy;
    ox = 1000;
    oy = 800;
    RenderWindow window(VideoMode(ox, oy), "Game SFML");
    menu(window);
    vw::view.reset((FloatRect(0,0,ox,oy)));

    Font font;//шрифт
    font.loadFromFile("a_SimplerClg.ttf");
    Text text("", font, 35);
    text.setColor(Color::White);

    Texture land;//карта
    land.loadFromFile("tile.png");//текстура блоков
    Sprite Land;
    Land.setTexture(land);


    Texture t;//герой
    t.loadFromFile("fang.png");//текстура героя
    pl::Player p(t);


    Texture villian;//злодей
    villian.loadFromFile("villian.png");
    vl::Enemy enemy1;
    enemy1.set(villian,2500,703);
    vl::Enemy enemy2;
    enemy2.set(villian,2700,250);
    vl::Enemy enemy3;
    enemy3.set(villian,2250,400);
    vl::Enemy enemy4;
    enemy4.set(villian,4000,250);
    vl::Enemy enemy5;
    enemy5.set(villian,4700,600);
    vl::Enemy enemy6;
    enemy6.set(villian,1800,510);


    SoundBuffer buffer;
    buffer.loadFromFile("Jump.ogg");
    Sound sound(buffer);

    Music music;
    music.openFromFile("Mario_Theme.ogg");
    music.play();
    music.setLoop(true);

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();//создание времени
        clock.restart();

        time = time / 150;

        if (time>20) time = 20;//конец создания времени

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if(p.life )
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))//влево
            {
                p.dx = -0.1;//придаем ускорение персонажу
            }

            if (Keyboard::isKeyPressed(Keyboard::Right))//вправо
            {
                p.dx = 0.1;//придаем ускорение персонажу

            }

            if (Keyboard::isKeyPressed(Keyboard::Up))//Высота
            {
                if (p.onGround)
                {
                    p.dy = -0.15;//ускорение при прыжке
                    p.onGround = false;
                    sound.play();
                }
            }
            vw:: PlayerCoordinate(p.getplayercoordinateX(), p.getplayercoordinateY());
        }

        p.update(time);
        enemy3.update(time);
        enemy1.update(time);
        enemy2.update(time);
        enemy4.update(time);
        enemy5.update(time);
        enemy6.update(time);
        window.setView(vw::view);

        if  (p.rect.intersects( enemy3.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy3.life)
            {
                if (p.dy>0)
                {
                    enemy3.dx = 0;
                    p.dy= -0.2;
                    enemy3.life=false;
                }
                else
                {
                    p.health -= 0.1;
                }
            }
        }
        if  (p.rect.intersects( enemy1.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy1.life)
            {
                if (p.dy>0)
                {
                    enemy1.dx = 0;
                    p.dy= -0.2;
                    enemy1.life=false;
                }
                else
                {
                    p.health = 50;
                }
            }
        }
        if  (p.rect.intersects( enemy2.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy2.life)
            {
                if (p.dy>0)
                {
                    enemy2.dx = 0;
                    p.dy= -0.2;
                    enemy2.life=false;
                }
                else
                {
                    p.health = 50;
                }
            }
        }

        if  (p.rect.intersects( enemy4.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy4.life)
            {
                if (p.dy>0)
                {
                    enemy4.dx = 0;
                    p.dy= -0.2;
                    enemy4.life=false;
                }
                else
                {
                    p.health -= 0.1;
                }
            }
        }
        if  (p.rect.intersects( enemy5.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy5.life)
            {
                if (p.dy>0)
                {
                    enemy5.dx = 0;
                    p.dy= -0.2;
                    enemy5.life=false;
                }
                else
                {
                    p.health -= 0.1;
                }
            }
        }

        if  (p.rect.intersects( enemy6.rect ) ) //если соприкасается со злодеем координатами,то
        {
            if (enemy6.life)
            {
                if (p.dy>0)
                {
                    enemy6.dx = 0;
                    p.dy= -0.2;
                    enemy6.life=false;
                }
                else
                {
                    p.health -= 0.1;
                }
            }
        }

        if(p.life == false)
        {
            window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }


        for (int i = 0; i < mp::H; i++)//графика для карты
            for (int j = 0; j < mp::W; j++)
            {
                if (mp::TileMap[i][j] == ' ')
                {
                    Land.setTextureRect(IntRect(0, 0, 32, 32));
                }
                if (mp::TileMap[i][j] == '0')
                {
                    Land.setTextureRect(IntRect(64, 0, 32, 32));
                }

                if (mp::TileMap[i][j] == 'B')
                {
                    Land.setTextureRect(IntRect(96, 0, 32, 32));

                }

                if (mp::TileMap[i][j] == 'P')
                {
                    Land.setTextureRect(IntRect(64, 0, 32, 32));
                }

                if (mp::TileMap[i][j] == 'M')
                {
                   Land.setTextureRect((IntRect(128,0,32,32)));
                }

                if ((mp::TileMap[i][j] == 'E') || (mp::TileMap[i][j] == 'Z') || (mp::TileMap[i][j] == 'U'))
                {
                    Land.setTextureRect((IntRect(163,2,35,32)));
                }

                if ((mp::TileMap[i][j] == 'Y')||(mp::TileMap[i][j] == 'A'))
                {
                    Land.setTextureRect((IntRect(198,0,35,32)));
                }

                if (mp::TileMap[i][j] == 'K')
                {
                    Land.setTextureRect((IntRect(235,0,32,32)));
                }

                if (mp::TileMap[i][j] == 'L')
                {
                    Land.setTextureRect((IntRect(268,0,35,32)));
                }

                if (mp::TileMap[i][j] == 'S')
                {
                    Land.setTextureRect((IntRect(313,0,35,32)));
                }
                if (mp::TileMap[i][j] == 'Q')
                {
                    Land.setTextureRect((IntRect(350,0,35,32)));
                }
                if (mp::TileMap[i][j] == 'W')
                {
                    Land.setTextureRect((IntRect(376,0,50,32)));
                }
                Land.setPosition(j * 32, i * 32);
                window.draw(Land);
            }

        std::ostringstream playerHealthString;    // объявили переменную здоровья
        playerHealthString << p.health;  //формируем строку
        std::ostringstream PlayerCoins;
        PlayerCoins << p.coin;
        text.setString("Health " + playerHealthString.str() + "\n\n Coins " + PlayerCoins.str() );//задаем строку тексту и вызываем сформированную выше строку методом .str()
        text.setPosition(vw::view.getCenter().x - 450, vw::view.getCenter().y - 350);//задаем позицию текста, отступая от персонажа

        window.draw(text);//рисую этот текст
        window.draw(p.sprite);
        window.draw(enemy1.sprite);
        window.draw(enemy5.sprite);
        window.draw(enemy2.sprite);
        window.draw(enemy3.sprite);
        window.draw(enemy4.sprite);
        window.draw(enemy6.sprite);
        window.display();
    }
    return 0;
}






