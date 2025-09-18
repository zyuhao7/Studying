import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("QML Data Types demo")

    property string mStr : " myh qiansexiamo"
    property int mInt : 5
    property bool isFemale : true
    property double mDouble : 3.14
    property url mUrl : "www.moyuhao.com"

    Rectangle{
        width : 200
        height : 100 + mInt
        anchors.centerIn: parent
        color : "blue"

        Text{
            id : mTextId
            anchors.centerIn: parent
            text : mStr
            font.bold: isFemale ? true : false

        }
    }

    Component.onCompleted: {
        print("hello world")
        console.log("app is running!")
    }

}
