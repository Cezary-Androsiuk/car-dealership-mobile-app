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
        Backend.loadData();
    }

    Connections{
        target: Backend

        function onDataLoaded(){
            mainLoader.setSource("DataView.qml")
        }

        function onNoDataFound(){
            mainLoader.setSource("NoDataView.qml")
        }

        function onDataError(details){
            mainLoader.setSource("DataErrorView.qml", { details: details })
        }
    }

    Loader{
        id: mainLoader
        anchors.fill: parent
    }
}
