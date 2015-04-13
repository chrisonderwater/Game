#include "LightsManager.h"
#include "math.h"
#include "Renderer.h"

LightsManager::LightsManager(b2World * world, Renderer * visual){
	this->visual = visual;
	this->world  = world;
	vertices.setPrimitiveType( sf::Triangles );
}


void LightsManager::setLights(std::vector<Light> * lights){
	this->lights = lights;
}

void LightsManager::draw(){
	visual->registerDraw(&vertices, 9);
}

//-----------------------------------
// Lighting algorithm
// Uses box2D raycasts and SFML vertexArrays
void LightsManager::update(){
	float currentRayAngle = 0;
	float rayLength = 15;
	float stepSize = 1.0f;
	float maxFractionSize = 1.0f;
	float bs = visual->getBlockSize();
	float lightLength = 15;
	b2Vec2 p1;
	b2Vec2 p2;
	vertices.resize( lights->size()*361*3 );
	b2Vec2 prevIntersectionPoint;

	for(int i=0; i<lights->size();i++){
		prevIntersectionPoint = b2Vec2(lights->at(i).x, lights->at(i).y);
		for(int j=0; j<=360; j+=stepSize){
		  currentRayAngle = degreesToRadians(j);
				  //set up input
		  b2RayCastInput input;
		  input.p1 = b2Vec2(lights->at(i).x,lights->at(i).y);
		  input.p2 = input.p1 + rayLength * b2Vec2( sinf(currentRayAngle), cosf(currentRayAngle) );;
		  input.maxFraction = maxFractionSize;
  
		  //check every fixture of every body to find closest
		  float closestFraction = 5; //start with end of line as p2
		  b2Vec2 intersectionNormal(0,0);
		  for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
			  for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
  
				  b2RayCastOutput output;
				  if ( ! f->RayCast( &output, input,0 ) )
					  continue;
				  if ( output.fraction < closestFraction ) {
					  closestFraction = output.fraction;
					  intersectionNormal = output.normal;
				  }            
			  }
		  }
  
		  b2Vec2 intersectionPoint = input.p1 + closestFraction * (input.p2 - input.p1);
		  vertices[(i*1083)+ j*3].position = sf::Vector2f(input.p1.x*bs,input.p1.y*bs);
		  vertices[(i*1083)+ j*3 + 1].position = sf::Vector2f(intersectionPoint.x*bs,intersectionPoint.y*bs);
		  vertices[(i*1083)+ j*3 + 2].position = sf::Vector2f(prevIntersectionPoint.x*bs,prevIntersectionPoint.y*bs);

		  sf::Color  color = lights->at(i).color;			

		  vertices[(i*1080)+ j*3].color        = color;
		  vertices[(i*1080)+ j*3 +1].color     = color ; //pointDistance(input.p1.x,input.p1.y, intersectionPoint.x,intersectionPoint.y) );
		  vertices[(i*1080)+ j*3 +2].color     = color; //pointDistance(input.p1.x,input.p1.y, prevIntersectionPoint.x,prevIntersectionPoint.y) );

          /*
		  vertices[(i*1080)+ j*3].color        = sf::Color(rand()%255,rand()%255,rand()%255, 80 );
		  vertices[(i*1080)+ j*3 +1].color     = sf::Color(rand()%255,rand()%255,rand()%255,80) ; //pointDistance(input.p1.x,input.p1.y, intersectionPoint.x,intersectionPoint.y) );
		  vertices[(i*1080)+ j*3 +2].color     = sf::Color(rand()%255,rand()%255,rand()%255,80); //pointDistance(input.p1.x,input.p1.y, prevIntersectionPoint.x,prevIntersectionPoint.y) );
		  */
		  prevIntersectionPoint = intersectionPoint;
		}
	}
}