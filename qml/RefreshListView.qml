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

    signal requestElementDetails(int elementIndex)

    required property var model


    readonly property double deltaLimit: -100;


    function splitNumerByThousands(value)
    {
        const price = value.toString()
        let outString = ""

        const overtake = price.length % 3
        for(let i=0; i<price.length; i++)
        {
            if(i % 3 === overtake && i !== 0)
                outString += " "
            outString += price[i]
        }

        return outString
    }

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

            readonly property int extendedHeight: 200
            readonly property int defaultHeight: 80
            readonly property int defaultImageWidth: (16.0/9.0) * (defaultHeight-8)

            property bool extended: false

            Behavior on height{ NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad } }

            Item{
                id: thumbnailContainer
                anchors{
                    top: parent.top
                    topMargin: row.extended? 30 : 4
                    left: parent.left
                    leftMargin: 4
                    bottom: parent.bottom
                    bottomMargin: 4
                }
                width: thumbnailImage.width

                Behavior on anchors.topMargin { NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad } }

                Rectangle{
                    id: noImageBorder
                    anchors.fill: parent
                    color: "transparent"
                    border.color: "lightgray"
                    border.width: 2
                }

                Image{
                    id: thumbnailImage
                    width: (16.0/9.0) * height
                    height: parent.height

                    source: modelData.thumbnail
                    fillMode: Image.PreserveAspectCrop
                }

            }



            Label{
                id: titleLabel
                anchors{
                    top: parent.top
                    left: parent.left
                    leftMargin: row.extended? 4 : (row.defaultImageWidth+8)
                    right: extendButtonSeparator.left
                }

                Behavior on anchors.leftMargin { NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad } }

                elide: Text.ElideRight
                text: modelData.offerName
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Label{
                id: priceLabel
                anchors{
                    left: thumbnailContainer.right
                    leftMargin: 4
                    bottom: parent.bottom
                    bottomMargin: parent.height * 0.3
                }

                Behavior on opacity { NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad } }

                text: splitNumerByThousands(modelData.price) + " PLN"
                opacity: row.extended ? 0.0 : 1.0
                font.pixelSize: 18
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }




            MouseArea{
                anchors{
                    fill: parent
                    margins: 4
                }
                onClicked: {
                    refreshingListView.requestElementDetails(index)
                }
            }

            Rectangle{
                id: extendButtonSeparator
                anchors{
                    top: parent.top
                    topMargin: 5
                    right: extendButton.left
                    bottom: parent.bottom
                    bottomMargin: 5
                }

                width: 1
                color: "white"
                opacity: row.extended ? 0.0 : 0.3

                Behavior on opacity { NumberAnimation{ duration: 150; easing.type: Easing.InOutQuad } }

            }

            Label{
                id: extendButton
                anchors{
                    right: parent.right
                    top: parent.top
                }
                width: height/2
                height: row.defaultHeight

                text: row.extended ? "^" : "v"
                font.pixelSize: row.extended ? 22 : 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea{
                anchors{
                    right: parent.right
                    top: parent.top
                }
                width: height/2
                height: parent.height

                onClicked: {
                    row.extended = !row.extended
                }
            }



        }
    }

}
