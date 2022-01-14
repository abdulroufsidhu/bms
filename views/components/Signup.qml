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
				hint: "Contact"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
				id: signup_email
				hint: "Email"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {

				id: signup_cnic
				hint: "National Identity"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}


/******************************************
* permanent address
******************************************/

			Text{
				text: qsTr("Permanent Address");
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

			Text{
				text: qsTr("Temporary Address");
				color: primary_text_color
				font.pixelSize: pixel_font_size_24
			}

			MyComboBox {
				id: signup_temp_country
				model_data_array: _country_list
				Layout.fillWidth: true
			}

			MyEditText {
				id: signup_temp_city
				hint: "City"
				Layout.alignment: Layout.Center
				Layout.fillWidth: true
			}
			MyEditText {
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
						output.text = _db.signup(
									signup_full_name.text_data,
									signup_email.text_data,
									signup_contact.text_data,
									signup_cnic.text_data,
									signup_password.text_data,
									signup_conf_password.text_data,
									signup_perm_country.currentValue,
									signup_perm_city.text_data,
									signup_perm_address.text_data,
									signup_temp_country.currentValue,
									signup_temp_city.text_data,
									signup_temp_address.text_data
									);

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
