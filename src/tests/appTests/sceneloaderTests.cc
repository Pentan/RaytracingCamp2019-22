#include <string>
#include <sstream>

#include <doctest.h>
#include "../testsupport.h"

#include <pinkycore/pptypes.h>
#include <pinkycore/assetlibrary.h>
#include <pinkycore/scene.h>

#include <pinkypi/sceneloader.h>

using namespace PinkyPi;

namespace {
    std::string KhronosGlTFSampleModelPath(std::string name) {
        std::stringstream ss;
        ss <<  PINKYPI_TEST_DATA_DIR;
        ss << "/glTF-Sample-Models/2.0/";
        ss << name << "/glTF/";
        ss << name << ".gltf";
        return ss.str();
    }
}

TEST_CASE("Scene loader test [SceneLoader]") {
    std::string gltfpath = KhronosGlTFSampleModelPath("Box");
    AssetLibrary *assetlib = SceneLoader::load(gltfpath);
    Scene *scene = assetlib->getDefaultScene();
    REQUIRE(scene != nullptr);
}
