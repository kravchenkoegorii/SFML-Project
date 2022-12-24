#pragma once
#include "Figure.h"
class Circle : public Figure
{
	sf::Color default_color;
	sf::CircleShape* circle;
public:
	Circle(float radius, sf::Color color);
	~Circle();
	void hide();
	void show();
	sf::FloatRect get_global_bounds();
	void set_scale(float x_scale, float y_scale);
	sf::Vector2f get_scale();
	void rotate(float degrees);
	bool check_intersection(Figure* another_figure);
	bool check_intersection(float x, float y);
	bool check_window_collision(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void move(float x, float y);
	void set_position(float x, float y);
	void set_outline(float thickness, sf::Color color);
	void set_color(sf::Color color);
	sf::Vector2f get_position();
	void reset();
	sf::Color get_color();
	string get_string();
};

