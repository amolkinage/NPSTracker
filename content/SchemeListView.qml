import QtQuick 2.5

Rectangle {
    id: rootScheme
    width: 320
    height: 410
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "white"

    property int   currentSchemeId: -1
    property string  currentSchemeName: ""

    function updateModel(){
        viewScheme.model = mainRect.getschemeModel();
    }

    Component.onCompleted: {
        mainRect.schemeView = viewScheme;
    }

    ListView {
        id: viewScheme
        anchors.fill: parent
        width: parent.width
        clip: true
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem


        onCurrentIndexChanged: {
        }

        delegate: Rectangle {
            height: 102
            width: parent.width
            color: "transparent"
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    viewScheme.currentIndex = index;
                }
            }

            Text {
                id: schemeNameText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                width: 125
                height: 40
                color: "#000000"
                font.family: "Open Sans"
                font.pointSize: 20
                font.weight: Font.Bold
                verticalAlignment: Text.AlignVCenter
                text: SchemeName
            }

            Text {
                id: schemeValueText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 0.31 * parent.width
                width: 190
                height: 40
                color: "#000000"
                font.family: "Open Sans"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: SchemeMarketValue
            }

            Text {
                id: schemeCAGR
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 135
                height: 40
                color: "#328930"
                font.family: "Open Sans"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: SchemeCAGR+"%"
                onTextChanged: {
                    if (parseFloat(SchemeCAGR) >= 0.0)
                        color = "#328930";
                    else
                        color = "#d40000";
                }
            }

            Text {
                id: schemeInvestValueText
                anchors.top: schemeNameText.bottom
                anchors.left: parent.left
                anchors.leftMargin: 15
                width: 330
                height: 30
                color: "#000000"
                font.family: "Open Sans"
                font.pointSize: 16
                font.bold: false
                elide: Text.ElideRight
                maximumLineCount: 1
                verticalAlignment: Text.AlignVCenter
                text: SchemeInvestValue
            }

            Text {
                id: schemeReturns
                anchors.top: schemeNameText.bottom
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 120
                height: 30
                color: "#328930"
                font.family: "Open Sans"
                font.pointSize: 18
                font.bold: false
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: SchemeReturns+"%"
                onTextChanged: {
                    if (parseFloat(SchemeReturns) >= 0.0)
                        color = "#328930";
                    else
                        color = "#d40000";
                }
            }

            Rectangle {
                id: endingLine
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: 1
                width: parent.width
                color: "#d7d7d7"
            }
        }

        highlight: Rectangle {
            width: rootScheme.width
            color: "#eeeeee"
        }
    }
}


