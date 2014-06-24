#include "storemanager.h"

int main() {
	StoreManager mgr();
	mgr.buildDatabases();
	mgr.executeTransactions();

}