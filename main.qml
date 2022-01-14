import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import "./views"
import "./views/pages"
import "./views/basicComponents/buttons"

ApplicationWindow {
	id: rootWindow
	x: 0
	y: 0
	width: 1600
	height: 900
	minimumWidth: 640
	minimumHeight: 480
	visible: true
	flags: "FramelessWindowHint"
	title: qsTr("Business Management System")
	color: secondary_color


	readonly property int hr: rootWindow.height / 480
	readonly property int wr: rootWindow.width / 640

	readonly property string primary_color: "#466a63"
	readonly property string secondary_color: "#6d9c89"
	readonly property string primary_text_color: "#FFE1C6"
	readonly property string secondary_text_color: "#AA000000"
	readonly property string primary_button_color: "#FF0"
	readonly property string secondary_button_color: "#0F0"
	readonly property string opaque_white: '#AAFFFFFF'
	readonly property string critical_button_color: "#F00"
	readonly property string skyblue_color: "#0CF"
	readonly property string red_color: "#F00"
	readonly property string transparent_color: "#00000000"

	readonly property int pixel_font_size : wr<hr?wr:hr
	readonly property int pixel_font_size_24: pixel_font_size*24

	header: ColumnLayout {
		width: rootWindow.width
		TitleBar {
			width: rootWindow.width
			id: title_bar
			Layout.fillWidth: true
		}

		MyButton {
			btn_text: "⮌"
			btn_font_pixel_size: pixel_font_size_24
			btn_text_color: secondary_text_color
			color: secondary_button_color
			MouseArea{
				anchors.fill: parent
				onClicked: {
					stack.pop()
				}
			}
		}

	}

// without auth clicking login button is changing stacks which shall not be done.
	StackView {
		id: stack
		anchors.fill: parent
		initialItem: auth_screen
	}

	Component {
		id: auth_screen
		AuthorizationPage{}
	}

	Component {
		id: s_v_component
		SwipeView {
			readonly property bool show_tab_bar: true
			interactive: false
			id: swipe_view;
			currentIndex: tab_bar.currentIndex
			HomePage {}
			StorePage {}
			OrganizationPage {}
			AccountPage {}
		}
	}

	footer: TabBar {
				id: tab_bar
				visible: visibilityCheck()
				currentIndex: stack.currentItem.currentIndex
				background: Rectangle {
					anchors.fill: parent;
					color: rootWindow.primary_color
				}
				MyTabButton { text: qsTr("🏠 Home") }
				MyTabButton { text: qsTr("🗄️ Store") }
				MyTabButton { text: qsTr("🏢 Organization") }
				MyTabButton { text: qsTr("👤 Account") }

				function visibilityCheck() {
					if (stack.currentItem.show_tab_bar) return true
					return false
				}

			}

}
