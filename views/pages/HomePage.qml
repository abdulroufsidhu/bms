import QtQuick 2.0
import QtQuick.Controls 2.15
import "../"
import "../basicComponents/buttons/"

Page {
	clip: true
	onFocusChanged: {
		if (focus) title_bar.window_title = "Home"
	}

	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color }
	Text {
		text: qsTr("Home")
	}
}
