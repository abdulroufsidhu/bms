import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
	property string btn_text: ""
	property string btn_text_color: rootWindow.secondary_text_color
	property int btn_font_pixel_size: rootWindow.pixel_font_size_24
	property int add_width: 64
	property int add_height: 16
	property string btn_col: primary_button_color;

	leftPadding: add_width/2;
	rightPadding: add_width/2;
	topPadding: add_height/2;
	bottomPadding: add_height/2;

	hoverEnabled: true

	onHoveredChanged: {
		focus = false
	}

	scale: (hovered|activeFocus) ? 1.1:1

	contentItem: Text {
		text: qsTr(btn_text)
		color: btn_text_color
		font.family: rootWindow.font.family
		font.pixelSize: btn_font_pixel_size;
		font.bold: true
		font.weight: Font.Black
	}

	background: Rectangle {
		id: btn_bg_rect
		color: (parent.hovered | parent.activeFocus) ? "orange" : btn_col
		radius: 5
		anchors.fill: parent
		opacity: (parent.hovered | parent.activeFocus) ? 1:0.7

		Behavior on color {
			ColorAnimation {
				duration: 500
			}
		}

	}

	Behavior on scale {
		NumberAnimation {
			duration: 200
		}
	}

}
