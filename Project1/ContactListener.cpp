/*This is a very simple extension of b2ContactListener that calls ->collision() of objects.*/

#include "Object.h"
#include "ContactListener.h"
#include "ObjectNames.h"

// Execute collsion statements!
void ContactListener::BeginContact(b2Contact * contact){
	Object * object1 = static_cast<Object *> (contact->GetFixtureA()->GetBody()->GetUserData());
	Object * object2 =  static_cast<Object *> (contact->GetFixtureB()->GetBody()->GetUserData());
	object1->collision(object2 ,(long)contact->GetFixtureA()->GetUserData());
	object2->collision(object1, (long)contact->GetFixtureB()->GetUserData());
}

void ContactListener::EndContact(b2Contact * contact){
	Object * object1 = static_cast<Object *> (contact->GetFixtureA()->GetBody()->GetUserData());
	Object * object2 =  static_cast<Object *> (contact->GetFixtureB()->GetBody()->GetUserData());
	object1->collisionEnd(object2 ,(long)contact->GetFixtureA()->GetUserData());
	object2->collisionEnd(object1, (long)contact->GetFixtureB()->GetUserData());
}

// List objects that neglect collisions.
void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
	/* handle pre-solve event */
	Object * object1 = static_cast<Object *> (contact->GetFixtureA()->GetBody()->GetUserData());
	Object * object2 =  static_cast<Object *> (contact->GetFixtureB()->GetBody()->GetUserData());


	// Actor can walk through block 2.
	if (object1->type == ObjectName::BLOCK2 && object2->type == ObjectName::ACTOR){
		contact->SetEnabled(false);
	} else if(object2->type == ObjectName::BLOCK2 && object1->type == ObjectName::ACTOR){
		contact->SetEnabled(false);
	}

	//Explosion goes through everything. The explosion effect is handled by the impact() function.
	if (object1->type == ObjectName::EXPLOSION || object2->type == ObjectName::EXPLOSION){
		contact->SetEnabled(false);
	} 

	if (object1->type == ObjectName::BOMB1 && object2->type == ObjectName::BLOCK2){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::BOMB1 && object1->type == ObjectName::BLOCK2){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ACTOR && object2->type == ObjectName::ITEM_LIFE){
		contact->SetEnabled(true);
	} else if (object2->type == ObjectName::ACTOR && object1->type == ObjectName::ITEM_LIFE){
		contact->SetEnabled(true);
	} else if ( object2->type == ObjectName::ITEM_LIFE || object1->type == ObjectName::ITEM_LIFE ){
		if(object1->type == ObjectName::ITEM_LIFE && object1->getBody()->GetType() == b2_staticBody) {
			contact->SetEnabled(false);
		} else if(object2->type == ObjectName::ITEM_LIFE && object2->getBody()->GetType() == b2_staticBody){
			contact->SetEnabled(false);
		}
	}
	
	if (object1->type == ObjectName::ENEMY1 && object2->type == ObjectName::BLOCK2){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ENEMY1 && object1->type == ObjectName::BLOCK2){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::BOMB1 && object2->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::BOMB1 && object1->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::BOMB1 && object2->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::BOMB1 && object1->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ENEMY1 && object2->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ENEMY1 && object1->type == ObjectName::LADDER){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ITEM_LIFE && object2->type == ObjectName::ENEMY1){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ITEM_LIFE && object1->type == ObjectName::ENEMY1){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ACTOR && object2->type == ObjectName::LOCK){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ACTOR && object1->type == ObjectName::LOCK){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ACTOR && object2->type == ObjectName::CORPSE){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ACTOR && object1->type == ObjectName::CORPSE){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ITEM_LIFE && object2->type == ObjectName::ENEMY1){
		contact->SetEnabled(false);
	} else if (object2->type == ObjectName::ITEM_LIFE && object1->type == ObjectName::ENEMY1){
		contact->SetEnabled(false);
	}

	if (object1->type == ObjectName::ACTOR && object2->type == ObjectName::LADDER){
		contact->SetEnabled(false);
		object1->collision(object2 , 0);
		object2->collision(object1, 0);
	} else if (object2->type == ObjectName::ACTOR && object1->type == ObjectName::LADDER){
		contact->SetEnabled(false);
		object1->collision(object2 , 0);
		object2->collision(object1, 0);
	}

	if (object1->type == ObjectName::ACTOR && object2->type == ObjectName::ITEM_POINTS){
		contact->SetEnabled(true);
	} else if (object2->type == ObjectName::ACTOR && object1->type == ObjectName::ITEM_POINTS){
		contact->SetEnabled(true);
	} else if ( object2->type == ObjectName::ITEM_POINTS || object1->type == ObjectName::ITEM_POINTS ){
		if(object1->type == ObjectName::ITEM_POINTS && object1->getBody()->GetType() == b2_staticBody) {
			contact->SetEnabled(false);
		} else if(object2->type == ObjectName::ITEM_POINTS && object2->getBody()->GetType() == b2_staticBody){
			contact->SetEnabled(false);
		}
	}
}