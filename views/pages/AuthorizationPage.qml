import QtQuick 2.0
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import "../"
import "../../"
import "../components"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = "Authorization"
	}
	background: Rectangle{ anchors.fill: parent; color: rootWindow.transparent_color}

		Login {
			id: login_rect
		}

		Component {
			id: loadable_signup_txt
			Rectangle {
				color: transparent_color
				implicitWidth: txt_dont_have_acc.implicitWidth + txt_signup.implicitWidth
				Text {
					id: txt_dont_have_acc
					font.pixelSize: rootWindow.pixel_font_size_24
					text: qsTr("Don't have an account already ? Please ")
					color: rootWindow.primary_text_color
				}

				Rectangle {
					anchors{
						left: txt_dont_have_acc.right
						top: txt_dont_have_acc.top
					}
					implicitHeight: txt_signup.implicitHeight
					implicitWidth: txt_signup.implicitWidth
					color: rootWindow.transparent_color
					Text{
						id: txt_signup
						text: qsTr("Signup")
						font.pixelSize: rootWindow.pixel_font_size_24
						color: rootWindow.primary_button_color
					}
					Rectangle {
						color: rootWindow.primary_button_color
						y: parent.height
						width: parent.width
						height: 3
					}
					MouseArea {
						anchors.fill: parent
						cursorShape: "PointingHandCursor"
					}
				}

			}
		}

		Loader {
			sourceComponent: loadable_signup_txt
			anchors {
				top: login_rect.bottom
				horizontalCenter: parent.horizontalCenter
				margins: rootWindow.pixel_font_size_24
			}
			asynchronous: true
		}

}

