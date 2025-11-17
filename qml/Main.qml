import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    width: 420
    height: 700
    visible: true

    onHeightChanged: console.log(width + " " + height)
    onWidthChanged: console.log(width + " " + height)

    Material.theme: Material.Dark

    Component.onCompleted: {
        console.log("main component completed")
        Backend.initialize();
    }



    Connections{
        target: Backend

        function onDataLoaded(){
            mainLoader.setSource("DataView.qml")
            toast.show("Downloaded!")
        }

        function onNoDataFound(){
            mainLoader.setSource("NoDataView.qml")
        }

        function onDataError(details){
            mainLoader.setSource("DataErrorView.qml", { details: details })
            toast.show("Download failed!")
        }

        function onDataStatus(message){
            if(mainLoader.item.loadingDataStatus)
                mainLoader.item.loadingDataStatus = message;
        }
    }

    Loader{
        id: mainLoader
        anchors.fill: parent
        sourceComponent: loading
    }

    Component{
        id: loading

        Item{
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
    }

    Toast{
        id: toast
    }
}
