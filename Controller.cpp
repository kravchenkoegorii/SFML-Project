#include "Controller.h"

#include <iostream>

Controller::Controller() 
{
	figures_count = 0;
	figures = new Figure * [figures_count];
	current_figure = nullptr;
	current_composite = nullptr;
}

Controller::~Controller() {
	clear();
	current_figure = nullptr;
	delete current_figure;
	current_composite = nullptr;
	delete current_composite;	
}

void Controller::add_figure(Figure* figure) {
	if (contains(figure))
		return;
	Figure** new_figures = new Figure * [figures_count + 1];
	for (int i = 0; i < figures_count; i++) {
		new_figures[i] = figures[i];
		figures[i] = nullptr;
		delete figures[i];
	}
	new_figures[figures_count++] = figure;

	delete[] figures;
	figures = new_figures;
	set_active_figure(figure);
}

void Controller::remove_figure(Figure* figure) {
	int figure_index = get_figure_index(figure);
	if (figure_index < 0)
		return;

	if (current_figure == figure)
		set_next_figure_active();
	

	int added_count = 0;
	Figure** new_figures = new Figure * [figures_count - 1];
	for (int i = 0; i < figures_count; i++) {
		if (i == figure_index) {
			delete figures[i];
			continue;
		}

		new_figures[added_count++] = figures[i];
		//figures[i] = nullptr;
		//delete figures[i];
	}
	delete[] figures;
	figures = new_figures;

	figures_count--;
}

bool Controller::is_empty() {
	return figures_count == 0;
}

void Controller::clear() {
	while (!is_empty()) {
		remove_figure(figures[figures_count - 1]);
	}
}

bool Controller::contains(Figure* figure) {
	return get_figure_index(figure) != -1;
}

int Controller::get_figure_index(Figure* figure) {
	if (figure == nullptr)
		return -1;

	for (int i = 0; i < figures_count; i++) {
		if (figure == figures[i])
			return i;
	}

	return -1;
}

Figure* Controller::get_active_figure() {
	return current_figure;
}

void Controller::set_active_figure(int index) {
	if (is_empty())
		return;
	
	if (index < 0)
		index = figures_count - 1;
	else if (index >= figures_count)
		index = 0;

	if (current_figure != nullptr) {
		//current_figure->set_outline(0, sf::Color::White);
		current_figure->hide();
	}

	current_figure = figures[index];
	//current_figure->set_outline(3, sf::Color::White);
	current_figure->show();
}

void Controller::set_active_figure(Figure* figure) {
	set_active_figure(get_figure_index(figure));
}

void Controller::set_next_figure_active() {
	set_active_figure(get_figure_index(current_figure) + 1);
}

void Controller::set_previous_figure_active() {
	set_active_figure(get_figure_index(current_figure) - 1);
}

Composite* Controller::get_composite() {
	return current_composite;
}

void Controller::set_composite(Composite* composite) {
	current_composite = composite;
}

void Controller::add_composite(Composite* composite) {
	add_figure(composite);
	set_composite(composite);
	set_active_figure(composite);
}

void Controller::remove_composite() {
	remove_figure(current_composite);
	set_composite(nullptr);
	set_next_figure_active();
}

bool Controller::action_intersections_with_figure(Figure* figure) {
	bool result = true;
	for (int i = 0; i < figures_count; i++) {
		if (figures[i] != figure && figures[i]->get_string() != "Composite") {
			figure->check_intersection(figures[i]);
		}
			
	}
	return result;
}

