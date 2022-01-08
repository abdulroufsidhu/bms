import QtQuick 2.0
import "./basicComponents/buttons"

Rectangle {
	property int titlebar_height: 40 + rootWindow.hr
	property string window_title: ""

	x: 0; y: 0
	width: parent.width
	height: titlebar_height
	color: rootWindow.primary_color

	MouseArea {
		id: mouse_area_title_bar
		property var clickPos
		anchors.fill: parent
		onPressed: { clickPos = Qt.point(mouse.x, mouse.y);	}
		onPositionChanged: {
			if (rootWindow.flags == Qt.FramelessWindowHint) {
				rootWindow.x += mouse.x - clickPos.x;
				rootWindow.y += mouse.y - clickPos.y;
			}
		}
	}

	MyCircularButton {
		id: btn_info_title_bar
		anchors{
			verticalCenter: parent.verticalCenter
			left: parent.left
			leftMargin: 5
		}
		rect_diameter: 32
		rect_color: rootWindow.skyblue_color
		btn_text: "<b>!</b>"
		btn_text_font_size: 24

		MouseArea {
			anchors.fill: parent
			onClicked: {
				if (rootWindow.flags == Qt.FramelessWindowHint) {
					rootWindow.flags = Qt.BypassWindowManagerHint
				} else {
					rootWindow.flags = Qt.FramelessWindowHint
				}
				btn_close_title_bar.visible = !btn_close_title_bar.visible
				btn_maximize_title_bar.visible = !btn_maximize_title_bar.visible
			}
		}
	}

	Text {
		anchors.centerIn: parent
		text: qsTr(window_title)
		font.pixelSize: 24
		font.bold: true
		color: rootWindow.primary_text_color
	}

	MyCircularButton {
		id: btn_maximize_title_bar
		anchors{
			verticalCenter: parent.verticalCenter
			right: btn_close_title_bar.left
			rightMargin: 5
		}
		rect_diameter: 32
		rect_color: rootWindow.primary_button_color
		btn_text_font_size: 24

		MouseArea {
			anchors.fill: parent
			onClicked: {
				if (rootWindow.visibility === 5) {
					rootWindow.visibility = 2;
				} else {
					rootWindow.visibility = 5;
				}
			}
		}

	}
	MyCircularButton {
		id: btn_close_title_bar
		anchors{
			verticalCenter: parent.verticalCenter
			right: parent.right
			rightMargin: 5
		}
		rect_diameter: 32
		rect_color: rootWindow.critical_button_color
		btn_text: "<b>X</b>"
		btn_text_font_size: 24

		MouseArea {
			anchors.fill: parent
			onClicked: Qt.quit();
		}

	}

}
