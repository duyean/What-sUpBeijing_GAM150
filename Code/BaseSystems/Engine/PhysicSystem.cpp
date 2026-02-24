#include "PhysicSystem.hpp"
#include <cmath>
#include "../EaseFunctions/AEVEC2OVERLOAD.hpp"

bool PhysicSystem::wasOverlapping(BoxCollider2D* a, BoxCollider2D* b) {
    if (a > b) std::swap(a, b);

    return std::any_of(
        overlappingPairs.begin(),
        overlappingPairs.end(),
        [&](const ColliderPair& p) {
            return p.a == a && p.b == b;
        }
    );
}

void PhysicSystem::setOverlapState(BoxCollider2D* a, BoxCollider2D* b, bool overlapping) {
    if (a > b) std::swap(a, b);

    ColliderPair pair{ a, b };

    if (overlapping) {
        if (!wasOverlapping(a, b)) {
            overlappingPairs.push_back(pair);
        }
    }
    else {
        overlappingPairs.erase(
            std::remove(overlappingPairs.begin(), overlappingPairs.end(), pair),
            overlappingPairs.end()
        );
    }
}

bool PhysicSystem::aabbOverlap(BoxCollider2D* a, BoxCollider2D* b) {
    auto* ta = a->entity->transform;
	auto* tb = b->entity->transform;

	AEVec2 d = abs(ta->getPosition() - tb->getPosition());
	AEVec2 e = a->halfExtents + b->halfExtents;

	return d.x <= e.x && d.y <= e.y;
}

void PhysicSystem::testPair(BoxCollider2D* a, BoxCollider2D* b) {
    bool hit = aabbOverlap(a, b);
    bool wasHit = wasOverlapping(a, b);

    if (hit && !wasHit) {
        a->notifyEnter(b);
        b->notifyEnter(a);

        //debug
        std::cout << a->entity->name << " collided with " << b->entity->name << std::endl;
    }
    else if (hit && wasHit) {
        a->notifyStay(b);
        b->notifyStay(a);
    }
    else if (!hit && wasHit) {
        a->notifyExit(b);
        b->notifyExit(a);
    }

    setOverlapState(a, b, hit);
}


void PhysicSystem::broadPhase()
{
    potentialPairs.clear(); // This is working correctly

    const float thresholdSqr = 100000.0f;
    const size_t count = colliders.size();

    for (size_t i = 0; i < count; ++i) {
        if (colliders[i]->isActive == false || colliders[i]->entity->isActive == false)
        {
            continue;
        }
        AEVec2 posA = colliders[i]->entity->transform->getPosition();

        for (size_t j = i + 1; j < count; ++j) {
            if (colliders[j]->isActive == false || colliders[j]->entity->isActive == false)
            {
                continue;
            }
            AEVec2 posB = colliders[j]->entity->transform->getPosition();

            float dx = posA.x - posB.x;
            float dy = posA.y - posB.y;
            float distSq = dx * dx + dy * dy;

            if (distSq < thresholdSqr) {
 
                potentialPairs.push_back({ colliders[i], colliders[j] });
            }
        }
    }
}

void PhysicSystem::narrowPhase()
{
	for (auto& pair : potentialPairs) {
		testPair(pair.a, pair.b);
	}
}

void PhysicSystem::fixedUpdate(double dt) {
    broadPhase();
    narrowPhase();
}

