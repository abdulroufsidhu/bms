import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
	property string btn_text: ""
	property string btn_text_color: rootWindow.secondary_text_color
	property int btn_font_pixel_size: rootWindow.pixel_font_size_24

	implicitWidth: mbt.implicitWidth + 64
	implicitHeight: mbt.implicitHeight + 16
	color: rootWindow.primary_button_color
	radius: 5

	Text {
		id: mbt
		text: qsTr(btn_text)
		color: btn_text_color
		anchors.centerIn: parent
		font.pixelSize: btn_font_pixel_size
	}

	MouseArea {
		anchors.fill: parent
		cursorShape: "PointingHandCursor"
	}

}
