TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

unix {
    INCLUDEPATH += "OpenGL/Linux/include/"
}

win32 {
    INCLUDEPATH += "OpenGL/Windows_x64_mingw/include/"
}

INCLUDEPATH += "OpenGL/GLM"
INCLUDEPATH += "OpenGL/"

INCLUDEPATH += "../L_Variable/include/"
INCLUDEPATH += "../L_Utility/include/"
INCLUDEPATH += "../LEti_Engine/include/"

INCLUDEPATH += "include/"

HEADERS += \
    include/Camera/Camera_2D.h \
    include/Camera/Camera_Base.h \
    include/Components/Buffer.h \
    include/Components/Colors.h \
    include/Components/Texture.h \
    include/Components/Vertices.h \
    include/Draw_Modules/Default_Draw_Module_2D.h \
    include/Draw_Modules/Draw_Module_Base.h \
    include/Draw_Modules/Draw_Module__Animation.h \
    include/Draw_Modules/Draw_Module__Text_Field.h \
    include/Picture/Font.h \
    include/Picture/Graphic_Resources_Manager.h \
    include/Picture/Picture.h \
    include/Renderer/Renderer.h \
    include/Shader/Shader.h \
    include/Window/Window_Controller.h

SOURCES += \
    source/Camera/Camera_2D.cpp \
    source/Camera/Camera_Base.cpp \
    source/Components/Buffer.cpp \
    source/Components/Colors.cpp \
    source/Components/Texture.cpp \
    source/Components/Vertices.cpp \
    source/Draw_Modules/Default_Draw_Module_2D.cpp \
    source/Draw_Modules/Draw_Module_Base.cpp \
    source/Draw_Modules/Draw_Module__Animation.cpp \
    source/Picture/Font.cpp \
    source/Picture/Graphic_Resources_Manager.cpp \
    source/Picture/Picture.cpp \
    source/Renderer/Renderer.cpp \
    source/Shader/Shader.cpp \
    source/Window/Window_Controller.cpp
