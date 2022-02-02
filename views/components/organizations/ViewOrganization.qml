import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2
import "../../basicComponents/graphics/"
import "../../basicComponents/buttons"

Popup {
	focus: true
	modal: true

	closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
//	required property string image_data
	id: pageViewOrganization
	property string name
	property string email
	property string contact

	StackView.onActivated: {
		back_btn_txt = back_text;
		back_btn_font_col = secondary_text_color;
	}

	clip: true
	onFocusChanged: {
		if (focus) title_bar.window_title = " 👁️ View Organization"
	}

	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color}

	padding: pixel_font_size*20

	ScrollView {
		anchors.horizontalCenter: parent.horizontalCenter
		height: parent.height

		ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
		ScrollBar.vertical.policy: ScrollBar.AlwaysOn

		ColumnLayout {

			anchors.fill: parent

			MyImage {
				id: img_profite_view_org
				source: _current_user.image
				Layout.alignment: Layout.Center

			}

			MyButton {
				id: btn_change_profile_img_view_org
				anchors{
					right: img_profite_view_org.right
					bottom: img_profite_view_org.bottom
				}
				btn_col: rootWindow.opaque_white
				add_width: 32
				add_height: 0
				btn_text: "📷︎"
				btn_font_pixel_size: pixel_font_size_24*1.5
				btn_text_color: rootWindow.secondary_text_color
				onClicked: image_picker.open()
			}

			FileDialog {
				id: image_picker
				title: qsTr("Please choose a file")
				nameFilters: [ "Image files (*.png *.jpg)"]
				//					nameFilters: [ "Image files (*.jpg *.png *.jpeg *.svg)"]
				onAccepted: {
//					rootWindow.txt_notification_text =  _current_user.setImage(image_picker.fileUrl)
				}
			}


			ColumnLayout{
				spacing: rootWindow.pixel_font_size*3
				Layout.alignment: Layout.Center

				Text {
					id: txt_name_view_org
					text: qsTr(pageViewOrganization.name)
					color: primary_text_color
					font.pixelSize: pixel_font_size_24*2
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_email_view_org
					text: qsTr("e-Mail: " + pageViewOrganization.email )
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_contact_view_org
					text: qsTr("Contact: " + pageViewOrganization.contact)
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

			}

		}
	}

}
