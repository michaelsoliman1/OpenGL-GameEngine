////
//// Created by michael on ١٢‏/١‏/٢٠٢١.
////
//
//#include "../graphics/texture/texture.h"
//#include "../components/light.h"
//#include "../components/transform.hpp"
//#include "../components/meshRenderer.hpp"
//#include "../components/camera.h"
//#include "../utils/enums.h"
//#include <../graphics/mesh/common-vertex-attributes.hpp>
//
//
//using namespace xGame;
//
//class Resources {
//    //textures
//    Texture* moonTexture = new Texture("assets/images/moon.jpg");
//
//    Texture* asphalt_albedo = new Texture("assets/images/materials/asphalt/albedo.jpg");
//    Texture* asphalt_specular = new Texture("assets/images/materials/asphalt/specular.jpg");
//    Texture* asphalt_roughness = new Texture("assets/images/materials/asphalt/roughness.jpg");
//    Texture* asphalt_emissive = new Texture("assets/images/materials/asphalt/emissive.jpg");
//
//    std::unordered_map<xGame::TextureType, xGame::Texture*> asphalt = {
//            {TextureType::ALBEDO, asphalt_albedo},
//            {TextureType::SPECULAR, asphalt_specular},
//            {TextureType::ROUGHNESS, asphalt_roughness},
//            {TextureType::EMISSIVE, asphalt_emissive},
//    };
//
//    Texture* metal_albedo = new Texture("assets/images/materials/metal/albedo.jpg");
//    Texture* metal_specular = new Texture("assets/images/materials/metal/specular.jpg");
//    Texture* metal_roughness = new Texture("assets/images/materials/metal/roughness.jpg");
//
//    std::unordered_map<xGame::TextureType, xGame::Texture*> metal = {
//        {TextureType::ALBEDO, metal_albedo},
//        {TextureType::SPECULAR, metal_specular},
//        {TextureType::ROUGHNESS, metal_roughness},
//    };
//
//
//    Light* light = new Light();
//    light->type = xGame::LightType::DIRECTIONAL;
//    light->enabled = true;
//    light->color = {1, 0.8, 0.2};
//    light->direction = {-1, -1, -1};
//    light->position = {0, 1, 5};
//    light->attenuation = {0, 0, 1};
//    light->spot_angle = {glm::pi<float>()/4, glm::pi<float>()/2};
//
//   xGame::Mesh* cube = xGame::Mesh::Cuboid(false);
//    xGame::Mesh* sphere = xGame::Mesh::Sphere({32, 16}, false);
//    xGame::Mesh* suzanne = xGame::Mesh::loadOBJ( "assets/models/Suzanne/Suzanne.obj");
//    xGame::Mesh* meshPlane = xGame::Mesh::Plane({1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

//    //materials
//    Material* checkersMaterial = new Material(asphalt, false, true, false, true);
//    Material* moonMat = new Material(metal,false, true, true,true);
//
//};
//
////textures
