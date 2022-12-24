#pragma once
#include "Controller.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Star.h"
#include "Square.h"
#include "Composite.h"

class EventHandler
{
	Controller controller;
	sf::Clock time;
	sf::Text label;
	sf::Text status;
	sf::VertexArray trail;
	sf::Sprite f1;
	

	bool is_menu_enabled;
	bool is_figure_grabbed;
	bool is_auto_move;
	bool is_aggregation_enabled;
public:
	EventHandler(sf::Clock& _time, sf::Text& _label, sf::Text& _status, sf::Sprite& _f1, sf::Font& _font);
	~EventHandler();
	void poll_event(sf::Event& event, sf::RenderWindow& window);
	void action_event(sf::Event& event, sf::RenderWindow& window);
	
	// ui_events
	void ui_event(sf::Event& event, sf::RenderWindow& window);
	void keyboard_event(sf::RenderWindow& window);
	void mousewheel_event(sf::Event& event, sf::RenderWindow& window);
	void mousemoved_event(sf::RenderWindow& window);

	void draw_event(sf::RenderWindow& window);
	bool active_figure_exists();
	bool active_composite_exists();
	sf::Color get_random_color();
};

