#include "Octree.h"
#include <math.h>

//** Rect **//
Rect::Rect(const Rect& other) : Rect(other.position, other.scale) { }
Rect::Rect(Vector3D pos, Vector3D size)
{ 
    position = Vector3D(pos);
    scale = Vector3D(size);

}

bool Rect::Contains(Rigidbody* a) {
    //on détermine le point le plus proche du rigidbody compris dans l'AABB
    Vector3D nearestPointInAABB;
    nearestPointInAABB.x = max(GetMinX(), min(a->GetPosition().x, GetMaxX()));
    nearestPointInAABB.y = max(GetMinY(), min(a->GetPosition().y, GetMaxY()));
    nearestPointInAABB.z = max(GetMinZ(), min(a->GetPosition().z, GetMaxZ()));

    //on calcule la distance entre ce point et le rigidbody
    float distance = Vector3D::Norm(nearestPointInAABB - a->GetPosition());

    //si distance entre le point et le rigidbody est plus grand que le rayon,
    //alors le rigidbody ne touche pas l'AABB on ne génère pas de contact
    if (distance > a->GetRadius())
        return false;
    return true;
}






//** Octree **//
Octree::Octree() : Octree(Rect(Vector3D(0,0,0), Vector3D(0,0,0)), 0, 0) { }
Octree::Octree(const Octree& other) : Octree(other.bounds, other.capacity, other.maxLevel) { }
Octree::Octree(const Rect& _bound, unsigned _capacity, unsigned _maxLevel) :
    bounds(_bound),
    capacity(_capacity),
    maxLevel(_maxLevel) {
    objects.reserve(_capacity);
}

// Inserts an object into this Octree
bool Octree::Insert(Rigidbody* obj) {
    //if (obj->qt != nullptr) return false;

    if (!isLeaf) // Octree n'est pas une feuille donc on ajoute dans les enfants de manière récursive
    {
        for (auto& child : children)
        {
           if(child->bounds.Contains(obj))
                return child->Insert(obj); // Si les collisions sont bizarre, enlever le return
        }
        // insert object into leaf
        //if (Octree* child = getChild(obj->bound))
            //return child->insert(obj);
    }

    // Octree est une feuille, donc on ajoute l'objet
    if (!bounds.Contains(obj))
        return false;

    objects.push_back(obj);

    // Subdivide if required
    if (isLeaf && level < maxLevel && objects.size() >= capacity) {
        Subdivide();
        Update(obj);
    }
    return true;
}

// Removes an object from this Octree
bool Octree::Remove(Rigidbody* obj) {
    auto objToFind = std::find(objects.begin(), objects.end(), obj);
    if (objToFind == objects.end())
        return false;

    objects.erase(objToFind);
    DiscardEmptyBuckets();
    return true;
}


// Removes and re-inserts object into Octree (for objects that move)
bool Octree::Update(Rigidbody* obj) {
    if (!Remove(obj)) return false;

    // Not contained in this node -- insert into parent
     if (parent != nullptr && !bounds.Contains(obj))
        return parent->Insert(obj);
     if (!isLeaf) {
        // Still within current node -- insert into leaf
        for (auto& child : children)
        {
            if (child->bounds.Contains(obj)) {
                return child->Insert(obj); // Si les collisions sont bizarre, enlever le return

            }
                 
        }
    }
    return Insert(obj);
}

// Returns total children count for this Octree
unsigned Octree::TotalChildren() const noexcept {
    unsigned total = 0;
    if (isLeaf) return total;
    for (Octree* child : children)
        total += child->TotalChildren();
    return 8 + total;
}

// Returns total object count for this Octree
unsigned Octree::TotalObjects() const noexcept {
    unsigned total = (unsigned)objects.size();
    if (!isLeaf) {
        for (Octree* child : children)
            total += child->TotalObjects();
    }
    return total;
}

void Octree::DrawOctree(int childId)
{
    if (!isLeaf) 
    {
        int i = 0;
        for (Octree* child : children) 
        {
            if (child != nullptr) 
                child->DrawOctree(++i);
        }
    }
    else 
    {
        std::cout << "Nb Rigibody : " << objects.size() << " - ID de la sous-division " << childId << " - Profondeur de l'arbre " << level << std::endl;
    }
}

// Removes all objects and children from this Octree
void Octree::Clear() noexcept {
    if (!objects.empty()) {
        objects.clear();
    }
    if (!isLeaf) {
        for (Octree* child : children)
            child->Clear();
        isLeaf = true;
    }
}

// Return all the leafs of the tree
void Octree::GetAllLeafs(std::vector<Octree*>& listLeafs)
{
    if (!isLeaf)
    {
        for (Octree* child : children)
            child->GetAllLeafs(listLeafs);
    }

    if(objects.size() > 1)// optimization for the collision case
        listLeafs.push_back(this);
}

// Return all the bounds of the tree
void Octree::GetAllBounds(std::vector<Rect>& boundsList)
{
    boundsList.push_back(bounds);
    if (!isLeaf)
    {
        for (Octree* child : children)
            child->GetAllBounds(boundsList);
    }
}

// Subdivides into eight quadrants
void Octree::Subdivide() {

    Vector3D childSize = Vector3D(bounds.scale.x * 0.5f, bounds.scale.y * 0.5f, bounds.scale.z * 0.5f);

    double width = childSize.x;
    double height = childSize.y;
    double depth = childSize.z;
    double x = 0, y = 0, z = 0;

    for (unsigned i = 0; i < 8; ++i) 
    {
        if(i < 4) // Top
            z = bounds.position.z + depth;
        else    // Bottom
            z = bounds.position.z - depth;

        switch (i%4) {
        case 0: // Top right
            x = bounds.position.x + width;
            y = bounds.position.y + height;
            break;
        case 1:  // Top left
            x = bounds.position.x - width;
            y = bounds.position.y + height;
            break;
        case 2:  // Bottom left
            x = bounds.position.x - width;
            y = bounds.position.y - height;
            break;
        case 3: // Bottom right
            x = bounds.position.x + width;
            y = bounds.position.y - height;
            break; 
        }
        children[i] = new Octree(Rect(Vector3D(x, y, z), childSize), capacity, maxLevel);
        children[i]->level = level + 1;
        children[i]->parent = this;
    }
    isLeaf = false;
}

// Discards buckets if all children are leaves and contain no objects
void Octree::DiscardEmptyBuckets() {
    if (!objects.empty()) return;
    if (!isLeaf) {
        for (Octree* child : children)
            if (!child->isLeaf || !child->objects.empty())
                return;
    }
    if (Clear(), parent != nullptr)
        parent->DiscardEmptyBuckets();
}


Octree::~Octree() {
    Clear();
    if (children[0]) delete children[0];
    if (children[1]) delete children[1];
    if (children[2]) delete children[2];
    if (children[3]) delete children[3];
    if (children[4]) delete children[4];
    if (children[5]) delete children[5];
    if (children[6]) delete children[6];
    if (children[7]) delete children[7];

}
