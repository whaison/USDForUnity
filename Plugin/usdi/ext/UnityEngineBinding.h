#pragma once
#ifdef usdiEnableMonoBinding
#include "etc/MonoWrapper.h"

namespace usdi {

void InitializeInternalMethods();
void ClearInternalMethodsCache();


extern void(*TransformAssign)(MonoObject *trans, XformData *data);
extern void(*TransformNotfyChange)(MonoObject *trans);
extern void(*CameraAssign)(MonoObject *camera, CameraData *data);
extern void(*MeshAssignBounds)(MonoObject *mesh, float3 *center, float3  *extents);


struct mVector2;
struct mVector3;
struct mQuaternion;

#define DeclUClass(Type) class m##Type; using mM##Type = mManaged<m##Type>;
DeclUClass(UObject);
DeclUClass(Material);
DeclUClass(Mesh);
DeclUClass(GameObject);
DeclUClass(Component);
DeclUClass(Transform);
DeclUClass(Camera);
DeclUClass(MeshFilter);
DeclUClass(MeshRenderer);
DeclUClass(Light);
DeclUClass(Light);
#undef DeclManeged


mDeclImage(UnityEngine);
mDeclImage(UnityEditor);

struct mVector2
{
public:
    mDeclTraits();
    float x, y;
    float& operator[](int i) { return ((float*)this)[i]; }
    const float& operator[](int i) const { return ((float*)this)[i]; }
};

struct mVector3
{
public:
    mDeclTraits();
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
    const float& operator[](int i) const { return ((float*)this)[i]; }
};

struct mQuaternion
{
public:
    mDeclTraits();
    float x, y, z, w;
    float& operator[](int i) { return ((float*)this)[i]; }
    const float& operator[](int i) const { return ((float*)this)[i]; }
};


class mUObject : public mObject
{
typedef mObject super;
public:
    mDeclTraits();

    mUObject(MonoObject *rep = nullptr);
    operator bool() const { return !isNull(); }

    bool        isNull() const;
    mObject     getSystemType();
    void        setName(const char *name);
    std::string getName();

    static mUObject instantiate(mUObject original);
};


class mMaterial : public mUObject
{
typedef mUObject super;
public:
    mDeclTraits();
    mMaterial(MonoObject *mo = nullptr);
};


class mMesh : public mUObject
{
typedef mUObject super;
public:
    mDeclTraits();
    static mMesh New();

    mMesh(MonoObject *mo = nullptr);
    int getVertexCount();
    void setVertices(mTArray<mVector3> v);
    void setNormals(mTArray<mVector3> v);
    void setUV(mTArray<mVector2> v);
    void setTriangles(mTArray<mInt32> v);
    void uploadMeshData(bool fix);
    void markDynamic();
    void setBounds(const AABB& v);

    static bool hasNativeBufferAPI();
    void* getNativeVertexBufferPtr(int nth);
    void* getNativeIndexBufferPtr();
};


class mGameObject : public mUObject
{
typedef mUObject super;
public:
    mDeclTraits();
    static mGameObject New(const char *name = "");

    mGameObject(MonoObject *game_object = nullptr);
    void SetActive(bool v);

    mObject getComponent(mObject type);
    mObject addComponent(mObject type);

    template<class C> C getComponent() { return C(getComponent(mGetSystemType<C>())); }
    template<class C> C addComponent() { return C(addComponent(mGetSystemType<C>())); }
    template<class C> C getOrAddComponent()
    {
        if (auto c = getComponent<C>()) { return c; }
        return addComponent<C>();
    }
};


class mComponent : public mUObject
{
typedef mUObject super;
public:
    mDeclTraits();
    mComponent(MonoObject *component = nullptr);
    mMGameObject getGameObject();
};


class mTransform : public mComponent
{
typedef mComponent super;
public:
    mDeclTraits();
    mTransform(MonoObject *component = nullptr);
    void setLocalPosition(const float3& v);
    void setLocalRotation(const quatf& v);
    void setLocalScale(const float3& v);
    void setParent(const mMTransform& parent);
    mMTransform findChild(const char *name);
};


class mCamera : public mComponent
{
typedef mComponent super;
public:
    mDeclTraits();
    mCamera(MonoObject *component = nullptr);
    void setNearClipPlane(float v);
    void setFarClipPlane(float v);
    void setFieldOfView(float v);
    void setAspect(float v);
};


class mMeshFilter : public mComponent
{
typedef mComponent super;
public:
    mDeclTraits();
    mMeshFilter(MonoObject *component = nullptr);
    mMMesh getSharedMesh();
    void setSharedMesh(const mMMesh& v);
};


class mMeshRenderer : public mComponent
{
typedef mComponent super;
public:
    mDeclTraits();
    mMeshRenderer(MonoObject *component = nullptr);
    void setSharedMaterial(const mMMaterial& m);
};


class mLight : public mComponent
{
typedef mComponent super;
public:
    mDeclTraits();
    mLight(MonoObject *component = nullptr);
};

} // namespace usdi
#endif // usdiEnableMonoBinding
