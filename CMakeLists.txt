cmake_minimum_required(VERSION 3.5)

project(L_Renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB_RECURSE LibFiles "include/*.h")
add_custom_target(headers SOURCES ${LibFiles})

add_library(L_Renderer STATIC
    source/Camera/Camera_2D.cpp 
    source/Camera/Camera_3D.cpp 
    source/Camera/Camera_Base.cpp 
    source/Components/Buffer.cpp 
    source/Components/Colors.cpp 
    source/Components/Texture.cpp 
    source/Components/Vertices.cpp 
    source/Draw_Modules/Default_Draw_Module.cpp 
    source/Draw_Modules/Draw_Module_Base.cpp 
    source/Draw_Modules/Draw_Module__Animation.cpp 
    source/Draw_Modules/Draw_Module__Text_Field.cpp 
    source/Picture/Font.cpp 
    source/Picture/Graphic_Resources_Manager.cpp 
    source/Picture/Picture.cpp 
    source/Renderer/Renderer.cpp 
    source/Shader/Shader_Components/Shader_Component.cpp 
    source/Shader/Shader_Components/Shader_Transform_Component.cpp 
    source/Shader/Shader_Types/Shader.cpp 
    source/Shader/Shader_Program.cpp 
    source/Window/Window_Controller.cpp
)

target_include_directories(L_Renderer PUBLIC 
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/include"
                            "${PROJECT_SOURCE_DIR}/OpenGL"
                            "${PROJECT_SOURCE_DIR}/../L_Utility/include"
                            "${PROJECT_SOURCE_DIR}/../L_Variable/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/include"
                            "${PROJECT_SOURCE_DIR}/../LEti_Engine/OpenGL/GLM"
)

if (WIN32)
    target_include_directories(L_Renderer PUBLIC
                                "${PROJECT_SOURCE_DIR}/OpenGL/Windows_x64_mingw/include"
    )
endif (WIN32)

if (UNIX)
    target_include_directories(L_Renderer PUBLIC
                                "${PROJECT_SOURCE_DIR}/OpenGL/Linux/include"
    )
endif (UNIX)
