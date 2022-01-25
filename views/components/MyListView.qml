import QtQuick 2.15
import QtQuick.Controls 2.15

//Rectangle {
//	property var lv_model
//	property bool view_btn_item: false
//	property bool sell_btn_item: false

//	color: rootWindow.primary_color
//	radius: rootWindow.pixel_font_size * 10
//	width: rootWindow.pixel_font_size * 540
//	anchors{
//		bottom:  parent.bottom
//		bottomMargin: rootWindow.pixel_font_size*20
//	}

	ListView {
		property bool view_btn_item: false
		property bool sell_btn_item: false
		property bool manage_btn_org: false
		property int total_btns: 0;

		onView_btn_itemChanged: {
			if (view_btn_item == true) ++total_btns;
			if (view_btn_item == false) --total_btns;
		}
		onSell_btn_itemChanged: {
			if (sell_btn_item == true) ++total_btns;
			if (sell_btn_item == false) --total_btns;
		}
		onManage_btn_orgChanged: {
			if (manage_btn_org == true) ++total_btns;
			if (manage_btn_org == false) --total_btns;
		}

		id: lv
		anchors.topMargin: rootWindow.pixel_font_size_24
		anchors.bottomMargin: rootWindow.pixel_font_size_24
		cacheBuffer: rootWindow.pixel_font_size * 40
		spacing: rootWindow.pixel_font_size*6
		clip: true

		ScrollBar.vertical: ScrollBar{  }


		delegate: ItemDelegate{
			width: lv.width
			implicitHeight: lvd_row.implicitHeight;
			Row {
				id: lvd_row
				width: parent.width
//				implicitHeight: lv_txt_delegate.implicitHeight
				spacing: rootWindow.pixel_font_size * 10
				Text {
					id: lv_txt_delegate
					width: lv.width -( view_item_btn.width + sell_item_btn.width + manage_org_btn.width + parent.spacing*(total_btns) )
					text: "Name: " + model.name + "\ne-Mail: " + model.email + "\nContact: " + model.contact
					font.pixelSize: rootWindow.pixel_font_size_24
					elide: Text.ElideLeft
					verticalAlignment: Text.AlignVCenter
					horizontalAlignment: Text.AlignLeft
					color: rootWindow.primary_text_color
				}
				Image {
					id: manage_org_btn;
					source: "qrc:/icons/icons/process.svg";
					visible: manage_btn_org;
					width: visible ? rootWindow.pixel_font_size * sourceSize.width/3.56 : 0
					height: rootWindow.pixel_font_size * sourceSize.height/3.56
					anchors.verticalCenter: lvd_row.verticalCenter
				}

				Image {
					id: view_item_btn;
					source: "qrc:/icons/icons/view 1.svg";
					visible: view_btn_item;
					width: visible ? rootWindow.pixel_font_size * sourceSize.width/2 : 0
					height: rootWindow.pixel_font_size * sourceSize.height/2
					anchors.verticalCenter: lvd_row.verticalCenter
				}
				Image {
					id: sell_item_btn;
					source: "qrc:/icons/icons/sell-label 1.svg";
					visible: sell_btn_item;
					width: visible ? rootWindow.pixel_font_size * sourceSize.width/2 : 0
					height: rootWindow.pixel_font_size * sourceSize.height/2
					anchors.verticalCenter: lvd_row.verticalCenter
				}
			}

			hoverEnabled: true

			background: Rectangle {
				anchors.fill: lvd_row;
				color: parent.hovered?secondary_color:primary_color
				radius: pixel_font_size*5
			}
		}

	}

//}


