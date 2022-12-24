#pragma once
#include "Figure.h"
class Square : public Figure
{
	float default_side;
	sf::Color default_color;
	sf::RectangleShape* square;
public:
	Square(float side, sf::Color color);
	~Square();
	void hide();
	void show();
	sf::FloatRect get_global_bounds();
	void set_scale(float x_scale, float y_scale);
	sf::Vector2f get_scale();
	bool check_intersection(Figure* another_figure);
	bool check_intersection(float x, float y);
	bool check_window_collision(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void set_position(float x, float y);
	void set_outline(float thickness, sf::Color color);
	void set_color(sf::Color color);
	sf::Color get_color();
	sf::Vector2f get_position();
	void reset();
	string get_string();
};

