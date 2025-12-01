import QtQuick
import QtQuick.Controls.Material

Item {
    id: refreshingListView
    anchors.fill: parent

    signal requestRefresh();
    signal refreshed();
    onRefreshed: {
        listView.refreshEnd()
    }

    required property var model


    readonly property double deltaLimit: -100;

    ListView{
        id: listView
        anchors.fill: parent

        property bool refreshing: false
        signal refreshStart();
        onRefreshStart: {
            refreshing = true;
            refreshingListView.requestRefresh();
        }

        signal refreshEnd();
        onRefreshEnd: {
            refreshing = false;
            headerItem.height = 0;
        }


        onContentYChanged: {
            if(dragging && contentY < 0)
            {
                headerItem.height = -refreshingListView.deltaLimit
            }
        }

        onDragEnded: {
            if(!refreshing)
            {
                if(contentY > refreshingListView.deltaLimit)
                {
                    headerItem.height = 0
                }
                else
                {
                    refreshStart();
                }
            }


        }

        model: refreshingListView.model

        header: Item{
            id: headerItem
            width: refreshingListView.width

            BusyIndicator{
                id: busyIndicator
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    topMargin: 10
                }

                rotation: 1;
                scale: (listView.contentY <= refreshingListView.deltaLimit || listView.refreshing) ? 0.8 : 0.6

                readonly property double yOffsetCenter: (-refreshingListView.deltaLimit - busyIndicator.height)/2
                y: parent.height === -refreshingListView.deltaLimit ? yOffsetCenter : (refreshingListView.deltaLimit + yOffsetCenter)
            }
        }

        delegate: Item{
            id: row
            width: refreshingListView.width
            height: extended ? extendedHeight : defaultHeight

            readonly property int extendedHeight: 170
            readonly property int defaultHeight: 80

            property bool extended: false

            Behavior on height{
                NumberAnimation{
                    duration: 150
                    easing.type: Easing.InOutQuad
                }
            }

            Item{
                anchors{
                    top: parent.top
                    bottom: parent.bottom
                    left: parent.left
                    right: extendButton.left
                }

                Rectangle{
                    id: noImageBorder
                    anchors.fill: thumbnailImage
                    color: "transparent"
                    border.color: "lightgray"
                    border.width: 2
                }

                Image{
                    id: thumbnailImage
                    anchors{
                        topMargin: row.extended? 15 : 4
                        leftMargin: row.extended? 15 : 4
                        rightMargin: row.extended? 15 : 4
                        bottomMargin: row.extended? 50 : 4
                        top: parent.top
                        bottom: parent.bottom
                        left: parent.left
                    }

                    Behavior on anchors.topMargin {
                        NumberAnimation{
                            duration: 150
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Behavior on anchors.leftMargin {
                        NumberAnimation{
                            duration: 150
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Behavior on anchors.rightMargin {
                        NumberAnimation{
                            duration: 150
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Behavior on anchors.bottomMargin {
                        NumberAnimation{
                            duration: 150
                            easing.type: Easing.InOutQuad
                        }
                    }

                    width: (16.0/9.0) * height
                    source: modelData.thumbnail
                    fillMode: Image.PreserveAspectCrop
                }

            }


            Label{
                id: extendButton
                anchors{
                    right: parent.right
                    top: parent.top
                }
                width: row.defaultHeight
                height: row.defaultHeight

                text: row.extended ? "^" : "v"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        row.extended = !row.extended
                    }
                }

            }



        }
    }

}
