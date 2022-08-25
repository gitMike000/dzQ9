import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import com.xx.boxer 1.0

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Boxer")


    property string sc: 'TaskUser{width:600; height:30;'

    property string nc: 'NewTask{width:600; height:150;}'
    property int num: 0
    property NewTask newTask: value

    function addThisDate(task, endTask, progress)
    {
        loader.saveRecord(task, endTask, progress)
        var itog = sc + 'taskname:"' + task + '";deadline:"' + endTask + '";progress:"' + progress + '"}'
        var el = Qt.createQmlObject(itog, list, "obj" + num++)
    }

    BoxeR {
     id : loader

     onEnd:
     {
        if (succed)
        {
            newTask = Qt.createQmlObject(nc, list, "objdata")
            loader.nextRecord()
        }
        else Qt.quit()
     }
     onLoadTask: {
        var itog = sc + 'taskname:"' + task + '";deadline:"' + endTask + '";progress:"' + progress + '"}'
        var el = Qt.createQmlObject(itog, list, "obj" + num++)
            loader.nextRecord()
     }
    }

    ScrollView {
       ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
       ScrollBar.vertical.policy: ScrollBar.AlwaysOn
       anchors.fill: parent
       Component.onCompleted: loader.load()
       ColumnLayout {
           id:list
           function add(task, endTask, progress) {
               root.addThisDate(task, endTask, progress)
               console.log(task)
               console.log(endTask)
               console.log(progress)
           }
       }
      }

}
