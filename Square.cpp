#include "Square.h"

Square::Square(float side, sf::Color color) {
	default_side = side;
	default_color = color;
	square = new sf::RectangleShape(sf::Vector2f(side, side));
	set_color(color);
}

Square::~Square() {
	delete square;
}

void Square::hide() {
	visible = false;
}

void Square::show() {
	visible = true;
}

sf::FloatRect Square::get_global_bounds() {
	return square->getGlobalBounds();
}

void Square::set_scale(float x_scale, float y_scale) {
	square->setScale(x_scale, y_scale);
}

sf::Vector2f Square::get_scale() {
	return square->getScale();
}

bool Square::check_intersection(Figure* another_figure) {
	bool result = square->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		square->setFillColor(another_figure->get_color());

	return result;
}

bool Square::check_intersection(float x, float y) {
	return square->getGlobalBounds().contains(x, y);
}

bool Square::check_window_collision(sf::RenderWindow& window) {
	if ((square->getPosition().x < 0 || square->getPosition().x > window.getSize().x - square->getGlobalBounds().width)
		|| (square->getPosition().y < 0 || square->getPosition().y > window.getSize().y - square->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Square::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*square);
};

void Square::move(float x, float y) {
	square->move(x, y);
}

void Square::set_outline(float thickness, sf::Color color) {
	square->setOutlineThickness(thickness);
	square->setOutlineColor(color);
}

void Square::set_color(sf::Color color) {
	square->setFillColor(color);
}

sf::Color Square::get_color() {
	return square->getFillColor();
}

sf::Vector2f Square::get_position() {
	return square->getPosition();
}

void Square::set_position(float x, float y) {
	square->setPosition(x, y);
}

void Square::reset() {
	square->setScale(1, 1);
	square->setFillColor(default_color);
}

string Square::get_string() {
	return "Square";
}