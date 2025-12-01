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
            width: refreshingListView.width
            height: 60

            Rectangle{
                anchors{
                    fill: parent
                    margins: 10
                }

                color: Qt.rgba(1, 1, 1, 0.3)
                radius: 10


                Label{
                    anchors{
                        fill: parent
                        leftMargin: 10
                    }

                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    text: {
                        if(index === 0)
                        {
                            return modelData.id
                                    + " " + Math.round(listView.contentY)
                                    // + " " + listView.atYBeginning
                                    // + " " + listView.atYEnd
                                    // + " " + listView.dragging
                                    // + " " + listView.dragEnded()
                            ;

                        }
                        else
                        {
                            return modelData.id;
                        }
                    }

                }
                Image {
                    source: modelData.thumbnail
                    height: 100
                    fillMode: Image.PreserveAspectFit
                }
            }

        }
    }

}
