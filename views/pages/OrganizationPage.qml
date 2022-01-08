import QtQuick 2.0
import QtQuick.Controls 2.15
import "../"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Organization"
	}
	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color }
	Text {
		text: qsTr("Organization")
	}
}
