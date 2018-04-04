#ifndef _ORDERACTIONS_H
#define _ORDERACTIONS_H

#include "globals.h"
#include "Asserts.h"

void createSalesOrder(char* customer, char* orderType, char* eventAlphaCode, char* edition, char* priceList, char* itemId)
{
	char* transaction = "createSalesOrder";
	char message[102];
	char orderId[1024];

	lr_start_transaction(transaction);

	nca_edit_set("ORDER_SOLD_TO_0", customer);
	nca_edit_set("ORDER_ORDER_TYPE_0", orderType);

	nca_edit_set("ORDER_PRICE_LIST_0", priceList);
	nca_edit_click("ORDER_DF_0");

	nca_set_window("Additional Header Information");
	nca_flex_set_cell_data("Additional Header Information", "Event", "", eventAlphaCode);
	nca_flex_set_cell_data("Additional Header Information", "Event Edition", "", edition);
	nca_flex_press_ok("Additional Header Information");

	nca_menu_select_item("Sales Orders", "File;Save");

	nca_edit_get_text("ORDER_ORDER_NUMBER_0", orderId);

	lr_save_string(orderId, "orderId");
	lr_save_string(customer, "customer");

	lr_message(orderId);

	nca_tab_select_item("ORDER_REGIONS", "Line Items");
	nca_edit_set("LINE_ORDERED_ITEM_DSP_0", itemId);
	nca_edit_set("LINE_ORDERED_QUANTITY_0", "5");
	nca_edit_click("LINE_DF_0");

	nca_flex_set_cell_data("Additional Line Attribute Information", "Event", "", eventAlphaCode);
	nca_flex_set_cell_data("Additional Line Attribute Information", "Event Edition", "", edition);
	nca_flex_press_ok("Additional Line Attribute Information");

	nca_menu_select_item("Sales Orders", "File;Save");
	nca_tab_select_item("ORDER_REGIONS", "Order Information");
	nca_tab_select_item("ORDER_TAB", "Main");
	nca_button_press("ORDER_CONTROL_BOOK_ORDER_0");

	nca_popup_message_press("Note_1", "OK");

	nca_edit_get_text("ORDER_ORDER_NUMBER_0", message);

	if (strlen(message) == 0)
	{
		lr_error_message("Failed to submit receipt");
		lr_end_transaction(transaction, LR_FAIL);
		return;
	}

	lr_end_transaction(transaction, LR_PASS);
}

void searchForOrderByNumberAndStatus(char* orderNumber, char* orderStatus)
{
	char* transaction = "searchOrderByNumberAndStatus";

	lr_start_transaction(transaction);

	nca_set_window("Find  Orders/Quotes");

	nca_edit_set("FIND_ORDER_NUMBER_0", orderNumber);

	nca_edit_set("FIND_STATUS_0", orderStatus);

	nca_button_press("FIND_FIND_LINES_BUTTON_0");

	nca_set_window("Order Organizer");

	nca_button_press("ORDERS_SUMMARY_OPEN_ORDER_BUTTON_0");

	nca_set_window("Sales Orders");

	lr_end_transaction(transaction, LR_PASS);
}

void searchForOrderByNumberAndLineItem(char* orderNumber, char* lineItemNumber)
{
	char* transaction = "searchOrderByNumber";

	lr_start_transaction(transaction);

	nca_set_window("Find  Orders/Quotes");

	nca_edit_set("FIND_ORDER_NUMBER_0", orderNumber);

	nca_tab_select_item("FIND_REGIONS", "Line Information");

	nca_edit_set("FIND_INTERNAL_PART_NUMBER_0", lineItemNumber);

	nca_button_press("FIND_FIND_LINES_BUTTON_0");

	nca_set_window("Order Organizer");

	lr_end_transaction(transaction, LR_PASS);
}

void searchForOrderByCustomerAndStatus(char* customer, char* orderStatus)
{
	char* transaction = "searchForOrderByCustomerAndStatus";

	lr_start_transaction(transaction);

	nca_set_window("Find  Orders/Quotes");

	nca_edit_set("FIND_SOLD_TO_0", customer);

	nca_edit_set("FIND_STATUS_0", orderStatus);

	nca_button_press("FIND_FIND_LINES_BUTTON_0");

	nca_set_window("Order Organizer");

	nca_button_press("ORDERS_SUMMARY_OPEN_ORDER_BUTTON_0");

	nca_set_window("Sales Orders");

	lr_end_transaction(transaction, LR_PASS);
}


void viewInvoiceDetails(char* row)
{
	char* transaction = "viewInvoiceDetail";
	char topwin[1024];
	int i = 0;
	lr_save_string(row, "row");

	lr_start_transaction(transaction);

	nca_tab_select_item("VIEW_ORDER_INFO_TAB", "Invoices / Credit Memos");
		
	while (i < 1000)
	{
		nca_get_top_window(topwin);
		if (strcmp(topwin, "Cancel Query") != 0)
			break;
		i++;
	}

	nca_edit_click(lr_eval_string("VIEW_ORDER_INVOICE_TRX_NUMBER_{row}"));
	
	nca_button_press("VIEW_ORDER_INVOICE_DETAILS_0");

	nca_set_window("Transactions (RX_UK_0052_OU : GBP)");

	lr_end_transaction(transaction, LR_PASS);

}

void getTransactionLineItemsInfo()
{
	char* transaction = "getTransactionLineItemsInfo";

	lr_start_transaction(transaction);

	nca_set_window("Transactions");

	nca_button_press("TGW_HEADER_HEADER_LINE_ITEMS_0");

	nca_set_window("Lines");

	lr_end_transaction(transaction, LR_PASS);
}


	void goToLineItemInfo()
{
		char* transaction = "goToStandLineItemInfo";

		lr_start_transaction(transaction);

		nca_set_window("Order Organizer");

		nca_tab_select_item("SUMMARY_VIEW_TAB", "Lines");

		nca_edit_click("LINES_SUMMARY_DF_0");

		nca_set_window("Additional Line Attribute Information");
		
		lr_end_transaction(transaction, LR_PASS);

}
void openOrderDetails() {
	char* transaction = "getOrderDetails";
	
	lr_start_transaction(transaction);
	
	nca_set_window("Order Organizer");
	
	nca_button_press("ORDERS_SUMMARY_OPEN_ORDER_BUTTON_0");
	
	nca_set_window("Sales Orders");
	
	lr_end_transaction(transaction, LR_PASS);
}

void openAdditionalHeaderInformation() {
	char* transaction = "getAdditionalInformation";
	
	lr_start_transaction(transaction);
	
	nca_edit_click("ORDER_DF_0");
	
	nca_set_window("Additional Header Information");
	
	lr_end_transaction(transaction, LR_PASS);
}

void openLineItems() {
	char* transaction = "openLineItems";
	
	lr_start_transaction(transaction);
	
	nca_tab_select_item("ORDER_REGIONS", "Line Items");
	
	lr_end_transaction(transaction, LR_PASS);
}

int findProductRowNumber(char* productId) {
	char* transaction = "findProductRowNumber";
	int maxLinesNumber = 20;
	char lineName[50];
	char tmp[10];
	int lineNumber;
	int i = 0;
	
	lr_start_transaction(transaction);
	
	for(i; i < maxLinesNumber; i++ ) {
		sprintf(lineName, "LINE_ORDERED_ITEM_DSP_%d", i);
		nca_edit_get_text(lineName, tmp);
		
		if(strstr(tmp, productId) != NULL) {
			lineNumber = i;
			lr_end_transaction(transaction, LR_PASS);
			return lineNumber;
		}
	}
	
	lr_error_message("Product row not found");
	lr_end_transaction(transaction, LR_FAIL);
	return;
}

void checkOrderedQuantity(int lineNumber, char* dbQuantity) {
	char* transaction = "checkOrderedQuantity";
	char lineName[50];
	char qty[10];
	
	lr_start_transaction(transaction);
	
	sprintf(lineName, "LINE_ORDERED_QUANTITY_%d", lineNumber);
	nca_edit_get_text(lineName, qty);
	
	if (strlen(qty) > 0) {
		strcat(qty, ".0");		// to match DB record
		assertEqual(qty, dbQuantity, "Quantity value is wrong");
		lr_end_transaction(transaction, LR_PASS);
		return;
	} else {
		lr_error_message("Quantity not found");
		lr_end_transaction(transaction, LR_FAIL);
		return;
	}
	
}

void checkStandId(int lineNumber, char* dbStandId) {
	char* transaction = "checkStandId";
	char lineName[50];
	char standId[10];
	
	lr_start_transaction(transaction);
	
	sprintf(lineName, "LINE_DF_%d", lineNumber);
	nca_edit_click(lineName);
	nca_set_window("Additional Line Attribute Information");
	nca_flex_get_cell_data("Additional Line Attribute Information", "Stand ID", "", standId);
	nca_win_close("Additional Line Attribute Information");

	if (strlen(standId) > 0) {
		assertEqual(standId, dbStandId, "Stand ID value is wrong");
		lr_end_transaction(transaction, LR_PASS);
		return;
	} else {
		lr_error_message("Stand ID not found");
		lr_end_transaction(transaction, LR_FAIL);
		return;
	}
}
#endif
