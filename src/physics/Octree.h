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

    bool Contains(Rigidbody* other);

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



class Octree {
public:
    Octree(const Rect& _bound, unsigned _capacity, unsigned _maxLevel);
    Octree(const Octree&);
    Octree();

    bool Insert(Rigidbody* obj);
    bool Remove(Rigidbody* obj);
    bool Update(Rigidbody* obj);
    //std::vector<Rigidbody*>& getObjectsInBound(const Rect& bound);
    unsigned TotalChildren() const noexcept;
    unsigned TotalObjects() const noexcept;
    void DrawOctree(int childId = -1);
    void Clear() noexcept;
    void GetAllLeafs(std::vector<Octree*>& listLeafs);
    void GetAllBounds(std::vector<Rect>& bounds);
    ~Octree();


    Rect      bounds;
    Octree* children[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    std::vector<Rigidbody*> objects;

private:
    bool      isLeaf = true;
    unsigned  level = 0;
    unsigned  capacity;
    unsigned  maxLevel;

    Octree* parent = nullptr; 


    void Subdivide();
    void DiscardEmptyBuckets();
};
