import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    id: rootWindow
    width: 420
    height: 700
    visible: true

    onHeightChanged: console.log(width + " " + height)
    onWidthChanged: console.log(width + " " + height)

    Material.theme: Material.Dark

    Component.onCompleted: {
        console.log("main component completed")
        Backend.downloadNewestData();
    }


    Connections{
        target: Backend

        function onDataLoaded(){
            if(mainLoader.item.objectName === "DataView") // test if item is already set as DataView
            {
                // if yes, then call function stopRefreshingView() at this object instead of loading it
                mainLoader.item.stopRefreshingView();
            }
            else
            {
                console.log("setting source...")
                mainLoader.setSource("DataView.qml")
            }
        }

        function onDataError(details){
            if(mainLoader.item.objectName === "DataErrorView")
            {
                mainLoader.item.stopRefreshingView();
            }
            else
            {
                mainLoader.setSource("DataErrorView.qml", { details: details })
            }
        }

        function onShowToast(message){
            toast.show(message)
        }

        function onDataStatus(message){
            if(mainLoader.item.loadingDataStatus)
                mainLoader.item.loadingDataStatus = message;
        }
    }

    Loader{
        id: mainLoader
        anchors.fill: parent
        source: "Loading.qml"
        onLoaded: {
            console.log("main loader loaded")
        }
    }

    Toast{
        id: toast
    }
}
