import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Rectangle {
	property string btn_text: ""
	property string btn_text_color: rootWindow.secondary_text_color
	property int btn_font_pixel_size: rootWindow.pixel_font_size_24
	property int add_width: 64
	property int add_height: 16

	implicitWidth: mbt.implicitWidth + add_width
	implicitHeight: mbt.implicitHeight + add_height
	color: rootWindow.primary_button_color
	radius: 5

	Text {
		id: mbt
		text: qsTr(btn_text)
		color: btn_text_color
		anchors.centerIn: parent
		font.pixelSize: btn_font_pixel_size
		font.bold: true
	}

	MouseArea {
		anchors.fill: parent
		cursorShape: "PointingHandCursor"
	}

}