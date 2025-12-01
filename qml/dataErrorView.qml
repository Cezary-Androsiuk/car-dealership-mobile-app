import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataErrorView
    required property string details

    objectName: "DataErrorView"

    function stopRefreshingView()
    {
        busyIndicator.running = false;
        busyIndicator.visible = false;
    }

    Column{
        anchors{
            left: parent.left
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        Label{
            anchors.horizontalCenter: parent.horizontalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: "Data error"
        }

        Label{
            anchors{
                left: parent.left
                right: parent.right
            }

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            wrapMode: Text.WordWrap

            text: dataErrorView.details
        }

        Button{
            anchors.horizontalCenter: parent.horizontalCenter

            text: "Retry"
            onClicked: {
                busyIndicator.running = true;
                busyIndicator.visible = true;
                Backend.downloadNewestData();
            }
        }

        BusyIndicator{
            id: busyIndicator
            anchors.horizontalCenter: parent.horizontalCenter
            running: false
            visible: false
        }
    }
}
