import QtQuick 2.0
import QtQuick.Controls 2.15

TabButton {
	property string bg_color: focus ? rootWindow.primary_button_color : rootWindow.primary_text_color
	property string txt_color: focus ? rootWindow.primary_button_color: rootWindow.primary_color

	text: qsTr("")
	font.bold: true
	font.pixelSize: rootWindow.pixel_font_size_24
	focusPolicy: Qt.ClickFocus
	background: Rectangle {
		width: parent.width;
		height: parent.focus ? 3: 0
		color: txt_color
	}
	contentItem: Text {
		text: parent.text
		font: parent.font
		color: bg_color
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		elide: Text.ElideRight
	}
}
