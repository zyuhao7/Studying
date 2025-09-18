import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QML syntax demo")

    property string textToShow : "Hello QML"
    Row{
        anchors.centerIn: parent
        spacing : 20
        Rectangle{
            id : redRectId
            width: 100
            height: 100
            color: "red"
            border.color : "black"
            border.width : 5
            // anchors.centerIn : parent  将矩形调整到父窗中心
            radius: 15
            MouseArea{
                anchors.fill: parent
                onClicked :{
                    console.log("Clicked on the red rectangle")
                    textToShow =  "red"
                }
            }
        }

        Rectangle{
            id : blueRectId
            width: 100
            height: 100
            color: "blue"
            border.color : "black"
            border.width : 5
            radius: 15
            MouseArea{
                anchors.fill: parent
                onClicked :{
                    console.log("Clicked on the blue rectangle")
                    textId.text =  "blue"
                }
            }
        }

        Rectangle{
            id : greenRectId
            width: 100
            height: 100
            color: "green"
            border.color : "black"
            border.width : 5
            radius: 15
            MouseArea{
                anchors.fill: parent
                onClicked : console.log("Clicked on the green rectangle")
            }
        }

        Rectangle{
            id : circleId
            width: 100
            height: 100
            color: "dodgerblue"
            border.color : "black"
            border.width : 5
            radius: 50
            Text{
                id : textId
                anchors.centerIn: parent
                text: textToShow        // 属性绑定
            }

            MouseArea{
                anchors.fill: parent
                onClicked : console.log("Clicked on the circle")
            }
        }
    }
}
