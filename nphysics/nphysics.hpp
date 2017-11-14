/////////////////////////////////////////////////////////////////////////////////
//
// NEngine C++ Library
// Copyright (c) 2017-2017 Sebastian Netsch
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef __NENGINE__NPHYSICS__NPHYSICS__
#define __NENGINE__NPHYSICS__NPHYSICS__

/////////////////////////////////////////////////////////////////////////////////
// ! mutex for thread safety
// ! vector for storage
// ! memory for shared pointer
// ! algorithm for min and max
// ! limits for numerical limit
/////////////////////////////////////////////////////////////////////////////////
#include <mutex>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits>

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for the nengine
/////////////////////////////////////////////////////////////////////////////////
namespace nengine {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace for nphysics
/////////////////////////////////////////////////////////////////////////////////
namespace nphysics {

/////////////////////////////////////////////////////////////////////////////////
// ! namespace using for easier and cleaner programming
/////////////////////////////////////////////////////////////////////////////////
using namespace nengine;
using namespace nengine::nphysics;

/////////////////////////////////////////////////////////////////////////////////
// ! the npolygon
/////////////////////////////////////////////////////////////////////////////////
class npolygon : public sf::Drawable
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		npolygon(const npolygon&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		npolygon& operator=(const npolygon&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		// @param1: a vector of points that resemble the npolygon
		// @param2: the SFML color the npolygon should have
		// @param3: the starting position
		/////////////////////////////////////////////////////////////////////////////////
		npolygon(std::vector<sf::Vector2f> const& points, sf::Color const& color, sf::Vector2f const& position)
			: _mutex()
			, _texture()
			, _convex()
			, _centroid()
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(points.size() <= 0)
				{
					return;
				}

				if(_is_convex(points))
				{
					_create_convex(points);
				}

				// set color
				_convex.setFillColor(color);

				// set position
				_convex.setPosition(position);
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		// @param1: a vector of points that resemble the npolygon
		// @param2: the SFML texture as a shared pointer the npolygon should have
		// @param3: the starting position
		/////////////////////////////////////////////////////////////////////////////////
		npolygon(std::vector<sf::Vector2f> const& points, std::shared_ptr<const sf::Texture> texture, sf::Vector2f const& position)
			: _mutex()
			, _texture(std::move(texture))
			, _convex()
			, _centroid()
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				if(points.size() <= 0)
				{
					return;
				}

				if(_is_convex(points))
				{
					_create_convex(points);
				}

				// set texture
				_convex.setTexture(_texture.get());

				// set position
				_convex.setPosition(position);
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to set the position of the npolygon
		// @param1: the new position
		/////////////////////////////////////////////////////////////////////////////////
		auto set_position(sf::Vector2f const& position) -> void
		{
			_convex.setPosition(position);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get the position of the npolygon
		// @return: the position
		/////////////////////////////////////////////////////////////////////////////////
		auto get_position() const -> sf::Vector2f
		{
			return _convex.getPosition();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to set the color of the npolygon
		// @param1: the new color
		/////////////////////////////////////////////////////////////////////////////////
		auto set_color(sf::Color const& color) -> void
		{
			_convex.setFillColor(color);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get the color of the npolygon
		// @return: the color
		/////////////////////////////////////////////////////////////////////////////////
		auto get_color() -> sf::Color
		{
			return _convex.getFillColor();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get the axes corssing through the npolygon (perpendicular)
		// @return: the perpendicular axes of the npolygon
		/////////////////////////////////////////////////////////////////////////////////
		auto get_axes() const -> std::vector<sf::Vector2f>
		{
			// storage vector
			std::vector<sf::Vector2f> tmp;

			// get points
			auto points = get_points();

			// calculate axes
			for(unsigned int i = 0; i < points.size(); i++)
			{
				// calculate the edge between each point and its direct neighbour
				sf::Vector2f edge;
				edge.x = points.at((i + 1) % points.size()).x - points.at(i).x;
				edge.y = points.at((i + 1) % points.size()).y - points.at(i).y;

				// get length of edge
				double length = sqrt((edge.x * edge.x) + (edge.y * edge.y));

				// normalize (break down length to 1)
				edge.x /= length;
				edge.y /= length;

				// push the perpendicular vector to edge into the axes vector as it is the axis
				tmp.push_back(sf::Vector2f(-edge.y, edge.x));
			}

			return tmp;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get all points that resemble a npolygon
		// @return: a vector of points
		/////////////////////////////////////////////////////////////////////////////////
		auto get_points() const -> const std::vector<sf::Vector2f>
		{
			// storage vector
			std::vector<sf::Vector2f> tmp;

			// find out change in position from original location to return the actual position
			sf::Vector2f change(get_position().x - _centroid.x, get_position().y - _centroid.y);

			for(int i = 0; i < _convex.getPointCount(); i++)
			{
				// get points position and adjust due to change from original position
				sf::Vector2f current = _convex.getPoint(i);
				current.x += change.x;
				current.y += change.y;
				tmp.push_back(current);
			}

			return tmp;
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get the perpedicular axes as drawables
		// @return: a vector of lines that resemble the npolygons perpendicular axes
		//          as drawables
		/////////////////////////////////////////////////////////////////////////////////
		auto _get_drawable_axes() const -> const std::vector<sf::VertexArray>
		{
			// length of axes
			const int axes_length = 200;

			// get axes
			auto axes = get_axes();

			// x and y for each axis, individual length and angle
			double x;
			double y;
			double length;
			double angle;

			// store line information
			std::vector<sf::VertexArray> lines;

			for(unsigned int i = 0; i < axes.size(); i++)
			{
				// single line
				sf::VertexArray line(sf::Lines, 2);
				line[0].color = sf::Color::Black;
				line[1].color = sf::Color::Black;

				// get the angle of the axis
				angle = atan(axes.at(i).y / axes.at(i).x);

				// calculate x and y with half lenghts
				x = cos(angle) * axes_length / 2;
				y = sin(angle) * axes_length / 2;


				// set position of the endpoints of the axis
				line[0].position = sf::Vector2f(get_position().x - x, get_position().y - y);
				line[1].position = sf::Vector2f(get_position().x + x, get_position().y + y);

				// store line
				lines.push_back(line);
			}

			// return drawable lines
			return lines;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to test if a shape is a convex shape and not concave
		// @param1: a vector of points that resemble a npolygon
		// @return: indicator if the shape is a convex polygon
		/////////////////////////////////////////////////////////////////////////////////
		auto _is_convex(std::vector<sf::Vector2f> const& points) -> bool
		{
			 // dots or lines are convex shapes
			if(points.size() < 3)
			{
				return true;
			}

			// lengths between points i, i + 1 and i + 2 on x and y axes
			sf::Vector2f distance_1;
			sf::Vector2f distance_2;
			float area;

			// get sign of compare for the first three points as a base for the rest of the comparisons
			distance_1.x = points.at(1).x - points.at(0).x;
			distance_1.y = points.at(1).y - points.at(0).y;
			distance_2.x = points.at(2).x - points.at(1).x;
			distance_2.y = points.at(2).y - points.at(1).y;
			area = distance_1.x * distance_2.y - distance_2.x * distance_1.y;

			// sign to compare the base area of the shape, false = positive, true = negative
			bool base_area_flag;
			if(area < 0)
			{
				base_area_flag = true;
			}
			else
			{
				base_area_flag = false;
			}

			// check area of the rest of the distances between points and compare to the base area
			for(unsigned int i = 0; i < points.size(); i++)
			{
				distance_1.x = points.at((i + 1) % points.size()).x - points.at(i).x;
				distance_1.y = points.at((i + 1) % points.size()).y - points.at(i).y;
				distance_2.x = points.at((i + 2) % points.size()).x - points.at((i + 1) % points.size()).x;
				distance_2.y = points.at((i + 2) % points.size()).y - points.at((i + 1) % points.size()).y;
				area = distance_1.x * distance_2.y - distance_2.x * distance_1.y;

				// if any of the computed areas has the opposite boolean value of the base area shape the shape is concave
				if((area < 0 && !base_area_flag) || (area > 0 && base_area_flag))
				{
					return false;
				}
			}

			// shape is convex
			return true;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to create a SFML ConvexShape
		// @param1: a vector of points that resemble a npolygon
		/////////////////////////////////////////////////////////////////////////////////
		auto _create_convex(std::vector<sf::Vector2f> const& points) -> void
		{
			// set number of points
			_convex.setPointCount(points.size());

			// set points
			for(unsigned int i = 0; i < points.size(); i++)
			{
				_convex.setPoint(i, points.at(i));
			}

			// set centroid
			_calculate_centroid();
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to calculate the original centroid position
		/////////////////////////////////////////////////////////////////////////////////
		auto _calculate_centroid() -> void
		{
			// to calculate central x and y coordinates
			// following the calculations for the centroid of a polygon (just wikipedia-search it)
			// --> the centroid of a non-self-intersecting closed polygon defined by n vertices(x0, y0), (x1, y1), ... (xn-1, yn-1) is the point c(cx,cy)
			auto points = get_points();

			//index for next i
			int index = 0;

			// area
			double area = 0;

			// get area for central x and y computation
			for(unsigned int i = 0; i < points.size(); i++)
			{
				// to not get a index out of bounds --> equivalent to [index = i; if(index > points.size()) --> index = 0]
				index = (i + 1) % points.size();

				// following the calculations for the centroid of a polygon (just wikipedia-search it)
				// get the mathematical sum for the area of a polygon
				area += points.at(i).x * points.at(index).y - points.at(i).y * points.at(index).x;
			}

			// following the calculations for the centroid of a polygon (just wikipedia-search it)
			area /= 2;

			// following the calculations for the centroid of a polygon (just wikipedia-search it)
			// get the mathematical sum for centroid calculation
			for(unsigned int i = 0; i < points.size(); i++)
			{
				// to not get a index out of bounds --> equivalent to [index = i; if(index > points.size()) --> index = 0]
				index = (i + 1) % points.size();

				// following the calculations for the centroid of a polygon (just wikipedia-search it)
				_centroid.x += ((points.at(i).x + points.at(index).x) * ((points.at(i).x * points.at(index).y) - (points.at(index).x * points.at(i).y)));
				_centroid.y += ((points.at(i).y + points.at(index).y) * ((points.at(i).x * points.at(index).y) - (points.at(index).x * points.at(i).y)));
			}

			// following the calculations for the centroid of a polygon (just wikipedia-search it)
			_centroid.x /= (6 * area);
			_centroid.y /= (6 * area);

			_convex.setOrigin(_centroid);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the SFML ConvexShape
		/////////////////////////////////////////////////////////////////////////////////
		sf::ConvexShape _convex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! a shared pointer to the ConvexShapes texture
		/////////////////////////////////////////////////////////////////////////////////
		std::shared_ptr<const sf::Texture> _texture;
		/////////////////////////////////////////////////////////////////////////////////
		// ! the central starting point of the convex shape at it's creation
		/////////////////////////////////////////////////////////////////////////////////
		sf::Vector2f _centroid;
		/////////////////////////////////////////////////////////////////////////////////
		// ! virtual draw function
		/////////////////////////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			target.draw(_convex, states);

			// set this value to true to draw all perpendicular axes of the polygon
			bool debug = false;
			if(debug)
			{
				auto axes = _get_drawable_axes();
				for(unsigned int i = 0; i < axes.size(); i++)
				{
					target.draw(axes.at(i), states);
				}
			}
		}
}; // end of class npolygon

/////////////////////////////////////////////////////////////////////////////////
// ! the ncollision_manager
/////////////////////////////////////////////////////////////////////////////////
class ncollision_manager
{
	public:
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete default constructor
		/////////////////////////////////////////////////////////////////////////////////
		ncollision_manager(const ncollision_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! delete copy constructor
		/////////////////////////////////////////////////////////////////////////////////
		ncollision_manager& operator=(const ncollision_manager&) = delete;
		/////////////////////////////////////////////////////////////////////////////////
		// ! custom constructor: with initialization list
		/////////////////////////////////////////////////////////////////////////////////
		ncollision_manager()
			: _mutex()
		{
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! checks if two SFML Sprites are colliding with offset
		// @param1: the first Sprite to be tested
		// @param2: the second Sprite to be tested
		// @param3: the offset with which the objects should be pushed away
		//          from each other
		// @return: the minimum translation vector for moving one of the Sprites away
		/////////////////////////////////////////////////////////////////////////////////
		auto check(sf::Sprite const &sprite1, sf::Sprite const &sprite2, double offset) -> sf::Vector2f
		{
			return check(sprite1.getGlobalBounds(), sprite2.getGlobalBounds(), offset);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! checks if two SFML Sprites are colliding
		// @param1: the first Sprite to be tested
		// @param2: the second Sprite to be tested
		// @return: the minimum translation vector for moving one of the Sprites away
		/////////////////////////////////////////////////////////////////////////////////
		auto check(sf::Sprite const &sprite1, sf::Sprite const &sprite2) -> sf::Vector2f
		{
			return check(sprite1.getGlobalBounds(), sprite2.getGlobalBounds(), 1.0);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! checks if two SFML FloatingRectangles are colliding with offset
		// @param1: the first FloatingRectangle to be tested
		// @param2: the second FloatingRectangle to be tested
		// @param3: the offset with which the objects should be pushed away
		//          from each other
		// @return: the minimum translation vector for moving the one of the
		//          FloatRects away
		/////////////////////////////////////////////////////////////////////////////////
		auto check(sf::FloatRect const &rect1, sf::FloatRect const &rect2, double offset) -> sf::Vector2f
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				// declaration && initialization of minimum translation vector
				sf::Vector2f mtv;
				mtv.x = 0;
				mtv.y = 0;

				// declaration && initialization of projection
				sf::Vector2f proj;
				proj.x = 0;
				proj.y = 0;
				
				// declaration && initialization of overlap
				sf::Vector2f overlap;
				overlap.x = 0;
				overlap.y = 0;
				
				// get projection on x axis
				proj.x = std::max(rect1.left + rect1.width, rect2.left + rect2.width) - std::min(rect1.left, rect2.left); // takes most right point and most left point and calculates difference between
				
				// test if projection is smaller the width of both objects
				if(proj.x < rect1.width + rect2.width)
				{
					// get projection on y axis
					proj.y = std::max(rect1.top + rect1.height, rect2.top + rect2.height) - std::min(rect1.top, rect2.top); // takes most bottom point and most top point and calculates difference between
					
					// test if projection is smaller the height of both objects
					if(proj.y < rect1.height + rect2.height)
					{
						// calculate x overlap
						overlap.x = rect1.width + rect2.width - proj.x;
						
						// calculate y overlap
						overlap.y = rect1.height + rect2.height - proj.y;
						
						// decide which overlap is greater and alter out_mtv accordingly
						if(overlap.x < overlap.y)
						{
							// if rect1 is left of rect2 --> * -offset otherwise * offset
							mtv.x = overlap.x * (rect1.left < rect2.left ? -offset : offset);
						}
						else
						{
							// if rect1 is on top of rect2 --> * -offset otherwise * offset
							mtv.y = overlap.y * (rect1.top < rect2.top ? -offset : offset);
						}
					}
				}

				return mtv;
			} // lock freed
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! checks if two SFML FloatingRectangles are colliding
		// @param1: the first FloatingRectangle to be tested
		// @param2: the second FloatingRectangle to be tested
		// @return: the minimum translation vector for moving the one of the
		//          FloatRects away
		/////////////////////////////////////////////////////////////////////////////////
		auto check(sf::FloatRect const &rect1, sf::FloatRect const &rect2) -> sf::Vector2f
		{
			return check(rect1, rect2, 1.0);
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! checks if two NPolygon shapes are colliding
		// @param1: the first NPolygon to be tested
		// @param2: the second NPolygon to be tested
		// @param3: the offset with which the objects should be pushed away
		//          from each other
		// @return: the minimum translation vector for moving the !second! NPolygon away
		//          invert for moving the !first! away
		/////////////////////////////////////////////////////////////////////////////////
		auto check(npolygon const &poly1, npolygon const &poly2) -> sf::Vector2f
		{
			std::unique_lock<std::mutex> lock(_mutex);
			{ // locked area
				// declaration && initialization of minimum translation vector
				sf::Vector2f mtv;
				mtv.x = 0;
				mtv.y = 0;

				// if there are no points return empty
				if((poly1.get_points().size() < 1) || (poly2.get_points().size() < 1))
				{
					return mtv;
				}

				// minimum translation axis for calculating minimum translation vector
				sf::Vector2f mta;
				mta.x = 0;
				mta.y = 0;

				// minimum translation value, when combined with minimum translation axis you get the minimum translation vector
				double mtval = std::numeric_limits<double>::max();

				// generate the axes for poly1
				std::vector<sf::Vector2f> poly1_axes = poly1.get_axes();

				// after calculating the axes for poly1, the checking for overlaps begins
				for(unsigned int i = 0; i < poly1_axes.size(); i++)
				{
					// generate projection structs for each shape
					nprojection poly1_projection = _get_projection(poly1, poly1_axes.at(i));
					nprojection poly2_projection = _get_projection(poly2, poly1_axes.at(i));

					// after calculating the axes for poly2, the checking for overlaps begins
					if(!_overlap(poly1_projection, poly2_projection))
					{
						return mtv;
					}
					else
					{
						// get value of overlap
						double tmp = _calculate_overlap(poly1_projection, poly2_projection);

						// if it's less than it's previous change minimum translation axis and minimum translation value
						if(tmp < mtval)
						{
							mtval = tmp;
							mta = poly1_axes.at(i);
						}
					}
				}

				// generate the axes for poly2
				std::vector<sf::Vector2f> poly2_axes = poly2.get_axes();

				// after calculating the axes for poly2, the checking for overlaps begins
				for(unsigned int i = 0; i < poly2_axes.size(); i++)
				{
					// generate projection structs for each shape
					nprojection poly1_projection = _get_projection(poly1, poly2_axes.at(i));
					nprojection poly2_projection = _get_projection(poly2, poly2_axes.at(i));

					// after calculating the axes for poly2, the checking for overlaps begins
					if(!_overlap(poly1_projection, poly2_projection))
					{
						return mtv;
					}
					else
					{
						// get value of overlap
						double tmp = _calculate_overlap(poly1_projection, poly2_projection);

						// if it's less than it's previous change minimum translation axis and minimum translation value
						if(tmp < mtval)
						{
							mtval = tmp;
							mta = poly2_axes.at(i);
						}
					}
				}

				// at this point a overlap (--> collision) happened
				// calculate direction vector
				sf::Vector2f direction_vec = sf::Vector2f((poly2.get_position().x - poly1.get_position().x), (poly2.get_position().y - poly1.get_position().y));;

				// get minimum translation vector
				mtv = _calculate_mtv(mta, mtval, direction_vec);

				return mtv;
			} // lock freed
		}
	private:
		/////////////////////////////////////////////////////////////////////////////////
		// ! for thread safety
		/////////////////////////////////////////////////////////////////////////////////
		std::mutex _mutex;
		/////////////////////////////////////////////////////////////////////////////////
		// ! struct for npolygon projection
		/////////////////////////////////////////////////////////////////////////////////
		struct nprojection
		{
			float min;
			float max;
		};
		/////////////////////////////////////////////////////////////////////////////////
		// ! to get a projection
		// @param1: the npolygon to be projected
		// @param2: the axis the npolygon will be projected on
		// @return: a nprojection
		/////////////////////////////////////////////////////////////////////////////////
		auto _get_projection(npolygon const& poly, sf::Vector2f const& axis) -> nprojection
		{
			// get points
			auto points = poly.get_points();

			// storage nprojection
			nprojection tmp;

			// set min and max to the first point as base
			tmp.min = ((points.at(0).x * axis.x) + (points.at(0).y * axis.y));
			tmp.max = tmp.min;

			// get projection of each point and decide min and max
			for(unsigned int i = 1; i < points.size(); i++)
			{
				// get projection of a point
				float next_projection = ((points.at(i).x * axis.x) + (points.at(i).y * axis.y));

				// decide min and max
				if(next_projection < tmp.min)
				{
					tmp.min = next_projection;
				}
				else if(next_projection > tmp.max)
				{
					tmp.max = next_projection;
				}
			}

			return tmp;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to determine if projections overlap
		// @param1: the first nprojection
		// @param2: the second nprojection
		// @return: true if overlap, false if no overlap
		/////////////////////////////////////////////////////////////////////////////////
		inline auto _overlap(nprojection const& proj1, nprojection const& proj2) -> bool
		{
			// if there is a gap, then there is no overlap
			if((proj1.max <= proj2.min) || (proj2.max <= proj1.min))
			{
				return false;
			}

			return true;
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! calclulate overlap between two nprojections
		// @param1: the first nprojection
		// @param2: the second nprojection
		// @return: the overlap distance
		/////////////////////////////////////////////////////////////////////////////////
		inline auto _calculate_overlap(nprojection const& proj1, nprojection const& proj2) -> double
		{
			// returns the distance between the maximum point of two projections and the biggest of the minimum points of two projections
			return std::min(proj1.max, proj2.max) - std::max(proj1.min, proj2.min);
			//return std::max(0.f /* to not get negative values! */, std::min(proj1.max, proj2.max)) - std::max(proj1.min, proj2.min); // original --> didn't work here, the y displacement was too high!
		}
		/////////////////////////////////////////////////////////////////////////////////
		// ! to calculate the minimum translation vector
		// @param1: the axis on which the npolygon has to move away from
		//          --> perpendicular
		// @param2: the minimum translation value, says how far the npolygon has to
		//          be pushed back
		// @param3: the overlap move direction
		// @return: the minimum translation vector for pushing the npolygons away
		//          from each other
		/////////////////////////////////////////////////////////////////////////////////
		auto _calculate_mtv(sf::Vector2f const& axis, double magnitude, sf::Vector2f const& direction) -> sf::Vector2f
		{
			// calculate angle of the axis relative to the global axes
			double angle = atan(axis.y / axis.x);

			// calculate change along x and y axes
			sf::Vector2f tmp(cos(angle) * magnitude, sin(angle) * magnitude);

			// check to macke sure mtv is not pointing towards the npolygon
			if(tmp.x * direction.x + tmp.y * direction.y < 0)
			{
				tmp.x = -tmp.x;
				tmp.y = -tmp.y;
			}

			return tmp;
		}
}; // end of class ncollision_manager

} // end of namespace nphysics

} // end of namespace nengine

#endif // end of __NENGINE__NPHYSICS__NPHYSICS__
