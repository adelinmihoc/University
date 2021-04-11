#include "Tests.h"
#include "Controller.h"

#include <assert.h>


void Tests::testAll() {
	testDomain();
	testDynamicArray();
	testRepository();
	testIterator();
	testController();
	std::cout << "\nAll tests done!\n\n";
}


void Tests::testDomain() {
	std::cout << "Testing domain\n";
	GuardianStatue guardStat{ "piertotum locomotor", "stone", 328, "warrior with poleax" };
	assert(guardStat.getPowerWordName() == "piertotum locomotor");
	assert(guardStat.getMaterial() == "stone");
	assert(guardStat.getAge() == 328);
	assert(guardStat.getCorporealForm() == "warrior with poleax");
	GuardianStatue guardStat2{ "piertotum locomotor", "stone", 328, "warrior with poleax" };
}


void Tests::testDynamicArray() {
	std::cout << "Testing dynamic array\n";
	DynamicVector<GuardianStatue> dv;
	GuardianStatue g1 = GuardianStatue{ "aa", "stone", 328, "warrior with poleax" };
	GuardianStatue g2 = GuardianStatue{ "aa1", "stone", 328, "warrior with poleax" };
	GuardianStatue g3 = GuardianStatue{ "aa2", "stone", 328, "warrior with poleax" };
	GuardianStatue g4 = GuardianStatue{ "aa3", "stone", 328, "warrior with poleax" };
	GuardianStatue g5 = GuardianStatue{ "aa4", "stone", 328, "warrior with poleax" };
	GuardianStatue g6 = GuardianStatue{ "aa5", "stone", 328, "warrior with poleax" };
	GuardianStatue g7 = GuardianStatue{ "aa6", "stone", 328, "warrior with poleax" };
	GuardianStatue g8 = GuardianStatue{ "aa7", "stone", 328, "warrior with poleax" };
	GuardianStatue g9 = GuardianStatue{ "aa8", "stone", 328, "warrior with poleax" };
	GuardianStatue g10 = GuardianStatue{ "aa9", "stone", 328, "warrior with poleax" };
	GuardianStatue g11 = GuardianStatue{ "aa0", "stone", 328, "warrior with poleax" };
	dv.addItem(g1);
	dv.addItem(g2);
	dv.addItem(g3);
	dv.addItem(g4);
	dv.addItem(g5);
	dv.addItem(g6);
	dv.addItem(g7);
	dv.addItem(g8);
	dv.addItem(g9);
	dv.addItem(g10);
	dv.addItem(g11);
	assert(dv.getCapacity() == 20);
	dv.deleteItem(-10);
	dv.updateItem(-10, g1);
	dv.deleteItem(10);
}


void Tests::testRepository() {
	std::cout << "Testing repository\n";
	Encyclopedia encl = Encyclopedia();
	GuardianStatue g1 = GuardianStatue{ "piertotum locomotor", "stone", 328, "warrior with poleax" };
	encl.addStatue(g1);
	assert(encl.getSize() == 1);
	try {
		encl.addStatue(g1);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	encl.deleteStatue("piertotum locomotor");
	assert(encl.getSize() == 0);
	try {
		encl.updateStatue(g1);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	encl.addStatue(g1);
	assert(encl.getSize() == 1);
	encl.updateStatue(g1);
	DynamicVector<GuardianStatue> gs = encl.getAllStatues();
	assert(gs.getSize() == 1);
	try {
		encl.deleteStatue("asd");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
}


void Tests::testIterator() {
	std::cout << "Testing iterator\n";
	GuardianStatue g1 = GuardianStatue{ "aa", "stone", 328, "warrior with poleax" };
	GuardianStatue g2 = GuardianStatue{ "aa1", "stone", 328, "warrior with poleax" };
	GuardianStatue g3 = GuardianStatue{ "aa2", "stone", 328, "warrior with poleax" };
	ApprenticeIterator it;
	it.add(g1);
	it.add(g2);
	assert(it.getStatue().getPowerWordName() == g1.getPowerWordName());
	it.next();
	it.next();
	it.next();
	DynamicVector<GuardianStatue> dv = it.getAll();
	assert(dv.getSize() == 2);
}



void Tests::testController() {
	std::cout << "Testing controller\n";
	Encyclopedia encl = Encyclopedia();
 	Enchantment ench = Enchantment(encl);
	assert(ench.getSize() == 0);
	ench.addGuardianStatue("piertotum locomotor", "stone", 328, "warrior with poleax");
	assert(ench.getSize() == 1);
	ench.deleteGuardianStatue("piertotum locomotor");
	assert(ench.getSize() == 0);
	try {
		ench.deleteGuardianStatue("piertotum locomotor");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	ench.addGuardianStatue("piertotum locomotor", "stone", 328, "warrior with poleax");
	try {
		ench.addGuardianStatue("piertotum locomotor", "stone", 328, "warrior with poleax");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	ench.updateGuardianStatue("piertotum locomotor", "stone", 328, "warrior with poleax");
	try {
		ench.updateGuardianStatue("afdD", "stone", 328, "warrior with poleax");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	DynamicVector<GuardianStatue> dv = ench.getAllGuardianStatues();
	assert(dv.getSize() == 1);
	DynamicVector<GuardianStatue> dv2 = ench.getAllApprenticeGuardianStatues();
	assert(dv2.getSize() == 0);
	ench.initialiseIterator();
	GuardianStatue gs = ench.nextGuardianStatues();
	assert(gs.getPowerWordName() == "piertotum locomotor");
	ench.saveGuardianStatue("piertotum locomotor");
	try {
		ench.saveGuardianStatue("asd");
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	DynamicVector<GuardianStatue> dv3 = ench.getAllApprenticesStatuesByMaterial("metal");
	DynamicVector<GuardianStatue> dv4 = ench.getAllApprenticesStatuesByMaterial("stone");
	DynamicVector<GuardianStatue> dv5 = ench.getAllApprenticeStatuesByMaterialAndAge("stone", 1000);
	assert(dv5.getSize() == 1);
}