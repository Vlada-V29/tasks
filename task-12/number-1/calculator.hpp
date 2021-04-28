#pragma once

#include <complex>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

class Calculator
{
public:

    using field_t = std::vector < std::vector < std::size_t > > ;

public:

    explicit Calculator(
		const std::size_t width, const std::size_t height, const std::size_t max_iterations) :
		m_width(width), m_height(height), m_max_iterations(max_iterations)
	{
		initialize();
	}

	~Calculator() noexcept = default;

private:

	void initialize();

public:

    const auto & field() const noexcept 
	{ 
		return m_field; 
	}

	const auto width () const noexcept 
	{ 
		return m_width;  
	}

	const auto height() const noexcept 
	{ 
		return m_height; 
	}

	const auto max_iterations() const noexcept 
	{ 
		return m_max_iterations; 
	}

public:

	void calculate(const sf::Vector2f center, const float width, const float height);
	// void set_const(std::complex < float >c);

private:

	std::size_t m_width;
	std::size_t m_height;

    std::size_t m_max_iterations;

	field_t m_field;

	std::complex < float > const_c = std::complex < float >(0.7885f * std::cos(3 * M_PI / 4), 0.7885f * std::sin(3 * M_PI / 4));//0.7885f * cos(3 * M_PI / 4), 0.7885f * sin(3 * M_PI / 4)

};