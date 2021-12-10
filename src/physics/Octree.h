#pragma once
#pragma once
#include <any>
#include <vector>
#include <algorithm>

struct Rect {
    double x, y, width, height;

    bool contains(const Rect& other) const noexcept;
    bool intersects(const Rect& other) const noexcept;
    double getLeft() const noexcept;
    double getTop() const noexcept;
    double getRight() const noexcept;
    double getBottom() const noexcept;

    Rect(const Rect&);
    Rect(double _x = 0, double _y = 0, double _width = 0, double _height = 0);
};

struct Collidable {
    friend class Octree;
public:
    Rect bound;
    //SimpleGE::ColliderComponent* data;

    //Collidable(const Rect& _bounds = {}, SimpleGE::ColliderComponent* _data = {});
private:
    Octree* qt = nullptr;
    Collidable(const Collidable&) = delete;
};

class Octree {
public:
    Octree(const Rect& _bound, unsigned _capacity, unsigned _maxLevel);
    Octree(const Octree&);
    Octree();

    bool insert(Collidable* obj);
    bool remove(Collidable* obj);
    bool update(Collidable* obj);
    std::vector<Collidable*>& getObjectsInBound(const Rect& bound);
    unsigned totalChildren() const noexcept;
    unsigned totalObjects() const noexcept;
    void clear() noexcept;

    ~Octree();
private:
    bool      isLeaf = true;
    unsigned  level = 0;
    unsigned  capacity;
    unsigned  maxLevel;
    Rect      bounds;
    Octree* parent = nullptr;
    Octree* children[4] = { nullptr, nullptr, nullptr, nullptr };
    std::vector<Collidable*> objects, foundObjects;

    void subdivide();
    void discardEmptyBuckets();
    inline Octree* getChild(const Rect& bound) const noexcept;
};
