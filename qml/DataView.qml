import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataView

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
}
