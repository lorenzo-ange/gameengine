cmake_minimum_required(VERSION 3.0.0)
project(gameengine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/engineTester/MainGameLoop.cpp
    src/entities/Camera.cpp
    src/entities/Camera.h
    src/entities/Entity.cpp
    src/entities/Entity.h
    src/entities/Light.cpp
    src/entities/Light.h
    src/entities/Player.cpp
    src/entities/Player.h
    src/guis/GuiRenderer.cpp
    src/guis/GuiRenderer.h
    src/guis/GuiShader.cpp
    src/guis/GuiShader.h
    src/guis/GuiTexture.cpp
    src/guis/GuiTexture.h
    src/models/RawModel.cpp
    src/models/RawModel.h
    src/models/TexturedModel.cpp
    src/models/TexturedModel.h
    src/renderEngine/DisplayManager.cpp
    src/renderEngine/DisplayManager.h
    src/renderEngine/EntityRenderer.cpp
    src/renderEngine/EntityRenderer.h
    src/renderEngine/Loader.cpp
    src/renderEngine/Loader.h
    src/renderEngine/MasterRenderer.cpp
    src/renderEngine/MasterRenderer.h
    src/renderEngine/OBJLoader.cpp
    src/renderEngine/OBJLoader.h
    src/renderEngine/TerrainRenderer.cpp
    src/renderEngine/TerrainRenderer.h
    src/shaders/ShaderProgram.cpp
    src/shaders/ShaderProgram.h
    src/shaders/StaticShader.cpp
    src/shaders/StaticShader.h
    src/shaders/TerrainShader.cpp
    src/shaders/TerrainShader.h
    src/skybox/SkyboxRenderer.cpp
    src/skybox/SkyboxRenderer.h
    src/skybox/SkyboxShader.cpp
    src/skybox/SkyboxShader.h
    src/terrains/Terrain.cpp
    src/terrains/Terrain.h
    src/textures/ModelTexture.cpp
    src/textures/ModelTexture.h
    src/textures/TerrainTexture.cpp
    src/textures/TerrainTexture.h
    src/textures/TerrainTexturePack.cpp
    src/textures/TerrainTexturePack.h
    src/textures/TextureData.cpp
    src/textures/TextureData.h
    src/textures/TextureLoader.cpp
    src/textures/TextureLoader.h
    src/toolbox/Keyboard.cpp
    src/toolbox/Keyboard.h
    src/toolbox/Maths.cpp
    src/toolbox/Maths.h)

add_executable(gameengine ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} )

target_link_libraries(gameengine ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} SDL2 SDL2_ttf SDL2_image)
#target_link_libraries (ES2 SDL2 SDL2_ttf SDL2_image m)

add_custom_command(TARGET gameengine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:gameengine>/res)

set( SHADERS
    src/shaders/vertexShader.txt
    src/shaders/fragmentShader.txt
    src/shaders/terrainVertexShader.txt
    src/shaders/terrainFragmentShader.txt
    src/skybox/skyboxVertexShader.txt
    src/skybox/skyboxFragmentShader.txt
    src/guis/guiVertexShader.txt
    src/guis/guiFragmentShader.txt
)
foreach(item IN LISTS SHADERS)
    add_custom_command(TARGET gameengine POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/${item} $<TARGET_FILE_DIR:gameengine>/${item})
endforeach()