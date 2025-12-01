import QtQuick
import QtQuick.Controls.Material

Item{
    id: loading
    anchors.fill: parent

    property alias loadingDataStatus: loadingDataStatusLabel.text

    BusyIndicator{
        id: busyIndicator
        anchors.centerIn: parent
        running: true
    }

    Label{
        id: loadingDataStatusLabel
        anchors{
            horizontalCenter: parent.horizontalCenter
            top: busyIndicator.bottom
            topMargin: 10
        }
        text: "Waiting for Backend..."
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
