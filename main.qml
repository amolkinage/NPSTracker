/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.5
import QtQml.Models 2.1

import "qrc:/content"

Rectangle {
    id: mainRect
    width: 1000
    height: 700


    property int portfoliolistViewActive: 1
    property QtObject schemeModel;
    property QtObject portfolioModel;

    property QtObject schemeView;

    property int   currentPortfolioIndex: 0
    property string currentPortfolioName: ""


    Component.onCompleted:
        portfoliolistViewActive = 1;

    function getschemeModel()
    {
        schemeModel = portfolioModel.getSchemeModel(currentPortfolioIndex);
        mainRect.schemeView.model = schemeModel;
        return schemeModel;
    }

    Rectangle {
        id: banner
        height: 80
        anchors.top: parent.top
        width: parent.width
        color: "#000000"

        Image {
            id: arrow
            source: "./content/images/icon-left-arrow.png"
            //source: "./content/images/addition.png"
            anchors.left: banner.left
            anchors.leftMargin: 20
            anchors.verticalCenter: banner.verticalCenter
            visible: portfolioListView.currentIndex == 0 ? false : true

            MouseArea {
                anchors.fill: parent
                onClicked: portfoliolistViewActive = 1;
            }
        }


        Item {
            id: textItem
            width: npsText.width + trackerText.width
            height: npsText.height + trackerText.height
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter

            Text {
                id: npsText
                anchors.verticalCenter: textItem.verticalCenter
                color: "#ffffff"
                font.family: "Abel"
                font.pointSize: 40
                text: "NPS"
            }
            Text {
                id: trackerText
                anchors.verticalCenter: textItem.verticalCenter
                anchors.left: npsText.right
                color: "#5caa15"
                font.family: "Abel"
                font.pointSize: 40
                text: "Tracker"
            }
        }

        Image {
            id: addition
            x: 950
            y: 25
            width: 28
            height: 44
            source: "./content/images/addition.png"
            anchors.right: banner.right
            anchors.rightMargin: 15
            anchors.verticalCenter: banner.verticalCenter
        }
    }

    ListView {
        id:portfolioListView
        width: parent.width
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250
        focus: false
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: portfoliolistViewActive == 0 ? 1 : 0
        onCurrentIndexChanged: {

        }



        /*PortfolioModel {
            id: portfolio
            portfolioId: listView.currentPortfolioId
            portfolioName: listView.currentPortfolioName
            //onPortfolioIdChanged: stock.updateStock();
            onDataReady: {
                root.positionViewAtIndex(1, ListView.SnapPosition)
                //stockView.update()
            }
        }*/

        model: ObjectModel {
            PortfolioListView {
                id: listView
                width: portfolioListView.width
                height: portfolioListView.height
            }

            SchemeListView{
                id: schemelistView
                width: portfolioListView.width
                height: portfolioListView.height

            }

        }
    }
}
