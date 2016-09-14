#include "Vector2f.h"

std::ostream &operator<<(std::ostream &out, Vector2f const &vector) {
	out << vector.x << "," << vector.y;
	return out;
}