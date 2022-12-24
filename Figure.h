#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Figure
{
protected:
	bool trail_movement;
	bool visible;
public:
	virtual ~Figure() {};
	void set_trail_movement(bool);
	bool get_trail_movement();
	bool is_visible();
	virtual void hide() = 0;
	virtual void show() = 0;
	virtual sf::FloatRect get_global_bounds() = 0;
	virtual sf::Vector2f get_position() = 0;
	virtual void set_scale(float, float) = 0;
	virtual sf::Vector2f get_scale() = 0;
	virtual bool check_intersection(Figure*) = 0;
	virtual bool check_intersection(float, float) = 0;
	virtual bool check_window_collision(sf::RenderWindow&) = 0;
	void auto_move(sf::RenderWindow&, float);
	virtual void draw(sf::RenderWindow&) = 0;
	virtual void move(float, float) = 0;
	virtual void set_position(float, float) = 0;
	virtual void set_outline(float, sf::Color) = 0;
	virtual void set_color(sf::Color) = 0;
	virtual sf::Color get_color() = 0;
	virtual void reset() = 0;
	virtual string get_string() = 0;
};

