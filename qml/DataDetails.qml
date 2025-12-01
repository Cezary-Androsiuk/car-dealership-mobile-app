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

    property var previousDataElement
    function show(){
        console.log("Showing data details")
        if(dataElement !== previousDataElement)
        {
            listFlickable.contentY = 0
            previousDataElement = dataElement
        }

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


    Item{
        id: listViewContainer
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

        Flickable{
            id: listFlickable
            anchors.fill: parent
            contentWidth: column.width
            contentHeight: column.height

            property bool scrollContentDown: false
            onContentHeightChanged: {
                /// code for comfort and extras - works only when extended list is the last one
                if(scrollContentDown)
                {
                    let comfortAndExtrasHeight = comfortAndExtrasContainer.height +
                        comfortAndExtrasHeader.height

                    let topPointHeight = comfortAndExtrasHeight > height ?
                            comfortAndExtrasHeight : height

                    contentY = contentHeight - topPointHeight
                }
            }

            Column{
                id: column
                spacing: 5

                Label{
                    id: offerNameLabel
                    width: listViewContainer.width

                    text: dataElement.offerName
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter

                    wrapMode: Text.WordWrap
                    font.bold: true
                    font.pixelSize: 20
                }

                Item{
                    id: imageContainer
                    width: listViewContainer.width
                    height: image.height + 15 // bottom margin


                    Rectangle{
                        id: noImageBorder
                        anchors.fill: image
                        color: "transparent"
                        border.color: "lightgray"
                        border.width: 2
                    }

                    Image{
                        id: image
                        anchors.centerIn: parent
                        width: parent.width
                        // height: (9/16) * width
                        source: dataElement.thumbnail
                        fillMode: Image.PreserveAspectFit
                    }
                }



                Label{
                    id: statusLabel
                    width: listViewContainer.width

                    text: "Stan: " + dataElement.status
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }


                Row{
                    id: priceRow
                    width: listViewContainer.width
                    spacing: 8

                    Label{
                        id: priceLabel
                        anchors.verticalCenter: parent.verticalCenter

                        text: "Cena: " + splitNumerByThousands(dataElement.price) + " PLN"
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }

                    Label{
                        id: negotiableLabel
                        anchors.verticalCenter: parent.verticalCenter

                        text: dataElement.negotiable? "(Do negocjacji)" : ""
                        font.pixelSize: 14
                        opacity: 0.7
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter

                    }
                }


                Label{
                    id: mileageLabel
                    width: listViewContainer.width

                    text: "Przebieg: " + splitNumerByThousands(dataElement.mileage) + " km"
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }


                Label{
                    id: yearLabel
                    width: listViewContainer.width

                    text: "Rok: " + dataElement.year
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }


                Label{
                    id: bodyTypeLabel
                    width: listViewContainer.width

                    text: "Typ nadwozia: " + dataElement.bodyType
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Label{
                    id: transmissionLabel
                    width: listViewContainer.width

                    text: "Skrzynia biegów: " + dataElement.transmission
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Label{
                    id: descriptionTitleLabel
                    width: listViewContainer.width

                    text: "Opis: "
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Item{
                    width: listViewContainer.width
                    height: descriptionLabel.height+20

                    Label{
                        id: descriptionLabel
                        width: parent.width
                        y: 10

                        text: dataElement.description
                        font.pixelSize: 16
                        font.italic: true
                        opacity: 0.8
                        horizontalAlignment: Text.AlignJustify
                        verticalAlignment: Text.AlignVCenter

                        wrapMode: Text.WordWrap
                    }
                }

                Label{
                    id: makeLabel
                    width: listViewContainer.width

                    text: "Marka: " + dataElement.make
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Label{
                    id: modelLabel
                    width: listViewContainer.width

                    text: "Model: " + dataElement.model
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Label{
                    id: versionLabel
                    width: listViewContainer.width

                    text: "Wersja: " + dataElement.version
                    font.pixelSize: 18
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Item{
                    id: engineDetailsContainer
                    width: listViewContainer.width
                    height: engineDetailsLabel.contentHeight + 10

                    Rectangle{
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "white"
                        border.width: 1
                        opacity: 0.3
                    }

                    Label{
                        id: engineDetailsLabel
                        anchors{
                            left: parent.left
                            right: parent.right
                            leftMargin: 5
                        }

                        height: parent.height
                        text: "Parametry silnika"
                        font.pixelSize: 20
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }

                    Label{
                        id: interactionLabel
                        anchors{
                            right: parent.right
                            top: parent.top
                        }
                        width: height
                        height: engineDetailsLabel.height

                        text: ">"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            engineDetailsPopup.open()
                        }
                    }
                }

                Item{
                    id: comfortAndExtrasContainer
                    width: listViewContainer.width
                    height: comfortAndExtrasContainer.extended ?
                                (comfortAndExtrasTitleLabel.height + comfortAndExtrasColumn.height) :
                                (comfortAndExtrasTitleLabel.height)

                    clip: true

                    property bool extended: false

                    Behavior on height{
                        NumberAnimation{
                            duration: 150
                            easing.type: Easing.InOutQuad
                        }
                    }

                    Rectangle{
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "white"
                        border.width: 1
                        opacity: 0.3
                    }

                    Item{
                        id: comfortAndExtrasHeader
                        width: parent.width
                        height: comfortAndExtrasTitleLabel.contentHeight + 10

                        Label{
                            id: comfortAndExtrasTitleLabel
                            anchors{
                                left: parent.left
                                right: parent.right
                                leftMargin: 5
                            }

                            height: parent.height
                            text: "Komfort i dodatki"
                            font.pixelSize: 20
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                        }

                        Label{
                            id: extendVisualizationLabel
                            anchors{
                                right: parent.right
                                top: parent.top
                            }
                            width: height
                            height: comfortAndExtrasTitleLabel.height

                            text: comfortAndExtrasContainer.extended ? "^" : "v"
                            // font.pixelSize: comfortAndExtrasContainer.extended ? 21 : 20
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                comfortAndExtrasContainer.extended = !comfortAndExtrasContainer.extended
                                if(comfortAndExtrasContainer.extended)
                                    listFlickable.scrollContentDown = true;
                            }
                        }
                    }


                    Column{
                        id: comfortAndExtrasColumn
                        anchors{
                            top: comfortAndExtrasHeader.bottom
                            left: parent.left
                            leftMargin: 10
                            right: parent.right
                            rightMargin: 10
                        }
                        visible: comfortAndExtrasContainer.extended
                        spacing: 5

                        Repeater{
                            model: dataElement.details.comfortAndExtras

                            Label{
                                id: comfortAndExtrasElementLabel
                                width: listViewContainer.width

                                text: modelData
                                font.pixelSize: 16
                                horizontalAlignment: Text.AlignLeft
                                verticalAlignment: Text.AlignVCenter
                                wrapMode: Text.WordWrap
                            }
                        }

                        Item{
                            id: listFooterItem2
                            width: listViewContainer.width
                            height: 10
                        }
                    }
                }

                Item{
                    id: listFooterItem1
                    width: listViewContainer.width
                    height: 30
                }

            }
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

        Rectangle{
            anchors.fill: parent
            color: "#1c1b1f"
        }

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

    Popup{
        id: engineDetailsPopup
        x: (parent.width - width)/2
        y: (parent.height - height) * 0.4
        width: parent.width * 0.7
        height: 400


        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape |
                     Popup.CloseOnPressOutside


        Item{
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: closePopupButton.top
            }

            Flickable{
                anchors.fill: parent
                contentWidth: popupColumn.width
                contentHeight: popupColumn.height

                Column{
                    id: popupColumn
                    spacing: 15

                    Label{
                        id: fuelTypeLabel
                        width: listViewContainer.width
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "Rodzaj paliwa: " + dataElement.details.engine.fuelType
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }

                    Label{
                        id: engineCapacityLabel
                        width: listViewContainer.width
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "Pojemność skokowa: " + splitNumerByThousands(
                                  dataElement.details.engine.engineCapacity) + " cm3"
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }

                    Label{
                        id: horsepowerLabel
                        width: listViewContainer.width
                        anchors.horizontalCenter: parent.horizontalCenter

                        text: "Moc: " + splitNumerByThousands(
                                  dataElement.details.engine.horsepower) + " KM"
                        font.pixelSize: 18
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }
                }
            }

        }

        Button{
            id: closePopupButton
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
            }

            text: "OK"
            onClicked: {
                engineDetailsPopup.close();
            }
        }
    }

}
