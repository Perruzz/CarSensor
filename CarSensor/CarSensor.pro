QT       += core gui
QT += charts
QT += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/Chart.cpp \
    View/ChartInfo.cpp \
    View/CabinTemperatureDialog.cpp \
    View/SensorsPanel.cpp \
    View/SpeedDialog.cpp \
    View/TirePressureDialog.cpp \
    View/SensorWidget.cpp \
    View/ToolBar.cpp \
    View/mainwindow.cpp \
    \
    Sensor/CarSensor.cpp \
    Sensor/TirePressureSensor.cpp \
    Sensor/SpeedSensor.cpp \
    Sensor/CabinTemperatureSensor.cpp \
    Sensor/Speed.cpp \
    Sensor/Temperature.cpp \
    \
    Sensor/Json/json.cpp \
    Sensor/Json/jsonvisitor.cpp \
    Sensor/Json/reader.cpp \
    Sensor/Json/jsonrepository.cpp \
    Sensor/Json/jsonfile.cpp \
    \
    main.cpp

HEADERS += \
    View/Chart.h \
    View/ChartInfo.h \
    View/CabinTemperatureDialog.h \
    View/SensorsPanel.h \
    View/SpeedDialog.h \
    View/TirePressureDialog.h \
    View/SensorWidget.h \
    View/ToolBar.h \
    View/mainwindow.h \
    \
    Sensor/SensorVisitor.h \
    Sensor/CarSensor.h \
    Sensor/TirePressureSensor.h \
    Sensor/SpeedSensor.h \
    Sensor/CabinTemperatureSensor.h \
    Sensor/Speed.h \
    Sensor/Temperature.h \
    \
    Sensor/Json/json.h \
    Sensor/Json/jsonvisitor.h \
    Sensor/Json/reader.h \
    Sensor/Json/jsonrepository.h \
    Sensor/Json/jsonfile.h \

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
