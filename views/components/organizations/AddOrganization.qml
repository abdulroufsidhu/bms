import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.2
import "../../basicComponents/inputs/"
import "../../basicComponents/buttons"

Page {
	clip: true
	StackView.onActivated: {
		back_btn_txt = back_text;
		back_btn_font_col = secondary_text_color;
	}
	background: Rectangle{anchors.fill: parent; color: secondary_color }

	ScrollView {
		padding: pixel_font_size_24;
		width: parent.width;
		height: parent.height;
		ColumnLayout {
			spacing: pixel_font_size*10;
			width: rootWindow.width - pixel_font_size_24*2;

			MyEditText {
				id: reg_org_name_et
				hint: "Organization Name"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_org_contact_et
				hint: "Organization Contact"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_org_email_et
				hint: "Organization Email"
				Layout.fillWidth: true;
			}
			MyComboBox {
				id: reg_org_country_cb
				model_data_array: _country_list
				Layout.fillWidth: true;
			}

			MyEditText {
				id: reg_org_city_et
				hint: "City"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_org_address_et
				hint: "Organization Address"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_org_reg_number_et
				hint: "Organization Registeration Number by government (NTN)"
				Layout.fillWidth: true;
			}
			MyButton {
				color: rootWindow.opaque_white
				add_width: 32
				add_height: 0
				btn_text: "📷︎ Logo "
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
				property string logourl: ""
				id: image_picker
				title: qsTr("Please choose a file")
				nameFilters: [ "Image files (*.png *.jpg)"]
				//					nameFilters: [ "Image files (*.jpg *.png *.jpeg *.svg)"]
				onAccepted: {
					logourl = image_picker.fileUrl
				}

				onRejected: {
					txt_notification_text = "You must select your organization's logo";
				}
			}

			MyButton {
				color: rootWindow.primary_button_color
				add_width: 32
				add_height: 0
				btn_text: "Register New Organization®️ "
				btn_font_pixel_size: pixel_font_size_24*1.5
				btn_text_color: rootWindow.secondary_text_color

				MouseArea {
					anchors.fill: parent
					onClicked: {
						if (image_picker.logourl.length < 1) {
							txt_notification_text = "Your must select logo"
							return
						}
						txt_notification_text = image_picker.logourl
					}
				}
			}

		}
	}

}
