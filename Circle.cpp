#include "Circle.h"

Circle::Circle(float radius, sf::Color color){
	default_color = color;
	circle = new sf::CircleShape(radius);
	set_color(color);
}

Circle::~Circle() {
	delete circle;
}

void Circle::hide() {
	visible = false;
}

void Circle::show() {
	visible = true;
}

sf::FloatRect Circle::get_global_bounds() {
	return circle->getGlobalBounds();
}

void Circle::set_scale(float x_scale, float y_scale) {
	circle->setScale(x_scale, y_scale);
}

sf::Vector2f Circle::get_scale() {
	return circle->getScale();
}

bool Circle::check_intersection(Figure* another_figure) {
	bool result = circle->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		circle->setFillColor(another_figure->get_color());

	return result;
}

bool Circle::check_intersection(float x, float y) {
	return circle->getGlobalBounds().contains(x, y);
}

bool Circle::check_window_collision(sf::RenderWindow& window) {
	if ((circle->getPosition().x < 0 || circle->getPosition().x > window.getSize().x - circle->getGlobalBounds().width)
		|| (circle->getPosition().y < 0 || circle->getPosition().y > window.getSize().y - circle->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Circle::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*circle);
};

void Circle::move(float x, float y) {
	circle->move(x, y);
}

void Circle::set_outline(float thickness, sf::Color color) {
	circle->setOutlineThickness(thickness);
	circle->setOutlineColor(color);
}

void Circle::set_color(sf::Color color) {
	circle->setFillColor(color);
}

sf::Color Circle::get_color() {
	return circle->getFillColor();
}

sf::Vector2f Circle::get_position() {
	return circle->getPosition();
}

void Circle::set_position(float x, float y) {
	circle->setPosition(x, y);
}

void Circle::reset() {
	circle->setFillColor(default_color);
	circle->setScale(1,1);
}

string Circle::get_string() {
	return "Circle";
}