#pragma once
#pragma once
#include <any>
#include <vector>
#include <algorithm>
#include "../math/Vector3D.h";
#include "rigidbody.h";

// C'est AABB en fait
struct Rect 
{
    Vector3D position;
    Vector3D scale;

    bool contains(Rigidbody* other);

    float GetMinX() { return position.x - scale.x; };
    float GetMaxX() { return position.x + scale.x; };
    float GetMinY() { return position.y - scale.y; };
    float GetMaxY() { return position.y + scale.y; };
    float GetMinZ() { return position.z - scale.z; };
    float GetMaxZ() { return position.z + scale.z; };
    Vector3D GetScale() { return scale; };
    Vector3D GetPosition() { return position; };

    Rect(const Rect&);
    Rect(Vector3D pos, Vector3D size);
};

// Noeud
/*struct Collidable {
    friend class Octree;
public:
    Rect bound;
    //SimpleGE::ColliderComponent* data;

    //Collidable(const Rect& _bounds = {}, SimpleGE::ColliderComponent* _data = {});
private:
    Octree* qt = nullptr;
    Collidable(const Collidable&) = delete;
};*/

class Octree {
public:
    //Octree(Vector3D pos, Vector3D size, unsigned _capacity, unsigned _maxLevel);
    Octree(const Rect& _bound, unsigned _capacity, unsigned _maxLevel);
    Octree(const Octree&);
    Octree();

    bool insert(Rigidbody* obj);
    bool remove(Rigidbody* obj);
    bool update(Rigidbody* obj);
    //std::vector<Rigidbody*>& getObjectsInBound(const Rect& bound);
    unsigned totalChildren() const noexcept;
    unsigned totalObjects() const noexcept;
    void drawOctree(int childId = -1);
    void clear() noexcept;

    ~Octree();
private:
    bool      isLeaf = true;
    unsigned  level = 0;
    unsigned  capacity;
    unsigned  maxLevel;
    Rect      bounds;
    Octree* parent = nullptr;
    Octree* children[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    std::vector<Rigidbody*> objects, foundObjects;

    void subdivide();
    void discardEmptyBuckets();
    //inline Octree* getChild(const Rect& bound) const noexcept;
};
