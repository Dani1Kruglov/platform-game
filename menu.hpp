

#ifndef HELLOSFML_MENU_HPP
#define HELLOSFML_MENU_HPP

#endif //HELLOSFML_MENU_HPP
#include <SFML/Graphics.hpp>

#pragma once
using namespace sf;

void menu(RenderWindow & window)
{
    Texture menuTexture1, menuTexture2, menuTexture3,aboutTexture, menuBackground, heroimage;
    menuTexture1.loadFromFile("1ur.png");
    menuTexture2.loadFromFile("progame.png");
    menuTexture3.loadFromFile("ex.png");
    aboutTexture.loadFromFile("outmenu.jpg");
    menuBackground.loadFromFile("gr.jpeg");
    heroimage.loadFromFile("back.png");
    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3),about(aboutTexture),  menuBg(menuBackground),heroim(heroimage);
    bool isMenu = 1;
    int menuNum = 0;
    heroim.setPosition(500,300);
    menu1.setPosition(25, 30);
    menu2.setPosition(24, 110);
    menu3.setPosition(28, 210);
    menuBg.setPosition(0, 0);



    while (isMenu)
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        menu1.setColor(Color::Black);
        menu2.setColor(Color::Black);
        menu3.setColor(Color::Black);
        menuNum = 0;
        window.clear(Color(192,192,192));

        if (IntRect(25, 30, 700, 120).contains(Mouse::getPosition(window)))
        {
            menu1.setColor(Color::Red);
            menuNum = 1;
        }
        if (IntRect(24, 110, 400, 110).contains(Mouse::getPosition(window)))
        {
            menu2.setColor(Color::Red);
            menuNum = 2;
        }
        if (IntRect(28, 210, 326, 98).contains(Mouse::getPosition(window)))
        {
            menu3.setColor(Color::Red);
            menuNum = 3;
        }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1)
                isMenu = false;//если нажали первую кнопку, то выходим из меню
            if (menuNum == 2)
            {
                window.draw(about);
                window.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            if (menuNum == 3)
            {
                window.close();
                isMenu = false;
            }

        }


        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(heroim);

        window.display();
    }
}