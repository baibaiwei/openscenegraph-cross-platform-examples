FEATURE Application.h/Include
#include "rendering.h"
#include "Resource.h"
#include "resources.h"

FEATURE Application.h/Impl
public:
    void loadScene(Resource &resource)
    {
        // Load scene.
        auto scene = resourceNode(resource, "osgt");
        if (!scene.valid())
        {
            platformLog("Could not load scene");
            return;
        }
        // TODO FEATURE VBO/IMPL
        // Load shaders.
        osg::Program *prog = createShaderProgram(shaderVertex, shaderFragment);
        // Apply shaders.
        scene->getOrCreateStateSet()->setAttribute(prog);
        // Set scene.
        this->viewer->setSceneData(scene);
    }
