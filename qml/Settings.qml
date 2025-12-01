import QtQuick
import QtQuick.Controls.Material

Item {
    id: settings
    anchors.fill: parent

    visible: false

    function show(){
        settings.visible = true;
    }

    function hide(){
        settings.visible = false;
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
                settings.hide()
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

    Item{
        anchors{
            top: pageHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Column{
            anchors.fill: parent
            spacing: 10

            Item{
                width: settings.width
                height: 60

                Button{
                    anchors.centerIn: parent
                    text: "Remove Cache"

                    onClicked: {
                        Backend.removeCache();
                    }
                }
            }

        }
    }

}
