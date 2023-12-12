#ifndef SHAPE_H
#define SHAPE_H

#include "Vec2.h"
#include <vector>

enum ShapeType {
	CIRCLE,
	POLYGON,
	BOX
};

struct Shape {
	virtual ~Shape() = default;
	virtual ShapeType GetType() const = 0;
	virtual Shape* Clone() const = 0;
	virtual float GetMomentOfInertia() const = 0;
};

struct CircleShape: public Shape {
	float radius;
	CircleShape(const float radius);
	~CircleShape();

	ShapeType GetType() const override;
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;
};
 
struct PolygonShape: public Shape {
	std::vector<Vec2> localVertices;
	std::vector<Vec2> worldVertices;
	PolygonShape() = default;
	PolygonShape(const std::vector<Vec2> vertices);
	~PolygonShape();

	ShapeType GetType() const override;
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;

	// transform vertices from local to world space
	void UpdateVertices(float angle, const Vec2& position);
};

struct BoxShape: public PolygonShape {
	float width;
	float height;

	BoxShape(float width, float height);
	virtual ShapeType GetType() const override;
	~BoxShape();
	Shape* Clone() const override;
	float GetMomentOfInertia() const override;
};

#endif
