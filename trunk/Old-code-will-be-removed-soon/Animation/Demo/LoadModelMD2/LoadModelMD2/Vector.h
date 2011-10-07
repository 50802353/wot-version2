class Vec2
{
private:
	float x;
	float y;
	
public:
	Vec2(float _x, float _y);
	Vec2 Add(Vec2 b);

	//Dot product (tich vo huong)
	Vec2 Dot(Vec2 b);
	
	float Angle(Vec2 b);
	
}