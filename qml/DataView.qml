import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataView

    objectName: "DataView"

    property bool isListRefreshing: false;
    function stopRefreshingView()
    {
        if(isListRefreshing)
        {
            isListRefreshing = false;
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

        RefreshListView{
            id: refreshListView
            model: Backend.data.objects
            onRequestRefresh: {
                isListRefreshing = true;
                Backend.downloadNewestData();
            }
        }
    }
}
