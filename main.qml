import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "./views"
import "./views/pages"
import "./views/basicComponents/buttons"

ApplicationWindow {
	id: rootWindow
	width: 960
	height: 540
	minimumWidth: 640
	minimumHeight: 480
	visible: true
	flags: "FramelessWindowHint"
	title: qsTr("Business Management System")
	color: secondary_color


	readonly property int hr: rootWindow.height / 480
	readonly property int wr: rootWindow.width / 640

	readonly property string primary_color: "#35626B"
	readonly property string secondary_color: "#4F838E"
	readonly property string primary_text_color: "#FFE1C6"
	readonly property string secondary_text_color: "#AA000000"
	readonly property string primary_button_color: "#EBFF00"
	readonly property string secondary_button_color: "#AAFFFFFF"
	readonly property string critical_button_color: "#FF0000"
	readonly property string skyblue_color: "#00C2FF"
	readonly property string red_color: "#FF0000"
	readonly property string transparent_color: "#00000000"

	readonly property int pixel_font_size : wr<hr?wr:hr
	readonly property int pixel_font_size_24: pixel_font_size*24

	header: TitleBar {
		id: title_bar
	}

	SwipeView {
		id: swipe_view;
		anchors{
			fill: parent
		}
		currentIndex: tab_bar.currentIndex
		AuthorizationPage {}
		HomePage {}
		StorePage {}
		OrganizationPage {}
		AccountPage {}
	}

	footer: TabBar {
		id: tab_bar
		currentIndex: swipe_view.currentIndex
		background: Rectangle { anchors.fill: parent; color: rootWindow.primary_color }
		MyTabButton { text: qsTr("Authorization") }
		MyTabButton { text: qsTr("Home") }
		MyTabButton { text: qsTr("Store") }
		MyTabButton { text: qsTr("Organization") }
		MyTabButton { text: qsTr("Account") }
	}
}
