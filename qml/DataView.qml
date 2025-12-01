import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataView

    objectName: "DataView"

    property bool isListRefreshing: false;
    property var startRefreshingTime;
    readonly property int refreshedSignalDelay: 500
    function stopRefreshingView()
    {
        if(!isListRefreshing)
            return;

        isListRefreshing = false;
        var refreshingTime = Date.now() - startRefreshingTime;

        console.log("duration: " + refreshingTime)

        /// ensure that refreshing will be at least <refreshedSignalDelay> duration
        if(refreshingTime > refreshedSignalDelay)
        {
            refreshListView.refreshed();
            return;
        }

        refreshedSignalDelayTimer.interval = refreshedSignalDelay - refreshingTime;
        refreshedSignalDelayTimer.start();
    }

    Timer{
        id: refreshedSignalDelayTimer
        interval: 2000
        repeat: false
        running: false
        onTriggered: {
            refreshListView.refreshed();
        }
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
                right: parent.right
                rightMargin: 10
            }

            text: "Settings"
            onClicked: {
                settings.show()
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
            leftMargin: 15
            right: parent.right
            rightMargin: 15
            bottom: parent.bottom
            bottomMargin: 15
        }

        clip: true

        /// gives a lot of latency
        RefreshListView{
            id: refreshListView
            model: Backend.data.objects
            onRequestRefresh: {
                isListRefreshing = true;
                startRefreshingTime = Date.now()
                Backend.downloadNewestData();
            }
            onRequestElementDetails: elementIndex => {
                dataDetails.dataElement = Backend.data.objects[elementIndex];
                dataDetails.show();
            }
        }
    }

    /// data details test purposes
    // Component.onCompleted: {
    //     dataDetails.dataElement = Backend.data.objects[0];
    //     dataDetails.show();
    // }

    /// basic stack view XD

    Settings{
        id: settings
    }

    DataDetails{
        id: dataDetails
    }
}
