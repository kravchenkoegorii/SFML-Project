#include "Triangle.h"

Triangle::Triangle(float size, sf::Color color) {
	default_color = color;
	triangle = new sf::CircleShape(size, 3);
	set_color(color);
}

Triangle::~Triangle() {
	delete triangle;
}

void Triangle::hide() {
	visible = false;
}

void Triangle::show() {
	visible = true;
}

sf::FloatRect Triangle::get_global_bounds() {
	return triangle->getGlobalBounds();
}

void Triangle::set_scale(float x_scale, float y_scale) {
	triangle->setScale(x_scale, y_scale);
}

sf::Vector2f Triangle::get_scale() {
	return triangle->getScale();
}

bool Triangle::check_intersection(Figure* another_figure) {
	bool result = triangle->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		triangle->setFillColor(another_figure->get_color());

	return result;
}

bool Triangle::check_intersection(float x, float y) {
	return triangle->getGlobalBounds().contains(x, y);
}

bool Triangle::check_window_collision(sf::RenderWindow& window) {
	if ((triangle->getPosition().x < 0 || triangle->getPosition().x > window.getSize().x - triangle->getGlobalBounds().width)
		|| (triangle->getPosition().y < 0 || triangle->getPosition().y > window.getSize().y - triangle->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Triangle::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*triangle);
};

void Triangle::move(float x, float y) {
	triangle->move(x, y);
}

void Triangle::set_outline(float thickness, sf::Color color) {
	triangle->setOutlineThickness(thickness);
	triangle->setOutlineColor(color);
}

void Triangle::set_color(sf::Color color) {
	triangle->setFillColor(color);
}

sf::Color Triangle::get_color() {
	return triangle->getFillColor();
}

sf::Vector2f Triangle::get_position() {
	return triangle->getPosition();
}

void Triangle::set_position(float x, float y) {
	triangle->setPosition(x, y);
}

void Triangle::reset() {
	triangle->setFillColor(default_color);
	triangle->setScale(1,1);
}

string Triangle::get_string() {
	return "Triangle";
}