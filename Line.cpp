#include "Line.h"

Line::Line(float length, float thickness, sf::Color color) {
	default_color = color;
	line = new sf::RectangleShape(sf::Vector2f(length, thickness));
	set_color(color);
}

Line::~Line() {
	delete line;
}

void Line::hide() {
	visible = false;
}

void Line::show() {
	visible = true;
}

sf::FloatRect Line::get_global_bounds() {
	return line->getGlobalBounds();
}

void Line::set_scale(float x_scale, float y_scale) {
	line->setScale(x_scale, y_scale);
}

sf::Vector2f Line::get_scale() {
	return line->getScale();
}

bool Line::check_intersection(Figure* another_figure) {
	bool result = line->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		line->setFillColor(another_figure->get_color());

	return result;
}

bool Line::check_intersection(float x, float y) {
	return line->getGlobalBounds().contains(x, y);
}

bool Line::check_window_collision(sf::RenderWindow& window) {
	if ((line->getPosition().x < 0 || line->getPosition().x > window.getSize().x - line->getGlobalBounds().width)
		|| (line->getPosition().y < 0 || line->getPosition().y > window.getSize().y - line->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Line::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*line);
};

void Line::move(float x, float y) {
	line->move(x, y);
}

void Line::set_outline(float thickness, sf::Color color) {
	line->setOutlineThickness(thickness);
	line->setOutlineColor(color);
}

void Line::set_color(sf::Color color) {
	line->setFillColor(color);
}

sf::Color Line::get_color() {
	return line->getFillColor();
}

sf::Vector2f Line::get_position() {
	return line->getPosition();
}

void Line::set_position(float x, float y) {
	line->setPosition(x, y);
}

void Line::reset() {
	line->setFillColor(default_color);
	line->setScale(1, 1);
}

string Line::get_string() {
	return "Line";
}