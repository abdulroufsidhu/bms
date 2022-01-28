import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12
import "../basicComponents/buttons"
import "../basicComponents/inputs"

Page {
	clip: true
	background: Rectangle{anchors.fill: parent; color: secondary_color}
	ScrollView {
		anchors.fill: parent
		padding: pixel_font_size_24

		ColumnLayout {
			width: rootWindow.width - pixel_font_size_24*2

			MyEditText {
				id: signup_full_name
				hint: "Full Name"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				id: signup_contact
				input_type: Qt.ImhDigitsOnly
				hint: "Contact"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				id: signup_email
				input_type: Qt.ImhEmailCharactersOnly
				hint: "Email"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				id: signup_cnic
				input_type: Qt.ImhDigitsOnly
				hint: "National Identity Number"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}


/******************************************
* permanent address
******************************************/

			Text{
				text: qsTr("Permanent Address");
				font.bold: true
				color: primary_text_color
				font.pixelSize: pixel_font_size_24
			}

			MyComboBox {
				id: signup_perm_country
				Layout.fillWidth: true
				model_data_array: _country_list
			}

			MyEditText {
				id: signup_perm_city
				hint: "City"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				id: signup_perm_address
				hint: "Address"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}

/******************************************
* temporary address
******************************************/

			Rectangle {
				Layout.fillWidth: true;
				color: transparent_color;
				Layout.minimumHeight: pixel_font_size_24 * 1.5;

				Text{
					text: qsTr("Temporary Address");
					color: primary_text_color
					font.bold: true
					font.pixelSize: pixel_font_size_24
					anchors.left: parent.left
				}

				MyCheckBox {
					anchors.right: parent.right
					id: t_addr_same_as_p
					cb_text: "same as above"
					cb_text_col: rootWindow.secondary_text_color
				}
			}


			MyComboBox {
				visible: !t_addr_same_as_p.checked
				id: signup_temp_country
				model_data_array: _country_list
				Layout.fillWidth: true
			}

			MyEditText {
				visible: !t_addr_same_as_p.checked
				id: signup_temp_city
				hint: "City"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				visible: !t_addr_same_as_p.checked
				id: signup_temp_address
				hint: "Address"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}

			MyEditText {
				id: signup_password
				hint: "password"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
				echo_mode: TextInput.Password
			}

			MyEditText {
				id: signup_conf_password
				hint: "confirm password"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
				echo_mode: TextInput.Password
			}

			Text{
				id: output
				color: red_color
				font.pixelSize: pixel_font_size_24
			}

			MyButton {
				btn_text: "Signup"
				MouseArea {
					anchors.fill: parent
					onClicked: {
							busy_indicator_popup.open();
							var t_city, t_country, t_address, p_city, p_country, p_address;
							p_city = signup_perm_city.text_data;
							p_country = signup_perm_country.currentValue;
							p_address = signup_perm_address.text_data;
							t_city = signup_temp_city.text_data;
							t_country = signup_temp_country.currentValue;
							t_address = signup_temp_address.text_data;
							if (t_addr_same_as_p.checked) {
								t_address = p_address;
								t_city = p_city;
								t_country = p_country;
							}
							_auth.signup(
										signup_full_name.text_data,
										signup_email.text_data,
										signup_contact.text_data,
										signup_cnic.text_data,
										signup_password.text_data,
										signup_conf_password.text_data,
										p_country,
										p_city,
										p_address,
										t_country,
										t_city,
										t_address
										);
					}
				}
				Connections {
					target: _auth
					function onSignedUp(r) {
						txt_notification_text = r;
						if (!txt_notification_text.length) {
							busy_indicator_popup.close();
							stack.pop(null);
							stack.push(s_v_component);
						}
						busy_indicator_popup.close();
					}
				}

			}
		}
	}
}

/*##^##
Designer {
		D{i:0;formeditorZoom:2}
}
##^##*/
