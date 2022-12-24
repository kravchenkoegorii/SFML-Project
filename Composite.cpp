#include "Composite.h"
using namespace std;
#include <iostream>

Composite::Composite(Figure* figure) {
	figures_count = 1;
    figures = new Figure * [figures_count];
	figures[figures_count-1] = figure;
	default_color = figure->get_color();
}

Composite::~Composite() {
    while(figures_count > 0)
    {
        remove(figures[0]);
    }
    delete[] figures;
}

void Composite::add(Figure* figure) {
    if (get_figure_index(figure) >= 0)
        return;
    Figure** new_figures = new Figure* [figures_count + 1];
    for (int i = 0; i < figures_count; i++) {
        new_figures[i] = figures[i];
        figures[i] = nullptr;
        delete figures[i];
    }
    new_figures[figures_count++] = figure;

    delete[] figures;
    figures = new_figures;
}

void Composite::remove(Figure* figure) {
    int figure_index = get_figure_index(figure);
    if (figure_index < 0)
        return;

    int added_count = 0;
    Figure** new_figures = new Figure* [figures_count - 1];
    for (int i = 0; i < figures_count; i++) {
        if (i != figure_index) {
            new_figures[added_count++] = figures[i];
        }
        
        figures[i] = nullptr;
        delete figures[i];
    }
    delete[] figures;
    figures = new_figures;

    figures_count--;
}

int Composite::get_figure_index(Figure* figure){
    for (int i = 0; i < figures_count; i++) {
        if (figure == figures[i])
            return i;
    }

    return -1;
}

void Composite::hide() {
    visible = false;
	for (int i = 0; i < figures_count; i++) {
		figures[i]->hide();
	}
}

void Composite::show() {
    visible = true;
	for (int i = 0; i < figures_count; i++) {
		figures[i]->show();
	}
}

sf::FloatRect Composite::get_global_bounds() {
    sf::FloatRect composite_bounds, figure_bounds;

    composite_bounds = (figures_count <= 0) ? composite_bounds : figures[0]->get_global_bounds();

    float right_up = composite_bounds.left + composite_bounds.width;
    float left_down = composite_bounds.top + composite_bounds.height;


    for (int i = 1; i < figures_count; i++)
    {
        figure_bounds = figures[i]->get_global_bounds();


        if (right_up < figure_bounds.left + figure_bounds.width)
        {
            right_up = figure_bounds.left + figure_bounds.width;
        }

        if (left_down < figure_bounds.top + figure_bounds.height)
        {
            left_down = figure_bounds.top + figure_bounds.height;
        }

        if (composite_bounds.left > figure_bounds.left)
        {
            composite_bounds.left = figure_bounds.left;
        }

        if (composite_bounds.top > figure_bounds.top)
        {
            composite_bounds.top = figure_bounds.top;
        }


    }
    composite_bounds.width = right_up - composite_bounds.left;
    composite_bounds.height = left_down - composite_bounds.top;


    return composite_bounds;
}

void Composite::set_scale(float x_scale, float y_scale) {
    for (int i = 0; i < figures_count; i++) {
        figures[i]->set_scale(x_scale, y_scale);
    }
}

sf::Vector2f Composite::get_scale() {
    return (figures_count <= 0) ? sf::Vector2f(0, 0) : figures[0]->get_scale();
}

bool Composite::check_intersection(Figure* another_figure) {
    if (get_figure_index(another_figure) >= 0)
        return false;

    bool result = false;
    for (int i = 0; i < figures_count; i++) {
        if (figures[i]->check_intersection(another_figure))
            result = true;
    }
    return result;
}                                                               

bool Composite::check_intersection(float x, float y) {
    for (int i = 0; i < figures_count; i++) {
        if (figures[i]->check_intersection(x, y))
            return true;
    }

    return get_global_bounds().contains(x, y);
}

bool Composite::check_window_collision(sf::RenderWindow& window) {
    for (int i = 0; i < figures_count; i++) {
        if (figures[i]->check_window_collision(window))
        {
            return true;
        }
    }
    
    return false;
}

void Composite::draw(sf::RenderWindow& window) {
    if (!is_visible())
        return;
    for (int i = 0; i < figures_count; i++) {
        figures[i]->show();
        //cout << figures[i]->get_string() << endl;
        figures[i]->draw(window);
    }
}

void Composite::move(float x, float y) {
    for (int i = 0; i < figures_count; i++) {
        figures[i]->move(x, y);
    }
}

void Composite::set_position(float x, float y) {
    move(x - get_position().x, y - get_position().y);
}

void Composite::set_outline(float thickness, sf::Color color) {
    for (int i = 0; i < figures_count; i++) {
        figures[i]->set_outline(thickness, color);
    }
}

void Composite::set_color(sf::Color color) {
    for (int i = 0; i < figures_count; i++) {
        figures[i]->set_color(color);
    }
}

sf::Color Composite::get_color() {
    return (figures_count <= 0) ? default_color : figures[0]->get_color();
}

sf::Vector2f Composite::get_position() {
    sf::FloatRect global_bounds = get_global_bounds();
    return sf::Vector2f(global_bounds.left + global_bounds.width / 2,
        global_bounds.top + global_bounds.height / 2);
}

void Composite::reset() {
    for (int i = 0; i < figures_count; i++) {
        figures[i]->reset();
    }
}

string Composite::get_string() {
    return "Composite";
}

