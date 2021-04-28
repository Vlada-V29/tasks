#pragma once

#include <SFML/Graphics.hpp>

class View
{
public:

	explicit View(const sf::Vector2f center, const float width, const float height) noexcept :
		m_center(center), m_width(width), m_height(height)
	{}

	~View() noexcept = default;

public:

	void move(const sf::Vector2f delta) noexcept
	{
		m_center += delta;
	}

	void scale(const float factor) noexcept
	{
		m_width  *= factor; 
		m_height *= factor;
	}

	const auto center() const noexcept 
	{
		return m_center; 
	}

	const auto width () const noexcept 
	{ 
		return m_width;  
	}

	const auto height() const noexcept 
	{ 
		return m_height; 
	}

private:

	sf::Vector2f m_center;

	float m_width;
	float m_height;
};