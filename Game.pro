QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -fconcepts-diagnostics-depth=200
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/gamecontroller.cpp \
    main.cpp \
    model/behaviors/attack.cpp \
    model/behaviors/behavior.cpp \
    model/behaviors/concrete/counterattackbehavior.cpp \
    model/behaviors/concrete/genericattackbehavior.cpp \
    model/behaviors/concrete/generichealthbehavior.cpp \
    model/behaviors/concrete/genericmovablebehavior.cpp \
    model/behaviors/concrete/healingbehavior.cpp \
    model/behaviors/concrete/poisonablebehavior.cpp \
    model/behaviors/concrete/poisoningbehavior.cpp \
    model/behaviors/concrete/poisononkilledbehavior.cpp \
    model/behaviors/concrete/walkablebehavior.cpp \
    model/behaviors/fire.cpp \
    model/behaviors/health.cpp \
    model/behaviors/movement.cpp \
    model/behaviors/poison.cpp \
    model/gameobject.cpp \
    model/gameobjectmodel.cpp \
    model/leafobject.cpp \
    model/modelfactory.cpp \
    model/nodeobject.cpp \
    view/gameview.cpp \
    view/gamewindow.cpp \
    view/renderer/colorrenderer.cpp \
    view/renderer/textrenderer.cpp \
    view/renderer/renderer.cpp \
    view/renderer/spriterenderer.cpp

HEADERS += \
    controller/gamecontroller.h \
    model/behaviors/attack.h \
    model/behaviors/behavior.h \
    model/behaviors/concrete/counterattackbehavior.h \
    model/behaviors/concrete/genericattackbehavior.h \
    model/behaviors/concrete/generichealthbehavior.h \
    model/behaviors/concrete/genericmovablebehavior.h \
    model/behaviors/concrete/healingbehavior.h \
    model/behaviors/concrete/poisonablebehavior.h \
    model/behaviors/concrete/poisoningbehavior.h \
    model/behaviors/concrete/poisononkilledbehavior.h \
    model/behaviors/concrete/walkablebehavior.h \
    model/behaviors/fire.h \
    model/behaviors/health.h \
    model/behaviors/movement.h \
    model/behaviors/poison.h \
    model/gameobject.h \
    model/gameobjectmodel.h \
    model/leafobject.h \
    model/modelfactory.h \
    model/nodeobject.h \
    view/gameview.h \
    view/gamewindow.h \
    view/renderer/colorrenderer.h \
    view/renderer/textrenderer.h \
    view/renderer/renderer.h \
    view/renderer/spriterenderer.h

FORMS += \
    gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
