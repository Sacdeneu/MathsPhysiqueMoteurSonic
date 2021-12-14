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
    /// <summary>
    /// Position de la zone (x,y,z)
    /// </summary>
    Vector3D position;
    
    /// <summary>
    /// hauteur, largeur, profondeur de la zone
    /// </summary>
    Vector3D scale;

    /// <summary>
    /// V�rifie si un rigiody est contenu dans la zone
    /// </summary>
    /// <param name="other">Rigidbody � v�rifier</param>
    /// <returns>Vrai ou faux</returns>
    bool Contains(Rigidbody* other);

    //GETTERS

    float GetMinX() { return position.x - scale.x; };
    float GetMaxX() { return position.x + scale.x; };
    float GetMinY() { return position.y - scale.y; };
    float GetMaxY() { return position.y + scale.y; };
    float GetMinZ() { return position.z - scale.z; };
    float GetMaxZ() { return position.z + scale.z; };
    Vector3D GetScale() { return scale; };
    Vector3D GetPosition() { return position; };

    //CONSTRUCTEURS

    /// <summary>
    /// Cr�e une zone � partir d'une autre zone
    /// </summary>
    /// <param name="">Zone � passer en r�f�rence</param>
    Rect(const Rect&);

    /// <summary>
    /// Cr�e une zone � partir de param�tres
    /// </summary>
    /// <param name="pos">Position de la zone</param>
    /// <param name="size">Scale de la zone</param>
    Rect(Vector3D pos, Vector3D size);
};



class Octree {
public:

    //CONSTRUCTEURS

    /// <summary>
    /// Cr�e un Octree � partir de param�tres
    /// </summary>
    /// <param name="_bound">Zone de base</param>
    /// <param name="_capacity">Capacit� d'une zone</param>
    /// <param name="_maxLevel">Niveau max de subdivision</param>
    Octree(const Rect& _bound, unsigned _capacity, unsigned _maxLevel);

    /// <summary>
    /// Cr�e un octree � partir d'un autre octree
    /// </summary>
    /// <param name="">Octree � passer en r�f�rence</param>
    Octree(const Octree&);

    /// <summary>
    /// Cr�e un Octree
    /// </summary>
    Octree();

    //FONCTIONS

    /// <summary>
    /// Ins�re un Rigidbody dans l'Octree
    /// </summary>
    /// <param name="obj">Rigidbody � ins�rer</param>
    /// <returns>Succ�s ou �chec de l'op�ration</returns>
    bool Insert(Rigidbody* obj);

    /// <summary>
    /// Supprime un Rigidbody dans l'Octree
    /// </summary>
    /// <param name="obj">Rigidbody � supprimer</param>
    /// <returns>Succ�s ou �chec de l'op�ration</returns>
    bool Remove(Rigidbody* obj);

    /// <summary>
    /// Supprime et r�-ins�re un objet dans l'Octree (pour les objets qui bougent)
    /// </summary>
    /// <param name="obj">Rigibody � r�-ins�rer</param>
    /// <returns>Succ�s ou �chec de l'op�ration</returns>
    bool Update(Rigidbody* obj);

    //std::vector<Rigidbody*>& getObjectsInBound(const Rect& bound);

    /// <summary>
    /// Retourne le nombre total d'enfants de l'Octree
    /// </summary>
    /// <returns>Nombre total d'enfants de l'Octree</returns>
    unsigned TotalChildren() const noexcept;

    /// <summary>
    /// Retourne le nombre total d'objets de l'Octree
    /// </summary>
    /// <returns>Nombre total d'objets de l'Octree</returns>
    unsigned TotalObjects() const noexcept;

    /// <summary>
    /// Debug de l'Octree (d�bug visuel en console)
    /// </summary>
    /// <param name="childId">Id de l'enfant � d�bug</param>
    void DrawOctree(int childId = -1);

    /// <summary>
    /// Supprime tous les objets et enfants de l'Octree
    /// </summary>
    void Clear() noexcept;

    /// <summary>
    /// Retourne toutes les feuilles d'un arbre
    /// </summary>
    /// <param name="listLeafs">Liste r�cup�rant les r�sultats</param>
    void GetAllLeafs(std::vector<Octree*>& listLeafs);

    /// <summary>
    /// Retourne toutes les zones de l'arbre
    /// </summary>
    /// <param name="bounds">Liste r�cup�rant les r�sultats</param>
    void GetAllBounds(std::vector<Rect>& bounds);

    ~Octree();

    //VARIABLES

    /// <summary>
    /// Zone de l'Octree
    /// </summary>
    Rect      bounds;

    /// <summary>
    /// Enfants de l'Octree
    /// </summary>
    Octree* children[8] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

    /// <summary>
    /// Objets de l'Octree
    /// </summary>
    std::vector<Rigidbody*> objects;

private:
    //VARIABLES PRIVEES

    /// <summary>
    /// L'Octree est-il une feuille ?
    /// </summary>
    bool      isLeaf = true; 

    /// <summary>
    /// Niveau de l'Octree
    /// </summary>
    unsigned  level = 0;

    /// <summary>
    /// Nombre maximum d'objets dans la zone de l'Octree
    /// </summary>
    unsigned  capacity;

    /// <summary>
    /// Niveau max de subdivision de l'Octree
    /// </summary>
    unsigned  maxLevel;

    /// <summary>
    /// Parent de l'octree
    /// </summary>
    Octree* parent = nullptr; 

    /// <summary>
    /// Subdivise l'Octree en 8 parties
    /// </summary>
    void Subdivide();

    /// <summary>
    /// Ignore les enfants si tous ne contiennent aucun objet et sont des feuilles
    /// </summary>
    void DiscardEmptyBuckets();
};
