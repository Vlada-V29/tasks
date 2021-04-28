#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "calculator.hpp"
#include "view.hpp"

class Visualizer
{
public:

	Visualizer() :
		m_window(sf::VideoMode(1000U, 1000U), "MANDELBROT VISUALIZER", sf::Style::Close),
		m_calculator(m_window.getSize().x, m_window.getSize().y, 100U), m_need_redraw(true),
		m_view(sf::Vector2f(0.0f, 0.0f), 6.0f, 6.0f / (m_calculator.width() / m_calculator.height()))
	{
		initialize();
	}

	~Visualizer() noexcept = default;

private:

	void initialize();

public:

    void run();

private:

    void review();
    void update();
    void render();

private:

    void handle_key_pressed(const sf::Keyboard::Key code) noexcept;

private:

    sf::RenderWindow m_window;
    sf::Image        m_image;
    sf::Sprite       m_sprite;
    sf::Texture      m_texture;
    sf::Font         m_font;
    sf::Text         m_text;

    // Calculator m_calculator = Calculator(float, float);
    Calculator m_calculator;
    // std::complex < float > const_c = std::complex < float >(0.7885f * std::cos(3 * M_PI / 4), 0.7885f * std::sin(3 * M_PI / 4));//0.7885f * cos(3 * M_PI / 4), 0.7885f * sin(3 * M_PI / 4)

	bool m_need_redraw;

    View m_view;

    std::vector < sf::Color > m_colors;
};