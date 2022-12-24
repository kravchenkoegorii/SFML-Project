#include "Figure.h"

void Figure::set_trail_movement(bool status) {
	trail_movement = status;
}

bool Figure::get_trail_movement() {
	return trail_movement;
}

bool Figure::is_visible() {
	return visible;
}

void Figure::auto_move(sf::RenderWindow& window, float elapsed_time) {
	move(1, sin(elapsed_time + 1));
}