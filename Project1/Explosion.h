#include "Object.h"

class Explosion: public Object {
	private:
		float impactAmount;
		bool step;
	public:
		void update(float time);
		void initialize(float width, float height);
		void draw();
		void collision(Object * other, int fixtureID);
		void setImpactAmount(float amount);
};