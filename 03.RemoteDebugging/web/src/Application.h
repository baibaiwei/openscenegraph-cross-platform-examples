
/*
This file is part of OpenSceneGraph cross-platform examples:
  https://github.com/OGStudio/openscenegraph-cross-platform-examples

Copyright (C) 2018 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H
#define OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

// Application+Logging Start
#include "Logger.h"

// Application+Logging End
// Application+Rendering Start
#include "render.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application+Rendering End
// Application+Debugging Start
#include "DebugPage.h"

// Application+Debugging End
// Application+frame+Reporting Start
#include "Reporter.h"

// Application+frame+Reporting End

namespace osgcpe
{

class Application
{
    public:
        Application(const std::string &name)
        {
            // Application+Logging Start
            this->setupLogging(name);
            
            // Application+Logging End
            // Application+Rendering Start
            this->setupRendering();
            
            // Application+Rendering End
            // Application+Debugging Start
            this->setupDebugging();
            
            // Application+Debugging End
            // Application+RedBGColorDebugging Start
            this->setupRedBGColorDebugging();
            
            // Application+RedBGColorDebugging End
        }
        ~Application()
        {
            // Application+Rendering Start
            this->tearRenderingDown();
            
            // Application+Rendering End
            // Application+Logging Start
            this->tearLoggingDown();
            
            // Application+Logging End
        }

        // Application+frame+Reporting Start
        public:
            Reporter frameReporter;
            void frame()
            {
                this->viewer->frame();
                this->frameReporter.report();
            }
        // Application+frame+Reporting End
        // Application+setupWindow-embedded Start
        public:
            void setupWindow(int width, int height)
            {
                this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            }
        // Application+setupWindow-embedded End

        // Application+Logging Start
        private:
            Logger *logger;
            void setupLogging(const std::string &appName)
            {
                // Create custom logger.
                this->logger = new Logger(appName);
                // Provide the logger to OpenSceneGraph.
                osg::setNotifyHandler(this->logger);
                // Only accept notifications of Info level or higher
                // like warnings and errors.
                osg::setNotifyLevel(osg::INFO);
                //osg::setNotifyLevel(osg::WARN);
            }
            void tearLoggingDown()
            {
                // Remove the logger from OpenSceneGraph.
                // This also destroys the logger: no need to deallocate it manually.
                osg::setNotifyHandler(0);
            }
        // Application+Logging End
        // Application+Rendering Start
        public:
            void setScene(osg::Node *scene)
            {
                this->viewer->setSceneData(scene);
            }
        private:
            osgViewer::Viewer *viewer;
            void setupRendering()
            {
                // Create OpenSceneGraph viewer.
                this->viewer = new osgViewer::Viewer;
                // Use single thread: CRITICAL for mobile and web.
                this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
                // Create manipulator: CRITICAL for mobile and web.
                this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
            }
            void tearRenderingDown()
            {
                delete this->viewer;
            }
        // Application+Rendering End
        // Application+Debugging Start
        public:
            DebugPage debugPage;
        
            void setupDebugging()
            {
                this->debugPage.title = "camera";
            }
        // Application+Debugging End
        // Application+RedBGColorDebugging Start
        private:
            void setupRedBGColorDebugging()
            {
                this->debugPage.addItem(
                    "RedBGColor",
                    [&] {
                        auto cam = this->viewer->getCamera();
                        auto color = cam->getClearColor();
                        int value = color.r() * 255.0;
                        return log::printfString("%d", value);
                    },
                    [&](const std::string &value) {
                        auto cam = this->viewer->getCamera();
                        auto color = cam->getClearColor();
                        color.r() = static_cast<float>(atoi(value.c_str())) / 255.0;
                        cam->setClearColor(color);
                    }
                );
            }
        
        // Application+RedBGColorDebugging End
};

} // namespace osgcpe

#endif // OPENSCENEGRAPH_CROSS_PLATFORM_EXAMPLES_APPLICATION_H

