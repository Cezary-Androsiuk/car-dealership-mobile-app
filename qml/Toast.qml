import QtQuick 2.15

Rectangle {
    id: toastRoot

    property alias text: toastText.text

    function show(message) {
        if(hideTimer.running)
            hideTimer.stop();

        toastText.text = message
        visible = true
        opacity = 1.0
        hideTimer.start()
    }

    function hide() {
        opacity = 0.0
        hideTimer.stop()
    }

    visible: false
    opacity: 0.0
    Behavior on opacity {
        NumberAnimation {
            duration: 300
            easing.type: Easing.InOutQuad
        }
    }

    color: "#333"
    radius: 15

    width: toastText.width + 40
    height: toastText.height + 20

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 80


    Text {
        id: toastText
        color: "white"
        font.pixelSize: 16
        anchors.centerIn: parent
    }

    Timer {
        id: hideTimer
        interval: 2500
        onTriggered: toastRoot.hide()
    }
}
