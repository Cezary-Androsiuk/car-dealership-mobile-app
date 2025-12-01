import QtQuick
import QtQuick.Controls.Material

Item {
    id: dataDetails
    anchors.fill: parent

    property var dataElement

    visible: false
    opacity: 0.0

    Behavior on opacity{
        NumberAnimation{
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }

    function show(){
        visible = true;
        opacity = 1.0
    }

    function hide(){
        opacity = 0.0
    }

    onOpacityChanged: {
        if(opacity === 0.0)
            visible = false;
    }

    Rectangle{
        anchors.fill: parent
        color: "#1c1b1f"
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
                left: parent.left
                leftMargin: 10
            }

            text: "Back"
            onClicked: {
                dataDetails.hide()
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

    readonly property var dataElementModel: [
        {
            type: "title",
            value: dataElement.
        },
        {
            type: "image",
            value: dataElement.thumbnail
        },

    ]

    Item{
        id: listViewContainer
        anchors{
            top: pageHeader.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }


        ListView{
            anchors.fill: parent
            model: dataElementModel

            delegate: Item{
                width: listViewContainer.width
                height: {
                    if(modelData.type === "image")
                        return 200
                    else if(modelData.type === "text")
                        return 60
                    else
                        return 5
                }

                Label{
                    anchors.centerIn: parent
                    text: modelData.type + modelData.value
                }
            }
        }

        // ListView{
        //     anchors.fill: parent
        //     model: Object.keys(dataDetails.dataElement)

        //     delegate: Item{
        //         width: parent.width
        //         height: 60

        //         Label{
        //             anchors.centerIn: parent
        //             text: modelData + " : " + dataDetails.dataElement[modelData]
        //         }
        //     }
        // }

        // ScrollView{
        //     anchors.fill: parent
        //     Column{
        //         width: parent.width
        //         Repeater{
        //             model: 20
        //             Rectangle{
        //                 width: parent.width
        //                 height: 120
        //                 color: Qt.rgba(1,0,0,index/20)
        //             }
        //         }
        //     }
        // }

    }
}
