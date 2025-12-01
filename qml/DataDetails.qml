import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataDetails

    property var dataElement

    visible: false

    function show(){
        dataDetails.visible = true;
    }

    function hide(){
        dataDetails.visible = false;
    }

    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f"
    }

    Item{
        id: pageHeader
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
        }
        height: parent.height * 0.1

        Button{
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 10
            }

            text: "Back"
            onClicked: {
                dataDetails.hide()
            }
        }

        Rectangle{
            id: pageHeaderSeparator
            anchors{
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
            }
            height: 1
            opacity: 0.3
        }
    }

}
