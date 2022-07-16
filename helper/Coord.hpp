
template <typename T>
struct Coord {
	T x;
	T y;
	constexpr inline Coord(T x, T y)noexcept : x(x), y(y) {}
};
