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
	flags: Qt.Window
//	flags: Qt.FramelessWindowHint
	title: qsTr("Business Management System")
	color: secondary_color
	font.family: "arial"
	font.pixelSize: pixel_font_size_24

	readonly property int hr: rootWindow.height / 480
	readonly property int wr: rootWindow.width / 640

	readonly property string primary_color: "#466a63"
	readonly property string secondary_color: "#6d9c89"
	readonly property string primary_text_color: "#FFE1C6"
	readonly property string secondary_text_color: "#AA000000"
	readonly property string primary_button_color: "#FFE600"
	readonly property string secondary_button_color: "#0C0"
	readonly property string opaque_white: '#AAFFFFFF'
	readonly property string critical_button_color: "#A00"
	readonly property string skyblue_color: "#0CF"
	readonly property string red_color: "#F00"
	readonly property string green_color: "#0F0"
	readonly property string transparent_color: "#00000000"

	readonly property int pixel_font_size : wr<hr?wr:hr
	readonly property int pixel_font_size_24: pixel_font_size*18

	readonly property string logout_txt: "⛔ Logout"
	readonly property string back_text: "⮌ Back"
	property string back_btn_txt: back_text
	property string back_btn_font_col: secondary_text_color

	property string txt_notification_text: ""
	property string txt_notification_col: primary_text_color
	property string txt_popup_col: primary_text_color
	property bool back_btn_visibility: true

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
				btn_text: back_btn_txt
				visible: back_btn_visibility
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
				ScrollBar.vertical.policy: ScrollBar.AlwaysOn
				Text {
					id: txt_notification
					text: qsTr(txt_notification_text)
					color: txt_notification_col
					font.family: rootWindow.font.family
					font.pixelSize: pixel_font_size_24
					onTextChanged: {
						if (text.length) {
							notification_popup.popup_text = text;
							notification_popup.open();
						} else {
							txt_notification_col = primary_text_color
						}
					}
				}
			}
		}
	}
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
				back_btn_visibility = false;
			}
			StackView.onRemoved: destroy();
			readonly property bool show_tab_bar: true
//			interactive: false
			id: swipe_view;
			currentIndex: tab_bar.currentIndex
			HomePage {}
			StorePage {}
			OrganizationPage { id: org_page}
			AccountPage {}
		}
	}

	Popup {
		id: busy_indicator_popup
		anchors.centerIn: parent
		modal: true
		focus: true
		padding: pixel_font_size_24
		background: Rectangle {
			anchors.fill: parent
			color: secondary_color
			radius: pixel_font_size*10
		}
		closePolicy: Popup.NoAutoClose // | Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
		BusyIndicator {
			running: true
		}
	}

	Popup {
		property string popup_text: "";
		id: notification_popup
		anchors.centerIn: parent
		modal: true
		focus: true
		padding: pixel_font_size_24
		background: Rectangle {
			anchors.fill: parent
			color: secondary_color
			radius: pixel_font_size*10
		}
		closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
		Text {
			id: notif_popup_msg
			text: qsTr(notification_popup.popup_text)
			font.family: rootWindow.font.family
			font.pixelSize: rootWindow.font.pixelSize
			font.bold: true
			color: txt_popup_col
		}
		onClosed: txt_popup_col = primary_text_color
	}

	footer: TabBar {
				id: tab_bar
				visible: visibilityCheck()
				currentIndex: stack.currentItem.currentIndex
				background: Rectangle {
					anchors.fill: parent;
					color: rootWindow.primary_color
				}
				MyTabButton { text: qsTr("🏠 Home"); }
				MyTabButton { text: qsTr("🗄️ Store"); }
				MyTabButton { text: qsTr("🏢 Organization"); }
				MyTabButton { text: qsTr("👤 Account"); }

				function visibilityCheck() {
					if (stack.currentItem.show_tab_bar) return true
					return false
				}

			}

}
