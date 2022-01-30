import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import "../"
import "../basicComponents/buttons"
import "../basicComponents/graphics"

Page {
	clip: true
	onFocusChanged: {
		if (focus) title_bar.window_title = " 👤 Account"
	}

	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color}

	padding: pixel_font_size*20

	ScrollView {
		anchors.horizontalCenter: parent.horizontalCenter
		height: parent.height

		ColumnLayout {

			anchors.fill: parent

			MyImage {
				id: img_profite_acc
				source: _current_user.image
				Layout.alignment: Layout.Center

			}

			MyButton {
				id: btn_change_profile_img_acc
				anchors{
					right: img_profite_acc.right
					bottom: img_profite_acc.bottom
				}
				color: rootWindow.opaque_white
				add_width: 32
				add_height: 0
				btn_text: "📷︎"
				btn_font_pixel_size: pixel_font_size_24*1.5
				btn_text_color: rootWindow.secondary_text_color

				MouseArea {
					anchors.fill: parent
					onClicked: {
						image_picker.open();
					}
				}
			}

			FileDialog {
				id: image_picker
				title: qsTr("Please choose a file")
				nameFilters: [ "Image files (*.png *.jpg)"]
				//					nameFilters: [ "Image files (*.jpg *.png *.jpeg *.svg)"]
				onAccepted: {
					rootWindow.txt_notification_text =  _current_user.setImage(image_picker.fileUrl)
				}
			}

			ColumnLayout{
				spacing: rootWindow.pixel_font_size*3
				Layout.alignment: Layout.Center

				Text {
					id: txt_name_acc
					text: qsTr(_current_user.person.name)
					color: primary_text_color
					font.pixelSize: pixel_font_size_24*2
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_email_acc
					text: qsTr("e-Mail: " + _current_user.person.email.text )
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_contact_acc
					text: qsTr("Contact: " + _current_user.person.contact.text)
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_designation_acc
					text: qsTr("at")
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_branch_acc
					text: qsTr("Branch: ")
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

				Text {
					id: txt_salary_acc
					text: qsTr("Salary: XXXXXXX")
					color: primary_text_color
					font.pixelSize: pixel_font_size_24
					Layout.alignment: Layout.Center
				}

			}

		}
	}

	Connections {
		target: _current_user
		function onRecievedEmpBranchName(r) {
			txt_branch_acc.text = "Branch: " + r;
		}

		function onRecievedEmpBranchCode(r) {
			let t = txt_branch_acc.text;
			txt_branch_acc.text = t + " " + r;
		}
		function onRecievedEmpJobName(r) {
			txt_designation_acc.text = r;
		}

		function onRecievedEmpOrgName(r) {
			let t = txt_designation_acc.text;
			txt_designation_acc.text = t + " at " + r
		}
		function onRecievedEmpSalary(r) {
			txt_salary_acc.text = "Salary: " + r
		}
	}

}
