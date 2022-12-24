#pragma once
#include "Figure.h"
#include "Composite.h"
class Controller
{
	int figures_count;
	Figure** figures;

	Figure* current_figure;
	Composite* current_composite;

public:
	Controller();
	~Controller();
	void add_figure(Figure* figure);
	void remove_figure(Figure* figure);
	bool contains(Figure* figure);
	int get_figure_index(Figure* figure);
	bool action_intersections_with_figure(Figure* figure);
	bool is_empty();
	void clear();
	
	Figure* get_active_figure();
	void set_active_figure(int index);
	void set_active_figure(Figure* figure);
	void set_next_figure_active();
	void set_previous_figure_active();
	
	Composite* get_composite();
	void set_composite(Composite* composite);
	void add_composite(Composite* composite);
	void remove_composite();
	
};

