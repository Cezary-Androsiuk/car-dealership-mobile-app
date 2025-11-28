import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataView

    property bool isListRefreshing: false;
    function stopRefreshingView()
    {
        if(isListRefreshing)
        {
            isListRefreshing = false;
            refreshListView.refreshed();
        }
    }

    Label{
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: "Data"
    }

    ListView{
        anchors.fill: parent
        model: Backend.data.objects

        delegate: Item{
            width: dataView.width
            height: col.height

            Rectangle{
                anchors.fill: parent
                color: Qt.rgba(1,0,0,index/Backend.data.objects.length)
            }

            Column{
                id: col
                Label{
                    text: "ID: " + modelData.id
                }
                Label{
                    text: "Offer Name: " + modelData.offerName
                }
                Image {
                    source: modelData.thumbnail
                    height: 100
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }

    RefreshListView{
        id: refreshListView
        model: Backend.list
        onRequestRefresh: {
            Backend.downloadNewestData();
        }
    }
}
