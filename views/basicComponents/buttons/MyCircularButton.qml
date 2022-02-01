import QtQuick 2.0
import QtQuick.Controls 2.15

Button {
	property string rect_color: rootWindow.primary_button_color
	property string btn_text: ""
	property int btn_text_font_size: rootWindow.pixel_font_size_24/2
	property string btn_text_color: rootWindow.primary_text_color
	property string border_color: primary_button_color
	property int border_width: 0
	property int text_rotation: (hovered | activeFocus) ? 360: 0

	padding: 4

	background: Rectangle {
		id: cb_bg_rect
		implicitWidth: cbt.implicitWidth > cbt.implicitHeight ? cbt.implicitWidth:cbt.implicitHeight
		implicitHeight: implicitWidth
		color: rect_color;
		radius: width/2
		opacity: (parent.hovered || parent.activeFocus) ? 1: 0.7
		border{
			width: border_width
			color: border_color
		}

	}

	Text {
			id: cbt
			anchors.centerIn: parent
			text: qsTr(btn_text)
			color: btn_text_color
			font.family: rootWindow.font.family
			font.pixelSize: btn_text_font_size
			font.bold: true
			rotation: text_rotation

			Behavior on rotation {
				NumberAnimation {
					duration: 500
				}
			}

	}

	hoverEnabled: true

}

//Rectangle {
//	property int rect_diameter: rootWindow.pixel_font_size_24 * 2 + ( btn_text.length * btn_text_font_size )
//	property string rect_color: rootWindow.primary_button_color
//	property string btn_text: ""
//	property int btn_text_font_size: rootWindow.pixel_font_size_24/2
//	property string btn_text_color: rootWindow.primary_text_color

//	implicitWidth: cbt.implicitWidth > cbt.implicitHeight ? cbt.implicitWidth:cbt.implicitHeight
//	implicitHeight: implicitWidth
//	radius: width/2
//	color: rect_color

//	Text {
//		id: cbt
//		anchors.centerIn: parent
//		text: qsTr(btn_text)
//		color: btn_text_color
//		font.family: rootWindow.font.family
//		font.pixelSize: btn_text_font_size
//	}

//}
