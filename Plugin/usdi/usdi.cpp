#include "pch.h"
#include "usdiInternal.h"
#include "usdiSchema.h"
#include "usdiXform.h"
#include "usdiCamera.h"
#include "usdiMesh.h"
#include "usdiPoints.h"
#include "usdiContext.h"



extern "C" {

usdiExport usdi::Context* usdiOpen(const char *path)
{
    usdiTraceFunc();
    auto *ret = new usdi::Context();
    if (!ret->open(path)) {
        delete ret;
        return nullptr;
    }

    return ret;
}

usdiExport usdi::Context* usdiCreateContext(const char *identifier)
{
    usdiTraceFunc();
    auto *ret = new usdi::Context();
    ret->create(identifier);
    return ret;
}

usdiExport void usdiDestroyContext(usdi::Context *ctx)
{
    usdiTraceFunc();
    delete ctx;
}

usdiExport bool usdiWrite(usdi::Context *ctx, const char *path)
{
    usdiTraceFunc();
    return ctx->write(path);
}

usdiExport void usdiSetImportConfig(usdi::Context *ctx, const usdi::ImportConfig *conf)
{
    usdiTraceFunc();
    ctx->setImportConfig(*conf);
}
usdiExport void usdiGetImportConfig(usdi::Context *ctx, usdi::ImportConfig *conf)
{
    usdiTraceFunc();
    *conf = ctx->getImportConfig();
}
usdiExport void usdiSetExportConfig(usdi::Context *ctx, const usdi::ExportConfig *conf)
{
    usdiTraceFunc();
    ctx->setExportConfig(*conf);
}
usdiExport void usdiGetExportConfig(usdi::Context *ctx, usdi::ExportConfig *conf)
{
    usdiTraceFunc();
    *conf = ctx->getExportConfig();
}

usdiExport usdi::Schema* usdiGetRoot(usdi::Context *ctx)
{
    usdiTraceFunc();
    if (!ctx) return nullptr;

    return ctx->getRootNode();
}


usdiExport int usdiGetID(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) { return 0; }
    return schema->getID();
}

usdiExport const char* usdiGetPath(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) { return nullptr; }
    return schema->getPath();
}

usdiExport const char* usdiGetName(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) { return nullptr; }
    return schema->getName();
}

usdiExport const char* usdiGetTypeName(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) { return nullptr; }
    return schema->getTypeName();
}

usdiExport usdi::Schema* usdiGetParent(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) { return nullptr; }
    return schema->getParent();
}

usdiExport int usdiGetNumChildren(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) return 0;
    return (int)schema->getNumChildren();
}

usdiExport usdi::Schema* usdiGetChild(usdi::Schema *schema, int i)
{
    usdiTraceFunc();
    if (!schema) return nullptr;
    return schema->getChild(i);

}


usdiExport usdi::Xform* usdiAsXform(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) return nullptr;
    return dynamic_cast<usdi::Xform*>(schema);
}

usdiExport usdi::Xform* usdiCreateXform(usdi::Schema *parent, const char *name)
{
    usdiTraceFunc();
    if (!parent) { usdiLog("usdiCreateXform(): parent must be set\n"); return nullptr; }
    if (!name) { usdiLog("usdiCreateXform(): name must be set\n"); return nullptr; }
    return new usdi::Xform(parent->getContext(), parent, name);
}

usdiExport bool usdiXformReadSample(usdi::Xform *xf, usdi::XformData *dst, usdi::Time t)
{
    usdiTraceFunc();
    if (!xf || !dst) return false;
    return xf->readSample(*dst, t);
}

usdiExport bool usdiXformWriteSample(usdi::Xform *xf, const usdi::XformData *src, usdi::Time t)
{
    usdiTraceFunc();
    if (!xf || !src) return false;
    return xf->writeSample(*src, t);
}


usdiExport usdi::Camera* usdiAsCamera(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) return nullptr;
    return dynamic_cast<usdi::Camera*>(schema);
}

usdiExport usdi::Camera* usdiCreateCamera(usdi::Schema *parent, const char *name)
{
    usdiTraceFunc();
    if (!parent) { usdiLog("usdiCreateCamera(): parent must be set\n"); return nullptr; }
    if (!name) { usdiLog("usdiCreateCamera(): name must be set\n"); return nullptr; }
    return new usdi::Camera(parent->getContext(), parent, name);
}

usdiExport bool usdiCameraReadSample(usdi::Camera *cam, usdi::CameraData *dst, usdi::Time t)
{
    usdiTraceFunc();
    if (!cam || !dst) return false;
    return cam->readSample(*dst, t);
}

usdiExport bool usdiCameraWriteSample(usdi::Camera *cam, const usdi::CameraData *src, usdi::Time t)
{
    usdiTraceFunc();
    if (!cam || !src) return false;
    return cam->writeSample(*src, t);
}


usdiExport usdi::Mesh* usdiAsMesh(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) return nullptr;
    return dynamic_cast<usdi::Mesh*>(schema);
}

usdiExport usdi::Mesh* usdiCreateMesh(usdi::Schema *parent, const char *name)
{
    usdiTraceFunc();
    if (!parent) { usdiLog("usdiCreateMesh(): parent must be set\n"); return nullptr; }
    if (!name) { usdiLog("usdiCreateMesh(): name must be set\n"); return nullptr; }
    return new usdi::Mesh(parent->getContext(), parent, name);
}

usdiExport void usdiMeshGetSummary(usdi::Mesh *mesh, usdi::MeshSummary *dst)
{
    usdiTraceFunc();
    if (!mesh || !dst) return;
    mesh->getSummary(*dst);
}

usdiExport bool usdiMeshReadSample(usdi::Mesh *mesh, usdi::MeshData *dst, usdi::Time t)
{
    usdiTraceFunc();
    if (!mesh || !dst) return false;
    return mesh->readSample(*dst, t);
}

usdiExport bool usdiMeshWriteSample(usdi::Mesh *mesh, const usdi::MeshData *src, usdi::Time t)
{
    usdiTraceFunc();
    if (!mesh || !src) return false;
    return mesh->writeSample(*src, t);
}


usdiExport usdi::Points* usdiAsPoints(usdi::Schema *schema)
{
    usdiTraceFunc();
    if (!schema) return nullptr;
    return dynamic_cast<usdi::Points*>(schema);
}

usdiExport usdi::Points* usdiCreatePoints(usdi::Schema *parent, const char *name)
{
    usdiTraceFunc();
    if (!parent) { usdiLog("usdiCreatePoints(): parent must be set\n"); return nullptr; }
    if (!name) { usdiLog("usdiCreatePoints(): name must be set\n"); return nullptr; }
    return new usdi::Points(parent->getContext(), parent, name);
    return nullptr;
}

usdiExport void usdiPointsGetSummary(usdi::Points *points, usdi::PointsSummary *dst)
{
    usdiTraceFunc();
    if (!points || !dst) return;
    points->getSummary(*dst);
}

usdiExport bool usdiPointsReadSample(usdi::Points *points, usdi::PointsData *dst, usdi::Time t)
{
    usdiTraceFunc();
    if (!points || !dst) return false;
    return points->readSample(*dst, t);
}

usdiExport bool usdiPointsWriteSample(usdi::Points *points, const usdi::PointsData *src, usdi::Time t)
{
    usdiTraceFunc();
    if (!points || !src) return false;
    return points->writeSample(*src, t);
}

} // extern "C"
