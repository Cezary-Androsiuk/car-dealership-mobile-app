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

    // Label{
    //     anchors.centerIn: parent
    //     verticalAlignment: Text.AlignVCenter
    //     horizontalAlignment: Text.AlignHCenter
    //     text: "Data"
    // }

    // ListView{
    //     anchors.fill: parent
    //     model: Backend.data.objects

    //     delegate: Item{
    //         width: dataView.width
    //         height: col.height

    //         Rectangle{
    //             anchors.fill: parent
    //             color: Qt.rgba(1,0,0,index/Backend.data.objects.length)
    //         }

    //         Column{
    //             id: col
    //             Label{
    //                 text: "ID: " + modelData.id
    //             }
    //             Label{
    //                 text: "Offer Name: " + modelData.offerName
    //             }
    //             Image {
    //                 source: modelData.thumbnail
    //                 height: 100
    //                 fillMode: Image.PreserveAspectFit
    //             }
    //         }
    //     }
    // }

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
            right: parent.right
            bottom: parent.bottom
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


    /// basic stack view XD

    Settings{
        id: settings
    }

    DataDetails{
        id: dataDetails
    }
}
