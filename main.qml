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
	readonly property string secondary_button_color: "#0C0"
	readonly property string opaque_white: '#AAFFFFFF'
	readonly property string critical_button_color: "#A00"
	readonly property string skyblue_color: "#0CF"
	readonly property string red_color: "#F00"
	readonly property string transparent_color: "#00000000"

	readonly property int pixel_font_size : wr<hr?wr:hr
	readonly property int pixel_font_size_24: pixel_font_size*24

	readonly property string logout_txt: "⛔ Logout"
	readonly property string back_text: "⮌ Back"
	property string back_btn_txt: back_text
	property string back_btn_font_col: secondary_text_color

	property string txt_notification_text: ""
	property string txt_notification_col: critical_button_color

	header: ColumnLayout {
		width: rootWindow.width
		TitleBar {
			width: rootWindow.width
			id: title_bar
			Layout.fillWidth: true
		}
		RowLayout {
			Layout.fillWidth: true;
			spacing: pixel_font_size_24
			MyButton {
				readonly property string logedin: _current_user.name
				btn_text: back_btn_txt
				btn_font_pixel_size: pixel_font_size_24
				btn_text_color: back_btn_font_col
				color: back_btn_col()
				MouseArea{
					anchors.fill: parent
					onClicked: {
						stack.pop()
					}
				}
				function back_btn_col() {
					if (stack.depth < 2 ) return rootWindow.opaque_white;
					return secondary_button_color;
				}
			}
			ScrollView {
				Layout.fillWidth: true;
				Layout.fillHeight: true;
				clip: true;
				rightPadding: pixel_font_size_24
				ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
				Text {
					id: txt_notification
					text: qsTr(txt_notification_text)
					color: txt_notification_col
					font.pixelSize: pixel_font_size_24
				}
			}


		}

	}
// without auth clicking login button is changing stacks which shall not be done.
	StackView {
		id: stack
		anchors.fill: parent
		initialItem: AuthorizationPage{
			StackView.onRemoved: destroy()
			StackView.onActivated: {
				back_btn_font_col = secondary_text_color;
				back_btn_txt = back_text;
			}
		}
	}

	Component {
		id: s_v_component
		SwipeView {
			StackView.onActivated: {
				back_btn_txt = logout_txt;
				back_btn_font_col = critical_button_color;
			}

			StackView.onRemoved: destroy();
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
