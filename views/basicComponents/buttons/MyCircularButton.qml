import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
	property int rect_diameter: rootWindow.pixel_font_size_24 * 2 + ( btn_text.length * btn_text_font_size )
	property string rect_color: rootWindow.primary_button_color
	property string btn_text: ""
	property int btn_text_font_size: rootWindow.pixel_font_size_24/2
	property string btn_text_color: rootWindow.primary_text_color

	implicitWidth: cbt.implicitWidth > cbt.implicitHeight ? cbt.implicitWidth:cbt.implicitHeight
	implicitHeight: implicitWidth
	radius: width/2
	color: rect_color

	Text {
		id: cbt
		anchors.centerIn: parent
		text: qsTr(btn_text)
		color: btn_text_color
		font.pixelSize: btn_text_font_size
	}

}
