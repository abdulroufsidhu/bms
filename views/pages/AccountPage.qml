import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../"
import "../basicComponents/buttons"

Page {
	onFocusChanged: {
		if (focus) title_bar.window_title = " 👤 Account"
	}

	background: Rectangle { anchors.fill: parent; color: rootWindow.transparent_color}

	padding: pixel_font_size*20

	Image {
		id: img_profite_acc
		source: "qrc:/icons/icons/user-profile 1.svg"
		width: sourceSize.width/2 * pixel_font_size
		height: sourceSize.height/2 * pixel_font_size
		anchors.horizontalCenter: parent.horizontalCenter
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
	}

	ColumnLayout{
		spacing: rootWindow.pixel_font_size*3
		anchors{
			horizontalCenter: parent.horizontalCenter
			top: img_profite_acc.bottom
			margins: pixel_font_size_24
		}


		Text {
			id: txt_name_acc
			text: qsTr("user name")
			color: primary_text_color
			font.pixelSize: pixel_font_size_24*2
			Layout.alignment: Layout.Center
		}

		Text {
			id: txt_email_acc
			text: qsTr("user@example.com")
			color: primary_text_color
			font.pixelSize: pixel_font_size_24
			Layout.alignment: Layout.Center
		}

		Text {
			id: txt_designation_acc
			text: qsTr("current position at organization")
			color: primary_text_color
			font.pixelSize: pixel_font_size_24
			Layout.alignment: Layout.Center
		}

		Text {
			id: txt_branch_acc
			text: qsTr("Branch: XXX")
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

		Text {
			id: txt_contact_acc
			text: qsTr("Contact: XXXXXXXX")
			color: primary_text_color
			font.pixelSize: pixel_font_size_24
			Layout.alignment: Layout.Center
		}

	}

}
