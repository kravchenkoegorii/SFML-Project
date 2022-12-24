#include "Rectangle.h"

Rectangle::Rectangle(float length, float width, sf::Color color) {
	default_color = color;
	rectangle = new sf::RectangleShape(sf::Vector2f(length, width));
	set_color(color);
}

Rectangle::~Rectangle() {
	delete rectangle;
}

void Rectangle::hide() {
	visible = false;
}

void Rectangle::show() {
	visible = true;
}

sf::FloatRect Rectangle::get_global_bounds() {
	return rectangle->getGlobalBounds();
}

void Rectangle::set_scale(float x_scale, float y_scale) {
	rectangle->setScale(x_scale, y_scale);
}

sf::Vector2f Rectangle::get_scale() {
	return rectangle->getScale();
}

bool Rectangle::check_intersection(Figure* another_figure) {
	bool result = rectangle->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		rectangle->setFillColor(another_figure->get_color());

	return result;
}

bool Rectangle::check_intersection(float x, float y) {
	return rectangle->getGlobalBounds().contains(x, y);
}

bool Rectangle::check_window_collision(sf::RenderWindow& window) {
	if ((rectangle->getPosition().x < 0 || rectangle->getPosition().x > window.getSize().x - rectangle->getGlobalBounds().width)
		|| (rectangle->getPosition().y < 0 || rectangle->getPosition().y > window.getSize().y - rectangle->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Rectangle::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*rectangle);
};

void Rectangle::move(float x, float y) {
	rectangle->move(x, y);
}

void Rectangle::set_outline(float thickness, sf::Color color) {
	rectangle->setOutlineThickness(thickness);
	rectangle->setOutlineColor(color);
}

void Rectangle::set_color(sf::Color color) {
	rectangle->setFillColor(color);
}

sf::Color Rectangle::get_color() {
	return rectangle->getFillColor();
}

sf::Vector2f Rectangle::get_position() {
	return rectangle->getPosition();
}

void Rectangle::set_position(float x, float y) {
	rectangle->setPosition(x, y);
}

void Rectangle::reset() {
	rectangle->setFillColor(default_color);
	rectangle->setScale(1, 1);
}

string Rectangle::get_string() {
	return "Rectangle";
}