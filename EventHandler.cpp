#include "EventHandler.h"
using namespace std;
#include <iostream>

EventHandler::EventHandler(sf::Clock& _time, sf::Text& _label, sf::Text& _status, sf::Sprite& _f1,  sf::Font& font) {
	trail.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	time = _time;
	label = _label;
	status = _status;
	font.loadFromFile("Resources\\ICTV-Bold.ttf");
	label.setFont(font);
	label.setCharacterSize(25);
	label.setFillColor(sf::Color::White);
	status.setFont(font);
	status.setCharacterSize(15);
	status.setFillColor(sf::Color::White);
	f1 = _f1;
	is_menu_enabled = false;
	is_figure_grabbed = false;
	is_auto_move = false;
	is_aggregation_enabled = false;
}

EventHandler::~EventHandler() {
	controller.clear();
	trail.clear();
}

void EventHandler::action_event(sf::Event& event, sf::RenderWindow& window) {
	if (!active_figure_exists())
		return;

	Figure* active_figure = controller.get_active_figure();

	if (active_figure->check_window_collision(window)) {
		is_auto_move = false;
		status.setString(controller.get_active_figure()->get_string() + " stopped moving");
	}

	if (!is_aggregation_enabled) {
		if (controller.action_intersections_with_figure(active_figure))
		status.setString(active_figure->get_string() + " changed color");
	}
		
}

void EventHandler::ui_event(sf::Event& event, sf::RenderWindow& window) {
	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	
	
	switch (event.type) {
	case sf::Event::MouseWheelMoved:
		mousewheel_event(event, window);
		break;
	case sf::Event::KeyPressed:
		window.setMouseCursor(cursor);
		keyboard_event(window);
		break;
	case sf::Event::MouseMoved:
		mousemoved_event(window);
		break;
	default:
		break;
	}	
	
}

void EventHandler::keyboard_event(sf::RenderWindow& window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
		is_menu_enabled = !is_menu_enabled;
		

	Figure* temp = nullptr;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		temp = new Circle(15, get_random_color());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		temp = new Line(70, 5, get_random_color());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		temp = new Rectangle(20, 10, get_random_color());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		temp = new Square(20, get_random_color());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		temp = new Star(get_random_color());
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		temp = new Triangle(20, get_random_color());
	
	if (temp) {
		controller.add_figure(temp);
		status.setString("Created " + temp->get_string());
	}
	

	if (!active_figure_exists())
		return;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		controller.set_previous_figure_active();
		status.setString("Selected " + controller.get_active_figure()->get_string());
	}	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		controller.set_next_figure_active();
		status.setString("Selected " + controller.get_active_figure()->get_string());
	}	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		controller.get_active_figure()->reset();
		status.setString("Reseted " + controller.get_active_figure()->get_string());
	}	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		controller.get_active_figure()->set_trail_movement(
			!(controller.get_active_figure()->get_trail_movement() == true));
		string res = controller.get_active_figure()->get_trail_movement() ? "enabled" : "disabled";
		status.setString("Trail " + res);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		controller.get_active_figure()->set_color(get_random_color());
		status.setString(controller.get_active_figure()->get_string() + " color changed");
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		if (controller.get_active_figure()->is_visible()) {
			controller.get_active_figure()->hide();
			status.setString(controller.get_active_figure()->get_string() + " hidden");
		}
		else {
			controller.get_active_figure()->show();
			status.setString(controller.get_active_figure()->get_string() + " shown");
		}
			
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		is_auto_move = !(is_auto_move);
		string res = is_auto_move ? " moved auto" : " stopped moving";
		status.setString(controller.get_active_figure()->get_string() + res);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) {
		if (!is_aggregation_enabled) {
			is_aggregation_enabled = true;
			controller.add_composite(new Composite(controller.get_active_figure()));
			status.setString("Composite created");
		}
		else if (is_aggregation_enabled && controller.get_active_figure() != controller.get_composite()) {
			controller.get_composite()->add(controller.get_active_figure());
			controller.set_active_figure(controller.get_composite());
			status.setString("Added " + controller.get_active_figure()->get_string() + " to Composite");
		}
		else {
			is_aggregation_enabled = false;
			controller.set_composite(nullptr);
			status.setString("Composite saved");
			//controller.set_next_figure_active();
		}

	}
		
	
}

void EventHandler::mousewheel_event(sf::Event& event, sf::RenderWindow& window) {
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
		active_figure_exists()) 
	{
		sf::Cursor cursor;
		cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
		window.setMouseCursor(cursor);
		Figure* figure = controller.get_active_figure();
		figure->set_scale(figure->get_scale().x + event.mouseWheel.delta,
			figure->get_scale().y + event.mouseWheel.delta);

		
		status.setString("Scaled " + controller.get_active_figure()->get_string());
	}

	
}

void EventHandler::mousemoved_event(sf::RenderWindow& window) {
	if (!active_figure_exists())
		return;

	float x = (float)sf::Mouse::getPosition(window).x;
	float y = (float)sf::Mouse::getPosition(window).y;
	sf::Cursor cursor;
	
	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_figure_grabbed) ||
		(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
			controller.get_active_figure()->check_intersection(x, y)))
	{
		is_figure_grabbed = true;
		controller.get_active_figure()->set_position(x - controller.get_active_figure()->get_global_bounds().width / 2 , 
			y - controller.get_active_figure()->get_global_bounds().height / 2);
		status.setString("Grabbed " + controller.get_active_figure()->get_string());
		
		cursor.loadFromSystem(sf::Cursor::Hand);
		window.setMouseCursor(cursor);
	}
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow);
		is_figure_grabbed = false;
	}
	window.setMouseCursor(cursor);
		
	
		
}

void EventHandler::poll_event(sf::Event& event, sf::RenderWindow& window) {
	if (event.type == sf::Event::Closed)
		return window.close();

	ui_event(event, window);
}

void EventHandler::draw_event(sf::RenderWindow& window) {
	window.clear(sf::Color(66, 112, 63));
	//window.clear(sf::Color(9, 143, 192));
	//window.clear(sf::Color(2, 119, 178));
	label.setPosition((window.getSize().x - label.getGlobalBounds().width) / 2.f, 5);
	status.setPosition(6, (float) window.getSize().y - 26);
	/*if (!is_menu_enabled)*/
		window.draw(label);
	window.draw(status);
	if (active_figure_exists()) {
		
		label.setString("<" + controller.get_active_figure()->get_string() + ">");
		if (controller.get_active_figure()->get_trail_movement()) {
			//controller.get_active_figure()->get_position()
			sf::FloatRect bounds = controller.get_active_figure()->get_global_bounds();
			trail.append(sf::Vertex(sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2)));
			window.draw(trail);
		}
		else
			trail.clear();
		if (is_auto_move) {
			controller.get_active_figure()->auto_move(window, time.getElapsedTime().asSeconds());
		}
		else
			time.restart();
		controller.get_active_figure()->draw(window);
		if (active_composite_exists()) {
			controller.get_composite()->show();
			controller.get_composite()->draw(window);
		}			
	}
	else {
		label.setString("<Selected figure>");
	}

	if (is_menu_enabled)
		window.draw(f1);

	window.display();

	
	
}

bool EventHandler::active_figure_exists() {
	return (controller.get_active_figure() != nullptr);
}

bool EventHandler::active_composite_exists() {
	return (controller.get_composite() != nullptr);
}

sf::Color EventHandler::get_random_color() {
	return sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
}
