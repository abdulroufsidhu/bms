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
				id: reg_branch_name_et
				hint: "branch Name"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_branch_contact_et
				hint: "branch Contact"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_branch_email_et
				hint: "branch Email"
				Layout.fillWidth: true;
			}
			MyComboBox {
				id: reg_branch_country_cb
				model_data_array: _country_list
				Layout.fillWidth: true;
			}

			MyEditText {
				id: reg_branch_city_et
				hint: "City"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_branch_address_et
				hint: "branch Address"
				Layout.fillWidth: true;
			}
			MyEditText {
				id: reg_branch_reg_number_et
				hint: "branch Registeration Number by government (NTN)"
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

			MyButton {
				color: rootWindow.primary_button_color
				add_width: 32
				add_height: 0
				btn_text: "Register New branch®️ "
				btn_font_pixel_size: pixel_font_size_24*1.5
				btn_text_color: rootWindow.secondary_text_color

				MouseArea {
					anchors.fill: parent
					onClicked: {
						if (image_picker.logourl.length < 1) {
							txt_notification_text = "You must choose logo"
							return
						}
						_auth.register_branch(
									_current_user.id,
									reg_branch_name_et.text_data,
									reg_branch_email_et.text_data,
									reg_branch_contact_et.text_data,
									reg_branch_reg_number_et.text_data,
									reg_branch_country_cb.currentValue,
									reg_branch_city_et.text_data,
									reg_branch_address_et.text_data,
									image_picker.logourl
								);
					}
				}

				Connections {
					target: _auth;
					function onOrgRegistered(r) {
						txt_notification_text = r;
						reg_branch_email_et.text_data = "";
						reg_branch_name_et.text_data = "";
						reg_branch_reg_number_et.text_data = "";
						reg_branch_address_et.text_data = "";
						reg_branch_email_et.text_data = "";
						reg_branch_contact_et.text_data = "";
						reg_branch_city_et.text_data = "";
						txt_notification_text = _branch_list.refresh();
						rootWindow.stack.pop();
					}
				}
			}
		}
	}
}
