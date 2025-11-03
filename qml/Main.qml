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
        mainLoader.sourceComponent = loading;
        Backend.startInitialization()
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
    }

    Loader{
        id: mainLoader
        anchors.fill: parent
    }

    Component{
        id: loading
        Item{
            anchors.fill: parent
            BusyIndicator{
                anchors.centerIn: parent
                running: true
            }
        }
    }

    Toast{
        id: toast
    }
}
