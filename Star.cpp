#include "Star.h"

Star::Star(sf::Color color) {
	default_color = color;
	star = new sf::ConvexShape(10);
	star->setPoint(0, sf::Vector2f(60, 0));
	star->setPoint(1, sf::Vector2f(72, 40));
	star->setPoint(2, sf::Vector2f(110, 40));
	star->setPoint(3, sf::Vector2f(80, 60));
	star->setPoint(4, sf::Vector2f(100, 100));
	star->setPoint(5, sf::Vector2f(60, 70));
	star->setPoint(6, sf::Vector2f(20, 100));
	star->setPoint(7, sf::Vector2f(40, 60));
	star->setPoint(8, sf::Vector2f(10, 40));
	star->setPoint(9, sf::Vector2f(48, 40));
	set_color(color);
}

Star::~Star() {
	delete star;
}

void Star::hide() {
	visible = false;
}

void Star::show() {
	visible = true;
}

sf::FloatRect Star::get_global_bounds() {
	return star->getGlobalBounds();
}

void Star::set_scale(float x_scale, float y_scale) {
	star->setScale(x_scale, y_scale);
}

sf::Vector2f Star::get_scale() {
	return star->getScale();
}

bool Star::check_intersection(Figure* another_figure) {
	bool result = star->getGlobalBounds().intersects(another_figure->get_global_bounds());
	if (result)
		star->setFillColor(another_figure->get_color());

	return result;
}

bool Star::check_intersection(float x, float y) {
	return star->getGlobalBounds().contains(x, y);
}

bool Star::check_window_collision(sf::RenderWindow& window) {
	if ((star->getPosition().x < 0 || star->getPosition().x > window.getSize().x - star->getGlobalBounds().width)
		|| (star->getPosition().y < 0 || star->getPosition().y > window.getSize().y - star->getGlobalBounds().height))
	{
		return true;
	}

	return false;
}

void Star::draw(sf::RenderWindow& window) {
	if (is_visible())
		window.draw(*star);
};

void Star::move(float x, float y) {
	star->move(x, y);
}

void Star::set_outline(float thickness, sf::Color color) {
	star->setOutlineThickness(thickness);
	star->setOutlineColor(color);
}

void Star::set_color(sf::Color color) {
	star->setFillColor(color);
}

sf::Color Star::get_color() {
	return star->getFillColor();
}

sf::Vector2f Star::get_position() {
	return star->getPosition();
}

void Star::set_position(float x, float y) {
	star->setPosition(x, y);
}

void Star::reset() {
	star->setFillColor(default_color);
	star->setScale(1, 1);
}

string Star::get_string() {
	return "Star";
}
