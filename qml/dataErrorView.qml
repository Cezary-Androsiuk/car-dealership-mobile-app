import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataErrorView

    required property string details

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
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: dataErrorView.details
        }
    }
}
