import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs
import DiamondSquare 1.0


Window {
    width: 1080
    height: 750
    visible: true
    title: "Mid point displacment"
    color: "#1a1a2e"

    DiamondSquare {
        id: diamondSquare
        anchors.fill: parent   // занять всё окно
        roughness: roughSlider.value
        waterLevel: waterSlider.value
        seed: parseFloat(seedT.text) || 0.0

        camX: diamondSquare.camX
        camY: diamondSquare.camY
        camScale: diamondSquare.camScale
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton

        property double lastX: 0
        property double lastY: 0

        onPressed: (mouse) => {
            lastX = mouse.x
            lastY = mouse.y
        }

        onPositionChanged: (mouse) => {
            if (pressed) {
                diamondSquare.camX += mouse.x - lastX
                diamondSquare.camY += mouse.y - lastY

                lastX = mouse.x
                lastY = mouse.y
            }
        }

        onWheel: (wheel) => {
            var factor = wheel.angleDelta.y > 0 ? 1.15 : 0.87

            var mx = (wheel.x - diamondSquare.camX) / diamondSquare.camScale
            var my = (wheel.y - diamondSquare.camY) / diamondSquare.camScale

            diamondSquare.camScale *= factor

            diamondSquare.camX = wheel.x - mx * diamondSquare.camScale
            diamondSquare.camY = wheel.y - my * diamondSquare.camScale
        }
    }

    Rectangle {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 16
            width: 220
            color: "#CC000000"
            radius: 12

            Flickable {
                anchors.fill: parent
                anchors.margins: 14
                contentHeight: panelCol.implicitHeight
                clip: true

                ColumnLayout {
                    id: panelCol
                    width: parent.width
                    spacing: 10

                    Text { text: "Шероховатость: " + roughSlider.value
                            color: "white"; font.pixelSize: 13 }

                    Slider{
                        id: roughSlider
                        from: 0.1; to: 0.99; value: 0.5
                        stepSize: 0.001
                        Layout.fillWidth: true

                    }
                    Rectangle { height: 1; Layout.fillWidth: true; color: "#44ffffff" }

                    Text { text: "Уровень воды: " + waterSlider.value
                            color: "white"; font.pixelSize: 13 }

                    Slider{
                        id: waterSlider
                        from: 0.0; to: 0.95; value: 0.35
                        stepSize: 0.01
                        Layout.fillWidth: true

                    }
                    Text { text: "Сид"; color: "white" }
                    TextField { id: seedT; text: "0";   color: "white"; background: Rectangle{color:"#33ffffff";radius:4} Layout.fillWidth: true }

                }
        }

    }
}
