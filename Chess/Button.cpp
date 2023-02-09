#include "Button.h"
#include <cmath>

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(this->shape);
    target.draw(this->text);
}

Button::Button( int function(int&, int&), sf::Color if_pressed, sf::Color normal, float x, float y,  float size_y, float size_x, sf::Text text)
{
   
    this->function = function;
    this->if_pressed = if_pressed;
    this->normal = normal;
    this->x = x;
    this->y = y;
    this->size_x = size_x;
    this->size_y = size_y;
    this->text = text;
    
    this->text.setFillColor(sf::Color(56, 56, 56, 240));
    float tmp = text.getGlobalBounds().height;
    float tmp2 = text.getGlobalBounds().width;
    float scale = std::min(size_y / tmp  , size_x / tmp2);
    this->text.scale(scale/1.5,scale/1.5);
    this->text.setOrigin(text.getGlobalBounds().width / 2-5, text.getGlobalBounds().height / 2 + 10);
    this->text.setPosition(x, y);
    shape.setSize(sf::Vector2f(size_x, size_y));
    shape.setOrigin(size_x / 2 , (size_y / 2) );
    shape.setPosition(x, y);
    shape.setFillColor(normal);
    this->scale = scale;
}

int Button::press(int& level, int& color)
{
    shape.setFillColor(if_pressed);
    pressed = 1;
    return (function)(level,color);
}

void Button::resize(float size)
{
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(size_y*scale/size, size_x * scale / size));
}
void Button::release()
{
    pressed = 0;
    shape.setFillColor(normal);
}
sf::RectangleShape Button::get_shape()
{
    return this->shape;
}